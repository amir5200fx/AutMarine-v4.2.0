#include <Mesh3d_CavityEntityNonConvexityTools.hxx>

#include <Geometry_Tools.hxx>
#include <Mesh3d_CavityShell.hxx>
#include <Mesh3d_CavityShellGeneral.hxx>
#include <Mesh3d_FacetTools.hxx>
#include <Mesh3d_EdgeTools.hxx>
#include <Mesh3d_BoundaryEdge.hxx>
#include <Mesh3d_CavityEntitySwapEdge.hxx>
#include <Mesh3d_CavityEntityNonConvexityGeneral.hxx>
#include <Mesh3d_CavityEntityPairedElements.hxx>
#include <Mesh3d_CavityEntityTripleElements.hxx>
#include <Mesh3d_CavityEntityQuadrupleElements.hxx>
#include <TColMesh3d_HAry1dOfEdge.hxx>

using namespace AutLib;
using namespace MeshLib;
using namespace GeoLib;

Standard_Boolean AutLib::MeshLib::Mesh3d_CavityEntityNonConvexityTools::IsLess
(
	Global_Handle(Mesh3d_CavityEntityNonConvexity) const & theNonConvexity0, 
	Global_Handle(Mesh3d_CavityEntityNonConvexity) const & theNonConvexity1
)
{
	Debug_Null_Pointer(theNonConvexity0);
	Debug_Null_Pointer(theNonConvexity1);

	return theNonConvexity0->Angle() < theNonConvexity1->Angle();
}

void AutLib::MeshLib::Mesh3d_CavityEntityNonConvexityTools::IdentifyNonConvexityOf
(
	Mesh3d_CavityShell & theShell, 
	const Standard_Real theCriteria_Radian
)
{
	TColMesh3d_HAry1dOfEdge Edges;
	theShell.RetrieveEdgesTo(Edges);

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

		Try_Exception_Handle_Exit(Angle = Mesh3d_EdgeTools::AngleOf(*Edges[Index]));

		if (Angle > theCriteria_Radian)
		{
			Global_Handle(Mesh3d_CavityEntityNonConvexity) NonConvexity = Mesh3d_CavityEntityNonConvexityTools::CreateNonConvexity(Edges[Index]);
			NonConvexity->SetShell(&theShell);
			NonConvexity->SetIndex(++K);
			NonConvexity->SetAngle(Geometry_Tools::RadianToDegree(Angle));

			//cout <<  " Angle = "<< NonConvexity->Angle() <<" nb of elements = " << Edges[Index]->NbElements() << endl;

			Try_Exception_Handle_Exit(theShell.ImportToEntities(NonConvexity));
		}
	}
}

void AutLib::MeshLib::Mesh3d_CavityEntityNonConvexityTools::IdentifyNonConvexityOf
(
	TColMesh3d_HAry1dOfCavityShell & theShells,
	const Standard_Real theCriteria_Degree
)
{
	Standard_Real Criteria = Geometry_Tools::DegToRadian(theCriteria_Degree);

	forThose
	(
		Index,
		0, 
		MaxIndexOf(theShells)
	)
	{
		Debug_Null_Pointer(theShells[Index]);

		if (Global_DownCast(Mesh3d_CavityShellGeneral, theShells[Index])) continue;

		Mesh3d_CavityEntityNonConvexityTools::IdentifyNonConvexityOf(*theShells[Index], Criteria);
	}
}

Global_Handle(Mesh3d_CavityEntityNonConvexity) AutLib::MeshLib::Mesh3d_CavityEntityNonConvexityTools::CreateNonConvexity(const Global_Handle(Mesh3d_Edge) theEdge)
{
	Debug_Null_Pointer(theEdge);
	Get_Const_Object(Edge) = *theEdge;

	if (Edge.NbElements() EQUAL 2)
	{
		return new Mesh3d_CavityEntityPairedElements(theEdge);
	}

	if (Edge.NbElements() EQUAL 3)
	{
		return new Mesh3d_CavityEntityTripleElements(theEdge);
	}

	if (Edge.NbElements() EQUAL 4)
	{
		return new Mesh3d_CavityEntityQuadrupleElements(theEdge);
	}

	return new Mesh3d_CavityEntityNonConvexityGeneral(theEdge);
}