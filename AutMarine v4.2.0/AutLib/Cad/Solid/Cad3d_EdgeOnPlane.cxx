#include <Cad3d_EdgeOnPlane.hxx>

#include <Global_Debug.hxx>
#include <Entity_Box2d.hxx>
#include <Cad3d_CurveOnPlane.hxx>
#include <Cad3d_PointOnPlane.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace CadLib;

AutLib::CadLib::Cad3d_EdgeOnPlane::Cad3d_EdgeOnPlane()
	: theIndex_(0)
	, theFirstPoint_(0)
	, theLastPoint_(0)
	, theCurve_(0)
{
}

AutLib::CadLib::Cad3d_EdgeOnPlane::Cad3d_EdgeOnPlane
(
	const Standard_Integer theIndex,
	const Global_Handle(Cad3d_PointOnPlane) theFirstPoint,
	const Global_Handle(Cad3d_PointOnPlane) theLastPoint, 
	Global_Handle(Cad3d_CurveOnPlane) theCurve
)
	: theIndex_(theIndex)
	, theFirstPoint_(theFirstPoint)
	, theLastPoint_(theLastPoint)
	, theCurve_(theCurve)
{
}

AutLib::CadLib::Cad3d_EdgeOnPlane::~Cad3d_EdgeOnPlane()
{
	//FreePointer(theCurve_);
}

void AutLib::CadLib::Cad3d_EdgeOnPlane::Init
(
	const Standard_Integer theIndex, 
	const Global_Handle(Cad3d_PointOnPlane) theFirstPoint,
	const Global_Handle(Cad3d_PointOnPlane) theLastPoint,
	Global_Handle(Cad3d_CurveOnPlane) theCurve
)
{
	theIndex_ = theIndex;
	theFirstPoint_ = theFirstPoint;
	theLastPoint_ = theLastPoint;
	theCurve_ = theCurve;
}

void AutLib::CadLib::Cad3d_EdgeOnPlane::Init
(
	const Global_Handle(Cad3d_PointOnPlane) theFirstPoint,
	const Global_Handle(Cad3d_PointOnPlane) theLastPoint,
	Global_Handle(Cad3d_CurveOnPlane) theCurve
)
{
	theFirstPoint_ = theFirstPoint;
	theLastPoint_ = theLastPoint;
	theCurve_ = theCurve;
}

Entity_Box2d AutLib::CadLib::Cad3d_EdgeOnPlane::BoundingBox(const Standard_Real theTolerance) const
{
	return theCurve_->BoundingBox(theTolerance);
}

void AutLib::CadLib::Cad3d_EdgeOnPlane::SetIndex(const Standard_Integer theIndex)
{
	theIndex_ = theIndex;
}

void AutLib::CadLib::Cad3d_EdgeOnPlane::SetWire(const Global_Handle(Cad3d_WireOnPlane) theWire)
{
	theWire_ = theWire;
}

void AutLib::CadLib::Cad3d_EdgeOnPlane::Reverse()
{
	Debug_Null_Pointer(theCurve_);
	theCurve_->Reverse();
	SWAP(theFirstPoint_, theLastPoint_);
}

void AutLib::CadLib::Cad3d_EdgeOnPlane::ExportToPlt(fstream & File) const
{
	if (theCurve_) theCurve_->ExportToPlt(File);
}

Global_Handle(Cad3d_EdgeOnPlane) AutLib::CadLib::Cad3d_EdgeOnPlane::Copy() const
{
	Global_Handle(Cad3d_EdgeOnPlane) Copy = new Cad3d_EdgeOnPlane(theIndex_, NULL, NULL, theCurve_->Copy());   // Modify: June 19, 2018

	return Copy;
}