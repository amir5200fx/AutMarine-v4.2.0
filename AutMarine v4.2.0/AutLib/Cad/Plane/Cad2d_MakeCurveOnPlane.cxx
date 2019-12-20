#include <Cad2d_MakeCurveOnPlane.hxx>

#include <Geometry_Tools.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

#include <Geom2d_Line.hxx>
#include <Geom2d_Circle.hxx>
#include <Geom2d_Ellipse.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>

void AutLib::CadLib::Cad2d_MakeCurveOnPlane::LineSegment
(
	const Geom_Pnt2d & thePoint1,
	const Geom_Pnt2d & thePoint2
)
{
	theCurve_ = new Geom2d_Line(thePoint1, gp_Dir2d(gp_Vec2d(thePoint1, thePoint2)));

	Geom2dAPI_ProjectPointOnCurve Projection;

	Projection.Init(thePoint1, theCurve_);
	theFirst_ = Projection.LowerDistanceParameter();
	Projection.Init(thePoint2, theCurve_);
	theLast_ = Projection.LowerDistanceParameter();
}

void AutLib::CadLib::Cad2d_MakeCurveOnPlane::CircularArc
(
	const gp_Ax22d & A,
	const Standard_Real Radius,
	const Standard_Real theDeg0,
	const Standard_Real theDeg1
)
{
	theCurve_ = new Geom2d_Circle(A, Radius);

	theFirst_ = Geometry_Tools::DegToRadian(theDeg0);
	theLast_ = Geometry_Tools::DegToRadian(theDeg1);
}

void AutLib::CadLib::Cad2d_MakeCurveOnPlane::CircularArc
(
	const gp_Ax2d & A,
	const Standard_Real Radius,
	const Standard_Real theDeg0,
	const Standard_Real theDeg1,
	const Standard_Boolean Sense
)
{
	CircularArc(gp_Ax22d(A, Sense), Radius, theDeg0, theDeg1);
}

void AutLib::CadLib::Cad2d_MakeCurveOnPlane::Ellipse
(
	const gp_Ax2d & MajorAxis,
	const Standard_Real MajorRadius,
	const Standard_Real MinorRadius,
	const Standard_Boolean Sense
)
{
	Ellipse(gp_Ax22d(MajorAxis, Sense), MajorRadius, MinorRadius);
}

void AutLib::CadLib::Cad2d_MakeCurveOnPlane::Ellipse
(
	const gp_Ax22d & Axis, 
	const Standard_Real MajorRadius,
	const Standard_Real MinorRadius
)
{
	theCurve_ = new Geom2d_Ellipse(Axis, MajorRadius, MinorRadius);

	theFirst_ = theCurve_->FirstParameter();
	theLast_ = theCurve_->LastParameter();
}