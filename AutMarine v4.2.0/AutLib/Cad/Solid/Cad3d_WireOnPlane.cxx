#include <Cad3d_WireOnPlane.hxx>

#include <Entity_Box2dTools.hxx>
#include <Cad3d_PointOnPlane.hxx>
#include <Cad3d_EdgeOnPlane.hxx>
#include <Cad3d_WireOnPlaneOrientationTools.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

AutLib::CadLib::Cad3d_WireOnPlane::Cad3d_WireOnPlane()
{
}

AutLib::CadLib::Cad3d_WireOnPlane::Cad3d_WireOnPlane
(
	const Standard_Integer theIndex,
	const Global_Handle(Cad3d_EdgeOnPlane) theEdge
)
	: theIndex_(theIndex)
{
	theEdges_.Resize(1);
	theEdges_[0] = (Global_Handle(Cad3d_EdgeOnPlane))theEdge;

	CalcBoundingBox();
}

AutLib::CadLib::Cad3d_WireOnPlane::Cad3d_WireOnPlane
(
	const Standard_Integer theIndex,
	const TColCad3d_HAry1dOfEdgeOnPlane & theEdges
)
	: theIndex_(theIndex)
	, theEdges_(theEdges)
{
	CalcBoundingBox();
}

AutLib::CadLib::Cad3d_WireOnPlane::~Cad3d_WireOnPlane()
{
}

void AutLib::CadLib::Cad3d_WireOnPlane::Init
(
	const Standard_Integer theIndex,
	const TColCad3d_HAry1dOfEdgeOnPlane & theEdges
)
{
	theIndex_ = theIndex;
	theEdges_ = theEdges;

	CalcBoundingBox();
}

void AutLib::CadLib::Cad3d_WireOnPlane::SetIndex(const Standard_Integer theIndex)
{
	theIndex_ = theIndex;
}

void AutLib::CadLib::Cad3d_WireOnPlane::SetOrientation(const Cad3d_WireOnPlaneOrientationInfo & theOrientation)
{
	if (theOrientation_ EQUAL Cad3d_WireOnPlaneOrientation_Unknown)
	{
		theOrientation_ = Cad3d_WireOnPlaneOrientationTools::RetrieveOrientationOf(theEdges_);
	}
	if (theOrientation_ NOT_EQUAL theOrientation) { Reverse(); }
}

void AutLib::CadLib::Cad3d_WireOnPlane::Reverse()
{
	if (theOrientation_ EQUAL Cad3d_WireOnPlaneOrientation_Unknown) { THROW_STANDARD_EXCEPTION("Unknown Orientation"); }

	forThose
	(
		Index,
		0,
		MaxIndexOf(theEdges_)
	)
	{
		Debug_Null_Pointer(theEdges_[Index]);
		theEdges_[Index]->Reverse();
	}
	theEdges_.Reverse();

	theOrientation_ = Cad3d_WireOnPlaneOrientationTools::ReverseOf(theOrientation_);
}

Standard_Integer AutLib::CadLib::Cad3d_WireOnPlane::MaxEdgeIndex() const
{
	Standard_Integer K = -1;
	forThose
	(
		Index,
		0,
		MaxIndexOf(theEdges_)
	)
	{
		Debug_Null_Pointer(theEdges_[Index]);
		if (theEdges_[Index]->Index() > K) K = theEdges_[Index]->Index();
	}
	return K;
}

Standard_Integer AutLib::CadLib::Cad3d_WireOnPlane::MaxPointIndex() const
{
	return Standard_Integer();
}

void AutLib::CadLib::Cad3d_WireOnPlane::RetrievePointsTo(TColCad3d_HAry1dOfPointOnPlane & thePoints) const
{
	thePoints.Resize(theEdges_.Size());
	forThose(Index, 0, MaxIndexOf(theEdges_))
	{
		thePoints[Index] = (Global_Handle(Cad3d_PointOnPlane))theEdges_[Index]->FirstPoint();
	}
}

void AutLib::CadLib::Cad3d_WireOnPlane::ExportToPlt(fstream & File) const
{
	forThose(Index, 0, MaxIndexOf(theEdges_))
	{
		if (theEdges_[Index]) theEdges_[Index]->ExportToPlt(File);
	}
}

void AutLib::CadLib::Cad3d_WireOnPlane::CalcBoundingBox()
{
	if (theEdges_.IsEmpty()) { THROW_STANDARD_EXCEPTION("Empty List"); }

	Entity_Box2d Box = theEdges_.First()->BoundingBox();
	forThose
	(
		Index,
		1,
		MaxIndexOf(theEdges_)
	)
	{
		Debug_Null_Pointer(theEdges_[Index]);

		Box = Entity_Box2dTools::Union(Box, theEdges_[Index]->BoundingBox());
	}
	theBox_ = Box;
}