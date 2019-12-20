#include <Prop_Propeller.hxx>

#include <Entity_Box3d.hxx>
#include <Geometry_Tools.hxx>
#include <Cad3d_Datum.hxx>
#include <Cad3d_DatumTools.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_SolidTools.hxx>
#include <Cad3d_RegisterDatum.hxx>
#include <IO_Tecplot.hxx>
#include <TColCad3d_HAry1dOfDatum.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;
using namespace IoLib;

#include <gp_Trsf.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Shell.hxx>
#include <TopExp_Explorer.hxx>
#include <TopExp.hxx>
#include <Bnd_Box.hxx>
#include <BRep_Tool.hxx>
#include <BRepBndLib.hxx>
#include <BRep_Builder.hxx>
#include <BRepBuilderAPI_Copy.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <BRepOffsetAPI_Sewing.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Common.hxx>
#include <BRepMesh_FastDiscret.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <GeomFill_BSplineCurves.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom_BSplineSurface.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>
#include <TopTools_IndexedMapOfShape.hxx>
#include <TColGeom_Array1OfBSplineCurve.hxx>
#include <GProp_GProps.hxx>
#include <BRepGProp.hxx>
#include <ShapeFix_Shape.hxx>

AutLib::CadLib::Prop_Propeller::Prop_Propeller()
{
	DefaultParameters();

	AllocateMemory();

	theSystem_ = gp_Ax2(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1), gp_Dir(1, 0, 0));
}

void AutLib::CadLib::Prop_Propeller::AllocateMemory()
{
	Standard_Integer NbSections = theParameters_.NbSections();

	theXParameters_.AllocateMemory(NbSections);

	thePropView_.AllocateMemory(NbSections);

	theBlades_.Resize(theParameters_.NbBlades());
}

void AutLib::CadLib::Prop_Propeller::MakeClosedBlade()
{
	//if (NOT IsDone_) { THROW_STANDARD_EXCEPTION(" Empty Hull"); }

	Get_Const_Object(Blade) = *theBlades_.First();
	/*Get_Const_Object(FacePtr) = Blade.Face();
	Get_Const_Object(BackPtr) = Blade.Back();

	Standard_Real U0, U1, V0, V1;

	FacePtr->Bounds(U0, U1, V0, V1);
	Global_Handle(Cad3d_Datum) Datum1 = new Cad3d_Datum(FacePtr->Value(MEAN(U0, U1), MEAN(V0, V1)), "Face");

	BackPtr->Bounds(U0, U1, V0, V1);
	Global_Handle(Cad3d_Datum) Datum2 = new Cad3d_Datum(BackPtr->Value(MEAN(U0, U1), MEAN(V0, V1)), "Back");*/

	TopoDS_Shape Face = BRepBuilderAPI_MakeFace(Blade.Face(), 1.0E-6);
	TopoDS_Shape Back = BRepBuilderAPI_MakeFace(Blade.Back(), 1.0E-6);

	myBlades_ = BRepAlgoAPI_Fuse(Face, Back);
	TColGeom_Array1OfBSplineCurve Curves(1, 8);
	Standard_Integer K = 0;
	for (TopExp_Explorer Explorer(myBlades_, TopAbs_EDGE); Explorer.More(); Explorer.Next())
	{
		TopoDS_Edge Edge = TopoDS::Edge(Explorer.Current());
		TopLoc_Location Loc;
		Standard_Real First, Last;
		Handle(Geom_Curve) Curve = BRep_Tool::Curve(Edge, First, Last);

		Handle(Geom_BSplineCurve) BSplCurve = Handle(Geom_BSplineCurve)::DownCast(Curve);

		if (BSplCurve.IsNull()) { THROW_STANDARD_EXCEPTION(" Null Curve"); }

		Curves.SetValue(++K, BSplCurve);
	}

	GeomFill_BSplineCurves Root(Curves.Value(1), Curves.Value(5), GeomFill_CoonsStyle);
	myBlades_ = BRepAlgoAPI_Fuse(myBlades_, BRepBuilderAPI_MakeFace(Root.Surface(), 1.0E-6));

	GeomFill_BSplineCurves TE(Curves.Value(3), Curves.Value(7), GeomFill_CoonsStyle);
	myBlades_ = BRepAlgoAPI_Fuse(myBlades_, BRepBuilderAPI_MakeFace(TE.Surface(), 1.0E-6));

	/*TE.Surface()->Bounds(U0, U1, V0, V1);
	Global_Handle(Cad3d_Datum) Datum3 = new Cad3d_Datum(TE.Surface()->Value(MEAN(U0, U1), MEAN(V0, V1)), "Trail");*/

	GeomFill_BSplineCurves Tip(Curves.Value(4), Curves.Value(8), GeomFill_CoonsStyle);
	myBlades_ = BRepAlgoAPI_Fuse(myBlades_, BRepBuilderAPI_MakeFace(Tip.Surface(), 1.0E-6));

	/*Tip.Surface()->Bounds(U0, U1, V0, V1);
	Global_Handle(Cad3d_Datum) Datum4 = new Cad3d_Datum(Tip.Surface()->Value(MEAN(U0, U1), MEAN(V0, V1)), "Tip");*/

	myBlades_.Reverse();
}

namespace AutLib
{
	namespace CadLib
	{
		static TColCad3d_HAry1dOfDatum RotatedDatum(const TColCad3d_HAry1dOfDatum& theDatum, const gp_Trsf& theTransform)
		{
			TColCad3d_HAry1dOfDatum Datum(theDatum.Size());
			forThose
			(
				Index,
				0,
				MaxIndexOf(theDatum)
			)
			{
				Global_Handle(Cad3d_Datum) datum = new Cad3d_Datum(*theDatum.Value(Index));
				datum->Transform(theTransform);

				Datum.SetValue(Index, datum);
			}
			MOVE(Datum);
		}
	}
}

void AutLib::CadLib::Prop_Propeller::MakeMyBlades()
{
	Standard_Real dTheta = 2 * M_PI / (Standard_Real)(theParameters_.NbBlades());

	/*TColCad3d_HAry1dOfDatum Datum;
	theDatum_.RetrieveTo(Datum);*/

	TopoDS_Compound Compound;
	TopoDS_Builder Builder;
	Builder.MakeCompound(Compound);

	Builder.Add(Compound, myBlades_);
	forThose
	(
		Index,
		1, 
		theParameters_.NbBlades() - 1
	)
	{
		Standard_Real Theta = Index*dTheta;

		gp_Trsf Rotate;
		Rotate.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 0, 1)), Theta);

		//theDatum_.EnQueue(::RotatedDatum(Datum, Rotate));

		BRepBuilderAPI_Transform Transform(Rotate);
		Transform.Perform(myBlades_, Standard_True);

		Builder.Add(Compound, Transform.Shape());
		
		//myBlades_ = BRepAlgoAPI_Fuse(myBlades_, Transform.Shape());
	}
	myBlades_ = Compound;
}

void AutLib::CadLib::Prop_Propeller::DiscreteMyBlades
(
	const Standard_Real Deflection, 
	const Standard_Real Angle
)
{
	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = Deflection;
	Params.Angle = Angle;

	Bnd_Box Box;
	BRepBndLib::Add(myBlades_, Box);

	BRepMesh_FastDiscret Mesh(Box, Params);

	Mesh.Perform(myBlades_);
}

void AutLib::CadLib::Prop_Propeller::DiscreteMyHub
(
	const Standard_Real Deflection,
	const Standard_Real Angle
)
{
	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = Deflection;
	Params.Angle = Angle;

	Bnd_Box Box;
	BRepBndLib::Add(myHub_, Box);
	BRepMesh_FastDiscret Mesh(Box, Params);

	Mesh.Perform(myHub_);
}

void AutLib::CadLib::Prop_Propeller::DiscreteMyProp
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

namespace AutLib
{
	namespace CadLib
	{

		static Entity_Box3d GetDomain(const TColCad3d_HAry1dOfDatum& theDatum)
		{
			TColGeom_Ary1dOfPnt3d Pts(theDatum.Size());
			forThose(Index, 0, MaxIndexOf(theDatum))
				Pts[Index] = theDatum[Index]->Coord();

			Standard_Real Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
			Geometry_Tools::CalcMinMax(Pts, Xmin, Xmax, Ymin, Ymax, Zmin, Zmax);

			return Entity_Box3d(Xmin, Xmax, Ymin, Ymax, Zmin, Zmax);
		}

		static inline Entity_Box3d GetSearchBox(const Geom_Pnt3d& theCentre, const Standard_Real theRadius)
		{
			return Entity_Box3d(theCentre.X() - theRadius, theCentre.X() + theRadius, theCentre.Y() - theRadius, theCentre.Y() + theRadius, theCentre.Z() - theRadius, theCentre.Z() + theRadius);
		}
	}
}

void AutLib::CadLib::Prop_Propeller::Make()
{
	CreateProfiles();

	CalcXParameters();

	CreateSections_NACA4Digits();

	CreateUnWrappedView();

	CreateWrappedView();

	CreateBladeFaces();

	MakeClosedBlade();

	MakeMyBlades();

	MakeMyHub();

	MakeMyProp();

	gp_Trsf Rotate;
	Rotate.SetRotation(gp_Ax1(gp_Pnt(0, 0, 0), gp_Dir(0, 1, 0)), M_PI / 2);
	
	BRepBuilderAPI_Transform Transform(Rotate);
	Transform.Perform(myModel_, Standard_True);
	myModel_ = Transform.Shape();

	if (toDiscrete_)
	{
		DiscreteMyProp();
	}
}

void AutLib::CadLib::Prop_Propeller::MakeMyProp()
{
	BRepOffsetAPI_Sewing Sewing1;
	Sewing1.Add(myBlades_);
	Sewing1.Perform();

	TopoDS_Shape Sewed1 = Sewing1.SewedShape();
	TopoDS_CompSolid Compound;
	TopoDS_Builder Builder;
	Builder.MakeCompSolid(Compound);

	for (TopExp_Explorer Explorer(Sewed1, TopAbs_SHELL); Explorer.More(); Explorer.Next())
	{
		TopoDS_Shell Shell = TopoDS::Shell(Explorer.Current());

		BRepBuilderAPI_MakeSolid brep_solid(Shell);
		TopoDS_Solid Solid = brep_solid.Solid();

		Builder.Add(Compound, Solid);

		//myModel_ = BRepAlgoAPI_Fuse(Solid, myModel_);
	}

	BRepOffsetAPI_Sewing Sewing2;
	Sewing2.Add(myHub_);
	Sewing2.Perform();

	TopoDS_Shape Sewed2 = Sewing2.SewedShape();

	BRepBuilderAPI_MakeSolid brep_solid2(TopoDS::Shell(Sewed2));
	//myModel_ = brep_solid2.Solid();
	myModel_ = BRepAlgoAPI_Fuse(Compound, brep_solid2.Solid());

	//GProp_GProps System;
	//BRepGProp::VolumeProperties(myModel_, System);

	/*Handle(ShapeFix_Shape) FixShape = new ShapeFix_Shape;
	FixShape->Init(myModel_);
	FixShape->SetPrecision(1.0E-4);
	FixShape->SetMaxTolerance(1.0E-4);
	FixShape->SetMinTolerance(1.0E-4);

	FixShape->FixWireTool()->FixAddPCurveMode() = 1;
	FixShape->FixWireTool()->FixRemovePCurveMode() = 1;
	FixShape->FixWireTool()->FixSeamMode() = 1;
	FixShape->FixWireTool()->FixShiftedMode() = 1;
	FixShape->FixWireTool()->FixSameParameterMode() = 1;
	FixShape->FixWireTool()->FixNotchedEdgesMode() = 1;
	FixShape->FixWireTool()->FixNonAdjacentIntersectingEdgesMode() = 1;

	FixShape->Perform();

	myModel_ = FixShape->Shape();*/

	/*BRepBuilderAPI_MakeSolid brep_solid1(TopoDS::Shell(Sewed1));
	TopoDS_Solid Solid1 = brep_solid1.Solid();

	BRepBuilderAPI_MakeSolid brep_solid2(TopoDS::Shell(Sewed2));
	TopoDS_Solid Solid2 = brep_solid2.Solid();*/

	//myModel_ = BRepAlgoAPI_Fuse(Sewed1, Sewed2);
}

//void AutLib::CadLib::Prop_Propeller::MakeMyProp()
//{
//	BRep_Builder shellMaker1;
//	TopoDS_Shell shellShape1;
//	shellMaker1.MakeShell(shellShape1);
//	for (TopExp_Explorer Explorer(myBlades_, TopAbs_FACE); Explorer.More(); Explorer.Next())
//	{
//		TopoDS_Face Face = TopoDS::Face(Explorer.Current());
//		shellMaker1.Add(shellShape1, Face);
//	}
//
//	BRepBuilderAPI_MakeSolid solidmaker1;
//	TopTools_IndexedMapOfShape shellMap1;
//	TopExp::MapShapes(shellShape1, TopAbs_SHELL, shellMap1);
//	for (Standard_Integer ishell = 1; ishell <= shellMap1.Extent(); ++ishell)
//	{
//		const TopoDS_Shell& shell = TopoDS::Shell(shellMap1(ishell));
//		solidmaker1.Add(shell);
//	}
//	TopoDS_Shape Solid1 = solidmaker1.Solid();
//
//	BRep_Builder shellMaker2;
//	TopoDS_Shell shellShape2;
//	shellMaker2.MakeShell(shellShape2);
//	for (TopExp_Explorer Explorer(myHub_, TopAbs_FACE); Explorer.More(); Explorer.Next())
//	{
//		TopoDS_Face Face = TopoDS::Face(Explorer.Current());
//		shellMaker2.Add(shellShape2, Face);
//	}
//
//	BRepBuilderAPI_MakeSolid solidmaker2;
//	TopTools_IndexedMapOfShape shellMap2;
//	TopExp::MapShapes(shellShape2, TopAbs_SHELL, shellMap2);
//	for (Standard_Integer ishell = 1; ishell <= shellMap2.Extent(); ++ishell)
//	{
//		const TopoDS_Shell& shell = TopoDS::Shell(shellMap2(ishell));
//		solidmaker2.Add(shell);
//	}
//	TopoDS_Shape Solid2 = solidmaker2.Solid();
//
//	myModel_ = BRepAlgoAPI_Fuse(Solid1, Solid2);
//
//}

void AutLib::CadLib::Prop_Propeller::ExportMyBladesToPlt(fstream & File) const
{
	for (TopExp_Explorer Explorer(myBlades_, TopAbs_FACE); Explorer.More(); Explorer.Next())
	{
		TopLoc_Location Loc;
		Handle(Poly_Triangulation) Triangulation = BRep_Tool::Triangulation(TopoDS::Face(Explorer.Current()), Loc);

		if (Triangulation.IsNull()) continue;

		M_IO IO_TecPlot::ExportMesh(Triangulation->Nodes(), Triangulation->Triangles(), File);
	}
}

void AutLib::CadLib::Prop_Propeller::ExportMyHubToPlt(fstream & File) const
{
	for (TopExp_Explorer Explorer(myHub_, TopAbs_FACE); Explorer.More(); Explorer.Next())
	{
		TopLoc_Location Loc;
		Handle(Poly_Triangulation) Triangulation = BRep_Tool::Triangulation(TopoDS::Face(Explorer.Current()), Loc);

		if (Triangulation.IsNull()) continue;

		M_IO IO_TecPlot::ExportMesh(Triangulation->Nodes(), Triangulation->Triangles(), File);
	}
}
