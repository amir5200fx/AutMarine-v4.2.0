#include <Cad2d_Plane.hxx>

#include <Geometry_Tools.hxx>
#include <Entity_Box2d.hxx>
#include <Entity_Box2dTools.hxx>
#include <Entity_Polygon2d.hxx>
#include <Entity_StaticChain2d.hxx>
#include <Entity_EdgeIndexTools.hxx>
#include <Merge_Chain2d.hxx>
#include <Cad2d_CurveOnPlane.hxx>
#include <Cad2d_WireOnPlane.hxx>
#include <Cad2d_PointOnPlane.hxx>
#include <Cad2d_PointsOnPlane.hxx>
#include <Cad2d_BlockPointOnPlane.hxx>
#include <Cad2d_EdgesOnPlane.hxx>
#include <Cad2d_BlockEdgeOnPlane.hxx>
#include <Cad2d_EdgeOnPlaneTools.hxx>
#include <Cad2d_WireOnPlaneTools.hxx>
#include <TColEntity_HAry1dOfStaticChain2d.hxx>
#include <TColCad2d_HNumbAvlTreeOfEdgeOnPlane.hxx>
#include <TColCad2d_HAry1dOfWireOnPlane.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

#include <gp_Trsf2d.hxx>
#include <gp_Ax22d.hxx>
#include <Geom2d_Curve.hxx>

static const Standard_Real DEFAULT_RESOLUTION = 1.0E-3;
static const Standard_Real DEFAULT_RADIUS = 1.0E-6;

AutLib::CadLib::Cad2d_Plane::Cad2d_Plane()
	: theTolerance_(0)
	, theOutterWire_(NULL)
	, theName_("Unknown")
{
}

AutLib::CadLib::Cad2d_Plane::~Cad2d_Plane()
{
	/*TColCad2d_HAry1dOfPointOnPlane Corners;
	RetrieveCornersTo(Corners);

	TColCad2d_HAry1dOfEdgeOnPlane Edges;
	RetrieveEdgesTo(Edges);*/

	//FreeMemory(Corners);
	//FreeMemory(Edges);

	if (theCorners_) { FreePointer(theCorners_); }
	if (theEdges_) { FreePointer(theEdges_); }
}

Entity_Box2d AutLib::CadLib::Cad2d_Plane::BoundingBox(const Standard_Real Offset) const
{
	/*TColCad2d_HAry1dOfCurveOnPlane Curves;
	RetrieveCurvesTo(Curves);

	Entity_Box2d Box(0, 0, 0, 0);
	forThose
	(
		Index,
		0,
		MaxIndexOf(Curves)
	)
	{
		Debug_Null_Pointer(Curves[Index]);

		Box = Entity_Box2dTools::Union(Box, Curves[Index]->BoundingBox());
	}*/

	Debug_Null_Pointer(theOutterWire_);

	Entity_Box2d Box = theOutterWire_->BoundingBox();
	Box = Box.OffsetBox(Offset);
	MOVE(Box);
}

Entity_StaticChain2d AutLib::CadLib::Cad2d_Plane::UniDiscrete(const Standard_Integer NbSegments) const
{
	if (NbSegments < 1) { THROW_STANDARD_EXCEPTION("Invalid Nb. of segments"); }

	TColCad2d_HAry1dOfCurveOnPlane Curves;
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

Standard_Integer AutLib::CadLib::Cad2d_Plane::NbFreeCorners() const
{
	Standard_Integer K = 0;
	TColCad2d_HAry1dOfPointOnPlane Corners;
	Cad2d_Plane::RetrieveCornersTo(Corners);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Corners)
	)
	{
		Debug_Null_Pointer(Corners[Index]);
		if (Corners[Index]->IsFree()) K++;
	}
	return K;
}

Standard_Boolean AutLib::CadLib::Cad2d_Plane::HasFreeCorner() const
{
	TColCad2d_HAry1dOfPointOnPlane Corners;
	Cad2d_Plane::RetrieveCornersTo(Corners);

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

void AutLib::CadLib::Cad2d_Plane::Make(const TColCad2d_HAry1dOfEdgeOnPlane & theEdges)
{
	TColCad2d_HAry1dOfPointOnPlane Points = Cad2d_EdgeOnPlaneTools::RetrievePointsFrom(theEdges);

	Cad2d_Plane::CreateDefaultPatch(theEdges, "Default Block Edge");
	Cad2d_Plane::CreateDefaultPoints(Points, "Default Block Point");

	Try_Exception_Handle_Exit(Cad2d_Plane::CreateWires(theEdges));

	Cad2d_Plane::SplitByWires();
}

void AutLib::CadLib::Cad2d_Plane::Make
(
	const TColCad2d_HAry1dOfCurveOnPlane & theCurves, 
	const Standard_Real theTolerance
)
{
	Cad2d_Plane::Make(Cad2d_EdgeOnPlaneTools::MakeEdges(theCurves, theTolerance));

	theTolerance_ = theTolerance;
}

void AutLib::CadLib::Cad2d_Plane::Make
(
	const gp_Ax22d& A,
	const TColCad2d_HAry1dOfCurveOnPlane& theCurves,
	const Standard_Real theTolerance
)
{
	gp_Trsf2d Transform;
	Transform.SetTransformation(A.XAxis(), gp::OX2d());

	forThose
	(
		Index,
		0,
		MaxIndexOf(theCurves)
	)
	{
		Debug_Null_Pointer(theCurves[Index]);

		Handle(Geom2d_Curve) Curve = (Handle(Geom2d_Curve))(theCurves[Index]->Curve());
		Curve->Transform(Transform);
	}

	Make(theCurves);
}

void AutLib::CadLib::Cad2d_Plane::Make
(
	const gp_Ax2d & A,
	const TColCad2d_HAry1dOfCurveOnPlane & theCurves,
	const Standard_Boolean Sense,
	const Standard_Real theTolerance
)
{
	Make(gp_Ax22d(A, Sense), theCurves);
}

void AutLib::CadLib::Cad2d_Plane::SetName(const Standard_String Name)
{
	theName_ = Name;
}

void AutLib::CadLib::Cad2d_Plane::RetrieveCurvesTo(TColCad2d_HAry1dOfCurveOnPlane & theCurves) const
{
	TColCad2d_HAry1dOfEdgeOnPlane Edges;
	Cad2d_Plane::RetrieveEdgesTo(Edges);

	theCurves = Cad2d_EdgeOnPlaneTools::RetrieveCurvesFrom(Edges);
}

void AutLib::CadLib::Cad2d_Plane::CreateSharpCornerBlock
(
	const Standard_Real theSharpAngle,
	const Standard_String theBlockName
)
{
	if (theCorners_->NbBlocks() > 1)
	{
		theCorners_->CompactBlocks("Deafult Block Point");
	}

	TColCad2d_HAry1dOfBlockPointOnPlane Blocks;
	theCorners_->RetrieveTo(Blocks);

	Debug_If_Condition(Blocks.Size() NOT_EQUAL 1);
	theCorners_->SelectBlockPoint(Blocks[0]->Name());
	Blocks[0]->SelectSharpCorners(theSharpAngle);

	theCorners_->Split(theBlockName);

	theCorners_->RemoveEmptyBlocks();
}

void AutLib::CadLib::Cad2d_Plane::SplitByWires()
{
	if (theEdges_->NbBlocks() > 1) { theEdges_->CompactBlocks("Deafult Block Curve"); }
	if (theEdges_->NbBlocks() NOT_EQUAL 1) { THROW_STANDARD_EXCEPTION("Invalid Data"); }
	if (theInnerWires_.IsEmpty()) { return; }

	TColCad2d_HAry1dOfBlockEdgeOnPlane Blocks;
	theEdges_->RetrieveTo(Blocks);

	Debug_If_Condition_Message(Blocks.Size() NOT_EQUAL 1, "Conflict Data");
	Get_Const_Pointer(Block) = theEdges_->SelectBlockCurve(Blocks[0]->Name());

	forThose
	(
		Index,
		0,
		MaxIndexOf(theInnerWires_)
	)
	{
		Debug_Null_Pointer(theInnerWires_[Index]);
		Get_Const_Object(Edges) = theInnerWires_[Index]->Edges();

		forThose
		(
			I,
			0,
			MaxIndexOf(Edges)
		)
		{
			Debug_Null_Pointer(Edges[I]);
			Block->SelectCurve(Edges[I]->Index());
		}
		theEdges_->Split("Default Inner Block " + std::to_string(Index + 1));
		Block = theEdges_->SelectBlockCurve(Blocks[0]->Name());
	}

	theEdges_->UnSelectAll();
	if (NOT Block->Size()) { THROW_STANDARD_EXCEPTION("Conflict Data"); }
}

void AutLib::CadLib::Cad2d_Plane::Mirror(const gp_Pnt2d & P)
{
	TColCad2d_HAry1dOfCurveOnPlane Curves;
	RetrieveCurvesTo(Curves);
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Curves)
	)
	{
		Debug_Null_Pointer(Curves[Index]);
		Curves[Index]->Mirror(P);
	}

	TColCad2d_HAry1dOfPointOnPlane Points;
	RetrieveCornersTo(Points);
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Points)
	)
	{
		Debug_Null_Pointer(Points[Index]);
		Points[Index]->Mirror(P);
	}
}

void AutLib::CadLib::Cad2d_Plane::Mirror(const gp_Ax2d & A)
{
	TColCad2d_HAry1dOfCurveOnPlane Curves;
	RetrieveCurvesTo(Curves);
	forThose
	(
		Index,
		0,
		MaxIndexOf(Curves)
	)
	{
		Debug_Null_Pointer(Curves[Index]);
		Curves[Index]->Mirror(A);
	}

	TColCad2d_HAry1dOfPointOnPlane Points;
	RetrieveCornersTo(Points);
	forThose
	(
		Index,
		0,
		MaxIndexOf(Points)
	)
	{
		Debug_Null_Pointer(Points[Index]);
		Points[Index]->Mirror(A);
	}
}

void AutLib::CadLib::Cad2d_Plane::Rotate
(
	const gp_Pnt2d & P,
	const Standard_Real Ang
)
{
	TColCad2d_HAry1dOfCurveOnPlane Curves;
	RetrieveCurvesTo(Curves);
	forThose
	(
		Index,
		0,
		MaxIndexOf(Curves)
	)
	{
		Debug_Null_Pointer(Curves[Index]);
		Curves[Index]->Rotate(P, Ang);
	}

	TColCad2d_HAry1dOfPointOnPlane Points;
	RetrieveCornersTo(Points);
	forThose
	(
		Index,
		0,
		MaxIndexOf(Points)
	)
	{
		Debug_Null_Pointer(Points[Index]);
		Points[Index]->Rotate(P, Ang);
	}
}

void AutLib::CadLib::Cad2d_Plane::Scale
(
	const gp_Pnt2d & P,
	const Standard_Real S
)
{
	TColCad2d_HAry1dOfCurveOnPlane Curves;
	RetrieveCurvesTo(Curves);
	forThose
	(
		Index,
		0,
		MaxIndexOf(Curves)
	)
	{
		Debug_Null_Pointer(Curves[Index]);
		Curves[Index]->Scale(P, S);
	}

	TColCad2d_HAry1dOfPointOnPlane Points;
	RetrieveCornersTo(Points);
	forThose
	(
		Index,
		0,
		MaxIndexOf(Points)
	)
	{
		Debug_Null_Pointer(Points[Index]);
		Points[Index]->Scale(P, S);
	}
}

void AutLib::CadLib::Cad2d_Plane::Translate(const gp_Vec2d & V)
{
	TColCad2d_HAry1dOfCurveOnPlane Curves;
	RetrieveCurvesTo(Curves);
	forThose
	(
		Index,
		0,
		MaxIndexOf(Curves)
	)
	{
		Debug_Null_Pointer(Curves[Index]);
		Curves[Index]->Translate(V);
	}

	TColCad2d_HAry1dOfPointOnPlane Points;
	RetrieveCornersTo(Points);
	forThose
	(
		Index,
		0,
		MaxIndexOf(Points)
	)
	{
		Debug_Null_Pointer(Points[Index]);
		Points[Index]->Translate(V);
	}
}

void AutLib::CadLib::Cad2d_Plane::Translate
(
	const gp_Pnt2d & P1, 
	const gp_Pnt2d & P2
)
{
	TColCad2d_HAry1dOfCurveOnPlane Curves;
	RetrieveCurvesTo(Curves);
	forThose
	(
		Index,
		0,
		MaxIndexOf(Curves)
	)
	{
		Debug_Null_Pointer(Curves[Index]);
		Curves[Index]->Translate(P1, P2);
	}

	TColCad2d_HAry1dOfPointOnPlane Points;
	RetrieveCornersTo(Points);
	forThose
	(
		Index,
		0,
		MaxIndexOf(Points)
	)
	{
		Debug_Null_Pointer(Points[Index]);
		Points[Index]->Translate(P1, P2);
	}
}

void AutLib::CadLib::Cad2d_Plane::Transform(const gp_Trsf2d & T)
{
	TColCad2d_HAry1dOfCurveOnPlane Curves;
	RetrieveCurvesTo(Curves);
	forThose
	(
		Index,
		0,
		MaxIndexOf(Curves)
	)
	{
		Debug_Null_Pointer(Curves[Index]);
		Curves[Index]->Transform(T);
	}

	TColCad2d_HAry1dOfPointOnPlane Points;
	RetrieveCornersTo(Points);
	forThose
	(
		Index,
		0,
		MaxIndexOf(Points)
	)
	{
		Debug_Null_Pointer(Points[Index]);
		Points[Index]->Transform(T);
	}
}

void AutLib::CadLib::Cad2d_Plane::ExportToPlt(fstream & File) const
{
	TColCad2d_HAry1dOfEdgeOnPlane Edges;
	RetrieveEdgesTo(Edges);

	forThose(Index, 0, MaxIndexOf(Edges))
	{
		Debug_Null_Pointer(Edges[Index]);

		Edges[Index]->ExportToPlt(File);
	}
}

void AutLib::CadLib::Cad2d_Plane::Report(Standard_OStream & Ostream) const
{
	Ostream << "----------------{ Plane Report }----------------" << endl;
	Ostream << endl;
	Ostream << "   Name: " << theName_ << endl;
	Ostream << "   Index: " << theIndex_ << endl;
	Ostream << endl;
	Ostream << "   Nb. of Edges: " << NbEdges() << endl;
	Ostream << "   Nb. of Points: " << NbCorners() << endl;
	Ostream << "   Nb. of Holes: " << NbHoles() << endl;
	Ostream << endl;
	Ostream << "   Has Free Corner? " << (HasFreeCorner() ? "YES" : "NO") << endl;
	if (HasFreeCorner()) Ostream << "   Nb. of Free Edges: " << NbFreeCorners() << endl;
	Ostream << endl;
	Ostream << "-------------{ End of Plane Report }-------------" << endl;
}

Global_Handle(Cad2d_Plane) AutLib::CadLib::Cad2d_Plane::Copy() const
{
	TColCad2d_HAry1dOfCurveOnPlane Curves;
	RetrieveCurvesTo(Curves);

	TColCad2d_HAry1dOfCurveOnPlane CopyCurves(Curves.Size());
	forThose(Index, 0, MaxIndexOf(Curves))
		CopyCurves[Index] = Curves[Index]->Copy();

	TColCad2d_HAry1dOfEdgeOnPlane Edges = Cad2d_EdgeOnPlaneTools::MakeEdges(CopyCurves, theTolerance_);

	TColCad2d_IndexedMapOfEdgeOnPlane IndexedEdges;
	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		std::pair<TColCad2d_IndexedMapOfEdgeOnPlane::iterator, Standard_Boolean> Insert;
		Insert = IndexedEdges.insert(std::pair<Standard_Integer, Global_Handle(Cad2d_EdgeOnPlane)>(Edges[Index]->Index(), Edges[Index]));

		if (Insert.second EQUAL Standard_False)
		{
			THROW_STANDARD_EXCEPTION(" Duplicate Data");
			return NULL;
		}
	}

	Global_Handle(Cad2d_EdgesOnPlane) CopyEdges = theEdges_->Copy(IndexedEdges);

	TColCad2d_HAry1dOfPointOnPlane Points = Cad2d_EdgeOnPlaneTools::RetrievePointsFrom(Edges);

	TColCad2d_IndexedMapOfPointOnPlane IndexedPoints;
	forThose
	(
		Index,
		0,
		MaxIndexOf(Points)
	)
	{
		Debug_Null_Pointer(Points[Index]);

		std::pair<TColCad2d_IndexedMapOfPointOnPlane::iterator, Standard_Boolean> Insert;
		Insert = IndexedPoints.insert(std::pair<Standard_Integer, Global_Handle(Cad2d_PointOnPlane)>(Points[Index]->Index(), Points[Index]));

		if (Insert.second EQUAL Standard_False)
		{
			THROW_STANDARD_EXCEPTION(" Duplicate Data");
			return NULL;
		}
	}

	Global_Handle(Cad2d_PointsOnPlane) CopyPoints = theCorners_->Copy(IndexedPoints);

	Global_Handle(Cad2d_Plane) Copy = new Cad2d_Plane;
	Copy->theCorners_ = CopyPoints;
	Copy->theEdges_ = CopyEdges;
	Copy->theIndex_ = theIndex_;
	Copy->theName_ = theName_;

	Copy->CreateWires(Edges);

	return Copy;
}

//Global_Handle(Cad2d_Plane) AutLib::CadLib::Cad2d_Plane::Copy() const
//{
//	Global_Handle(Cad2d_WireOnPlane) OutterWire = theOutter_->Copy();
//	Debug_Null_Pointer(OutterWire);
//
//	TColCad2d_HAry1dOfWireOnPlane Inner(theInner_.Size());
//	forThose
//	(
//		Index,
//		0,
//		MaxIndexOf(Inner)
//	)
//	{
//		Debug_Null_Pointer(theInner_[Index]);
//		Inner[Index] = theInner_[Index]->Copy();
//	}
//
//	TColCad2d_HBasicQueueOfEdgeOnPlane QEdges;
//	QEdges.EnQueue(OutterWire->Edges());
//
//	forThose
//	(
//		Index,
//		0,
//		MaxIndexOf(Inner)
//	)
//	{
//		Debug_Null_Pointer(Inner[Index]);
//		QEdges.EnQueue(Inner[Index]->Edges());
//	}
//	TColCad2d_HAry1dOfEdgeOnPlane Edges;
//	QEdges.RetrieveTo(Edges);
//
//	TColCad2d_IndexedMapOfEdgeOnPlane IndexedEdges;
//	forThose
//	(
//		Index,
//		0,
//		MaxIndexOf(Edges)
//	)
//	{
//		Debug_Null_Pointer(Edges[Index]);
//
//		std::pair<TColCad2d_IndexedMapOfEdgeOnPlane::iterator, Standard_Boolean> Insert;
//		Insert = IndexedEdges.insert(std::pair<Standard_Integer, Global_Handle(Cad2d_EdgeOnPlane)>(Edges[Index]->Index(), Edges[Index]));
//
//		if (Insert.second EQUAL Standard_False)
//		{
//			THROW_STANDARD_EXCEPTION(" Duplicate Data");
//			return NULL;
//		}
//	}
//
//	Global_Handle(Cad2d_EdgesOnPlane) CopyEdges = theEdges_->Copy(IndexedEdges);
//
//	TColCad2d_HAry1dOfPointOnPlane Points = Cad2d_EdgeOnPlaneTools::RetrievePointsFrom(Edges);
//
//	TColCad2d_IndexedMapOfPointOnPlane IndexedPoints;
//	forThose
//	(
//		Index,
//		0,
//		MaxIndexOf(Points)
//	)
//	{
//		Debug_Null_Pointer(Points[Index]);
//
//		std::pair<TColCad2d_IndexedMapOfPointOnPlane::iterator, Standard_Boolean> Insert;
//		Insert = IndexedPoints.insert(std::pair<Standard_Integer, Global_Handle(Cad2d_PointOnPlane)>(Points[Index]->Index(), Points[Index]));
//
//		if (Insert.second EQUAL Standard_False)
//		{
//			THROW_STANDARD_EXCEPTION(" Duplicate Data");
//			return NULL;
//		}
//	}
//
//	Global_Handle(Cad2d_PointsOnPlane) CopyPoints = theCorners_->Copy(IndexedPoints);
//
//	Global_Handle(Cad2d_Plane) Copy = new Cad2d_Plane;
//	Copy->theCorners_ = CopyPoints;
//	Copy->theEdges_ = CopyEdges;
//	Copy->theIndex_ = theIndex_;
//	Copy->theInner_ = Inner;
//	Copy->theName_ = theName_;
//	Copy->theOutter_ = OutterWire;
//
//	return Copy;
//}

void AutLib::CadLib::Cad2d_Plane::CreateDefaultPatch
(
	const TColCad2d_HAry1dOfEdgeOnPlane & Curves,
	const Standard_String theName
)
{
	Global_Handle(Cad2d_BlockEdgeOnPlane) DefaultBlock = new Cad2d_BlockEdgeOnPlane(Curves, theName);

	theEdges_ = new Cad2d_EdgesOnPlane(DefaultBlock, DefaultBlock->Name());
}

void AutLib::CadLib::Cad2d_Plane::CreateDefaultPoints
(
	const TColCad2d_HAry1dOfPointOnPlane & Points,
	const Standard_String theName
)
{
	Global_Handle(Cad2d_BlockPointOnPlane) DefaultBlock = new Cad2d_BlockPointOnPlane(Points, theName);

	theCorners_ = new Cad2d_PointsOnPlane(DefaultBlock, DefaultBlock->Name());
}

void AutLib::CadLib::Cad2d_Plane::CreateWires(const TColCad2d_HAry1dOfEdgeOnPlane & theEdges)
{
	auto Wires = Cad2d_WireOnPlaneTools::TrackWires(theEdges);

	if (NOT Cad2d_WireOnPlaneTools::IdentifyBoundaries(Wires, theInnerWires_, theOutterWire_))
	{
		THROW_STANDARD_EXCEPTION("Invalid Plane");
	}
}