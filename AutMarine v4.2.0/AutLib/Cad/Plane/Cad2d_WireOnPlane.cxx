#include <Cad2d_WireOnPlane.hxx>

#include <Entity_Box2d.hxx>
#include <Entity_Box2dTools.hxx>
#include <Cad2d_PointOnPlane.hxx>
#include <Cad2d_EdgeOnPlane.hxx>
#include <Cad2d_WireOnPlaneOrientationTools.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

AutLib::CadLib::Cad2d_WireOnPlane::Cad2d_WireOnPlane()
{
}

AutLib::CadLib::Cad2d_WireOnPlane::Cad2d_WireOnPlane
(
	const Standard_Integer theIndex,
	const Global_Handle(Cad2d_EdgeOnPlane) theEdge
)
	: theIndex_(theIndex)
{
	theEdges_.Resize(1);
	theEdges_[0] = (Global_Handle(Cad2d_EdgeOnPlane))theEdge;

	CalcBoundingBox();
}

AutLib::CadLib::Cad2d_WireOnPlane::Cad2d_WireOnPlane
(
	const Standard_Integer theIndex, 
	const TColCad2d_HAry1dOfEdgeOnPlane & theEdges
)
	: theIndex_(theIndex)
	, theEdges_(theEdges)
{
	CalcBoundingBox();
}

AutLib::CadLib::Cad2d_WireOnPlane::~Cad2d_WireOnPlane()
{
	/*TColCad2d_HAry1dOfPointOnPlane Points;
	RetrievePointsTo(Points);

	FreeMemory(Points);
	FreeMemory(theEdges_);*/
}

void AutLib::CadLib::Cad2d_WireOnPlane::Init
(
	const Standard_Integer theIndex, 
	const TColCad2d_HAry1dOfEdgeOnPlane & theEdges
)
{
	theIndex_ = theIndex;
	theEdges_ = theEdges;

	CalcBoundingBox();
}

void AutLib::CadLib::Cad2d_WireOnPlane::SetIndex(const Standard_Integer theIndex)
{
	theIndex_ = theIndex;
}

void AutLib::CadLib::Cad2d_WireOnPlane::SetOrientation(const Cad2d_WireOnPlaneOrientationInfo & theOrientation)
{
	if (theOrientation_ EQUAL Cad2d_WireOnPlaneOrientation_Unknown)
	{
		theOrientation_ = Cad2d_WireOnPlaneOrientationTools::RetrieveOrientationOf(theEdges_);
	}
	if (theOrientation_ NOT_EQUAL theOrientation) { Reverse(); }
}

Standard_Integer AutLib::CadLib::Cad2d_WireOnPlane::MaxEdgeIndex() const
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

Standard_Integer AutLib::CadLib::Cad2d_WireOnPlane::MaxPointIndex() const
{
	TColCad2d_HAry1dOfPointOnPlane Points;
	RetrievePointsTo(Points);

	Standard_Integer K = -1;
	forThose
	(
		Index, 
		0, 
		MaxIndexOf(Points)
	)
	{
		Debug_Null_Pointer(Points[Index]);
		if (Points[Index]->Index() > K) K = Points[Index]->Index();
	}
	return K;
}

void AutLib::CadLib::Cad2d_WireOnPlane::Reverse()
{
	if (theOrientation_ EQUAL Cad2d_WireOnPlaneOrientation_Unknown) { THROW_STANDARD_EXCEPTION("Unknown Orientation"); }

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

	theOrientation_ = Cad2d_WireOnPlaneOrientationTools::ReverseOf(theOrientation_);
}

const Entity_Box2d& AutLib::CadLib::Cad2d_WireOnPlane::BoundingBox() const
{
	return theBox_;
}

void AutLib::CadLib::Cad2d_WireOnPlane::RetrievePointsTo(TColCad2d_HAry1dOfPointOnPlane & thePoints) const
{
	thePoints.Resize(theEdges_.Size());
	forThose(Index, 0, MaxIndexOf(theEdges_))
	{
		thePoints[Index] = (Global_Handle(Cad2d_PointOnPlane))theEdges_[Index]->FirstPoint();
	}
}

void AutLib::CadLib::Cad2d_WireOnPlane::ExportToPlt(fstream & File) const
{
	forThose(Index, 0, MaxIndexOf(theEdges_))
	{
		if (theEdges_[Index]) theEdges_[Index]->ExportToPlt(File);
	}
}

Global_Handle(Cad2d_WireOnPlane) AutLib::CadLib::Cad2d_WireOnPlane::Copy() const
{
	TColCad2d_HAry1dOfEdgeOnPlane Edges(theEdges_.Size());
	forThose
	(
		Index,
		0,
		MaxIndexOf(theEdges_)
	)
	{
		Debug_Null_Pointer(theEdges_[Index]);
		Edges[Index] = theEdges_[Index]->Copy();
	}
	Global_Handle(Cad2d_WireOnPlane) Copy = new Cad2d_WireOnPlane(theIndex_, Edges);

	forThose(Index, 0, MaxIndexOf(Edges))
		if (Edges[Index]) Edges[Index]->SetWire(Copy);
	return Copy;
}

void AutLib::CadLib::Cad2d_WireOnPlane::CalcBoundingBox()
{
	if (theEdges_.IsEmpty()) { THROW_STANDARD_EXCEPTION("Empty List"); }

	Entity_Box2d Box(0, 0, 0, 0);
	forThose
	(
		Index,
		0,
		MaxIndexOf(theEdges_)
	)
	{
		Debug_Null_Pointer(theEdges_[Index]);

		Box = Entity_Box2dTools::Union(Box, theEdges_[Index]->BoundingBox());
	}
	theBox_ = Box;
}