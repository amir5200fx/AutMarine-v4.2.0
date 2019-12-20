#include <Cad3d_MarineModel.hxx>

#include <Global_Debug.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_SolidTools.hxx>
//#include <Cad3d_DatumTools.hxx>
#include <IO_TecPlot.hxx>
#include <IO_IGESRead.hxx>
//#include <TColCad3d_HAry1dOfDatum.hxx>

#include <gp_Trsf.hxx>
#include <gp_Ax3.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include <BRepMesh_FastDiscret.hxx>
#include <BRepGProp.hxx>
#include <GProp_GProps.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>
#include <TopoDS.hxx>
#include <TopExp_Explorer.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace IoLib;

AutLib::CadLib::Cad3d_MarineModel::Cad3d_MarineModel()
	: theName_("UnKnown")
	, theIgesFileName_("MyModel.igs")
	, toDiscrete_(Standard_False)
	, toSolid_(Standard_False)
{
}

AutLib::CadLib::Cad3d_MarineModel::~Cad3d_MarineModel()
{
	/*TColCad3d_HAry1dOfDatum Datum;
	theDatum_.RetrieveTo(Datum);

	FreeMemory(Datum);*/
}

void AutLib::CadLib::Cad3d_MarineModel::Make()
{
	THROW_STANDARD_EXCEPTION("This method is not supposed to be called");
}

Standard_Real AutLib::CadLib::Cad3d_MarineModel::CalcVolume() const
{
	GProp_GProps System;
	BRepGProp::VolumeProperties(myModel_, System);
	return System.Mass();
}

Global_Handle(Cad3d_Solid) AutLib::CadLib::Cad3d_MarineModel::GetSolid
(
	const Standard_Real Deflection,
	const Standard_Real Angle
) const
{
	if (myModel_.IsNull()) return NULL;

	Standard_SStream Temp;
	IGESControl_Controller::Init();

	IGESControl_Writer Writer("MM", 0);
	Writer.AddShape(myModel_);
	Writer.ComputeModel();

	Standard_Boolean OK = Writer.Write("~GetSolid_AutMarine.tmp");

	TopoDS_Shape Shape;
	IO_IGESRead::ReadFileNonDiscretized("~GetSolid_AutMarine.tmp", Shape);

	if (toDiscrete_)
	{
		BRepMesh_FastDiscret::Parameters Params;
		Params.Deflection = Deflection;
		Params.Angle = Angle;

		Bnd_Box Box;
		BRepBndLib::Add(Shape, Box);
		BRepMesh_FastDiscret Mesh(Box, Params);

		Mesh.Perform(Shape);
	}

	std::remove("~GetSolid_AutMarine.tmp");

	Global_Handle(Cad3d_Solid) Solid = new Cad3d_Solid;
	Solid->Make(Cad3d_SolidTools::GetSurfaces(Shape));
	Solid->SetName(theName_);

	return Solid;
}

void AutLib::CadLib::Cad3d_MarineModel::SetName(const Standard_String theName)
{
	theName_ = theName;
}

void AutLib::CadLib::Cad3d_MarineModel::SetIGESFileName(const Standard_String theName)
{
	theIgesFileName_ = theName;
}

void AutLib::CadLib::Cad3d_MarineModel::SetToDiscreteMyModel()
{
	toDiscrete_ = Standard_True;
}

void AutLib::CadLib::Cad3d_MarineModel::SetToMakeAsSolid()
{
	toSolid_ = Standard_True;
}

void AutLib::CadLib::Cad3d_MarineModel::DiscreteMyModel
(
	const Standard_Real Deflection,
	const Standard_Real Angle
)
{
	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = Deflection;
	Params.Angle = Angle;

	Bnd_Box Box;
	BRepBndLib::Add(myModel_, Box);
	BRepMesh_FastDiscret Mesh(Box, Params);

	Mesh.Perform(myModel_);
}

void AutLib::CadLib::Cad3d_MarineModel::TransformTo(const gp_Ax2 & theSystem)
{
	gp_Ax3 System1(theSystem_);
	gp_Ax3 System2(theSystem);

	gp_Trsf Trsf;
	Trsf.SetTransformation(System1, System2);
	Trsf.Invert();

	BRepBuilderAPI_Transform Transform(Trsf);
	Transform.Perform(myModel_, Standard_True);
	myModel_ = Transform.Shape();

	//DiscreteMyModel();

	theSystem_ = theSystem;
}

void AutLib::CadLib::Cad3d_MarineModel::Scale(const Standard_Real theValue)
{
	gp_Trsf Trsf;
	Trsf.SetScale(theSystem_.Location(), theValue);

	BRepBuilderAPI_Transform Transform(Trsf);
	Transform.Perform(myModel_, Standard_True);
	myModel_ = Transform.Shape();
}

void AutLib::CadLib::Cad3d_MarineModel::ExportToIGES() const
{
	IGESControl_Controller::Init();

	IGESControl_Writer Writer("MM", 0);
	Writer.AddShape(myModel_);
	Writer.ComputeModel();

	Standard_Boolean OK = Writer.Write(theIgesFileName_.c_str());
}

void AutLib::CadLib::Cad3d_MarineModel::ExportMyModelToPlt(fstream & File) const
{
	for (TopExp_Explorer Explorer(myModel_, TopAbs_FACE); Explorer.More(); Explorer.Next())
	{
		TopLoc_Location Loc;
		Handle(Poly_Triangulation) Triangulation = BRep_Tool::Triangulation(TopoDS::Face(Explorer.Current()), Loc);

		if (Triangulation.IsNull()) continue;

		M_IO IO_TecPlot::ExportMesh(Triangulation->Nodes(), Triangulation->Triangles(), File);
	}
}

void AutLib::CadLib::Cad3d_MarineModel::ExportCurvesOfMyModelToPlt(fstream & File) const
{
	for (TopExp_Explorer Explorer(myModel_, TopAbs_EDGE); Explorer.More(); Explorer.Next())
	{
		TopLoc_Location Loc;
		TopoDS_Edge Edge = TopoDS::Edge(Explorer.Current());

		if (Edge.IsNull()) continue;

		M_IO IO_TecPlot::ExportCurve(Edge, 40, File);
	}
}

void AutLib::CadLib::Cad3d_MarineModel::CalcBoundingBox()
{
	Bnd_Box Box;
	BRepBndLib::Add(myModel_, Box);

	Standard_Real Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
	Box.Get(Xmin, Ymin, Zmin, Xmax, Ymax, Zmax);

	theBox_ = M_GEO Entity_Box3d(Xmin, Xmax, Ymin, Ymax, Zmin, Zmax);
}