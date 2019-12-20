#include <Cad3d_EdgeOnSolid.hxx>

#include <Entity_Polygon2d.hxx>
#include <Entity_PolyLine3d.hxx>
#include <Cad3d_CurveOnSurface.hxx>
#include <Cad3d_CurveOnPlane.hxx>
#include <Cad3d_SurfaceOnSolid.hxx>
#include <Geom_Pnt2d.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

AutLib::CadLib::Cad3d_EdgeOnSolid::Cad3d_EdgeOnSolid()
	: theCurveOnPlane_(0)
	, theCurveOnSurface_(0)
	, thePaired_(NULL)
	, thePairedOnSolid_(NULL)
{
}

AutLib::CadLib::Cad3d_EdgeOnSolid::Cad3d_EdgeOnSolid
(
	const Standard_Integer Index,
	Global_Handle(Cad3d_CurveOnPlane) theCurveOnPlane,
	Global_Handle(Cad3d_CurveOnSurface) theCurveOnSurface,
	const Global_Handle(Cad3d_SurfaceOnSolid) theSurface
)
	: theCurveOnPlane_(theCurveOnPlane)
	, theCurveOnSurface_(theCurveOnSurface)
	, theSurface_(theSurface)
	, theIndex_(Index)
	, thePaired_(NULL)
	, thePairedOnSolid_(NULL) 
{
}

AutLib::CadLib::Cad3d_EdgeOnSolid::~Cad3d_EdgeOnSolid()
{
	ReleaseMemory();
}

void AutLib::CadLib::Cad3d_EdgeOnSolid::Init
(
	const Standard_Integer Index,
	Global_Handle(Cad3d_CurveOnPlane) theCurveOnPlane, 
	Global_Handle(Cad3d_CurveOnSurface) theCurveOnSurface,
	const Global_Handle(Cad3d_SurfaceOnSolid) theSurface
)
{
	theIndex_ = Index;

	theCurveOnPlane_ = theCurveOnPlane;
	theCurveOnSurface_ = theCurveOnSurface;

	theSurface_ = theSurface;
}

void AutLib::CadLib::Cad3d_EdgeOnSolid::SetIndex(const Standard_Integer Index)
{
	theIndex_ = Index;
}

void AutLib::CadLib::Cad3d_EdgeOnSolid::SetStart(const Global_Handle(Cad3d_PointOnSolid) theStartPoint)
{
	theP0_ = theStartPoint;
}

void AutLib::CadLib::Cad3d_EdgeOnSolid::SetLast(const Global_Handle(Cad3d_PointOnSolid) theLastPoint)
{
	theP1_ = theLastPoint;
}

void AutLib::CadLib::Cad3d_EdgeOnSolid::SetEdgeOnPlane(Global_Handle(Cad3d_CurveOnPlane) theCurveOnPlane)
{
	theCurveOnPlane_ = theCurveOnPlane;
}

void AutLib::CadLib::Cad3d_EdgeOnSolid::SetEdgeOnSurface(Global_Handle(Cad3d_CurveOnSurface) theCurveOnSurface)
{
	theCurveOnSurface_ = theCurveOnSurface;
}

void AutLib::CadLib::Cad3d_EdgeOnSolid::SetSurface(const Global_Handle(Cad3d_SurfaceOnSolid) theSurface)
{
	theSurface_ = theSurface;
}

void AutLib::CadLib::Cad3d_EdgeOnSolid::SetPaired(const Global_Handle(Cad3d_EdgeOnSolid) thePaired)
{
	thePaired_ = thePaired;
}

void AutLib::CadLib::Cad3d_EdgeOnSolid::SetPairedOnSolid(const Global_Handle(Cad3d_PairedOnSolid) thePairedOnSolid)
{
	thePairedOnSolid_ = thePairedOnSolid;
}

void AutLib::CadLib::Cad3d_EdgeOnSolid::Reverse()
{
	if (theCurveOnPlane_) theCurveOnPlane_->Reverse();
	if (theCurveOnSurface_) theCurveOnSurface_->Reverse();

	SWAP(theP0_, theP1_);
}

void AutLib::CadLib::Cad3d_EdgeOnSolid::ExportParametricCurvesToPlt(fstream & File) const
{
	/*Entity_Polygon2d Poly = theCurveOnPlane_->UniformParametricDiscretize(40);
	Get_Const_Object(Parameters) = Poly.Points();

	Entity_PolyLine3d PolyLine;
	Get_Object(Coords) = PolyLine.Points();

	Coords.Resize(Poly.NbPoints());

	forThose(Index, 0, MaxIndexOf(Coords))
		Coords.SetValue(Index, theSurface_->Value(Parameters[Index]));

	PolyLine.ExportToPlt(File);*/
	theCurveOnPlane_->ExportToPlt(File);
}

void AutLib::CadLib::Cad3d_EdgeOnSolid::ExportToPlt(fstream & File) const
{
	theCurveOnSurface_->ExportToPlt(File);
}

void AutLib::CadLib::Cad3d_EdgeOnSolid::PrintEnds(Standard_OStream & Ostream) const
{
	Debug_Null_Pointer(theSurface_);

	Ostream << "-------------{Coords of the Edge}----------------" << endl;
	Ostream << " Space First Coord: " << theCurveOnSurface_->StartCoord() << endl;
	Ostream << " Space Last Coord: " << theCurveOnSurface_->LastCoord() << endl;
	Ostream << "     .....    " << endl;
	Ostream << " Parametric First Coord: " << theSurface_->Value(theCurveOnPlane_->FirstCoord()) << endl;
	Ostream << " Parametric Last Coord: " << theSurface_->Value(theCurveOnPlane_->LastCoord()) << endl;
	Ostream << "----------{End of Coords of the Edge}------------" << endl;
}

void AutLib::CadLib::Cad3d_EdgeOnSolid::ReleaseMemory()
{
	FreePointer(theCurveOnPlane_);
	FreePointer(theCurveOnSurface_);
}