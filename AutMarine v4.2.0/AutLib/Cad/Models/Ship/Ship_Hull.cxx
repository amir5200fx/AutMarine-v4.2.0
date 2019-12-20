#include <Ship_Hull.hxx>

#include <Geom_Pnt3d.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_SolidTools.hxx>
#include <Ship_ConstParameters.hxx>
#include <Ship_SectionControlPoints.hxx>
#include <IO_Tecplot.hxx>

using namespace AutLib;
using namespace CadLib;

#include <gp_Ax2.hxx>
#include <gp_Pln.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom_BSplineSurface.hxx>
#include <GeomFill_BSplineCurves.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <BRep_Builder.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepOffsetAPI_Sewing.hxx>
#include <BRepAlgoAPI_Section.hxx>
#include <BRep_Tool.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Compound.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Solid.hxx>
#include <TopExp_Explorer.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_Array1OfReal.hxx>
#include <TColgp_Array1OfPnt2d.hxx>
#include <TColGeom_Array1OfBSplineCurve.hxx>

AutLib::CadLib::Ship_Hull::Ship_Hull()
	: theIgesSectionFileName_("MySectionsOfHull.igs")
{
	DefaultParameters();

	theSystem_ = gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
}

AutLib::CadLib::Ship_Hull::~Ship_Hull()
{
	FreePointer(theControlNet_);
}

Global_Handle(Cad3d_Solid) AutLib::CadLib::Ship_Hull::GetSolid() const
{
	Global_Handle(Cad3d_Solid) Solid = new Cad3d_Solid;
	Cad3d_SolidTools::MakeSolid(myModel_, *Solid);
	Solid->SetName(theName_);
	return Solid;
}

TopoDS_Shape AutLib::CadLib::Ship_Hull::GetStation(const Standard_Real theX) const
{
	BRepAlgoAPI_Section Section(myModel_, gp_Pln(gp_Pnt(theX, 0, 0), gp_Dir(1, 0, 0)));
	return Section.Shape();
}

TopoDS_Shape AutLib::CadLib::Ship_Hull::GetButtock(const Standard_Real theY) const
{
	BRepAlgoAPI_Section Section(myModel_, gp_Pln(gp_Pnt(0, theY, 0), gp_Dir(0, 1, 0)));
	return Section.Shape();
}

TopoDS_Shape AutLib::CadLib::Ship_Hull::GetWater(const Standard_Real theZ) const
{
	BRepAlgoAPI_Section Section(myModel_, gp_Pln(gp_Pnt(0, 0, theZ), gp_Dir(0, 0, 1)));
	return Section.Shape();
}

void AutLib::CadLib::Ship_Hull::CalcMyStations
(
	const Standard_Integer theNbSections,
	const Standard_Real theXmin, 
	const Standard_Real theXmax
)
{
	Standard_Real DX = theXmax - theXmin;
	if (DX <= 0) THROW_STANDARD_EXCEPTION("Invalid Data");
	if (theNbSections < 3) THROW_STANDARD_EXCEPTION("Invalid Nb. of Sections");

	BRep_Builder Builder;
	TopoDS_Compound Compound;
	Builder.MakeCompound(Compound);
	if (NOT mySections_.IsNull()) Builder.Add(Compound, mySections_);
	Standard_Real dx = DX / (Standard_Real)(theNbSections - 1);
	forThose
	(
		Index,
		0, 
		theNbSections - 1
	)
	{
		Standard_Real X = theXmin + Index*dx;
		TopoDS_Shape Shape = GetStation(X);
		if (Shape.IsNull()) continue;
		Builder.Add(Compound, Shape);
	}
	mySections_ = Compound;
}

void AutLib::CadLib::Ship_Hull::CalcMyButtocks
(
	const Standard_Integer theNbSections,
	const Standard_Real theYmin,
	const Standard_Real theYmax
)
{
	Standard_Real DX = theYmax - theYmin;
	if (DX <= 0) THROW_STANDARD_EXCEPTION("Invalid Data");
	if (theNbSections < 3) THROW_STANDARD_EXCEPTION("Invalid Nb. of Sections");

	BRep_Builder Builder;
	TopoDS_Compound Compound;
	Builder.MakeCompound(Compound);
	if (NOT mySections_.IsNull()) Builder.Add(Compound, mySections_);
	Standard_Real dx = DX / (Standard_Real)(theNbSections - 1);
	forThose
	(
		Index,
		0,
		theNbSections - 1
	)
	{
		Standard_Real X = theYmin + Index*dx;
		TopoDS_Shape Shape = GetButtock(X);
		if (Shape.IsNull()) continue;
		Builder.Add(Compound, Shape);
	}
	mySections_ = Compound;
}

void AutLib::CadLib::Ship_Hull::CalcMyWaters
(
	const Standard_Integer theNbSections, 
	const Standard_Real theZmin, 
	const Standard_Real theZmax
)
{
	Standard_Real DX = theZmax - theZmin;
	if (DX <= 0) THROW_STANDARD_EXCEPTION("Invalid Data");
	if (theNbSections < 3) THROW_STANDARD_EXCEPTION("Invalid Nb. of Sections");

	BRep_Builder Builder;
	TopoDS_Compound Compound;
	Builder.MakeCompound(Compound);
	if (NOT mySections_.IsNull()) Builder.Add(Compound, mySections_);
	Standard_Real dx = DX / (Standard_Real)(theNbSections - 1);
	forThose
	(
		Index,
		0,
		theNbSections - 1
	)
	{
		Standard_Real X = theZmin + Index*dx;
		TopoDS_Shape Shape = GetWater(X);
		if (Shape.IsNull()) continue;
		Builder.Add(Compound, Shape);
	}
	mySections_ = Compound;
}

void AutLib::CadLib::Ship_Hull::Make()
{
	AllocateMemory();

	Try_Exception_Handle_Exit(CalcxXSections());

	CalcxParameters();

	CreateRawSections();

	ApplyParameters();

	Try_Exception_Handle_Exit(SetupControlNet());

	SetupPatch();

	MakeFace();

	if (toSolid_)
	{
		MakeSolid();
	}

	if (toDiscrete_)
	{
		Cad3d_MarineModel::DiscreteMyModel();
	}

	IsDone_ = Standard_True;
}

void AutLib::CadLib::Ship_Hull::ExportMySectionsToPlt(fstream & File) const
{
	for (TopExp_Explorer Explorer(mySections_, TopAbs_EDGE); Explorer.More(); Explorer.Next())
	{
		TopLoc_Location Loc;
		TopoDS_Edge Edge = TopoDS::Edge(Explorer.Current());

		if (Edge.IsNull()) continue;

		M_IO IO_TecPlot::ExportCurve(Edge, 40, File);
	}
}

void AutLib::CadLib::Ship_Hull::ExportMySectionsToIGES() const
{
	IGESControl_Controller::Init();

	IGESControl_Writer Writer("MM", 0);
	Writer.AddShape(mySections_);
	Writer.ComputeModel();

	Standard_Boolean OK = Writer.Write(theIgesSectionFileName_.c_str());
}

void AutLib::CadLib::Ship_Hull::AllocateMemory()
{
	const Ship_Dimensions & Dimensions = theParameters_.Dimensions();

	Standard_Integer nbSections = Dimensions.NbNetColumns();
	Standard_Integer nbRows = Dimensions.NbNetRows();

	theXParameters_.AllocateMemory(nbSections);

	theControlNet_ = new TColgp_Array2OfPnt(1, nbSections, 1, nbRows);

	theSections_.Resize(nbSections);

	theProfiles_.SetMemory(nbSections - 2);
}

void AutLib::CadLib::Ship_Hull::SetSection(const Standard_Integer Index, Global_Handle(Ship_SectionControlPoints) Section)
{
	Try_Exception_Handle_Exit(theSections_[Index] = Section);
}

void AutLib::CadLib::Ship_Hull::SetControlPoint(const Standard_Integer I, const Standard_Integer J, const Geom_Pnt3d & Coord)
{
	theControlNet_->SetValue(I + 1, J + 1, Coord);
}

void AutLib::CadLib::Ship_Hull::MakeFace()
{
	myModel_ = BRepBuilderAPI_MakeFace(theHull_, 1.0E-6);

	gp_Ax2 A2(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0));

	Handle(Geom_BSplineSurface) Hull = Handle(Geom_BSplineSurface)::DownCast(theHull_);
	Debug_If_Condition_Message(Hull.IsNull(), "Invalid Data");

	Handle(Geom_BSplineSurface) Pair = new Geom_BSplineSurface
	(
		Hull->Poles(),
		Hull->UKnots(),
		Hull->VKnots(),
		Hull->UMultiplicities(),
		Hull->VMultiplicities(),
		Hull->UDegree(),
		Hull->VDegree()
	);
	Pair->Mirror(A2);

	TopoDS_Shape PairShape = BRepBuilderAPI_MakeFace(Pair, 1.0E-6);
	PairShape.Reverse();

	myModel_ = BRepAlgoAPI_Fuse(myModel_, PairShape);

	TColGeom_Array1OfBSplineCurve Curves(1, 8);
	Standard_Integer K = 0;
	for (TopExp_Explorer Explorer(myModel_, TopAbs_EDGE); Explorer.More(); Explorer.Next())
	{
		TopoDS_Edge Edge = TopoDS::Edge(Explorer.Current());
		TopLoc_Location Loc;
		Standard_Real First, Last;
		Handle(Geom_Curve) Curve = BRep_Tool::Curve(Edge, First, Last);

		Handle(Geom_BSplineCurve) BSplCurve = Handle(Geom_BSplineCurve)::DownCast(Curve);

		if (BSplCurve.IsNull()) { THROW_STANDARD_EXCEPTION(" Null Curve"); }

		Curves.SetValue(++K, BSplCurve);
	}

	GeomFill_BSplineCurves Transom(Curves.Value(1), Curves.Value(5), GeomFill_CoonsStyle);
	myModel_ = BRepAlgoAPI_Fuse(myModel_, BRepBuilderAPI_MakeFace(Transom.Surface(), 1.0E-6));

	GeomFill_BSplineCurves Deck(Curves.Value(3), Curves.Value(7), GeomFill_CoonsStyle);
	myModel_ = BRepAlgoAPI_Fuse(myModel_, BRepBuilderAPI_MakeFace(Deck.Surface(), 1.0E-6));

	//myModel_.Reverse();
}

void AutLib::CadLib::Ship_Hull::MakeSolid()
{
	BRepOffsetAPI_Sewing Sewing;
	Sewing.Add(myModel_);
	Sewing.Perform();

	TopoDS_Shape Sewed = Sewing.SewedShape();

	BRepBuilderAPI_MakeSolid brep_solid(TopoDS::Shell(Sewed));
	myModel_ = brep_solid.Solid();

	//myModel_.Compose(TopAbs_Orientation::TopAbs_EXTERNAL);
}