#include <Cad3d_Plane.hxx>

#include <Entity_Box2d.hxx>
#include <Entity_StaticChain2d.hxx>
#include <Entity_EdgeIndexTools.hxx>
#include <Entity_Polygon2d.hxx>
#include <Merge_Chain2d.hxx>
#include <Cad3d_PointOnPlane.hxx>
#include <Cad3d_EdgeOnPlane.hxx>
#include <Cad3d_WireOnPlane.hxx>
#include <Cad3d_EdgeOnPlaneTools.hxx>
#include <Cad3d_WireOnPlaneTools.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

static const Standard_Real DEFAULT_RESOLUTION = 1.0E-3;
static const Standard_Real DEFAULT_RADIUS = 1.0E-6;

AutLib::CadLib::Cad3d_Plane::Cad3d_Plane()
	: theTolerance_(0)
	, theOutterWire_(NULL)
	, theName_("Unknown")
{
}

AutLib::CadLib::Cad3d_Plane::~Cad3d_Plane()
{
	FreeMemory(theCorners_);
	FreeMemory(theEdges_);

	FreeMemory(theInnerWires_);
	FreePointer(theOutterWire_);
}

Entity_Box2d AutLib::CadLib::Cad3d_Plane::BoundingBox(const Standard_Real Offset) const
{
	Debug_Null_Pointer(theOutterWire_);

	Entity_Box2d Box = theOutterWire_->BoundingBox();
	Box = Box.OffsetBox(Offset);
	MOVE(Box);
}

Entity_StaticChain2d AutLib::CadLib::Cad3d_Plane::UniDiscrete(const Standard_Integer NbSegments) const
{
	if (NbSegments < 1) { THROW_STANDARD_EXCEPTION("Invalid Nb. of segments"); }

	TColCad3d_HAry1dOfCurveOnPlane Curves;
	RetrieveCurvesTo(Curves);

	const Standard_Integer NbCurves = Curves.Size();

	Debug_If_Condition_Message(NbCurves < 1, " The plane has no curve");

	TColEntity_HAry1dOfStaticChain2d Chains(NbCurves);
	forThose(Index, 0, MaxIndexOf(Curves))
	{
		Debug_Null_Pointer(Curves[Index]);

		Chains[Index] = new Entity_StaticChain2d;
		Chains[Index]->Init(Curves[Index]->UniformParametricDiscretize(NbSegments).Points(), Entity_EdgeIndexTools::OrderedList(NbSegments));
	}

	Merge_Chain2d Merge(DEFAULT_RESOLUTION, DEFAULT_RADIUS);

	Merge.Import(Chains);
	Merge.Perform();

	Debug_If_Condition_Message(NOT Merge.IsDone(), " Merging is not Performed");

	FreeMemory(Chains);

	return *Merge.Merged();
}

Standard_Integer AutLib::CadLib::Cad3d_Plane::NbFreeCorners() const
{
	Get_Const_Object(Corners) = Cad3d_Plane::Corners();

	forThose
	(
		Index,
		0,
		MaxIndexOf(Corners)
	)
	{
		Debug_Null_Pointer(Corners[Index]);
		if (Corners[Index]->IsFree()) return Standard_True;
	}
	return Standard_False;
}

Standard_Boolean AutLib::CadLib::Cad3d_Plane::HasFreeCorner() const
{
	Get_Const_Object(Corners) = Cad3d_Plane::Corners();
	forThose
	(
		Index, 
		0, 
		MaxIndexOf(Corners)
	)
	{
		Debug_Null_Pointer(Corners[Index]);
		if (Corners[Index]->IsFree()) return Standard_True;
	}
	return Standard_False;
}

Standard_Boolean AutLib::CadLib::Cad3d_Plane::CheckOrientations(const Standard_Boolean Reversed) const
{
	Cad3d_WireOnPlaneOrientationInfo InnerOrient = Cad3d_WireOnPlaneOrientation_CW;
	if (Reversed) InnerOrient = Cad3d_WireOnPlaneOrientation_CCW;

	Cad3d_WireOnPlaneOrientationInfo OutterOrient = Cad3d_WireOnPlaneOrientation_CCW;
	if (Reversed) OutterOrient = Cad3d_WireOnPlaneOrientation_CW;

	if (NOT theOutterWire_) { THROW_STANDARD_EXCEPTION("Empty outter wire"); }
	if (theOutterWire_->Orientation() NOT_EQUAL OutterOrient) return Standard_True;

	forThose
	(
		Index,
		0, 
		MaxIndexOf(theInnerWires_)
	)
	{
		Debug_Null_Pointer(theInnerWires_[Index]);
		if (theInnerWires_[Index]->Orientation() NOT_EQUAL InnerOrient) return Standard_True;
	}
	return Standard_False;
}

void AutLib::CadLib::Cad3d_Plane::Make(const TColCad3d_HAry1dOfEdgeOnPlane & theEdges)
{
	theEdges_ = theEdges;
	theCorners_ = Cad3d_EdgeOnPlaneTools::RetrievePointsFrom(theEdges);

	Cad3d_Plane::CreateWires(theEdges);
}

void AutLib::CadLib::Cad3d_Plane::Make
(
	const TColCad3d_HAry1dOfCurveOnPlane & theCurves, 
	const Standard_Real theTolerance
)
{
	Cad3d_Plane::Make(Cad3d_EdgeOnPlaneTools::MakeEdges(theCurves, theTolerance));

	theTolerance_ = theTolerance;
}

void AutLib::CadLib::Cad3d_Plane::SetName(const Standard_String Name)
{
	theName_ = Name;
}

void AutLib::CadLib::Cad3d_Plane::RetrieveCurvesTo(TColCad3d_HAry1dOfCurveOnPlane & theCurves) const
{
	theCurves = Cad3d_EdgeOnPlaneTools::RetrieveCurvesFrom(Edges());
}

void AutLib::CadLib::Cad3d_Plane::ExportToPlt(fstream & File) const
{
	Get_Const_Object(Edges) = Cad3d_Plane::Edges();

	forThose
	(
		Index,
		0, 
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		Edges[Index]->ExportToPlt(File);
	}
}

void AutLib::CadLib::Cad3d_Plane::ExportWiresToPlt(fstream & File) const
{
	if (theOutterWire_) theOutterWire_->ExportToPlt(File);
	forThose(Index, 0, MaxIndexOf(theInnerWires_))
		if (theInnerWires_[Index]) theInnerWires_[Index]->ExportToPlt(File);
}

void AutLib::CadLib::Cad3d_Plane::Report(Standard_OStream & Ostream) const
{
	Ostream << "----------------{ Plane Report }----------------" << endl;
	Ostream << endl;
	Ostream << "   Name: " << theName_ << endl;
	Ostream << "   Index: " << theIndex_ << endl;
	Ostream << endl;
	Ostream << "   Nb. of Edges: " << NbEdges() << endl;
	Ostream << "   Nb. of Holes: " << NbHoles() << endl;
	Ostream << endl;
	Ostream << "   Has Free Corner? " << (HasFreeCorner() ? "YES" : "NO") << endl;
	if (HasFreeCorner()) Ostream << "   Nb. of Free Edges: " << NbFreeCorners() << endl;
	Ostream << endl;
	Ostream << "-------------{ End of Plane Report }-------------" << endl;
}

void AutLib::CadLib::Cad3d_Plane::CreateWires(const TColCad3d_HAry1dOfEdgeOnPlane & theEdges)
{
	auto Wires = Cad3d_WireOnPlaneTools::TrackWires(theEdges, theName_);

	if (NOT Cad3d_WireOnPlaneTools::IdentifyBoundaries(Wires, theInnerWires_, theOutterWire_))
	{
		THROW_STANDARD_EXCEPTION("Invalid Plane");
	}
}