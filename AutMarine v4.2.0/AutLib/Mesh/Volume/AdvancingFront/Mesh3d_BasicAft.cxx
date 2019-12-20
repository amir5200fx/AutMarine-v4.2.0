#include <Mesh3d_BasicAft.hxx>

#include <Time.hxx>
#include <GeoMesh_StaticTriangleMesh3d.hxx>
#include <Entity_Triangulation3d.hxx>
#include <Geometry_Tools.hxx>
#include <Geometry_Intersect.hxx>
#include <Mesh3d_FacetTools.hxx>
#include <Mesh3d_SolidMesher.hxx>
#include <Mesh3d_BoundaryNode.hxx>
#include <Mesh3d_BoundaryEdge.hxx>
#include <Mesh3d_BoundaryFacet.hxx>
#include <TColMesh3d_HBasicQueueOfEdge.hxx>
#include <TColMesh3d_HBasicQueueOfFacet.hxx>
#include <TColCad3d_HAry1dOfSolid.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace MeshLib;
using namespace CadLib;

static const Standard_Real DEFAULT_PAINTING_FACTOR = 1.05;
static const Standard_Real DEAFULT_MAX_GRADATION = 0.8;
static const Standard_Integer DEFAULT_MAX_NB_LEVELS = 1500;

#define GET_DOMAIN_NAME theDomainName_

#define Get_Current_Mesh(MESH) Get_Object(MESH) = *Mesh3d_Volume::CurrentMesh()
#define Get_Current_Const_Mesh(MESH) Get_Const_Object(MESH) = *Mesh3d_Volume::CurrentMesh()

AutLib::MeshLib::Mesh3d_BasicAft::Mesh3d_BasicAft
(
	const Mesh3d_SizeMap & theSizeMap,
	Global_Handle(TColMesh3d_GeomSearchOfNode) theSearchEngine
)
	: Mesh3d_Volume()
	, theMap_(theSizeMap)
	, theSearch_(*theSearchEngine)
	, theVerbosity_(0)
	, theDomainName_(" Unknown")
	, theALLOWED_MAX_LEVEL_(DEFAULT_MAX_NB_LEVELS)
	, UseExactMetric_(Standard_False)
	, theMaxGradation_(DEAFULT_MAX_GRADATION)
	, SurfaceMeshOnly_(Standard_False)
{
}

AutLib::MeshLib::Mesh3d_BasicAft::~Mesh3d_BasicAft()
{
}

Standard_Integer AutLib::MeshLib::Mesh3d_BasicAft::NbRegions() const
{
	return theShapes_.Size();
}

Standard_Boolean AutLib::MeshLib::Mesh3d_BasicAft::IsDone() const
{
	return IsDone_;
}

void AutLib::MeshLib::Mesh3d_BasicAft::SetToUseExactMetricForSurfaceMesh()
{
	UseExactMetric_ = Standard_True;
}

void AutLib::MeshLib::Mesh3d_BasicAft::SetVerbosity(const Standard_Integer Verbose)
{
	theVerbosity_ = MAX(Verbose, 0);
}

void AutLib::MeshLib::Mesh3d_BasicAft::SetDomainName(const Standard_String theName)
{
	theDomainName_ = theName;
}

void AutLib::MeshLib::Mesh3d_BasicAft::SetToSurfaceMeshOnly()
{
	SurfaceMeshOnly_ = Standard_True;
}

void AutLib::MeshLib::Mesh3d_BasicAft::Import(const M_CAD Cad3d_Solid & theSolid)
{
	theShapes_.EnQueue((Global_Handle(M_CAD Cad3d_Solid))&theSolid);
}

void AutLib::MeshLib::Mesh3d_BasicAft::Perform()
{
	Standard_Integer nbRegions = NbRegions();
	Standard_Integer Region;

	IsDone_ = Standard_True;

	if (NOT nbRegions)
	{
		THROW_STANDARD_EXCEPTION(" There is no Region to be Meshed");
	}

	Mesh3d_Volume::AllocateMemory(nbRegions);

	TColCad3d_HAry1dOfSolid Shapes;
	theShapes_.RetrieveTo(Shapes);

	forThose
	(
		Index,
		0,
		nbRegions - 1
	)
	{
		Region = Index;

		theDomains_[Index] = new Mesh3d_SolidMesher(theMap_, *Shapes[Region]);
		Get_Object(Domain) = *Mesh3d_Volume::Domain(Region);
		
		if (theVerbosity_) Domain.SetVerbosity(theVerbosity_ - 1);
		if (UseExactMetric_) Domain.UseExactMetric();

		Try_Exception_Handle_Exit(Domain.Perform());
		
		if (NOT Domain.IsDone())
		{
			THROW_STANDARD_EXCEPTION(" Boundary Region Is NOT discretized");
		}
		
		if (SurfaceMeshOnly_) continue;

		Mesh3d_Volume::SetCurrent(Region);
		
		Import(Domain.Merged());
		
		theFront_.SetLevelNumber(0);
		theFront_.SetLevelMaxIndex(NbNodes());

		MeshGeneration();
	}
}

void AutLib::MeshLib::Mesh3d_BasicAft::Perform(const M_GEO Entity_Triangulation3d & theTriangulation)
{
	Standard_Integer nbRegions = 1;

	IsDone_ = Standard_True;

	if (NOT nbRegions)
	{
		THROW_STANDARD_EXCEPTION(" There is no Region to be Meshed");
	}

	Mesh3d_Volume::AllocateMemory(nbRegions);

	Import(theTriangulation);

	theFront_.SetLevelNumber(0);
	theFront_.SetLevelMaxIndex(NbNodes());

	MeshGeneration();
}

Standard_Integer AutLib::MeshLib::Mesh3d_BasicAft::MeshGeneration()
{
	if (theFront_.IsFrontEmpty())
	{
		THROW_BAD_BOUNDARY_EXCEPTION(" Front is empty");
	}

	Get_Current_Const_Mesh(Mesh);

	const Standard_Real FirstTime = (Standard_Real)getCPUTime();

	while (NOT theFront_.IsFrontEmpty())
	{
		Try_Exception_Handle_Exit(MeshingOneLevel());

		if (IsSameLevelSupply())
		{
			theInfo_.SetType(Mesh3d_Aft_Generation);

			continue;
		}

		if (IsCavityRemoverSupply())
		{
			theInfo_.SetType(Mesh3d_Aft_Rapair);

			continue;
		}

		theFront_.SetLevelNumber(theFront_.LevelNumber() + 1);

		if (theFront_.LevelNumber() >= theALLOWED_MAX_LEVEL_)
			return 0;

		if (IsNextLevelSupply())
		{
			theInfo_.SetType(Mesh3d_Aft_Generation);
		}
	}

	const Standard_Real LastTime = (Standard_Real)getCPUTime();

	if (theVerbosity_)
	{
		cout << "    - " << " The Volume has been discretized successfully!\n";
		cout << "    - " << Mesh.NbElements() << " Tetrahedrons has been generated in " << (LastTime - FirstTime) << " sec" << endl;
	}

	if (theVerbosity_)
	{
		cout << "\n\n";
		cout << "  Meshing Process has been done!\n\n";

		cout << "  CPU time used = " << (LastTime - FirstTime) << " sec\n";
		cout << "  SPEED = " << Mesh.NbElements() / (LastTime - FirstTime) * 60.0 << " ELMs/ min\n";
		cout << "  SPEED = " << Mesh.NbElements() / (LastTime - FirstTime) << " ELMs/ sec\n\n";
	}

	return 1;
}

void AutLib::MeshLib::Mesh3d_BasicAft::MeshingOneLevel()
{
	TColMesh3d_HAry1dOfNode
		NodesInRadius1,
		NodesInRadius2,
		EarlyNodes;

	TColMesh3d_HAry1dOfFacet
		EffectiveFacets,
		Local;

	TColMesh3d_HAry1dOfEdge EffectiveEdges;
	TColStd_Array1OfReal Quality;

	ModifyLocalFront(DEFAULT_PAINTING_FACTOR);

	while (GetFront())
	{  // shortest segment on the GF		
		if (NOT IsBelongToFront())
			continue;
		//if (NbElements() > 30000) continue;
		// Remove the Current from front
		RemoveCurrentFromFront();

		// get desired element size from back-ground mesh
		CalcElementSize();

		// Calculate optimum corrdinate of new point
		CalcOptimumPoint();

		CalcSearchRadius();

		// Geometric search of the front
		RetrieveEarlyNodes(EarlyNodes);

		RetrieveLocalFacets(EarlyNodes, Local);

		// Set depth of searching radius
		SetDepthSearching();

		RetrieveNodesInRadius(EarlyNodes, NodesInRadius1, NodesInRadius2);

		RetrieveEffectiveFronts(NodesInRadius2, Local, EffectiveFacets);

		Mesh3d_FacetTools::RetrieveEdges(EffectiveFacets, EffectiveEdges);

		if (IsValidNewPoint(EffectiveFacets))
		{
			AppendOptimumPoint(NodesInRadius1);
		}

		// sort the candidate elements according to quality
		// note that the new point is excluded from sorting
		SortNodes(NodesInRadius1);

		FindValidNode(NodesInRadius1, NodesInRadius2, EffectiveEdges, EffectiveFacets);

		Update();
	}
}

void AutLib::MeshLib::Mesh3d_BasicAft::Import(const M_GEO Entity_Triangulation3d & theFront)
{
	Debug_Null_Pointer(CurrentMesh());

	Get_Current_Mesh(Mesh);

	GeoMesh_StaticTriangleMesh3d GeoMesh(theFront);

	Mesh.NbNodes() = GeoMesh.NbPoints();
	Mesh.NbEdges() = GeoMesh.NbEdges();
	Mesh.NbFacets() = GeoMesh.NbTriangles();
	Mesh.NbElements() = 0;

	Try_Exception_Handle_Exit(Mesh3d_BasicAft::CreateBoundary(GeoMesh));

	//ActiveFront();

	Get_Const_Object(Nodes) = Mesh3d_FacetTools::RetrieveNodesFrom(theBoundary_);
	Get_Const_Object(Edges) = Mesh3d_FacetTools::RetrieveEdgesFrom(theBoundary_);

	/*Compute MIN and Max coords for X and Y
	Compute MAX overall dimension*/

	// Set Searching Region
	theSearch_.SetRegion(theFront.BoundingBox().OffsetBox(EPS6));

	// insert nodes into the ADtree
	theSearch_.Insert(Nodes);

	// Insert To Front
	Try_Exception_Handle_Exit(Mesh.InsertToFronts(Nodes));
	Try_Exception_Handle_Exit(Mesh.InsertToFronts(theBoundary_));

	theFront_.InsertToFronts(theBoundary_);

	// Insert To Mesh
	Try_Exception_Handle_Exit(Mesh.InsertToMesh(Nodes));
	Try_Exception_Handle_Exit(Mesh.InsertToMesh(Edges));
	Try_Exception_Handle_Exit(Mesh.InsertToMesh(theBoundary_));

	theDimension_ = theSearch_.BoundingBox().Diameter();

	if (theVerbosity_)
	{
		cout << "   The boundary is imported successfully!\n";
	}
}

void AutLib::MeshLib::Mesh3d_BasicAft::CreateBoundary(const M_GEO GeoMesh_StaticTriangleMesh3d & theFront)
{
	Get_Current_Mesh(Mesh);

	TColMesh3d_HAry1dOfNode Nodes(theFront.NbPoints());

	Get_Const_Object(Coords) = theFront.Points();
	Get_Const_Object(StaticEdges) = theFront.Edges();
	Get_Const_Object(Triangles) = theFront.Triangles();

	forThose
	(
		Index,
		0,
		MaxIndexOf(Nodes)
	)
	{
		Nodes[Index] = new Mesh3d_BoundaryNode(Index + 1, Coords[Index]);

		Debug_Null_Pointer(Nodes[Index]);
	}

	TColMesh3d_HAry1dOfEdge Edges(StaticEdges.Size());
	forThose
	(
		Index, 
		0, 
		MaxIndexOf(Edges)
	)
	{
		Standard_Integer V0 = StaticEdges[Index].V0();
		Standard_Integer V1 = StaticEdges[Index].V1();

		Global_Handle(Mesh3d_Node) Node0 = Nodes[Index_Of(V0)];
		Global_Handle(Mesh3d_Node) Node1 = Nodes[Index_Of(V1)];

		Debug_Null_Pointer(Node0);
		Debug_Null_Pointer(Node1);

		Edges[Index] = new Mesh3d_BoundaryEdge
		(
			Index + 1,
			theMap_.CalcDistance(Node0->Coord(), Node1->Coord()),
			Node0,
			Node1
		);

		Mesh.AttachToMeshNodes(Edges[Index]);
		Mesh.AttachToFrontNodes(Edges[Index]);
	}

	theBoundary_.Resize(theFront.NbTriangles());

	forThose
	(
		Index,
		0, 
		MaxIndexOf(theBoundary_)
	)
	{
		Get_Object(Node0) = *Nodes[Index_Of(Triangles[Index].V0())];
		Get_Object(Node1) = *Nodes[Index_Of(Triangles[Index].V1())];
		Get_Object(Node2) = *Nodes[Index_Of(Triangles[Index].V2())];

		Get_Const_Object(EdgesInTriangle) = theFront.EdgesInTriangle(Index);

		Get_Object(Edge0) = *Edges[Index_Of(EdgesInTriangle.V0())];
		Get_Object(Edge1) = *Edges[Index_Of(EdgesInTriangle.V1())];
		Get_Object(Edge2) = *Edges[Index_Of(EdgesInTriangle.V2())];

		theBoundary_[Index] = new Mesh3d_BoundaryFacet
		(
			Index + 1,
			&Node0, 
			&Node1, 
			&Node2, 
			&Edge0, 
			&Edge1, 
			&Edge2
		);

		Debug_Null_Pointer(theBoundary_[Index]);

		Mesh.AttachToMesh(theBoundary_[Index]);
		Mesh.AttachToFront(theBoundary_[Index]);

		Mesh3d_BasicAft::CalcGeometryOf(*theBoundary_[Index]);
	}

	// Checking for Valid boundary
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		if (Edges[Index]->NbFrontFacets() NOT_EQUAL 2) { THROW_BAD_BOUNDARY_EXCEPTION(" Invalid Boundary: The Boundary is open or have non-maifold edges"); }
		if (Edges[Index]->NbFacets() NOT_EQUAL 2) { THROW_BAD_BOUNDARY_EXCEPTION(" Invalid Boundary: The Boundary is open or have non-maifold edges"); }
	}
}

void AutLib::MeshLib::Mesh3d_BasicAft::ModifyLocalFront(const Standard_Real Factor)
{
	if (Factor < ONE)
	{
		THROW_STANDARD_EXCEPTION(" Invalid Factor");
	}

	if (theSearch_.IsEmpty())
		return;

	Get_Current_Mesh(Mesh);

	TColMesh3d_HAry1dOfNode Nodes;
	Mesh.RetrieveFrontsTo(Nodes);
	
	forThose
	(
		Index,
		0,
		MaxIndexOf(Nodes)
	)
	{
		Debug_Null_Pointer(Nodes[Index]);

		Get_Object(Node) = *Nodes[Index];

		TColMesh3d_HAry1dOfEdge Edges;
		Node.RetrieveFrontsTo(Edges);

		Standard_Real MaxLength = 0.;
		forThose
		(
			J, 
			0,
			MaxIndexOf(Edges)
		)
		{
			Debug_Null_Pointer(Edges[J]);

			if (Edges[J]->Length() > MaxLength)
				MaxLength = Edges[J]->Length();
		}

		MaxLength *= Factor;

		Debug_If_Condition_Message(MaxLength EQUAL 0, " Invalid MaxLength Value");

		Node.SetRadius(MAX(Node.Radius(), MaxLength));

		TColMesh3d_HAry1dOfNode theFronts;
		theSearch_.Search(theMap_.CalcSearchingRegion(MaxLength, Node.Coord()), theFronts);

		TColMesh3d_HAry1dOfNode theInners;
		Mesh3d_BasicAft::NodesInRadius(MaxLength, Node.Coord(), theFronts, theInners);

		forThose
		(
			J,
			0,
			MaxIndexOf(theInners)
		)
		{
			theInners[J]->SetRadius(MAX(theInners[J]->Radius(), MaxLength));
		}
	}
}

void AutLib::MeshLib::Mesh3d_BasicAft::FindValidNode
(
	const TColMesh3d_HAry1dOfNode & theNodesInRadius, 
	const TColMesh3d_HAry1dOfNode & theEarly,
	const TColMesh3d_HAry1dOfEdge & theEffectiveEdges, 
	const TColMesh3d_HAry1dOfFacet & theEffectiveFacet
)
{
	Get_Const_Object(theCurrent) = Mesh3d_BasicAft::CurrentFacet();

	Debug_Null_Pointer(theCurrent.Node0());
	Debug_Null_Pointer(theCurrent.Node1());
	Debug_Null_Pointer(theCurrent.Node2());

	Get_Object(theP0) = theCurrent.Node0()->Coord();
	Get_Object(theP1) = theCurrent.Node1()->Coord();
	Get_Object(theP2) = theCurrent.Node2()->Coord();

	Standard_Integer V0 = theCurrent.Node0()->Index();
	Standard_Integer V1 = theCurrent.Node1()->Index();
	Standard_Integer V2 = theCurrent.Node2()->Index();

	Standard_Real theCriteria = (theInfo_.MinDistanceFactor()*theCurrent.Length())*(theInfo_.MinDistanceFactor()*theCurrent.Length());

	Standard_Integer Flag = 0;
	forThose
	(
		Index,
		0, 
		MaxIndexOf(theNodesInRadius)
	)
	{
		Debug_Null_Pointer(theNodesInRadius[Index]);
		Get_Const_Object(theNode) = *theNodesInRadius[Index];
		Get_Const_Object(theCoord) = theNode.Coord();

		Standard_Integer IP = theNode.Index();

		Continue_If(&theNode EQUAL theCurrent.Node0() OR &theNode EQUAL theCurrent.Node1() OR &theNode EQUAL theCurrent.Node2());

		// test 1: is it the new point on the left side of iFace
		Continue_If(NOT Geometry_Tools::IsPointLeftTriangle(theNode.Coord(), theP0, theP1, theP2));

		Flag = 0;
		// test 2: intersection test
		forThose
		(
			J,
			0,
			MaxIndexOf(theEffectiveEdges)
		)
		{
			Debug_Null_Pointer(theEffectiveEdges[J]);

			Debug_Null_Pointer(theEffectiveEdges[J]->Node0());
			Debug_Null_Pointer(theEffectiveEdges[J]->Node1());

			Get_Const_Object(Node0) = *theEffectiveEdges[J]->Node0();
			Get_Const_Object(Node1) = *theEffectiveEdges[J]->Node1();

			if (NOT Geometry_Tools::IsOneCommonPointLineSegmentTriangle(Node0.Index(), Node1.Index(), V0, V1, IP))
			{
				if (Geometry_Intersect::IsIntersectLineSegmentTriangle(Node0.Coord(), Node1.Coord(), theP0, theP1, theCoord))
				{
					Flag = 1;
					break;
				}
			}

			if (NOT Geometry_Tools::IsOneCommonPointLineSegmentTriangle(Node0.Index(), Node1.Index(), V1, V2, IP))
			{
				if (Geometry_Intersect::IsIntersectLineSegmentTriangle(Node0.Coord(), Node1.Coord(), theP1, theP2, theCoord))
				{
					Flag = 1;
					break;
				}
			}

			if (NOT Geometry_Tools::IsOneCommonPointLineSegmentTriangle(Node0.Index(), Node1.Index(), V2, V0, IP))
			{
				if (Geometry_Intersect::IsIntersectLineSegmentTriangle(Node0.Coord(), Node1.Coord(), theP2, theP0, theCoord))
				{
					Flag = 1;
					break;
				}
			}
		}

		Continue_If(Flag);

		forThose
		(
			J,
			0, 
			MaxIndexOf(theEffectiveFacet)
		)
		{
			Debug_Null_Pointer(theEffectiveFacet[J]);

			Debug_Null_Pointer(theEffectiveFacet[J]->Node0());
			Debug_Null_Pointer(theEffectiveFacet[J]->Node1());
			Debug_Null_Pointer(theEffectiveFacet[J]->Node2());

			Get_Const_Object(Node0) = *theEffectiveFacet[J]->Node0();
			Get_Const_Object(Node1) = *theEffectiveFacet[J]->Node1();
			Get_Const_Object(Node2) = *theEffectiveFacet[J]->Node2();

			Get_Const_Object(p0) = Node0.Coord();
			Get_Const_Object(p1) = Node1.Coord();
			Get_Const_Object(p2) = Node2.Coord();

			Standard_Integer v0 = Node0.Index();
			Standard_Integer v1 = Node1.Index();
			Standard_Integer v2 = Node2.Index();

			if (NOT Geometry_Tools::IsOneCommonPointLineSegmentTriangle(V0, IP, v0, v1, v2))
			{
				if (Geometry_Intersect::IsIntersectLineSegmentTriangle(theP0, theCoord, p0, p1, p2))
				{
					Flag = 1;
					break;
				}
			}

			if (NOT Geometry_Tools::IsOneCommonPointLineSegmentTriangle(V1, IP, v0, v1, v2))
			{
				if (Geometry_Intersect::IsIntersectLineSegmentTriangle(theP1, theCoord, p0, p1, p2))
				{
					Flag = 1;
					break;
				}
			}

			if (NOT Geometry_Tools::IsOneCommonPointLineSegmentTriangle(V2, IP, v0, v1, v2))
			{
				if (Geometry_Intersect::IsIntersectLineSegmentTriangle(theP2, theCoord, p0, p1, p2))
				{
					Flag = 1;
					break;
				}
			}
		}

		Continue_If(Flag);

		// test 3: Distance Edges from edges
		forThose
		(
			J,
			0,
			MaxIndexOf(theEarly)
		)
		{
			Debug_Null_Pointer(theEarly[J]);

			Get_Const_Object(JNode) = *theEarly[J];

			Continue_If(&JNode EQUAL theCurrent.Node0() OR &JNode EQUAL theCurrent.Node1() OR &JNode EQUAL theCurrent.Node2() OR JNode.Index() EQUAL IP);

			if (Geometry_Tools::IsPointInsideOnTetrahedron(JNode.Coord(), theP0, theP1, theP2, theCoord))
			{
				Flag = 1;
				break;
			}

			if (theMap_.CalcDistanceFromTriangleSQ(JNode.Coord(), theP0, theCoord, theP2) < theCriteria)
			{
				Flag = 1;
				break;
			}

			if (theMap_.CalcDistanceFromTriangleSQ(JNode.Coord(), theP1, theCoord, theP0) < theCriteria)
			{
				Flag = 1;
				break;
			}

			if (theMap_.CalcDistanceFromTriangleSQ(JNode.Coord(), theP2, theCoord, theP1) < theCriteria)
			{
				Flag = 1;
				break;
			}
		}

		Continue_If(Flag);

		forThose
		(
			J, 
			0,
			MaxIndexOf(theEffectiveEdges)
		)
		{
			Debug_Null_Pointer(theEffectiveEdges[J]);

			Debug_Null_Pointer(theEffectiveEdges[J]->Node0());
			Debug_Null_Pointer(theEffectiveEdges[J]->Node1());

			Get_Const_Object(Edge) = *theEffectiveEdges[J];

			Standard_Real theMinDistance = theInfo_.MinEdgeDistanceFactor()*Edge.Length();
			Standard_Real theSquareMinDistance = theMinDistance*theMinDistance;

			Debug_Null_Pointer(Edge.Node0());
			Debug_Null_Pointer(Edge.Node1());

			Get_Const_Object(Node0) = *Edge.Node0();
			Get_Const_Object(Node1) = *Edge.Node1();

			if (NOT Geometry_Tools::IsOneCommonPointTwoLineSegment(Node0.Index(), Node1.Index(), V0, IP))
			{
				if (theMap_.CalcDistanceEdgeFromEdgeSQ(Node0.Coord(), Node1.Coord(), theP0, theCoord) < theSquareMinDistance)
				{
					Flag = 1;
					break;
				}
			}

			if (NOT Geometry_Tools::IsOneCommonPointTwoLineSegment(Node0.Index(), Node1.Index(), V1, IP))
			{
				if (theMap_.CalcDistanceEdgeFromEdgeSQ(Node0.Coord(), Node1.Coord(), theP1, theCoord) < theSquareMinDistance)
				{
					Flag = 1;
					break;
				}
			}

			if (NOT Geometry_Tools::IsOneCommonPointTwoLineSegment(Node0.Index(), Node1.Index(), V2, IP))
			{
				if (theMap_.CalcDistanceEdgeFromEdgeSQ(Node0.Coord(), Node1.Coord(), theP2, theCoord) < theSquareMinDistance)
				{
					Flag = 1;
					break;
				}
			}
		}

		Continue_If(Flag);

		theInfo_.SetValidNode(theNodesInRadius[Index]);

		return;
	}

	theInfo_.SetValidNode(NULL);
}

void AutLib::MeshLib::Mesh3d_BasicAft::SetPairedFacets()
{
	theInfo_.SetCreatedFacet0(NULL);
	theInfo_.SetCreatedFacet1(NULL);
	theInfo_.SetCreatedFacet2(NULL);

	theInfo_.SetPairedFacet0(NULL);
	theInfo_.SetPairedFacet1(NULL);
	theInfo_.SetPairedFacet2(NULL);

	if (theInfo_.Condition() EQUAL Mesh3d_NewPoint)
	{
		return;
	}

	Get_Current_Const_Mesh(Mesh);
	
	Get_Const_Object(theCurrent) = Mesh3d_BasicAft::CurrentFacet();

	Debug_Null_Pointer(theCurrent.Edge0());
	Debug_Null_Pointer(theCurrent.Edge1());
	Debug_Null_Pointer(theCurrent.Edge2());

	TColMesh3d_HBasicQueueOfFacet QFacets0, QFacets1, QFacets2;
	theCurrent.Edge0()->RetrieveFrontsTo(QFacets0);
	theCurrent.Edge1()->RetrieveFrontsTo(QFacets1);
	theCurrent.Edge2()->RetrieveFrontsTo(QFacets2);

	Get_Const_Object(theValidNode) = Mesh3d_BasicAft::ValidNode();

	Global_Handle(Mesh3d_Facet) Facet;
	while (QFacets0.DeQueue(Facet))
	{
		Debug_Null_Pointer(Facet);
		Get_Const_Object(theFacet) = *Facet;

		Standard_Boolean IsPaired = Geometry_Tools::IsPairedTwoTriangle
		(
			theCurrent.Node1()->Index(), 
			theCurrent.Node2()->Index(),
			theValidNode.Index(),
			theFacet.Node0()->Index(),
			theFacet.Node1()->Index(),
			theFacet.Node2()->Index()
		);

		if (IsPaired)
		{
			theInfo_.SetPairedFacet0(Facet);
			break;
		}
	}

	while (QFacets1.DeQueue(Facet))
	{
		Debug_Null_Pointer(Facet);
		Get_Const_Object(theFacet) = *Facet;

		Standard_Boolean IsPaired = Geometry_Tools::IsPairedTwoTriangle
		(
			theCurrent.Node2()->Index(),
			theCurrent.Node0()->Index(),
			theValidNode.Index(),
			theFacet.Node0()->Index(),
			theFacet.Node1()->Index(),
			theFacet.Node2()->Index()
		);

		if (IsPaired)
		{
			theInfo_.SetPairedFacet1(Facet);
			break;
		}
	}

	while (QFacets2.DeQueue(Facet))
	{
		Debug_Null_Pointer(Facet);
		Get_Const_Object(theFacet) = *Facet;

		Standard_Boolean IsPaired = Geometry_Tools::IsPairedTwoTriangle
		(
			theCurrent.Node0()->Index(),
			theCurrent.Node1()->Index(),
			theValidNode.Index(),
			theFacet.Node0()->Index(),
			theFacet.Node1()->Index(),
			theFacet.Node2()->Index()
		);

		if (IsPaired)
		{
			theInfo_.SetPairedFacet2(Facet);
			break;
		}
	}
}

void AutLib::MeshLib::Mesh3d_BasicAft::SetPairedEdges()
{
	theInfo_.SetCreatedEdge3(NULL);
	theInfo_.SetCreatedEdge4(NULL);
	theInfo_.SetCreatedEdge5(NULL);

	theInfo_.SetPairedEdge3(NULL);
	theInfo_.SetPairedEdge4(NULL);
	theInfo_.SetPairedEdge5(NULL);

	if (theInfo_.Condition() EQUAL Mesh3d_NewPoint)
	{
		return;
	}

	Get_Const_Object(CurrentFacet) = Mesh3d_BasicAft::CurrentFacet();

	Standard_Integer Vn = ValidNode().Index();

	Debug_Null_Pointer(CurrentFacet.Node0());
	Debug_Null_Pointer(CurrentFacet.Node1());
	Debug_Null_Pointer(CurrentFacet.Node2());

	Standard_Integer V0 = CurrentFacet.Node0()->Index();
	Standard_Integer V1 = CurrentFacet.Node1()->Index();
	Standard_Integer V2 = CurrentFacet.Node2()->Index();

	TColMesh3d_HBasicQueueOfEdge QEdges;
	ValidNode().RetrieveFrontsTo(QEdges);

	Global_Handle(Mesh3d_Edge) Edge;
	while (QEdges.DeQueue(Edge))
	{
		Debug_Null_Pointer(Edge);
		Get_Const_Object(theEdge) = *Edge;

		Standard_Integer E0 = theEdge.Node0()->Index();
		Standard_Integer E1 = theEdge.Node1()->Index();

		if (Geometry_Tools::IsPairedTwoLineSegment(E0, E1, V0, Vn))
		{
			theInfo_.SetPairedEdge3(Edge);
		}

		if (Geometry_Tools::IsPairedTwoLineSegment(E0, E1, V1, Vn))
		{
			theInfo_.SetPairedEdge4(Edge);
		}

		if (Geometry_Tools::IsPairedTwoLineSegment(E0, E1, V2, Vn))
		{
			theInfo_.SetPairedEdge5(Edge);
		}
	}
}

void AutLib::MeshLib::Mesh3d_BasicAft::UpdateEdges()
{
	Get_Current_Mesh(Mesh);

	Global_Handle(Mesh3d_Node) Node = theInfo_.ValidNode();
	Get_Const_Object(Coord) = Node->Coord();

	Get_Const_Object(theCurrent) = Mesh3d_BasicAft::CurrentFacet();

	Debug_If_Condition(theInfo_.IsPairedEdge3() AND theInfo_.IsCreatedEdge3());
	Debug_If_Condition(theInfo_.IsPairedEdge4() AND theInfo_.IsCreatedEdge4());
	Debug_If_Condition(theInfo_.IsPairedEdge5() AND theInfo_.IsCreatedEdge5());

	if (theInfo_.IsPairedEdge3())
	{
		theInfo_.SetCreatedEdge3(NULL);
	}
	else
	{
		Mesh.NbEdges()++;

		Standard_Real Length = theMap_.CalcDistance(theCurrent.Node0()->Coord(), Coord);

		Global_Handle(Mesh3d_Edge) newEdge = new Mesh3d_Edge(NbEdges(), Length, theCurrent.Node0(), theInfo_.ValidNode());

		Debug_Null_Pointer(newEdge);

		UpdateMaxLength(Length, *newEdge);

		Mesh.AttachToMeshNodes(newEdge);
		Mesh.AttachToFrontNodes(newEdge);

		Mesh.InsertToMesh(newEdge);

		theInfo_.SetCreatedEdge3(newEdge);
	}

	if (theInfo_.IsPairedEdge4())
	{
		theInfo_.SetCreatedEdge4(NULL);
	}
	else
	{
		Mesh.NbEdges()++;

		Standard_Real Length = theMap_.CalcDistance(theCurrent.Node1()->Coord(), Coord);

		Global_Handle(Mesh3d_Edge) newEdge = new Mesh3d_Edge(NbEdges(), Length, theCurrent.Node1(), theInfo_.ValidNode());

		Debug_Null_Pointer(newEdge);

		UpdateMaxLength(Length, *newEdge);

		Mesh.AttachToMeshNodes(newEdge);
		Mesh.AttachToFrontNodes(newEdge);

		Mesh.InsertToMesh(newEdge);

		theInfo_.SetCreatedEdge4(newEdge);
	}

	if (theInfo_.IsPairedEdge5())
	{
		theInfo_.SetCreatedEdge5(NULL);
	}
	else
	{
		Mesh.NbEdges()++;

		Standard_Real Length = theMap_.CalcDistance(theCurrent.Node2()->Coord(), Coord);

		Global_Handle(Mesh3d_Edge) newEdge = new Mesh3d_Edge(NbEdges(), Length, theCurrent.Node2(), theInfo_.ValidNode());

		Debug_Null_Pointer(newEdge);

		UpdateMaxLength(Length, *newEdge);

		Mesh.AttachToMeshNodes(newEdge);
		Mesh.AttachToFrontNodes(newEdge);

		Mesh.InsertToMesh(newEdge);

		theInfo_.SetCreatedEdge5(newEdge);
	}
}

void AutLib::MeshLib::Mesh3d_BasicAft::UpdateFacets()
{
	Get_Current_Mesh(Mesh);

	Get_Const_Object(theCurrent) = Mesh3d_BasicAft::CurrentFacet();

	Global_Handle(Mesh3d_Edge) E0 = theCurrent.Edge0();
	Global_Handle(Mesh3d_Edge) E1 = theCurrent.Edge1();
	Global_Handle(Mesh3d_Edge) E2 = theCurrent.Edge2();

	Global_Handle(Mesh3d_Edge) E3;
	Global_Handle(Mesh3d_Edge) E4;
	Global_Handle(Mesh3d_Edge) E5;

	if (theInfo_.CreatedEdge3()) E3 = theInfo_.CreatedEdge3();
	else E3 = theInfo_.PairedEdge3();

	if (theInfo_.CreatedEdge4()) E4 = theInfo_.CreatedEdge4();
	else E4 = theInfo_.PairedEdge4();

	if (theInfo_.CreatedEdge5()) E5 = theInfo_.CreatedEdge5();
	else E5 = theInfo_.PairedEdge5();

	Debug_Null_Pointer(E0);
	Debug_Null_Pointer(E1);
	Debug_Null_Pointer(E2);
	Debug_Null_Pointer(E3);
	Debug_Null_Pointer(E4);
	Debug_Null_Pointer(E5);

	Global_Handle(Mesh3d_Facet) Facet = theInfo_.PairedFacet0();

	if (Facet)
	{
		theInfo_.SetCreatedFacet0(NULL);

		// remove the old coicident face from the GF
		Try_Exception_Handle_Exit(Mesh.deAttachFromFront(Facet));
		Try_Exception_Handle_Exit(Mesh.RemoveFromFronts(Facet));

		// remove cavity face
		if (Facet->IsCavity())
		{
			Facet->SetAsNotCavity();
		}
	}
	else
	{
		Mesh.NbFacets()++;

		Global_Handle(Mesh3d_Facet) newFacet = new Mesh3d_Facet
		(
			NbFacets(),
			theCurrent.Node1(),
			theCurrent.Node2(),
			theInfo_.ValidNode(),
			E5,
			E4,
			E0
		);

		theInfo_.SetCreatedFacet0(newFacet);

		// insert the new Face into the FACES TREE
		Mesh.AttachToFront(newFacet);
		Mesh.AttachToMesh(newFacet);

		Mesh.InsertToFronts(newFacet);
		Mesh.InsertToMesh(newFacet);

		Mesh3d_BasicAft::CalcGeometryOf(*newFacet);
	}

	Facet = theInfo_.PairedFacet1();

	if (Facet)
	{
		theInfo_.SetCreatedFacet1(NULL);

		// remove the old coicident face from the GF
		Try_Exception_Handle_Exit(Mesh.deAttachFromFront(Facet));
		Try_Exception_Handle_Exit(Mesh.RemoveFromFronts(Facet));

		// remove cavity face
		if (Facet->IsCavity())
		{
			Facet->SetAsNotCavity();
		}
	}
	else
	{
		Mesh.NbFacets()++;

		Global_Handle(Mesh3d_Facet) newFacet = new Mesh3d_Facet
		(
			NbFacets(),
			theCurrent.Node2(),
			theCurrent.Node0(),
			theInfo_.ValidNode(),
			E3,
			E5,
			E1
		);

		theInfo_.SetCreatedFacet1(newFacet);

		// insert the new Face into the FACES TREE
		Mesh.AttachToFront(newFacet);
		Mesh.AttachToMesh(newFacet);

		Mesh.InsertToFronts(newFacet);
		Mesh.InsertToMesh(newFacet);

		Mesh3d_BasicAft::CalcGeometryOf(*newFacet);
	}

	Facet = theInfo_.PairedFacet2();

	if (Facet)
	{
		theInfo_.SetCreatedFacet2(NULL);

		// remove the old coicident face from the GF
		Try_Exception_Handle_Exit(Mesh.deAttachFromFront(Facet));
		Try_Exception_Handle_Exit(Mesh.RemoveFromFronts(Facet));

		// remove cavity face
		if (Facet->IsCavity())
		{
			Facet->SetAsNotCavity();
		}
	}
	else
	{
		Mesh.NbFacets()++;

		Global_Handle(Mesh3d_Facet) newFacet = new Mesh3d_Facet
		(
			NbFacets(),
			theCurrent.Node0(),
			theCurrent.Node1(),
			theInfo_.ValidNode(),
			E4,
			E3,
			E2
		);

		theInfo_.SetCreatedFacet2(newFacet);

		// insert the new Face into the FACES TREE
		Mesh.AttachToFront(newFacet);
		Mesh.AttachToMesh(newFacet);

		Mesh.InsertToFronts(newFacet);
		Mesh.InsertToMesh(newFacet);

		Mesh3d_BasicAft::CalcGeometryOf(*newFacet);
	}
}

void AutLib::MeshLib::Mesh3d_BasicAft::UpdateElement()
{
	Get_Current_Mesh(Mesh);
	
	Global_Handle(Mesh3d_Element) theElement = theInfo_.CreatedElement();
	Debug_Null_Pointer(theElement);

	Mesh.AttachToMeshNodes(theElement);
	Mesh.AttachToMeshEdges(theElement);

	/* Attach the element to the facets */
	
	Get_Object(theCurrent) = Mesh3d_BasicAft::CurrentFacet();

	// update right/ left side element pointer of the faces
	// update adjacent elements
	theCurrent.SetLeftElement(theElement);
	theElement->SetNeighbor(3, theCurrent.RightElement());

	if (theCurrent.RightElement())
	{
		theCurrent.RightElement()->SetNeighbor(theCurrent.RightElement()->OppositeVertexIndex(&theCurrent), theElement);
	}

	if (theInfo_.IsCreatedFacet0())
	{
		theInfo_.CreatedFacet0()->SetRightElement(theElement);
		theElement->SetNeighbor(0, NULL);
	}
	else
	{
		Global_Handle(Mesh3d_Facet) Facet = theInfo_.PairedFacet0();
		Debug_Null_Pointer(Facet);

		Global_Handle(Mesh3d_Element) Neighbor0 = Facet->RightElement();
		theElement->SetNeighbor(0, Neighbor0);

		if (Facet->LeftElement()) { THROW_STANDARD_EXCEPTION("Contradiction data"); }

		Facet->SetLeftElement(theElement);

		if (Neighbor0) { Neighbor0->SetNeighbor(Neighbor0->OppositeVertexIndex(Facet), theElement); }
	}

	if (theInfo_.IsCreatedFacet1())
	{
		theInfo_.CreatedFacet1()->SetRightElement(theElement);
		theElement->SetNeighbor(1, NULL);
	}
	else
	{
		Global_Handle(Mesh3d_Facet) Facet = theInfo_.PairedFacet1();
		Debug_Null_Pointer(Facet);

		Global_Handle(Mesh3d_Element) Neighbor1 = Facet->RightElement();
		theElement->SetNeighbor(1, Neighbor1);

		if (Facet->LeftElement()) { THROW_STANDARD_EXCEPTION("Contradiction data"); }

		Facet->SetLeftElement(theElement);

		if (Neighbor1) { Neighbor1->SetNeighbor(Neighbor1->OppositeVertexIndex(Facet), theElement); }
	}

	if (theInfo_.IsCreatedFacet2())
	{
		theInfo_.CreatedFacet2()->SetRightElement(theElement);
		theElement->SetNeighbor(2, NULL);
	}
	else
	{
		Global_Handle(Mesh3d_Facet) Facet = theInfo_.PairedFacet2();
		Debug_Null_Pointer(Facet);

		Global_Handle(Mesh3d_Element) Neighbor2 = Facet->RightElement();
		theElement->SetNeighbor(2, Neighbor2);

		if (Facet->LeftElement()) { THROW_STANDARD_EXCEPTION("Contradiction data"); }

		Facet->SetLeftElement(theElement);

		if (Neighbor2) { Neighbor2->SetNeighbor(Neighbor2->OppositeVertexIndex(Facet), theElement); }
	}

	// updating the ELMENTS TREE
	Mesh.InsertToMesh(theElement);
}

