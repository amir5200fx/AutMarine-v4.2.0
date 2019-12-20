#include <Cad3d_RingOnPlane.hxx>

#include <Cad3d_PointOnPlane.hxx>
#include <Cad3d_CurveOnPlane.hxx>

using namespace AutLib;
using namespace CadLib;

AutLib::CadLib::Cad3d_RingOnPlane::Cad3d_RingOnPlane()
{
}

AutLib::CadLib::Cad3d_RingOnPlane::Cad3d_RingOnPlane
(
	const Standard_Integer theIndex,
	const Global_Handle(Cad3d_PointOnPlane) thePoint,
	Global_Handle(Cad3d_CurveOnPlane) theCurve
)
	: Cad3d_EdgeOnPlane(theIndex, thePoint, thePoint, theCurve)
{
}

AutLib::CadLib::Cad3d_RingOnPlane::~Cad3d_RingOnPlane()
{
}

void AutLib::CadLib::Cad3d_RingOnPlane::Init
(
	const Standard_Integer theIndex,
	const Global_Handle(Cad3d_PointOnPlane) thePoint,
	Global_Handle(Cad3d_CurveOnPlane) theCurve
)
{
	Cad3d_EdgeOnPlane::Init(theIndex, thePoint, thePoint, theCurve);
}

Global_Handle(Cad3d_RingOnPlane) AutLib::CadLib::Cad3d_RingOnPlane::Copy() const
{
	Global_Handle(Cad3d_RingOnPlane) Copy = new Cad3d_RingOnPlane(theIndex_, NULL, theCurve_->Copy());
	return Copy;
}