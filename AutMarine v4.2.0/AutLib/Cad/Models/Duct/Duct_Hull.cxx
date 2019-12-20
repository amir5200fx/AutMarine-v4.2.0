#include <Duct_Hull.hxx>

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

AutLib::CadLib::Duct_Hull::Duct_Hull()
	: theIgesSectionFileName_("MySectionsOfHull.igs")
{
	DefaultParameters();

	theSystem_ = gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
}

AutLib::CadLib::Duct_Hull::~Duct_Hull()
{
	FreePointer(theControlNet_);
}

void AutLib::CadLib::Duct_Hull::Make()
{
	AllocateMemory();

	Try_Exception_Handle_Exit(CalcxXSections());

	CreateProfiles();

	CalcxParameters();

	CreateSections();

	Try_Exception_Handle_Exit(SetupControlNet());

	SetupPatch();

	MakeFace();

	if (toDiscrete_)
	{
		Cad3d_MarineModel::DiscreteMyModel();
	}

	IsDone_ = Standard_True;
}

void AutLib::CadLib::Duct_Hull::AllocateMemory()
{
	const Duct_Dimensions & Dimensions = theParameters_.Dimensions();

	Standard_Integer nbSections = Dimensions.NbSections();
	Standard_Integer nbRows = 11;

	theXParameters_.AllocateMemory(nbSections);

	theControlNet_ = new TColgp_Array2OfPnt(1, nbSections, 1, nbRows);
	theWeightNet_ = new TColStd_Array2OfReal(1, nbSections, 1, nbRows);

	theSections_.Resize(nbSections);

	theProfiles_.SetMemory(nbSections);
}

void AutLib::CadLib::Duct_Hull::MakeFace()
{
	myModel_ = BRepBuilderAPI_MakeFace(theHull_, 1.0E-6);

	gp_Ax2 A2(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0));

	Handle(Geom_BSplineSurface) Hull = Handle(Geom_BSplineSurface)::DownCast(theHull_);
	Debug_If_Condition_Message(Hull.IsNull(), "Invalid Data");

	Handle(Geom_BSplineSurface) Pair = new Geom_BSplineSurface
	(
		Hull->Poles(),
		*Hull->Weights(),
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
}