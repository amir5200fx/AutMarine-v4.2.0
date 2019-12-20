#include <Mesh3d_CavityRemover.hxx>

#include <Geometry_Distance.hxx>
#include <Geometry_Intersect.hxx>
#include <Geometry_Tools.hxx>
#include <Geometry_ItemsSort.hxx>
#include <Mesh3d_CavityEntityNonConvexity.hxx>
#include <Mesh3d_CavityEntitySwapEdge.hxx>
#include <Mesh3d_CavityEntityNonConvexityTools.hxx>
#include <Mesh3d_CavityEntitySwapEdgeTools.hxx>
#include <Mesh3d_CavityEntitySwapEdgeTools.hxx>
#include <Mesh3d_CavityShellFourFacet.hxx>
#include <Mesh3d_CavityShellSixFacet.hxx>
#include <Mesh3d_CavityShellEightFacet.hxx>
#include <Mesh3d_CavityShellTenFacet.hxx>
#include <Mesh3d_CavityShellGeneral.hxx>
#include <Mesh3d_NodeTools.hxx>
#include <Mesh3d_EdgeTools.hxx>
#include <Mesh3d_CavityShellTools.hxx>
#include <Mesh3d_CavityRemoverTools.hxx>
#include <Mesh3d_CavityShellFourFacetTools.hxx>
#include <Mesh3d_QualityMapIsotropicValidElement.hxx>
#include <Mesh3d_EdgeRemovalEquatorialTriangles.hxx>
#include <Mesh3d_EdgeRemovalEquatorialTrianglesTools.hxx>

static const Standard_Real DEFAULT_NONCONVEXITY_ANGLE = 181.0;

using namespace AutLib;
using namespace MeshLib;
using namespace GeoLib;

#define Get_Current_Mesh(MESH) Get_Object(MESH) = *Mesh3d_Volume::CurrentMesh()
#define Get_Current_Const_Mesh(MESH) Get_Const_Object(MESH) = *Mesh3d_Volume::CurrentMesh()

AutLib::MeshLib::Mesh3d_CavityRemover::Mesh3d_CavityRemover
(
	const Mesh3d_SizeMap & theSizeMap,
	Global_Handle(TColMesh3d_GeomSearchOfNode) theSearchEngine
)
	: Mesh3d_BasicAft(theSizeMap, theSearchEngine)
	, theNonConvexityAngle_(DEFAULT_NONCONVEXITY_ANGLE)
{
	Set_Numbering(theShells_, Mesh3d_CavityShellTools::IsLess);
}

AutLib::MeshLib::Mesh3d_CavityRemover::~Mesh3d_CavityRemover()
{
}

Standard_Integer AutLib::MeshLib::Mesh3d_CavityRemover::MeshGeneration()
{
	Standard_Integer BasicAft;
	Try_Exception_Handle_Exit(BasicAft = Mesh3d_BasicAft::MeshGeneration());

	if (NOT BasicAft)
	{
		return 0;
	}

	if (theVerbosity_)
	{
		cout << "  Cavity Remover envolved!" << endl;
	}

	Try_Exception_Handle_Exit(RepairLevel1());

	forThose(Iteration, 1, 4)
	{
		Try_Exception_Handle_Exit(RepairLevel2());

		ClearShells();
	}

	return 1;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_CavityRemover::MeshCavityShell(Global_Handle(Mesh3d_CavityShell) theShell)
{
	Global_Handle(Mesh3d_CavityShellFourFacet) FourFacetShell = Global_DownCast(Mesh3d_CavityShellFourFacet, theShell);
	if (FourFacetShell)
	{
		return Mesh3d_CavityRemover::MeshCavityShell(FourFacetShell);
	}

	Global_Handle(Mesh3d_CavityShellSixFacet) SixFacetShell = Global_DownCast(Mesh3d_CavityShellSixFacet, theShell);
	if (SixFacetShell)
	{
		//cout << "SIX FACET SHELL" << endl;
		return Mesh3d_CavityRemover::MeshCavityShell(SixFacetShell);
	}

	Global_Handle(Mesh3d_CavityShellEightFacet) EightFacetShell = Global_DownCast(Mesh3d_CavityShellEightFacet, theShell);
	if (EightFacetShell)
	{
		//cout << "EIGHT FACET SHELL" << endl;
		return Mesh3d_CavityRemover::MeshCavityShell(EightFacetShell);
	}

	/*Global_Handle(Mesh3d_CavityShellTenFacet) TenFacetShell = Global_DownCast(Mesh3d_CavityShellTenFacet, theShell);
	if (TenFacetShell)
	{
		return Mesh3d_CavityRemover::MeshCavityShell(TenFacetShell);
	}*/

	/*Global_Handle(Mesh3d_CavityShellGeneral) GeneralShell = Global_DownCast(Mesh3d_CavityShellGeneral, theShell);
	if (GeneralShell)
	{
		cout << "general shell, nb. of facets = " << GeneralShell->NbFacets() << endl;
		Standard_Boolean Generated = Mesh3d_CavityRemover::MeshCavityShell(GeneralShell);
		GeneralShell->ClearEntities();
		cout << "general shell, nb. of facets = " << GeneralShell->NbFacets() << endl;
		PAUSE;
		return Generated;
	}*/

	return Standard_False;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_CavityRemover::MeshCavityShell(Global_Handle(Mesh3d_CavityShellFourFacet) theShell)
{
	Debug_Null_Pointer(theShell);

	Get_Const_Object(Shell) = *theShell;

	TColMesh3d_HAry1dOfFacet Facets;
	Shell.RetrieveFacetsTo(Facets);

	Global_Handle(Mesh3d_Facet) Current(0);
	Global_Handle(Mesh3d_Node) Valid(0);

	Mesh3d_CavityShellFourFacetTools::RetrieveCandidates(Shell, Current, Valid);

	Debug_Null_Pointer(Current);
	Debug_Null_Pointer(Valid);

	Try_Exception_Handle_Exit(Mesh3d_CavityRemover::GenerateOneElement(Current, Valid));

	return Standard_True;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_CavityRemover::MeshCavityShell(Global_Handle(Mesh3d_CavityShellSixFacet) theShell)
{
	Debug_Null_Pointer(theShell);

	Get_Const_Object(Shell) = *theShell;

	TColMesh3d_HAry1dOfNode Equatorial = Shell.Equatorial();

	if (Equatorial.Size() NOT_EQUAL 3) { THROW_STANDARD_EXCEPTION("Invalid Equatorial"); }

	Global_Handle(Mesh3d_Facet) newFace = ImportFacetToMesh(Equatorial[0], Equatorial[1], Equatorial[2]);

	Get_Current_Mesh(Mesh);
	Mesh.AttachToFront(newFace);
	Mesh.InsertToFronts(newFace);

	GenerateOneElement(newFace, Shell.Vertex0(), Standard_False);

	newFace->Reverse();

	Mesh.AttachToFront(newFace);
	Mesh.InsertToFronts(newFace);

	GenerateOneElement(newFace, Shell.Vertex1(), Standard_False);

	return Standard_True;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_CavityRemover::MeshCavityShell(Global_Handle(Mesh3d_CavityShellEightFacet) theShell)
{
	Debug_Null_Pointer(theShell);

	Get_Const_Object(Shell) = *theShell;

	if (Shell.IsConvex())
	{
		TColMesh3d_HAry1dOfFacet Facets;
		Shell.RetrieveFacetsTo(Facets);

		Global_Handle(Mesh3d_Node) Node = new Mesh3d_Node(NbNodes() + 1, Shell.Centre());
		Try_Exception_Handle_Exit(Mesh3d_CavityRemover::GenerateOneElement(Facets[0], Node, Standard_True));

		forThose
		(
			Index,
			1,
			MaxIndexOf(Facets)
		)
		{
			Debug_Null_Pointer(Facets[Index]);

			Try_Exception_Handle_Exit(Mesh3d_CavityRemover::GenerateOneElement(Facets[Index], Node, Standard_False));
		}

		return Standard_True;
	}

	Global_Handle(Mesh3d_Node) PickNode = Shell.HasPick();
	if (PickNode)
	{
		//cout << " PICK REMOVAL, nb facets = " << theShell->NbFacets() << endl;
		Standard_Boolean Meshed = MeshPick(PickNode, theShell);
		//cout << "PICK REMOVAL = " << Meshed << endl;
		//cout << " PICK REMOVAL, nb facets = " << theShell->NbFacets() << endl;
		Debug_If_Condition_Message(CheckShell(Shell), "Something goes wrong!");
		if (Meshed) return Meshed;
	}

	TColMesh3d_HAry1dOfCavityEntityNonConvexity NonConvexities;
	Shell.RetrieveNonConvexitiesTo(NonConvexities);

	if (NonConvexities.IsEmpty()) { THROW_STANDARD_EXCEPTION("Contradictory data"); }

	Geometry_ItemsSort<Global_Handle(Mesh3d_CavityEntityNonConvexity)> Sort(&Mesh3d_CavityEntityNonConvexityTools::IsLess);
	Sort.Peform(NonConvexities);

	NonConvexities.Reverse();

	forThose
	(
		Index,
		0,
		MaxIndexOf(NonConvexities)
	)
	{
		Debug_Null_Pointer(NonConvexities[Index]);
		Get_Const_Object(NonConvexity) = *NonConvexities[Index];

		Get_Const_Pointer(Edge) = NonConvexity.Edge();
		TColMesh3d_HAry1dOfFacet RemovedFacets;
		Edge->RetrieveFrontsTo(RemovedFacets);

		Global_Handle(Mesh3d_Edge) newEdge = FrontFlip((Global_Handle(Mesh3d_Edge))NonConvexity.Edge());

		if (newEdge)
		{
			TColMesh3d_HAry1dOfFacet AddedFacets;
			newEdge->RetrieveFrontsTo(AddedFacets);

			Debug_If_Condition(AddedFacets.Size() NOT_EQUAL 2);

			theShell->RemoveFromEntities(NonConvexities[Index]);

			Try_Exception_Handle_Exit(theShell->RemoveFromFacets(RemovedFacets[0]));
			Try_Exception_Handle_Exit(theShell->RemoveFromFacets(RemovedFacets[1]));

			Try_Exception_Handle_Exit(theShell->ImportToFacets(AddedFacets[0]));
			Try_Exception_Handle_Exit(theShell->ImportToFacets(AddedFacets[1]));

			Debug_If_Condition(theShell->NbFacets() NOT_EQUAL 8);

			TColMesh3d_HAry1dOfFacet Facets;
			theShell->RetrieveFacetsTo(Facets);

			Try_Exception_Handle_Exit(FormFront(Facets));

			Try_Exception_Handle_Exit(Mesh3d_BasicAft::MeshGeneration());

			theShell->Clear();

			if (NOT theCavity_.IsCertaintyEmpty())
			{
				TColMesh3d_HAry1dOfFacet CavityFacets;
				theCavity_.RetrieveCertaintyTo(CavityFacets);

				forThose(J, 0, MaxIndexOf(CavityFacets))
					theShell->ImportToFacets(CavityFacets[J]);
			}

			if (Shell.IsEmpty()) return Standard_True;
			break;
		}
	}
	return Standard_False;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_CavityRemover::MeshCavityShell(Global_Handle(Mesh3d_CavityShellTenFacet) theShell)
{
	Debug_Null_Pointer(theShell);

	Get_Const_Object(Shell) = *theShell;

	if (Shell.IsConvex())
	{
		TColMesh3d_HAry1dOfFacet Facets;
		Shell.RetrieveFacetsTo(Facets);

		Global_Handle(Mesh3d_Node) Node = new Mesh3d_Node(NbNodes() + 1, Shell.Centre());
		Try_Exception_Handle_Exit(Mesh3d_CavityRemover::GenerateOneElement(Facets[0], Node, Standard_True));

		forThose
		(
			Index,
			1,
			MaxIndexOf(Facets)
		)
		{
			Debug_Null_Pointer(Facets[Index]);

			Try_Exception_Handle_Exit(Mesh3d_CavityRemover::GenerateOneElement(Facets[Index], Node, Standard_False));
		}

		return Standard_True;
	}

	TColMesh3d_HAry1dOfCavityEntityNonConvexity NonConvexities;
	Shell.RetrieveNonConvexitiesTo(NonConvexities);

	if (NonConvexities.IsEmpty()) { THROW_STANDARD_EXCEPTION("Contradictory data"); }

	Geometry_ItemsSort<Global_Handle(Mesh3d_CavityEntityNonConvexity)> Sort(&Mesh3d_CavityEntityNonConvexityTools::IsLess);
	Sort.Peform(NonConvexities);

	NonConvexities.Reverse();

	forThose
	(
		Index,
		0,
		MaxIndexOf(NonConvexities)
	)
	{
		Debug_Null_Pointer(NonConvexities[Index]);
		Get_Const_Object(NonConvexity) = *NonConvexities[Index];

		Get_Const_Pointer(Edge) = NonConvexity.Edge();
		TColMesh3d_HAry1dOfFacet RemovedFacets;
		Edge->RetrieveFrontsTo(RemovedFacets);

		Global_Handle(Mesh3d_Edge) newEdge = FrontFlip((Global_Handle(Mesh3d_Edge))NonConvexity.Edge());

		if (newEdge)
		{
			TColMesh3d_HAry1dOfFacet AddedFacets;
			newEdge->RetrieveFrontsTo(AddedFacets);

			Debug_If_Condition(AddedFacets.Size() NOT_EQUAL 2);

			theShell->RemoveFromEntities(NonConvexities[Index]);

			Try_Exception_Handle_Exit(theShell->RemoveFromFacets(RemovedFacets[0]));
			Try_Exception_Handle_Exit(theShell->RemoveFromFacets(RemovedFacets[1]));

			Try_Exception_Handle_Exit(theShell->ImportToFacets(AddedFacets[0]));
			Try_Exception_Handle_Exit(theShell->ImportToFacets(AddedFacets[1]));

			Debug_If_Condition(theShell->NbFacets() NOT_EQUAL 10);

			TColMesh3d_HAry1dOfFacet Facets;
			theShell->RetrieveFacetsTo(Facets);

			Try_Exception_Handle_Exit(FormFront(Facets));

			Try_Exception_Handle_Exit(Mesh3d_BasicAft::MeshGeneration());

			theShell->Clear();

			if (NOT theCavity_.IsCertaintyEmpty())
			{
				TColMesh3d_HAry1dOfFacet CavityFacets;
				theCavity_.RetrieveCertaintyTo(CavityFacets);

				forThose(J, 0, MaxIndexOf(CavityFacets))
					theShell->ImportToFacets(CavityFacets[J]);
			}

			if (Shell.IsEmpty()) return Standard_True;
			break;
		}
	}
	return Standard_False;
}

namespace AutLib
{
	namespace MeshLib
	{
		static void UpdateSwapEdges(TColMesh3d_HAry1dOfCavityEntitySwapEdge& theSwapEdges)
		{
			Standard_Real Angle;
			forThose
			(
				Index,
				0,
				MaxIndexOf(theSwapEdges)
			)
			{
				Debug_Null_Pointer(theSwapEdges[Index]);
				Debug_Null_Pointer(theSwapEdges[Index]->Edge());

				Try_Exception_Handle_Exit(Angle = Mesh3d_EdgeTools::AngleOf(*theSwapEdges[Index]->Edge()));

				theSwapEdges[Index]->SetAngle(Angle);
			}
		}
	}
}

Standard_Boolean AutLib::MeshLib::Mesh3d_CavityRemover::MeshCavityShell(Global_Handle(Mesh3d_CavityShellGeneral) theShell)
{
	Debug_Null_Pointer(theShell);

	Get_Const_Object(Shell) = *theShell;
	
	if (Shell.NbFacets() <= 8) { return Standard_True; }

	TColMesh3d_HAry1dOfCavityEntitySwapEdge SwapEdges;
	theShell->RetrieveSwapEdgesTo(SwapEdges);

	::UpdateSwapEdges(SwapEdges);

	if (SwapEdges.IsEmpty()) { THROW_STANDARD_EXCEPTION("Contradictory data"); }

	Geometry_ItemsSort<Global_Handle(Mesh3d_CavityEntitySwapEdge)> Sort(&Mesh3d_CavityEntitySwapEdgeTools::IsLess);
	Sort.Peform(SwapEdges);

	SwapEdges.Reverse();

	forThose
	(
		Index, 
		0,
		MaxIndexOf(SwapEdges)
	)
	{
		Debug_Null_Pointer(SwapEdges[Index]);

		theShell->RemoveFromEntities(SwapEdges[Index]);

		if (NOT SwapEdges[Index]->Edge()->IsOnFront()) continue;
		if (NOT IsValidToSwap(SwapEdges[Index]->Edge(), theShell)) continue;
		//cout << "Flip" << endl;
		//cout << theShell->NbFacets() << endl;
		TColMesh3d_HAry1dOfFacet RemovedFacets;
		SwapEdges[Index]->Edge()->RetrieveFrontsTo(RemovedFacets);

		Try_Exception_Handle_Exit(theShell->RemoveFromFacets(RemovedFacets[0]));
		Try_Exception_Handle_Exit(theShell->RemoveFromFacets(RemovedFacets[1]));

		Get_Pointer(Node0) = SwapEdges[Index]->Edge()->Node0();
		Get_Pointer(Node1) = SwapEdges[Index]->Edge()->Node1();

		Global_Handle(Mesh3d_Edge) newEdge = FrontFlip((Global_Handle(Mesh3d_Edge))SwapEdges[Index]->Edge());

		TColMesh3d_HAry1dOfFacet AddedFacets;
		newEdge->RetrieveFrontsTo(AddedFacets);

		Debug_If_Condition(AddedFacets.Size() NOT_EQUAL 2);

		Try_Exception_Handle_Exit(theShell->ImportToFacets(AddedFacets[0]));
		Try_Exception_Handle_Exit(theShell->ImportToFacets(AddedFacets[1]));

		//cout << "node 0 = " << Node0->NbFrontFacets() << endl;
		//cout << "node 1 = " << Node1->NbFrontFacets() << endl;
		if (IsPickNode(Node0, theShell))
		{
			cout << "Mesh pick 1" << endl;
			Standard_Boolean Meshed = MeshPick(Node0, theShell);
			Debug_If_Condition_Message(CheckShell(*theShell), "Something goes wrong!");
			if (Meshed) return MeshCavityShell(theShell);
		}

		if (IsPickNode(Node1, theShell))
		{
			//cout << "Mesh pick 2" << endl;
			Standard_Boolean Meshed = MeshPick(Node1, theShell);
			Debug_If_Condition_Message(CheckShell(*theShell), "Something goes wrong!");
			if (Meshed) return MeshCavityShell(theShell);
		}
	}
	return Standard_False;
}

namespace AutLib
{
	namespace MeshLib
	{

		static TColMesh3d_HAry1dOfNode RetrieveEquatorialNodesFrom(const TColMesh3d_HAry1dOfFacet& theFacets, const Global_Handle(Mesh3d_Node) theCentre)
		{
			TColMesh3d_HAry1dOfNode totNodes = Mesh3d_FacetTools::RetrieveNodesFrom(theFacets);
			TColMesh3d_HBasicQueueOfNode QNodes;
			forThose
			(
				Index,
				0, 
				MaxIndexOf(totNodes)
			)
			{
				Debug_Null_Pointer(totNodes[Index]);
				if (totNodes[Index] NOT_EQUAL theCentre) QNodes.EnQueue(totNodes[Index]);
			}
			TColMesh3d_HAry1dOfNode Nodes;
			QNodes.RetrieveTo(Nodes);

			MOVE(Nodes);
		}
	}
}

Standard_Boolean AutLib::MeshLib::Mesh3d_CavityRemover::MeshPick
(
	Global_Handle(Mesh3d_Node) theNode, 
	Global_Handle(Mesh3d_CavityShell) theShell
)
{
	Debug_Null_Pointer(theNode);
	Debug_Null_Pointer(theShell);

	TColMesh3d_HAry1dOfFacet Facets;
	theNode->RetrieveFrontsTo(Facets);

	TColMesh3d_HAry1dOfFacet FacetsOnShell = theShell->RetrieveFacetsOnShell(Facets);

	if (FacetsOnShell.Size() NOT_EQUAL 3) { THROW_STANDARD_EXCEPTION("It's not a Pick"); }

	TColMesh3d_HAry1dOfNode EquatorialNodes = ::RetrieveEquatorialNodesFrom(FacetsOnShell, theNode);

	if (EquatorialNodes.Size() NOT_EQUAL 3) { THROW_STANDARD_EXCEPTION("Contradictory Data"); }

	if (Geometry_Tools::VolumeOfTetrahedron(EquatorialNodes[0]->Coord(), EquatorialNodes[1]->Coord(), EquatorialNodes[2]->Coord(), theNode->Coord()) < 0) EquatorialNodes.Reverse();

	TColMesh3d_HAry1dOfNode totNodes;
	theShell->RetrieveNodesTo(totNodes);

	TColMesh3d_HBasicQueueOfNode QNodes;
	forThose
	(
		Index,
		0,
		MaxIndexOf(totNodes)
	)
	{
		if (totNodes[Index] EQUAL EquatorialNodes[0]) continue;
		if (totNodes[Index] EQUAL EquatorialNodes[1]) continue;
		if (totNodes[Index] EQUAL EquatorialNodes[2]) continue;
		QNodes.EnQueue(totNodes[Index]);
	}
	TColMesh3d_HAry1dOfNode Nodes;
	QNodes.RetrieveTo(Nodes);

	TColMesh3d_HAry1dOfEdge totEdges;
	theShell->RetrieveEdgesTo(totEdges);

	TColMesh3d_HBasicQueueOfEdge QEdges;
	forThose
	(
		Index,
		0, 
		MaxIndexOf(totEdges)
	)
	{
		if (totEdges[Index]->Node0() EQUAL EquatorialNodes[0] OR totEdges[Index]->Node1() EQUAL EquatorialNodes[0]) continue;
		if (totEdges[Index]->Node0() EQUAL EquatorialNodes[1] OR totEdges[Index]->Node1() EQUAL EquatorialNodes[1]) continue;
		if (totEdges[Index]->Node0() EQUAL EquatorialNodes[2] OR totEdges[Index]->Node1() EQUAL EquatorialNodes[2]) continue;
		QEdges.EnQueue(totEdges[Index]);
	}
	TColMesh3d_HAry1dOfEdge Edges;
	QEdges.RetrieveTo(Edges);

	if (NOT IsValidNewFace(EquatorialNodes[0]->Coord(), EquatorialNodes[1]->Coord(), EquatorialNodes[2]->Coord(), Nodes, Edges, 0.01))
	{
		return Standard_False;
	}

	Global_Handle(Mesh3d_Facet) newFace = ImportFacetToMesh(EquatorialNodes[0], EquatorialNodes[1], EquatorialNodes[2]);

	Get_Current_Mesh(Mesh);
	Mesh.AttachToFront(newFace);
	Mesh.InsertToFronts(newFace);

	GenerateOneElement(newFace, theNode, Standard_False);

	newFace->Reverse();

	Mesh.AttachToFront(newFace);
	Mesh.InsertToFronts(newFace);

	theShell->RemoveFromFacets(FacetsOnShell[0]);
	theShell->RemoveFromFacets(FacetsOnShell[1]);
	theShell->RemoveFromFacets(FacetsOnShell[2]);

	theShell->ImportToFacets(newFace);

	return Standard_True;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_CavityRemover::CheckFront(const TColMesh3d_HAry1dOfFacet & theFacet) const
{
	forThose(Index, 0, MaxIndexOf(theFacet))
		if (NOT theFacet[Index]->IsOnFront()) return Standard_True;
	return Standard_False;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_CavityRemover::CheckFront1(const TColMesh3d_HAry1dOfFacet & theFacet) const
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(theFacet)
	)
	{
		Debug_Null_Pointer(theFacet[Index]);
		forThose(J, 0, 2)
		{
			Debug_Null_Pointer(theFacet[Index]->Edge(J));
			if (theFacet[Index]->Edge(J)->NbFrontFacets() NOT_EQUAL 2) return Standard_True;
		}
	}
	return Standard_False;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_CavityRemover::CheckFront2(const TColMesh3d_HAry1dOfFacet & theFacets) const
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(theFacets)
	)
	{
		Debug_Null_Pointer(theFacets[Index]);
		forThose(J, 0, 2)
		{
			Debug_Null_Pointer(theFacets[Index]->Edge(J));
			if (NOT theFacets[Index]->Edge(J)->IsContainAtFront(theFacets[Index]))
			{
				return Standard_True;
			}
		}
	}
	return Standard_False;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_CavityRemover::CheckShell(const Mesh3d_CavityShell & theShell) const
{
	TColMesh3d_HAry1dOfFacet Facets;
	theShell.RetrieveFacetsTo(Facets);

	return CheckFront2(Facets);
}

namespace AutLib
{
	namespace MeshLib
	{
		Standard_Real MaxLength(const Geom_Pnt3d & theP0, const Geom_Pnt3d & theP1, const Geom_Pnt3d & theP2)
		{
			Standard_Real L1 = Distance(theP0, theP1);
			Standard_Real L2 = Distance(theP1, theP2);
			Standard_Real L3 = Distance(theP2, theP0);

			return MAX(L1, MAX(L2, L3));
		}
	}
}

Standard_Boolean AutLib::MeshLib::Mesh3d_CavityRemover::IsValidNewFace
(
	const Geom_Pnt3d & theP0,
	const Geom_Pnt3d & theP1,
	const Geom_Pnt3d & theP2,
	const TColMesh3d_HAry1dOfNode & theNodes,
	const TColMesh3d_HAry1dOfEdge & theEdges, 
	const Standard_Real theDisCoeff
) const
{
	Standard_Real Criteria = ::MaxLength(theP0, theP1, theP2)*theDisCoeff;
	forThose
	(
		Index,
		0,
		MaxIndexOf(theNodes)
	)
	{
		Debug_Null_Pointer(theNodes[Index]);

		if (Geometry_Distance::DistancePointFromTriangle(theNodes[Index]->Coord(), theP0, theP1, theP2) < Criteria) { return Standard_False; }
	}

	forThose
	(
		Index,
		0,
		MaxIndexOf(theEdges)
	)
	{
		Debug_Null_Pointer(theEdges[Index]);

		Debug_Null_Pointer(theEdges[Index]->Node0());
		Debug_Null_Pointer(theEdges[Index]->Node1());

		if (Geometry_Intersect::IsIntersectLineSegmentTriangle(theEdges[Index]->Node0()->Coord(), theEdges[Index]->Node1()->Coord(), theP0, theP1, theP2)) { return Standard_False; }
	}
	return Standard_True;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_CavityRemover::IsPickNode
(
	const Global_Handle(Mesh3d_Node) theNode, 
	const Global_Handle(Mesh3d_CavityShell) theShell
) const
{
	TColMesh3d_HAry1dOfFacet totFacets;
	theNode->RetrieveFrontsTo(totFacets);

	if (totFacets.Size() EQUAL 3) return Standard_True;

	TColMesh3d_HAry1dOfFacet Facets = theShell->RetrieveFacetsOnShell(totFacets);

	if (Facets.Size() EQUAL 3) return Standard_True;
	return Standard_False;
}

Standard_Integer AutLib::MeshLib::Mesh3d_CavityRemover::OneLevelRemoveDefiniteElements
(
	TColMesh3d_HAry1dOfFacet & theRetrieveFacets,
	TColMesh3d_HAry1dOfFacet & theRemoveFacets,
	const Standard_Boolean theThreeEntities,
	const Standard_Boolean theFourEntities
)
{
	Get_Current_Mesh(Mesh);

	TColMesh3d_HAry1dOfFacet FrontFacet;
	Mesh.RetrieveFrontsTo(FrontFacet);

	TColMesh3d_HAry1dOfElement BadElements;
	Mesh3d_CavityRemoverTools::DefiniteElementsToRemove
	(
		FrontFacet, 
		BadElements,
		theThreeEntities, 
		theFourEntities
	);

	TColMesh3d_HAvlTreeOfFacet CompactRetrieveFacets, CompactRemoveFacets;
	Set_Numbering(CompactRetrieveFacets, Mesh3d_FacetTools::IsLess);
	Set_Numbering(CompactRemoveFacets, Mesh3d_FacetTools::IsLess);

	TColMesh3d_HBasicQueueOfFacet QRemoveFacets;
	forThose
	(
		Index,
		0,
		MaxIndexOf(BadElements)
	)
	{
		Debug_Null_Pointer(BadElements[Index]);

		TColMesh3d_HAry1dOfNode RetrieveNodes, RemoveNodes;
		TColMesh3d_HAry1dOfEdge RetrieveEdges, RemoveEdges;
		TColMesh3d_HAry1dOfFacet RetrieveFacets, RemoveFacets;

		Mesh.RemoveFromTopology
		(
			BadElements[Index],
			RetrieveFacets,
			RetrieveEdges,
			RetrieveNodes,
			RemoveFacets,
			RemoveEdges,
			RemoveNodes,
			Standard_True
		);

		Try_Exception_Handle_Exit(CompactRetrieveFacets.Insert(RetrieveFacets));
		Try_Exception_Handle_Exit(CompactRemoveFacets.Insert(RemoveFacets));

		if (NOT CompactRetrieveFacets.IsEmpty())
		{
			Try_Exception_Handle_Exit(CompactRetrieveFacets.RemoveIgnoreWarning(RemoveFacets));
		}

		QRemoveFacets.EnQueue(RemoveFacets);

		theSearch_.Remove(RemoveNodes);

		theSearch_.Insert(RetrieveNodes);
	}
	QRemoveFacets.RetrieveTo(theRemoveFacets);

	if (NOT CompactRetrieveFacets.IsEmpty())
	{
		Try_Exception_Handle_Exit(CompactRetrieveFacets.RemoveIgnoreWarning(theRemoveFacets));
	}

	CompactRetrieveFacets.RetrieveTo(theRetrieveFacets);
	CompactRemoveFacets.RetrieveTo(theRemoveFacets);

	return BadElements.Size();
}

namespace AutLib
{
	namespace MeshLib
	{

		static void FindApices(const TColMesh3d_HAry1dOfNode& theNodes, const Global_Handle(Mesh3d_CavityShell) theShell, Global_Handle(Mesh3d_Node)& theVertex0, Global_Handle(Mesh3d_Node)& theVertex1)
		{
			TColMesh3d_HBasicQueueOfNode QNodes;
			forThose
			(
				Index,
				0,
				MaxIndexOf(theNodes)
			)
			{
				Debug_Null_Pointer(theNodes[Index]);

				if (theShell->IsOnShell(theNodes[Index])) QNodes.EnQueue(theNodes[Index]);
			}
			TColMesh3d_HAry1dOfNode Nodes;
			QNodes.RetrieveTo(Nodes);

			if (Nodes.Size() NOT_EQUAL 2) { THROW_STANDARD_EXCEPTION("Contradictory Data"); }

			theVertex0 = Nodes[0];
			theVertex1 = Nodes[1];
		}
	}
}

Global_Handle(Mesh3d_EdgeRemovalEquatorialTriangles) AutLib::MeshLib::Mesh3d_CavityRemover::IsValidToSwap
(
	const Global_Handle(Mesh3d_Edge) theEdge,
	const Global_Handle(Mesh3d_CavityShell) theShell
) const
{
	Debug_Null_Pointer(theEdge);

	Get_Const_Object(Edge) = *theEdge;

	Mesh3d_QualityMapIsotropicValidElement Quality;
	Global_Handle(Mesh3d_EdgeRemovalEquatorialTriangles) EquatorialTriangles = Mesh3d_EdgeRemovalEquatorialTrianglesTools::CreateEquatorialTriangle(Edge, Quality);

	if (NOT EquatorialTriangles) { return NULL; }

	Global_Handle(Mesh3d_Node) Vertex0;
	Global_Handle(Mesh3d_Node) Vertex1;
	::FindApices(EquatorialTriangles->Nodes(), theShell, Vertex0, Vertex1);

	TColMesh3d_HAry1dOfEdge totEdges;
	theShell->RetrieveEdgesTo(totEdges);

	TColMesh3d_HBasicQueueOfEdge QEdges;
	forThose
	(
		Index,
		0, 
		MaxIndexOf(totEdges)
	)
	{
		if (totEdges[Index] EQUAL theEdge) continue;
		if (totEdges[Index]->Node0() EQUAL Vertex0 OR totEdges[Index]->Node0() EQUAL Vertex1) continue;
		if (totEdges[Index]->Node1() EQUAL Vertex0 OR totEdges[Index]->Node1() EQUAL Vertex1) continue;
		QEdges.EnQueue(totEdges[Index]);
	}

	TColMesh3d_HAry1dOfEdge Edges;
	QEdges.RetrieveTo(Edges);

	if (NOT IsValidNewEdge(Vertex0->Coord(), Vertex1->Coord(), Edges)) 
	{ 
		FreePointer(EquatorialTriangles);
		return NULL;
	}

	TColMesh3d_HAry1dOfNode totNodes;
	theShell->RetrieveNodesTo(totNodes);
	TColMesh3d_HBasicQueueOfNode QNodes;
	forThose
	(
		Index,
		0,
		MaxIndexOf(totNodes)
	)
	{
		if (totNodes[Index] EQUAL Edge.Node0()) continue;
		if (totNodes[Index] EQUAL Edge.Node1()) continue;
		if (totNodes[Index] EQUAL Vertex0) continue;
		if (totNodes[Index] EQUAL Vertex1) continue;
		QNodes.EnQueue(totNodes[Index]);
	}
	TColMesh3d_HAry1dOfNode Nodes;
	QNodes.RetrieveTo(Nodes);

	Get_Const_Object(Node0) = *Edge.Node0();
	Get_Const_Object(Node1) = *Edge.Node1();

	if (NOT IsValidNewFace(Node0.Coord(), Vertex0->Coord(), Node1.Coord(), Nodes, Edges, 0.1)) { FreePointer(EquatorialTriangles); return NULL; }
	if (NOT IsValidNewFace(Node1.Coord(), Vertex1->Coord(), Node0.Coord(), Nodes, Edges, 0.1)) { FreePointer(EquatorialTriangles); return NULL; }

	return EquatorialTriangles;
}

Global_Handle(Mesh3d_Facet) AutLib::MeshLib::Mesh3d_CavityRemover::ImportFacetToMesh
(
	Global_Handle(Mesh3d_Node) theNode0,
	Global_Handle(Mesh3d_Node) theNode1,
	Global_Handle(Mesh3d_Node) theNode2
)
{
	Get_Current_Mesh(Mesh);

	Debug_Null_Pointer(theNode0);
	Debug_Null_Pointer(theNode1);
	Debug_Null_Pointer(theNode2);

	Get_Const_Object(Node0) = *theNode0;
	Get_Const_Object(Node1) = *theNode1;
	Get_Const_Object(Node2) = *theNode2;

	Global_Handle(Mesh3d_Edge) Edge2 = Mesh3d_NodeTools::HasAFrontEdgeBetween(Node0, Node1);

	if (NOT Edge2)
	{
		Mesh.NbEdges()++;

		Standard_Real Length = theMap_.CalcDistance(Node0.Coord(), Node1.Coord());

		Edge2 = new Mesh3d_Edge(Mesh.NbEdges(), Length, (Global_Handle(Mesh3d_Node))&Node0, (Global_Handle(Mesh3d_Node))&Node1);

		Debug_Null_Pointer(Edge2);

		UpdateMaxLength(Length, *Edge2);

		Mesh.AttachToMeshNodes(Edge2);
		Mesh.AttachToFrontNodes(Edge2);

		Mesh.InsertToMesh(Edge2);
	}

	Global_Handle(Mesh3d_Edge) Edge0 = Mesh3d_NodeTools::HasAFrontEdgeBetween(Node1, Node2);

	if (NOT Edge0)
	{
		Mesh.NbEdges()++;

		Standard_Real Length = theMap_.CalcDistance(Node1.Coord(), Node2.Coord());

		Edge0 = new Mesh3d_Edge(Mesh.NbEdges(), Length, (Global_Handle(Mesh3d_Node))&Node1, (Global_Handle(Mesh3d_Node))&Node2);

		Debug_Null_Pointer(Edge0);

		UpdateMaxLength(Length, *Edge0);

		Mesh.AttachToMeshNodes(Edge0);
		Mesh.AttachToFrontNodes(Edge0);

		Mesh.InsertToMesh(Edge0);
	}

	Global_Handle(Mesh3d_Edge) Edge1 = Mesh3d_NodeTools::HasAFrontEdgeBetween(Node2, Node0);

	if (NOT Edge1)
	{
		Mesh.NbEdges()++;

		Standard_Real Length = theMap_.CalcDistance(Node2.Coord(), Node0.Coord());

		Edge1 = new Mesh3d_Edge(Mesh.NbEdges(), Length, (Global_Handle(Mesh3d_Node))&Node2, (Global_Handle(Mesh3d_Node))&Node0);

		Debug_Null_Pointer(Edge1);

		UpdateMaxLength(Length, *Edge1);

		Mesh.AttachToMeshNodes(Edge1);
		Mesh.AttachToFrontNodes(Edge1);

		Mesh.InsertToMesh(Edge1);
	}

	Global_Handle(Mesh3d_Facet) newFacet = new Mesh3d_Facet
	(
		++Mesh.NbFacets(),
		(Global_Handle(Mesh3d_Node))&Node0,
		(Global_Handle(Mesh3d_Node))&Node1,
		(Global_Handle(Mesh3d_Node))&Node2,
		Edge0,
		Edge1,
		Edge2
	);

	Try_Exception_Handle_Exit(Mesh.AttachToMesh(newFacet));
	Try_Exception_Handle_Exit(Mesh.InsertToMesh(newFacet));

	Mesh3d_BasicAft::CalcGeometryOf(*newFacet);

	return newFacet;
}

Global_Handle(Mesh3d_Edge) AutLib::MeshLib::Mesh3d_CavityRemover::FrontFlip(Global_Handle(Mesh3d_Edge) theEdge)
{
	Get_Current_Mesh(Mesh);

	Debug_Null_Pointer(theEdge);

	Get_Const_Object(Edge) = *theEdge;

	Mesh3d_QualityMapIsotropicValidElement Quality;
	Global_Handle(Mesh3d_EdgeRemovalEquatorialTriangles) EquatorialTriangles = Mesh3d_EdgeRemovalEquatorialTrianglesTools::CreateEquatorialTriangle(Edge, Quality);

	if (NOT EquatorialTriangles) { return NULL; }

	Global_Handle(Mesh3d_Node) Node0 = theEdge->Node0();
	Global_Handle(Mesh3d_Node) Node1 = theEdge->Node1();

	RemoveEdge(theEdge);

	TColMesh3d_HAry1dOfFacet Facets;
	Mesh3d_CavityRemover::ImportFacetsToMesh(*EquatorialTriangles, Facets);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Facets)
	)
	{
		Debug_Null_Pointer(Facets[Index]);

		Try_Exception_Handle_Exit(Mesh.AttachToFront(Facets[Index]));
		Try_Exception_Handle_Exit(Mesh.InsertToFronts(Facets[Index]));

		Try_Exception_Handle_Exit(Mesh3d_CavityRemover::GenerateOneElement(Facets[Index], Node1, Standard_False));

		Facets[Index]->Reverse();

		Try_Exception_Handle_Exit(Mesh.AttachToFront(Facets[Index]));
		Try_Exception_Handle_Exit(Mesh.InsertToFronts(Facets[Index]));

		Try_Exception_Handle_Exit(Mesh3d_CavityRemover::GenerateOneElement(Facets[Index], Node0, Standard_False));
	}

	Get_Const_Object(Nodes) = EquatorialTriangles->Nodes();
	Global_Handle(Mesh3d_Edge) newEdge = Mesh3d_NodeTools::HasAFrontEdgeBetween(*Nodes.First(), *Nodes.Last());

	if (NOT newEdge) { THROW_STANDARD_EXCEPTION("Contradictory data"); }

	return newEdge;
}

void AutLib::MeshLib::Mesh3d_CavityRemover::RemoveEdge(Global_Handle(Mesh3d_Edge) theEdge)
{
	Debug_Null_Pointer(theEdge);

	TColMesh3d_HAry1dOfElement Elements;
	theEdge->RetrieveTo(Elements);

	if (Elements.IsEmpty()) { THROW_STANDARD_EXCEPTION("Invalid Data"); }

	Get_Current_Mesh(Mesh);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Elements)
	)
	{
		Debug_Null_Pointer(Elements[Index]);

		TColMesh3d_HAry1dOfNode RetrieveNodes, RemoveNodes;
		TColMesh3d_HAry1dOfEdge RetrieveEdges, RemoveEdges;
		TColMesh3d_HAry1dOfFacet RetrieveFacets, RemoveFacets;

		Mesh.RemoveFromTopology
		(
			Elements[Index],
			RetrieveFacets,
			RetrieveEdges,
			RetrieveNodes,
			RemoveFacets,
			RemoveEdges,
			RemoveNodes,
			Standard_True
		);

		theSearch_.Remove(RemoveNodes);

		theSearch_.Insert(RetrieveNodes);
	}
}

void AutLib::MeshLib::Mesh3d_CavityRemover::RemoveDefiniteElements(TColMesh3d_HAry1dOfFacet & theRetrieveFacets)
{
	TColMesh3d_HAry1dOfFacet RetrieveFacets, RemoveFacets;
	Standard_Integer NbElements = Mesh3d_CavityRemover::OneLevelRemoveDefiniteElements
	(
		RetrieveFacets,
		RemoveFacets,
		Standard_True,
		Standard_True
	);

	TColMesh3d_HAvlTreeOfFacet CompactFacets;
	Set_Numbering(CompactFacets, Mesh3d_FacetTools::IsLess);

	Try_Exception_Handle_Exit(CompactFacets.Insert(RetrieveFacets));

	while (NbElements)
	{
		NbElements = Mesh3d_CavityRemover::OneLevelRemoveDefiniteElements
		(
			RetrieveFacets, 
			RemoveFacets, 
			Standard_True, 
			Standard_True
		);

		Try_Exception_Handle_Exit(CompactFacets.Insert(RetrieveFacets));
		Try_Exception_Handle_Exit(CompactFacets.RemoveIgnoreWarning(RemoveFacets));
	}
	CompactFacets.RetrieveTo(theRetrieveFacets);
}

void AutLib::MeshLib::Mesh3d_CavityRemover::FormFront()
{
	Get_Current_Mesh(Mesh);

	TColMesh3d_HAry1dOfFacet Fronts;
	Mesh.RetrieveFrontsTo(Fronts);

	theFront_.ClearCurrentLevel();
	theFront_.ClearNextLevel();

	theFront_.InsertToFronts(Fronts);

	TColMesh3d_HAry1dOfNode FrontNodes;
	Mesh.RetrieveFrontsTo(FrontNodes);

	theFront_.SetLevelMaxIndex(Mesh3d_NodeTools::GetMaxIndexOf(FrontNodes));
}

void AutLib::MeshLib::Mesh3d_CavityRemover::FormFront(const TColMesh3d_HAry1dOfFacet & theFacets)
{
	Get_Current_Mesh(Mesh);

	theFront_.ClearCurrentLevel();
	theFront_.ClearNextLevel();

	theFront_.InsertToFronts(theFacets);

	TColMesh3d_HAry1dOfNode FrontNodes;
	Mesh.RetrieveFrontsTo(FrontNodes);

	theFront_.SetLevelMaxIndex(Mesh3d_NodeTools::GetMaxIndexOf(FrontNodes));
}

void AutLib::MeshLib::Mesh3d_CavityRemover::MarkAsUnCavity(const TColMesh3d_HAry1dOfFacet & theFacets)
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(theFacets)
	)
	{
		Debug_Null_Pointer(theFacets[Index]);
		theFacets[Index]->SetAsNotCavity();
	}
}

void AutLib::MeshLib::Mesh3d_CavityRemover::GenerateOneElement
(
	Global_Handle(Mesh3d_Facet) theCurrent,
	Global_Handle(Mesh3d_Node) theNode,
	const Standard_Boolean CreationNode
)
{
	Debug_Null_Pointer(theCurrent);

	theInfo_.Reset();
	theInfo_.SetCurrent(theCurrent);

	//Debug_If_Condition_Message(NOT Mesh3d_BasicAft::IsBelongToFront(), "Contradictory data, the current is not belong to the front");

	if (NOT Mesh3d_BasicAft::IsBelongToFront()) { THROW_STANDARD_EXCEPTION("Contradictory data, the current is not belong to the front"); }

	Mesh3d_BasicAft::RemoveCurrentFromFront();

	if (CreationNode)
	{
		theInfo_.SetCreatedNode(theNode);
		theInfo_.SetAppendedCondition(Standard_True);
		theInfo_.SetValidNode(theNode);
	}
	else
	{
		theInfo_.SetCreatedNode(NULL);
		theInfo_.SetAppendedCondition(Standard_False);
		theInfo_.SetValidNode(theNode);
	}

	Mesh3d_BasicAft::Update();
}

void AutLib::MeshLib::Mesh3d_CavityRemover::ImportFacetsToMesh
(
	const Mesh3d_EdgeRemovalEquatorialTriangles & theEquatorialTriangles, 
	TColMesh3d_HAry1dOfFacet & theFacets
)
{
	Get_Current_Mesh(Mesh);

	Get_Const_Object(Nodes) = theEquatorialTriangles.Nodes();
	Get_Const_Object(Triangles) = theEquatorialTriangles.Triangles();
	//Get_Const_Object(Edges) = theEquatorialTriangles.Edges();

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

		theFacets[Index] = ImportFacetToMesh(Nodes[Index_Of(V0)], Nodes[Index_Of(V1)], Nodes[Index_Of(V2)]);
	}
}

void AutLib::MeshLib::Mesh3d_CavityRemover::RepairLevel1()
{
	Get_Current_Mesh(Mesh);

	TColMesh3d_HAry1dOfFacet FrontFacet;
	Mesh.RetrieveFrontsTo(FrontFacet);

	MarkAsUnCavity(FrontFacet);

	// Remove Cavity list
	theCavity_.ClearUnCertainty();
	theCavity_.ClearCertainty();

	TColMesh3d_HAry1dOfFacet RetrieveFacets;
	Mesh3d_CavityRemover::RemoveDefiniteElements(RetrieveFacets);

	if (RetrieveFacets.IsEmpty()) { return; }

	Try_Exception_Handle_Exit(Mesh3d_CavityRemover::FormFront());

	Try_Exception_Handle_Exit(Mesh3d_BasicAft::MeshGeneration());
}

void AutLib::MeshLib::Mesh3d_CavityRemover::RepairLevel2()
{
	Get_Current_Mesh(Mesh);
	
	TColMesh3d_HAry1dOfFacet RetrieveFacets;
	Mesh3d_CavityRemover::RemoveDefiniteElements(RetrieveFacets);

	TColMesh3d_HAry1dOfFacet FrontFacet;
	Mesh.RetrieveFrontsTo(FrontFacet);

	MarkAsUnCavity(FrontFacet);

	// Remove Cavity list
	theCavity_.ClearUnCertainty();
	theCavity_.ClearCertainty();
	
	TColMesh3d_HAry1dOfCavityShell Shells;
	Mesh3d_CavityRemoverTools::CreateCavityShells(FrontFacet, Shells);

	Try_Exception_Handle_Exit(theShells_.Insert(Shells));

	Mesh3d_CavityEntityNonConvexityTools::IdentifyNonConvexityOf(Shells, theNonConvexityAngle_);
	Mesh3d_CavityEntitySwapEdgeTools::IdentifySwapEdgesOf(Shells);

	if (Shells.IsEmpty()) return;

	forThose
	(
		Index,
		0,
		MaxIndexOf(Shells)
	)
	{
		Debug_Null_Pointer(Shells[Index]);

		if (Mesh3d_CavityRemover::MeshCavityShell(Shells[Index]))
		{
			Try_Exception_Handle_Exit(theShells_.Remove(Shells[Index]));

			FreePointer(Shells[Index]);
		}
	}
}

void AutLib::MeshLib::Mesh3d_CavityRemover::ClearShells()
{
	TColMesh3d_HAry1dOfCavityShell Shells;
	theShells_.RetrieveTo(Shells);
	theShells_.Clear();

	FreeMemory(Shells);
}