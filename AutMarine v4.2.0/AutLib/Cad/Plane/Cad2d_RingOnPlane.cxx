#include <Cad2d_RingOnPlane.hxx>

#include <Cad2d_PointOnPlane.hxx>
#include <Cad2d_CurveOnPlane.hxx>

using namespace AutLib;
using namespace CadLib;

AutLib::CadLib::Cad2d_RingOnPlane::Cad2d_RingOnPlane()
{
}

AutLib::CadLib::Cad2d_RingOnPlane::Cad2d_RingOnPlane
(
	const Standard_Integer theIndex,
	const Global_Handle(Cad2d_PointOnPlane) thePoint,
	Global_Handle(Cad2d_CurveOnPlane) theCurve
)
	: Cad2d_EdgeOnPlane(theIndex, thePoint, thePoint, theCurve)
{
}

AutLib::CadLib::Cad2d_RingOnPlane::~Cad2d_RingOnPlane()
{
}

void AutLib::CadLib::Cad2d_RingOnPlane::Init
(
	const Standard_Integer theIndex, 
	const Global_Handle(Cad2d_PointOnPlane) thePoint,
	Global_Handle(Cad2d_CurveOnPlane) theCurve
)
{
	Cad2d_EdgeOnPlane::Init(theIndex, thePoint, thePoint, theCurve);
}

Global_Handle(Cad2d_RingOnPlane) AutLib::CadLib::Cad2d_RingOnPlane::Copy() const
{
	Global_Handle(Cad2d_PointOnPlane) Point = theFirstPoint_->Copy();
	Global_Handle(Cad2d_RingOnPlane) Copy = new Cad2d_RingOnPlane(theIndex_, Point, theCurve_->Copy());

	Try_Exception_Handle_Exit(Point->ImportEdge(Copy));

	return Copy;
}