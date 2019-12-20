#include <Cad3d_CurveOnPlaneTools.hxx>

#include <Geom_Pnt3d.hxx>
#include <Entity_Box2d.hxx>
#include <Entity_Box2dTools.hxx>
#include <Cad3d_CurveOnPlane.hxx>
#include <Cad3d_EdgeOnSolid.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

#include <Geom_Surface.hxx>
#include <TopoDS_Edge.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <ShapeBuild_Edge.hxx>

TColCad3d_HAry1dOfCurveOnPlane AutLib::CadLib::Cad3d_CurveOnPlaneTools::RetrieveCurvesOnPlane(const TColCad3d_HAry1dOfEdgeOnSolid & Edges)
{
	TColCad3d_HAry1dOfCurveOnPlane CurvesOnPlane(Edges.Size());
	forThose(Index, 0, MaxIndexOf(Edges))
		CurvesOnPlane[Index] = (Global_Handle(Cad3d_CurveOnPlane))Edges[Index]->CurveOnPlane();

	MOVE(CurvesOnPlane);
}

Entity_Box2d AutLib::CadLib::Cad3d_CurveOnPlaneTools::BoundingBoxOf
(
	const TColCad3d_HAry1dOfCurveOnPlane & theCurves,
	const Standard_Real Offset
)
{
	if (NOT theCurves.Size()) { THROW_STANDARD_EXCEPTION(" The List is Empty"); }

	Entity_Box2d Box = theCurves.First()->BoundingBox();
	forThose
	(
		Index,
		1,
		MaxIndexOf(theCurves)
	)
	{
		Debug_Null_Pointer(theCurves[Index]);

		Box = Entity_Box2dTools::Union(Box, theCurves[Index]->BoundingBox());
	}

	return Box.OffsetBox(Offset);
}

Standard_Boolean AutLib::CadLib::Cad3d_CurveOnPlaneTools::IsSameDirection
(
	const Global_Handle(Cad3d_CurveOnPlane) theCurve1,
	const Global_Handle(Cad3d_CurveOnPlane) theCurve2, 
	const Handle(Geom_Surface) theSurface1,
	const Handle(Geom_Surface) theSurface2
)
{
	Geom_Pnt2d p1 = theCurve1->FirstCoord();
	Geom_Pnt2d p2 = theCurve1->NormalizedParameterValue(0.5);

	Geom_Pnt2d q1 = theCurve2->FirstCoord();
	Geom_Pnt2d q2 = theCurve2->NormalizedParameterValue(0.5);

	Geom_Pnt3d P1 = theSurface1->Value(p1.X(), p1.Y());
	Geom_Pnt3d P2 = theSurface1->Value(p2.X(), p2.Y());

	Geom_Pnt3d Q1 = theSurface2->Value(q1.X(), q1.Y());
	Geom_Pnt3d Q2 = theSurface2->Value(q2.X(), q2.Y());

	return DotProduct(P2 - P1, Q2 - Q1) > 0;
}

TopoDS_Edge AutLib::CadLib::Cad3d_CurveOnPlaneTools::Get_TopoDS_Edge(const Cad3d_CurveOnPlane & theCurve, const Handle(Geom_Surface) theSurface)
{
	Geom_Pnt2d p1 = theCurve.FirstCoord();
	Geom_Pnt2d p2 = theCurve.LastCoord();

	gp_Pnt P1 = theSurface->Value(p1.X(), p1.Y());
	gp_Pnt P2 = theSurface->Value(p2.X(), p2.Y());

	BRepBuilderAPI_MakeEdge MakeEdge;
	MakeEdge.Init(theCurve.Curve(), theSurface, P1, P2, theCurve.FirstParameter(), theCurve.LastParameter());

	THROW_STANDARD_EXCEPTION_IF(NOT MakeEdge.IsDone(), "Invalid Data");

	TopoDS_Edge Edge = MakeEdge.Edge();

	ShapeBuild_Edge Builder;
	Builder.BuildCurve3d(Edge);

	return Edge;
}