#include <Mesh3d_Optimization.hxx>

#include <Geometry_Sort.hxx>
#include <Geometry_Intersect.hxx>
#include <Mesh3d_Node.hxx>
#include <Mesh3d_Edge.hxx>
#include <Mesh3d_Facet.hxx>
#include <Mesh3d_BoundaryNode.hxx>
#include <Mesh3d_BoundaryFacet.hxx>
#include <Mesh3d_Element.hxx>
#include <Mesh3d_NodeTools.hxx>
#include <Mesh3d_OptTetInfo.hxx>
#include <Mesh3d_OptimizationTools.hxx>
#include <Mesh3d_OptimizationTetInfoTools.hxx>
#include <Mesh3d_QualityMap.hxx>
#include <Mesh3d_QualityMap3dTools.hxx>
#include <Mesh3d_Mesh.hxx>
#include <Mesh3d_TMesh.hxx>
#include <Mesh3d_Volume.hxx>
#include <Mesh3d_SizeMap.hxx>
#include <Mesh3d_EdgeRemovalEquatorialTriangles.hxx>
#include <Mesh3d_EdgeRemovalEquatorialTrianglesTools.hxx>
#include <TColMesh3d_HAry1dOfNode.hxx>

using namespace AutLib;
using namespace MeshLib;
using namespace GeoLib;

static const Standard_Real DEFAULT_LAPLACIAN_UNDERRELAXATION = 0.85;

AutLib::MeshLib::Mesh3d_Optimization::Mesh3d_Optimization
(
	const Mesh3d_QualityMap & theQualityMap,
	const Mesh3d_SizeMap& theSizeMap,
	Mesh3d_Volume & theMesh
)
	: theQualityMap_(theQualityMap)
	, theSizeMap_(theSizeMap)
	, theMesh_(theMesh)
	, theVerbose_(0)
{
}

void AutLib::MeshLib::Mesh3d_Optimization::SetVerbosity(const Standard_Integer theVerbose)
{
	theVerbose_ = theVerbose;
}

void AutLib::MeshLib::Mesh3d_Optimization::Perform()
{
	forThose
	(
		Index,
		0,
		theMesh_.NbMeshes() - 1
	)
	{
		Debug_Null_Pointer(theMesh_.Mesh(Index));
		Debug_Null_Pointer(Global_DownCast(Mesh3d_TMesh, theMesh_.Mesh(Index)));

		Global_Handle(Mesh3d_TMesh) Mesh = Global_DownCast(Mesh3d_TMesh, theMesh_.Mesh(Index));

		Perform(*Mesh);

		Perform(*Mesh);

		Perform(*Mesh);
	}
}

void AutLib::MeshLib::Mesh3d_Optimization::Perform(Mesh3d_TMesh & theMesh)
{
	Standard_Real Worst0 = CalcWorstQuality(theMesh);

	if (theVerbose_)
	{
		cout << "   Optimization is Applied to: " << theMesh.Name() << endl;
		cout << "    Worst Element Quality= " << Worst0 << endl;
	}

	Topological(theMesh);

	Smoothing(theMesh);

	Standard_Real Worst = CalcWorstQuality(theMesh);

	if (theVerbose_)
	{
		cout << "   Optimization has been Done!\n";
		cout << "    Worst Element Quality= " << Worst << endl;
	}
}

Standard_Real AutLib::MeshLib::Mesh3d_Optimization::CalcWorstQuality(const Mesh3d_TMesh & theMesh) const
{
	TColMesh3d_HAry1dOfElement Elements;
	theMesh.RetrieveTo(Elements);

	Standard_Real Worst = RealLast();
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Elements)
	)
	{
		Debug_Null_Pointer(Elements[Index]);

		Standard_Real Quality = CalcQuality(*Elements[Index]);
		if (Quality < Worst) Worst = Quality;
	}
	return Worst;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_Optimization::NonSmooth
(
	Global_Handle(Mesh3d_Node) theNode,
	TColMesh3d_HAry1dOfOptTetInfo & theElements,
	Standard_Real & theWorst
) const
{
	/* get vertex to be altered */
	Geom_Pnt3d v = theNode->Coord();
	Geom_Pnt3d origpoint = v;

	/* find the worst quality of all incident tets */
	Standard_Real worstqual = RealLast();

	forThose
	(
		Index,
		0,
		MaxIndexOf(theElements)
	)
	{
		Get_Const_Object(Element) = theElements[Index]->theElement_;

		Get_Const_Object(Node0) = *Element.Node(0);
		Get_Const_Object(Node1) = *Element.Node(1);
		Get_Const_Object(Node2) = *Element.Node(2);
		Get_Const_Object(Node3) = *Element.Node(3);

		Standard_Real Quality = theQualityMap_.CalcQuality
		(
			Node0.Coord(),
			Node1.Coord(),
			Node2.Coord(),
			Node3.Coord()
		);
		if (Quality < worstqual) worstqual = Quality;
	}

	if (worstqual <= 0) { THROW_STANDARD_EXCEPTION("all elements must have quality larger than zero"); }

	theWorst = worstqual;

	forThose
	(
		Index,
		0,
		MaxIndexOf(theElements)
	)
	{
		Debug_Null_Pointer(theElements[Index]);
		theQualityMap_.CalcOptInfo(theNode, *theElements[Index]);
	}

	TColGeom_Ary1dOfPnt3d activegrads;
	theQualityMap_.GetActiveSet(theElements, theSmoothingConfig_.ActiveSetFactor(), worstqual, activegrads);

	if (activegrads.IsEmpty()) return Standard_False;

	/* d <- point on the convex hull of all gradients nearest origin */
	Geom_Pnt3d d = Mesh3d_OptimizationTools::MinConvexHullPoint(activegrads);

	/* if d is the origin, we can't improve this vertex with smoothing. */
	Standard_Real dlength = d.TwoNorm();

	if (dlength < 10 * EPS6)
	{
		return Standard_False;
	}

	Standard_Integer numIter = 0;
	Standard_Real improvement = 0;


	/* otherwise, it's time to do some smoothing! */
	do
	{
		/* find r, the expected rate of improvement. r is computed as the minimum
		dot product between the improvment direction d and all of the active
		gradients, so it's like "how fast do we move in the direction of the
		gradient least favored by d." */

		/* start with an absurdly big r */
		Standard_Real r = RealLast();

		/* find the smallest dot product */
		forThose(i, 0, MaxIndexOf(activegrads))
		{
			Standard_Real newr = GeoLib::DotProduct(d, activegrads[i]);

			if (newr <= 0)
			{
				theNode->SetCoord(origpoint);
				return Standard_False;
			}

			if (newr < r)
			{
				r = newr;
			}
		}

		/* save the worst quality from the previous step */
		Standard_Real oldworstqual = worstqual;

		/* initialize alpha to the nearest intersection with another
		quality function */
		Standard_Real alpha = theQualityMap_.GetInitialAlpha(theElements, d, r, EPS6, worstqual);

		/* if we didn't find a limit for alpha above, at least limit it
		so that we don't invert any elements. */
		if (alpha == RealLast())
		{
			forThose(i, 0, MaxIndexOf(theElements))
			{
				/* if moving in the direction d will decrease
				this element's volume */
				Standard_Real rate = DotProduct(d, getPoint(theElements[i]->volumegrad));

				if (rate < 0.0)
				{
					Standard_Real newalpha = -theElements[i]->volume / (2.0*rate);

					/* if this is smaller than the current step size,
					use it */
					if (newalpha < alpha)
					{
						alpha = newalpha;
					}
				}
			}
		}

		/* do normal line search */
		NonSmoothLineSearch
		(
			theNode,
			theElements,
			d,
			worstqual,
			r,
			alpha
		);

		/* move vertex in direction d step size alpha */
		Geom_Pnt3d change = alpha*d;

		v += change;
		theNode->SetCoord(v);

		/* recompute quality information */
		oldworstqual = worstqual;
		worstqual = RealLast();

		forThose(i, 0, MaxIndexOf(theElements))
		{
			Get_Const_Object(Element) = theElements[i]->theElement_;

			Mesh3d_Node* node0 = Element.Node(0);
			Mesh3d_Node* node1 = Element.Node(1);
			Mesh3d_Node* node2 = Element.Node(2);
			Mesh3d_Node* node3 = Element.Node(3);

			Standard_Real thisqual = theQualityMap_.CalcQuality
			(
				node0->Coord(),
				node1->Coord(),
				node2->Coord(),
				node3->Coord()
			);

			/* is this the worst quality we've seen? */
			if (thisqual < worstqual) worstqual = thisqual;
		}

		/* how much did we improve this step? */
		improvement = worstqual - oldworstqual;

		if (improvement < 0)
		{
			theNode->SetCoord(origpoint);
			return Standard_False;
		}

		/* recompute the active set */
		forThose(i, 0, MaxIndexOf(theElements))
		{
			/* compute gradient info for this tet */
			theQualityMap_.CalcOptInfo(theNode, *theElements[i]);
		}		

		theQualityMap_.GetActiveSet(theElements, theSmoothingConfig_.ActiveSetFactor(), worstqual, activegrads);

		/* d <- point on the convex hull of all gradients nearest origin */
		d = Mesh3d_OptimizationTools::MinConvexHullPoint(activegrads);

		numIter++;

		dlength = d.TwoNorm();

	} while
		(
		(dlength > 10 * EPS6) &&
			(numIter < theSmoothingConfig_.MaxSmoothingIterations()) &&
			(improvement > theSmoothingConfig_.MinSmoothingImprovement())
			);

	theWorst = worstqual;

	return Standard_True;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_Optimization::SingleVertexSmoothing
(
	Global_Handle(Mesh3d_Node) theNode,
	Standard_Real & theWorst,
	Standard_Integer & optattempts,
	Standard_Integer & optsuccesses
) const
{
	if (Global_DownCast(Mesh3d_BoundaryNode, theNode)) { return Standard_False; }

	TColMesh3d_HAry1dOfElement Elements;
	theNode->RetrieveTo(Elements);

	TColMesh3d_HAry1dOfOptTetInfo incidenttets(Elements.Size());
	forThose(Index, 0, MaxIndexOf(incidenttets))
	{
		incidenttets[Index] = new Mesh3d_OptTetInfo(*Elements[Index]);

		Debug_Null_Pointer(incidenttets[Index]);
	}

	optattempts++;

	Standard_Boolean optsmoothed = NonSmooth(theNode, incidenttets, theWorst);

	FreeMemory(incidenttets);

	if (optsmoothed) optsuccesses++;
	if (optsmoothed) return Standard_True;
	return Standard_False;
}

Standard_Real AutLib::MeshLib::Mesh3d_Optimization::WorstQuality(Global_Handle(Mesh3d_Node) theNode) const
{
	TColMesh3d_HAry1dOfElement Elements;
	theNode->RetrieveTo(Elements);

	Standard_Real Worst = RealLast();
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Elements)
	)
	{
		Get_Const_Object(Element) = *Elements[Index];

		Mesh3d_Node* node0 = Element.Node(0);
		Mesh3d_Node* node1 = Element.Node(1);
		Mesh3d_Node* node2 = Element.Node(2);
		Mesh3d_Node* node3 = Element.Node(3);

		Standard_Real thisqual = theQualityMap_.CalcQuality
		(
			node0->Coord(),
			node1->Coord(),
			node2->Coord(),
			node3->Coord()
		);

		if (thisqual < Worst) Worst = thisqual;
	}
	return Worst;
}

Standard_Real AutLib::MeshLib::Mesh3d_Optimization::WorstQuality(Global_Handle(Mesh3d_Edge) theEdge) const
{
	TColMesh3d_HAry1dOfElement Elements;
	theEdge->RetrieveTo(Elements);

	Standard_Real Worst = RealLast();
	forThose
	(
		Index,
		0,
		MaxIndexOf(Elements)
	)
	{
		Get_Const_Object(Element) = *Elements[Index];

		Mesh3d_Node* node0 = Element.Node(0);
		Mesh3d_Node* node1 = Element.Node(1);
		Mesh3d_Node* node2 = Element.Node(2);
		Mesh3d_Node* node3 = Element.Node(3);

		Standard_Real thisqual = theQualityMap_.CalcQuality
		(
			node0->Coord(),
			node1->Coord(),
			node2->Coord(),
			node3->Coord()
		);

		if (thisqual < Worst) Worst = thisqual;
	}
	return Worst;
}

void AutLib::MeshLib::Mesh3d_Optimization::NonSmoothLineSearch
(
	Global_Handle(Mesh3d_Node) theNode,
	const TColMesh3d_HAry1dOfOptTetInfo & theElements,
	Geom_Pnt3d & d,
	const Standard_Real theWorst, 
	const Standard_Real r,
	Standard_Real & alpha
) const
{
	Standard_Real worstqual;      /* the current worst quality */
	Standard_Real origworstqual;  /* the original worst quality */
	Standard_Real oldworstqual;   /* the worst quality at the last step */
	Standard_Real thisqual;       /* the quality of the current tet */

						   /* save the original worst quality */
	origworstqual = oldworstqual = theWorst;

	/* fetch the original vertex coordinates from the mesh */
	Geom_Pnt3d v = theNode->Coord();
	Geom_Pnt3d origvertex = v;

	Standard_Integer numIter = 0;

	worstqual = RealLast();

	/* keep trying until alpha gets too small or we exceed maximum
	number of iterations */
	while ((alpha > theSmoothingConfig_.MinStepSize()) && (numIter < theSmoothingConfig_.MaxLineIterations()))
	{
		/* compute the offset from original vertex positon,
		alpha * d */
		Geom_Pnt3d offset = alpha*d;

		/* move the vertex */
		v += offset;

		theNode->SetCoord(v);

		/* recompute all of the quality functions affected
		by v's position, taking note of the smallest one */
		forThose(i, 0, MaxIndexOf(theElements))
		{
			Get_Const_Object(Element) = theElements[i]->theElement_;

			Mesh3d_Node* node0 = Element.Node(0);
			Mesh3d_Node* node1 = Element.Node(1);
			Mesh3d_Node* node2 = Element.Node(2);
			Mesh3d_Node* node3 = Element.Node(3);

			thisqual = theQualityMap_.CalcQuality
			(
				node0->Coord(),
				node1->Coord(),
				node2->Coord(),
				node3->Coord()
			);

			/* is this the worst quality we've seen? */
			if (thisqual < worstqual) worstqual = thisqual;
		}

		/* if this is not the first iteration, and
		we did better on the last iteration, use
		the step size from the previous iteration */
		if ((oldworstqual > origworstqual) && (oldworstqual > worstqual))
		{
			/* use the previous step's alpha */
			alpha = alpha * 2;

			/* put vertex back where it started */
			theNode->SetCoord(origvertex);

			return;
		}

		/* if we have succeeded in gaining 90% of the expected
		improvement, accept this initial step size */
		if ((worstqual - origworstqual) > (0.9 * (alpha)* r))
		{
			/* put vertex back where it started */
			theNode->SetCoord(origvertex);

			return;
		}

		/* cut alpha down by half and try again */
		alpha *= 0.5;

		/* save the worst quality from this step */
		oldworstqual = worstqual;
	}

	/* no positive alpha could be found that improved things... give up and return zero */
	alpha = 0.0;
}

void AutLib::MeshLib::Mesh3d_Optimization::Topological(Mesh3d_TMesh & theMesh)
{
	TColMesh3d_HAry1dOfFacet Facets;
	theMesh.RetrieveTo(Facets);

	Standard_Integer NbAttempts23 = 0;
	Standard_Integer NbSuccess23 = 0;

	forThose
	(
		Index,
		0, 
		MaxIndexOf(Facets)
	)
	{
		Debug_Null_Pointer(Facets[Index]);

		if (Global_DownCast(Mesh3d_BoundaryFacet, Facets[Index])) continue;

		if (Facets[Index]->IsOnFront()) continue;

		if (Facets[Index]->Node0()->IsOnFront()) continue;
		if (Facets[Index]->Node1()->IsOnFront()) continue;
		if (Facets[Index]->Node2()->IsOnFront()) continue;

		NbAttempts23++;

		if (Flip(Facets[Index], theMesh)) NbSuccess23++;
	}

	if (theVerbose_ > 1)
	{
		cout << "    Flip23 - Nb. of Attempts= " << NbAttempts23 << endl;
		cout << "    Flip23 - Nb. of success= " << NbSuccess23 << endl;
	}

	TColMesh3d_HAry1dOfEdge Edges;
	theMesh.RetrieveTo(Edges);

	Standard_Integer NbAttempts = 0;
	Standard_Integer NbSuccess = 0;

	forThose
	(
		Index,
		0, 
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		if (Global_DownCast(Mesh3d_BoundaryEdge, Edges[Index])) continue;

		if (Edges[Index]->IsOnFront()) continue;

		if (Edges[Index]->Node0()->IsOnFront()) continue;
		if (Edges[Index]->Node1()->IsOnFront()) continue;

		NbAttempts++;

		if (Flip(Edges[Index], theMesh)) NbSuccess++;
	}

	if (theVerbose_ > 1)
	{
		cout << "    Flip Edge - Nb. of Attempts= " << NbAttempts << endl;
		cout << "    Flip Edge - Nb. of success= " << NbSuccess << endl;
	}
}

void AutLib::MeshLib::Mesh3d_Optimization::Smoothing(Mesh3d_TMesh & theMesh)
{
	TColMesh3d_HAry1dOfNode Nodes;
	theMesh.RetrieveTo(Nodes);

	forThose(Iter, 1, theSmoothingConfig_.MaxSmoothingIterations())
	{
		if (theVerbose_)
		{
			cout << "    Smootthing Iteration Nb. " << Iter << endl;
		}

		NonSmoothing(Nodes);

		LaplacianSmoothing(Nodes, DEFAULT_LAPLACIAN_UNDERRELAXATION);
	}
}

void AutLib::MeshLib::Mesh3d_Optimization::LaplacianSmoothing(TColMesh3d_HAry1dOfNode & theNodes, const Standard_Real theUnderRelaxation)
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(theNodes)
	)
	{
		Debug_Null_Pointer(theNodes[Index]);

		if (Global_DownCast(Mesh3d_BoundaryNode, theNodes[Index])) continue;
		if (theNodes[Index]->IsOnFront()) continue;

		Standard_Real oldWorst = WorstQuality(theNodes[Index]);

		Get_Object(Node) = *theNodes[Index];

		Geom_Pnt3d SaveCoordinate = Node.Coord();
		TColMesh3d_HAry1dOfEdge Edges = Node.RetrieveEdges();

		Geom_Pnt3d AvgPt(0, 0, 0);
		forThose(J, 0, MaxIndexOf(Edges))
		{
			Get_Const_Object(n1) = *Edges[J]->Node0();
			Get_Const_Object(n2) = *Edges[J]->Node1();

			if (n1.Index() NOT_EQUAL Node.Index()) { AvgPt += n1.Coord() + theUnderRelaxation * (1.0 / theSizeMap_.CalcUnitDistance(n1.Coord(), Node.Coord()))*(Node.Coord() - n1.Coord()); }
			else { AvgPt += n2.Coord() + theUnderRelaxation * (1.0 / theSizeMap_.CalcUnitDistance(n2.Coord(), Node.Coord()))*(Node.Coord() - n2.Coord()); }
		}

		Node.SetCoord(AvgPt / (Standard_Real)Edges.Size());

		Standard_Real Worst = WorstQuality(theNodes[Index]);

		if (Worst <= oldWorst)
		{
			Node.SetCoord(SaveCoordinate);
			continue;
		}
	}
}

void AutLib::MeshLib::Mesh3d_Optimization::NonSmoothing(TColMesh3d_HAry1dOfNode & theNodes)
{
	Standard_Integer attempt = 0;
	Standard_Integer success = 0;

	Standard_Real worst = RealLast();

	forThose
	(
		Index,
		0, 
		MaxIndexOf(theNodes)
	)
	{
		Debug_Null_Pointer(theNodes[Index]);

		if (Global_DownCast(Mesh3d_BoundaryNode, theNodes[Index])) continue;
		if (theNodes[Index]->IsOnFront()) continue;

		Standard_Real WorstQual = 0;
		Standard_Boolean Smoothed = SingleVertexSmoothing(theNodes[Index], WorstQual, attempt, success);

		if (Smoothed)
		{
			if (WorstQual < worst) worst = WorstQual;
		}
	}
}

void AutLib::MeshLib::Mesh3d_Optimization::Sort(TColMesh3d_HAry1dOfNode & theNodes) const
{
	TColStd_Ary1dOfReal Q(theNodes.Size());
	TColStd_Ary1dOfInteger I(theNodes.Size());

	TColMesh3d_HAry1dOfNode Nodes = theNodes;

	forThose(Index, 0, MaxIndexOf(I)) I[Index] = Index;

	forThose(Index, 0, MaxIndexOf(Q)) Q[Index] = WorstQuality(theNodes[Index]);

	Geometry_Sort<Standard_Real>::Sort(Q, I);

	forThose(Index, 0, MaxIndexOf(theNodes))
		theNodes[Index] = Nodes[I[Index]];
}

void AutLib::MeshLib::Mesh3d_Optimization::ImportFacetsToMesh
(
	const Mesh3d_EdgeRemovalEquatorialTriangles & theEquatorialTriangles,
	TColMesh3d_HAry1dOfFacet & theFacets,
	Mesh3d_TMesh & theMesh
)
{
	Get_Const_Object(Nodes) = theEquatorialTriangles.Nodes();
	Get_Const_Object(Triangles) = theEquatorialTriangles.Triangles();

	theFacets.Resize(Triangles.Size());

	forThose
	(
		Index,
		0,
		MaxIndexOf(Triangles)
	)
	{
		Get_Const_Object(Triangle) = Triangles[Index];

		Standard_Integer V0 = Triangle.V0();
		Standard_Integer V1 = Triangle.V1();
		Standard_Integer V2 = Triangle.V2();

		Get_Const_Object(Node0) = *Nodes[Index_Of(V0)];
		Get_Const_Object(Node1) = *Nodes[Index_Of(V1)];
		Get_Const_Object(Node2) = *Nodes[Index_Of(V2)];

		Global_Handle(Mesh3d_Edge) Edge2 = Mesh3d_NodeTools::HasAFrontEdgeBetween(Node0, Node1);

		if (NOT Edge2)
		{
			theMesh.NbEdges()++;

			Standard_Real Length = theSizeMap_.CalcDistance(Node0.Coord(), Node1.Coord());

			Edge2 = new Mesh3d_Edge(theMesh.NbEdges(), Length, (Global_Handle(Mesh3d_Node))&Node0, (Global_Handle(Mesh3d_Node))&Node1);

			Debug_Null_Pointer(Edge2);

			theMesh.UpdateMaxLength(Length, *Edge2);

			theMesh.AttachToMeshNodes(Edge2);
			theMesh.AttachToFrontNodes(Edge2);

			theMesh.InsertToMesh(Edge2);
		}

		Global_Handle(Mesh3d_Edge) Edge0 = Mesh3d_NodeTools::HasAFrontEdgeBetween(Node1, Node2);

		if (NOT Edge0)
		{
			theMesh.NbEdges()++;

			Standard_Real Length = theSizeMap_.CalcDistance(Node1.Coord(), Node2.Coord());

			Edge0 = new Mesh3d_Edge(theMesh.NbEdges(), Length, (Global_Handle(Mesh3d_Node))&Node1, (Global_Handle(Mesh3d_Node))&Node2);

			Debug_Null_Pointer(Edge0);

			theMesh.UpdateMaxLength(Length, *Edge0);

			theMesh.AttachToMeshNodes(Edge0);
			theMesh.AttachToFrontNodes(Edge0);

			theMesh.InsertToMesh(Edge0);
		}

		Global_Handle(Mesh3d_Edge) Edge1 = Mesh3d_NodeTools::HasAFrontEdgeBetween(Node2, Node0);

		if (NOT Edge1)
		{
			theMesh.NbEdges()++;

			Standard_Real Length = theSizeMap_.CalcDistance(Node2.Coord(), Node0.Coord());

			Edge1 = new Mesh3d_Edge(theMesh.NbEdges(), Length, (Global_Handle(Mesh3d_Node))&Node2, (Global_Handle(Mesh3d_Node))&Node0);

			Debug_Null_Pointer(Edge1);

			theMesh.UpdateMaxLength(Length, *Edge1);

			theMesh.AttachToMeshNodes(Edge1);
			theMesh.AttachToFrontNodes(Edge1);

			theMesh.InsertToMesh(Edge1);
		}

		Global_Handle(Mesh3d_Facet) newFacet = new Mesh3d_Facet
		(
			++theMesh.NbFacets(),
			(Global_Handle(Mesh3d_Node))&Node0,
			(Global_Handle(Mesh3d_Node))&Node1,
			(Global_Handle(Mesh3d_Node))&Node2,
			Edge0,
			Edge1,
			Edge2
		);

		Try_Exception_Handle_Exit(theMesh.AttachToMesh(newFacet));
		Try_Exception_Handle_Exit(theMesh.InsertToMesh(newFacet));

		theMesh.CalcGeometryOf(*newFacet, theSizeMap_);

		theFacets[Index] = newFacet;
	}
}

Standard_Boolean AutLib::MeshLib::Mesh3d_Optimization::Flip(Global_Handle(Mesh3d_Edge) theEdge, Mesh3d_TMesh& theMesh)
{
	Debug_Null_Pointer(theEdge);

	Global_Handle(Mesh3d_EdgeRemovalEquatorialTriangles) EquatorialTriangles = Mesh3d_EdgeRemovalEquatorialTrianglesTools::CreateEquatorialTriangle(*theEdge, theQualityMap_);

	if (NOT EquatorialTriangles) return Standard_False;

	Standard_Real oldWorst = WorstQuality(theEdge);

	if (EquatorialTriangles->WorstQuality() <= oldWorst) return Standard_False;

	Global_Handle(Mesh3d_Node) Node0 = theEdge->Node0();
	Global_Handle(Mesh3d_Node) Node1 = theEdge->Node1();

	theMesh.ForcedToRemoveFromTopology(theEdge);

	TColMesh3d_HAry1dOfFacet Facets;
	ImportFacetsToMesh(*EquatorialTriangles, Facets, theMesh);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Facets)
	)
	{
		Debug_Null_Pointer(Facets[Index]);

		//Try_Exception_Handle_Exit(theMesh.AttachToFront(Facets[Index]));
		//Try_Exception_Handle_Exit(theMesh.InsertToFronts(Facets[Index]));

		theMesh.AddToTopology(Facets[Index], Node1, theSizeMap_, Standard_False);

		Facets[Index]->Reverse();

		//Try_Exception_Handle_Exit(theMesh.AttachToFront(Facets[Index]));
		//Try_Exception_Handle_Exit(theMesh.InsertToFronts(Facets[Index]));

		theMesh.AddToTopology(Facets[Index], Node0, theSizeMap_, Standard_False);
	}
	return Standard_True;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_Optimization::Flip
(
	Global_Handle(Mesh3d_Facet) theFacet,
	Mesh3d_TMesh & theMesh
)
{
	Get_Const_Pointer(Left) = theFacet->LeftElement();
	Get_Const_Pointer(Right) = theFacet->RightElement();

	Debug_Null_Pointer(Left);
	Debug_Null_Pointer(Right);

	Global_Handle(Mesh3d_Node) Vrtx1 = Left->OppositeVertex(theFacet);
	Global_Handle(Mesh3d_Node) Vrtx2 = Right->OppositeVertex(theFacet);

	Standard_Boolean Intersect = Geometry_Intersect::IsIntersectLineSegmentTriangle
	(
		Vrtx1->Coord(),
		Vrtx2->Coord(),
		theFacet->Node0()->Coord(),
		theFacet->Node1()->Coord(),
		theFacet->Node2()->Coord()
	);

	if (NOT Intersect) return Standard_False;

	Standard_Real Qleft = theQualityMap_.CalcQuality(Left->Node(0)->Coord(), Left->Node(1)->Coord(), Left->Node(2)->Coord(), Left->Node(3)->Coord());
	Standard_Real QRight = theQualityMap_.CalcQuality(Right->Node(0)->Coord(), Right->Node(1)->Coord(), Right->Node(2)->Coord(), Right->Node(3)->Coord());

	Standard_Real oldWorst = MIN(Qleft, QRight);

	const Geom_Pnt3d& P1 = theFacet->Node0()->Coord();
	const Geom_Pnt3d& P2 = theFacet->Node1()->Coord();
	const Geom_Pnt3d& P3 = theFacet->Node2()->Coord();

	const Geom_Pnt3d& V1 = Vrtx1->Coord();
	const Geom_Pnt3d& V2 = Vrtx2->Coord();

	Standard_Real Q1 = theQualityMap_.CalcQuality(P1, P2, V2, V1);
	Standard_Real Q2 = theQualityMap_.CalcQuality(P2, P3, V2, V1);
	Standard_Real Q3 = theQualityMap_.CalcQuality(P3, P1, V2, V1);

	Standard_Real Worst = MIN(Q3, MIN(Q2, Q1));

	if (Worst <= oldWorst) return Standard_False;

	theMesh.RemoveFromTopology(theFacet->LeftElement(), Standard_True);
	theMesh.RemoveFromTopology(theFacet->RightElement(), Standard_True);

	TColMesh3d_HAry1dOfFacet Facets;
	Vrtx1->RetrieveFrontsTo(Facets);

	if (Facets.Size() NOT_EQUAL 3) { THROW_STANDARD_EXCEPTION("Invalid Data"); }

	forThose
	(
		Index, 
		0, 
		MaxIndexOf(Facets)
	)
	{
		Debug_Null_Pointer(Facets[Index]);

		theMesh.AddToTopology(Facets[Index], Vrtx2, theSizeMap_, Standard_True);
	}
	return Standard_True;
}
