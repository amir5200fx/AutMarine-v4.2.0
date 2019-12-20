#include <Mesh3d_CurveIntegrandTools.hxx>

#include <Geom_Curve.hxx>
#include <Mesh3d_SizeMap.hxx>

Standard_Real AutLib::MeshLib::Mesh3d_CurveIntegrandTools::Integrand(const Standard_Real X, const Mesh3d_CurveIntegrand & CurveIntegrand)
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

	gp_Pnt Point;
	gp_Vec Vector;

	Curve.D1(Parameter, Point, Vector);
	
	return Map.Integrand(Point, Geom_Pnt3d(Vector.XYZ()));
}