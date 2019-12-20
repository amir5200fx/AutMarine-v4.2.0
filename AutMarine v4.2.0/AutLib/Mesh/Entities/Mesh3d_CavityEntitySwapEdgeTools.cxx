#include <Mesh3d_CavityEntitySwapEdgeTools.hxx>

#include <Geometry_Tools.hxx>
#include <Mesh3d_BoundaryEdge.hxx>
#include <Mesh3d_EdgeTools.hxx>
#include <Mesh3d_CavityShell.hxx>
#include <Mesh3d_CavityEntitySwapEdge.hxx>
#include <Mesh3d_CavityShellGeneral.hxx>
#include <TColMesh3d_HAry1dOfEdge.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace MeshLib;

Standard_Boolean AutLib::MeshLib::Mesh3d_CavityEntitySwapEdgeTools::IsLess
(
	Global_Handle(Mesh3d_CavityEntitySwapEdge) const & theSwapEdge0,
	Global_Handle(Mesh3d_CavityEntitySwapEdge) const & theSwapEdge1
)
{
	Debug_Null_Pointer(theSwapEdge0);
	Debug_Null_Pointer(theSwapEdge1);

	return theSwapEdge0->Angle() < theSwapEdge1->Angle();
}

void AutLib::MeshLib::Mesh3d_CavityEntitySwapEdgeTools::IdentifySwapEdgesOf(Mesh3d_CavityShell & theShell)
{
	TColMesh3d_HAry1dOfEdge Edges;
	theShell.RetrieveEdgesTo(Edges);
	//cout << "IdentifySwapEdgesOf" << endl;
	Standard_Real Angle;
	Standard_Integer K = 0;
	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		if (Global_DownCast(Mesh3d_BoundaryEdge, Edges[Index])) continue;

		Debug_Null_Pointer(Edges[Index]->Node0());
		Debug_Null_Pointer(Edges[Index]->Node1());

		Get_Const_Object(Node0) = *Edges[Index]->Node0();
		Get_Const_Object(Node1) = *Edges[Index]->Node1();

		TColMesh3d_HAry1dOfFacet FacetsOnShell0 = theShell.RetrieveFacetsOnShell(Node0.RetrieveFrontFacets());
		TColMesh3d_HAry1dOfFacet FacetsOnShell1 = theShell.RetrieveFacetsOnShell(Node1.RetrieveFrontFacets());

		if (FacetsOnShell0.Size() NOT_EQUAL 4 AND FacetsOnShell1.Size() NOT_EQUAL 4) continue;

		Try_Exception_Handle_Exit(Angle = Mesh3d_EdgeTools::AngleOf(*Edges[Index]));
		//cout << K << endl;
		Global_Handle(Mesh3d_CavityEntitySwapEdge) SwapEdge = new Mesh3d_CavityEntitySwapEdge(Edges[Index], &theShell);
		SwapEdge->SetIndex(++K);
		SwapEdge->SetAngle(Geometry_Tools::RadianToDegree(Angle));

		Try_Exception_Handle_Exit(theShell.ImportToEntities(SwapEdge));
	}
	//PAUSE;
}

void AutLib::MeshLib::Mesh3d_CavityEntitySwapEdgeTools::IdentifySwapEdgesOf(TColMesh3d_HAry1dOfCavityShell & theShells)
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(theShells)
	)
	{
		Debug_Null_Pointer(theShells[Index]);

		if (NOT Global_DownCast(Mesh3d_CavityShellGeneral, theShells[Index])) continue;

		Mesh3d_CavityEntitySwapEdgeTools::IdentifySwapEdgesOf(*theShells[Index]);
	}
}