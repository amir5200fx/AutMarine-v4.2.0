#include "Mesh2d_CurveIntegrandTools.hxx"

#include <Geom2d_Curve.hxx>
#include <gp_Pnt2d.hxx>
#include <gp_Vec2d.hxx>
#include <Geom_Pnt2d.hxx>
#include <Mesh2d_SizeMap.hxx>
#include <Cad2d_CurveOnPlane.hxx>
#include <Geom2d_Curve.hxx>

Standard_Real AutLib::MeshLib::Mesh2d_CurveIntegrandTools::Integrand(const Standard_Real X, const Mesh2d_CurveIntegrand & CurveIntegrand)
{
	Debug_Null_Pointer(CurveIntegrand.Map());
	Debug_Null_Pointer(CurveIntegrand.Curve());

	Get_Const_Object(Map) = *CurveIntegrand.Map();
	Get_Const_Object(Curve) = *CurveIntegrand.Curve();
	
	Standard_Real First = CurveIntegrand.FirstParameter();
	Standard_Real Last = CurveIntegrand.LastParameter();
	Standard_Real Parameter = X;

	if (Parameter < First) Parameter = First;
	if (Parameter > Last) Parameter = Last;

	gp_Pnt2d Point;
	gp_Vec2d Vector;

	Curve.D1(Parameter, Point, Vector);
	
	return Map.Integrand(Point, Geom_Pnt2d(Vector.XY()));
}