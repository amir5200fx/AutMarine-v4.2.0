#include <Cad2d_MakePlane.hxx>

#include <Cad2d_CurveOnPlane.hxx>
#include <Cad2d_EdgeOnPlane.hxx>
#include <Cad2d_WireOnPlane.hxx>
#include <Cad2d_WireOnPlaneTools.hxx>
#include <TColCad2d_HAry1dOfCurveOnPlane.hxx>

using namespace AutLib;
using namespace CadLib;

#include <gp_Ax22d.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>

void AutLib::CadLib::Cad2d_MakePlane::Box
(
	const GeoLib::Geom_Pnt2d & Corner,
	const Standard_Real Dx, 
	const Standard_Real Dy
)
{
	Cad2d_MakePlane::Box(Corner, Corner + Geom_Pnt2d(Dx, Dy));
}

void AutLib::CadLib::Cad2d_MakePlane::Box
(
	const GeoLib::Geom_Pnt2d & Corner0,
	const GeoLib::Geom_Pnt2d & Corner1
)
{
	Geom_Pnt2d P0 = Corner0;
	Geom_Pnt2d P1(Corner1.X(), Corner0.Y());
	Geom_Pnt2d P2 = Corner1;
	Geom_Pnt2d P3(Corner0.X(), Corner1.Y());

	gp_Vec2d V0(P0, P1);
	gp_Vec2d V1(P1, P2);
	gp_Vec2d V2(P2, P3);
	gp_Vec2d V3(P3, P0);

	Handle(Geom2d_Curve) C0 = new Geom2d_Line(P0, gp_Dir2d(V0));
	Handle(Geom2d_Curve) C1 = new Geom2d_Line(P1, gp_Dir2d(V1));
	Handle(Geom2d_Curve) C2 = new Geom2d_Line(P2, gp_Dir2d(V2));
	Handle(Geom2d_Curve) C3 = new Geom2d_Line(P3, gp_Dir2d(V3));

	Standard_Real U0, U1;

	Geom2dAPI_ProjectPointOnCurve Projection;

	Projection.Init(P0, C0);
	U0 = Projection.LowerDistanceParameter();
	Projection.Init(P1, C0);
	U1 = Projection.LowerDistanceParameter();
	Global_Handle(Cad2d_CurveOnPlane) Curve0 = new Cad2d_CurveOnPlane(U0, U1, C0);

	Projection.Init(P1, C1);
	U0 = Projection.LowerDistanceParameter();
	Projection.Init(P2, C1);
	U1 = Projection.LowerDistanceParameter();
	Global_Handle(Cad2d_CurveOnPlane) Curve1 = new Cad2d_CurveOnPlane(U0, U1, C1);

	Projection.Init(P2, C2);
	U0 = Projection.LowerDistanceParameter();
	Projection.Init(P3, C2);
	U1 = Projection.LowerDistanceParameter();
	Global_Handle(Cad2d_CurveOnPlane) Curve2 = new Cad2d_CurveOnPlane(U0, U1, C2);

	Projection.Init(P3, C3);
	U0 = Projection.LowerDistanceParameter();
	Projection.Init(P0, C3);
	U1 = Projection.LowerDistanceParameter();
	Global_Handle(Cad2d_CurveOnPlane) Curve3 = new Cad2d_CurveOnPlane(U0, U1, C3);

	TColCad2d_HAry1dOfCurveOnPlane Curves(4);
	Curves[0] = Curve0;
	Curves[1] = Curve1;
	Curves[2] = Curve2;
	Curves[3] = Curve3;

	Cad2d_Plane::Make(Curves);
}

void AutLib::CadLib::Cad2d_MakePlane::Box
(
	const gp_Ax22d & A, 
	const Standard_Real Dx, 
	const Standard_Real Dy
)
{
	gp_Trsf2d T;
	T.SetTransformation(A.XAxis());

	Geom_Pnt2d P0;
	Geom_Pnt2d P1(Dx, Dy);

	Box(P0, P1);

	Transform(T.Inverted());
}

void AutLib::CadLib::Cad2d_MakePlane::Box
(
	const gp_Ax2d & A,
	const Standard_Real Dx,
	const Standard_Real Dy, 
	const Standard_Boolean Sense
)
{
	Box(gp_Ax22d(A, Sense), Dx, Dy);
}

void AutLib::CadLib::Cad2d_MakePlane::Circle
(
	const gp_Ax22d & A, 
	const Standard_Real Radius
)
{
	Handle(Geom2d_Curve) Circle = new Geom2d_Circle(A, Radius);

	Global_Handle(Cad2d_CurveOnPlane) Curve = new Cad2d_CurveOnPlane(Circle->FirstParameter(), Circle->LastParameter(), Circle);

	TColCad2d_HAry1dOfCurveOnPlane Curves(1);
	Curves[0] = Curve;
	
	Cad2d_Plane::Make(Curves);
}

void AutLib::CadLib::Cad2d_MakePlane::Circle
(
	const gp_Ax2d & A,
	const Standard_Real Radius,
	const Standard_Boolean Sense
)
{
	Circle(gp_Ax22d(A, Sense), Radius);
}