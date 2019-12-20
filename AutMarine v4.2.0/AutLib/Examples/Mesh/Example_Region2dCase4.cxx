#include <Examples\Mesh\Example_Region2d.hxx>

#include <Entity_Metric2.hxx>
#include <Model2d_Naca4Digit.hxx>
#include <Cad2d_MakePlane.hxx>
#include <Cad2d_EdgeOnPlane.hxx>
#include <Cad2d_BlockEdgeOnPlane.hxx>
#include <Cad2d_BooleanOperators.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh2d_Region.hxx>
#include <Mesh2d_Plane.hxx>
#include <SizeMap2d_AdaptiveCurvesSizeMapTool.hxx>
#include <SizeMap2d_SharpCornersSizeMapTool.hxx>
#include <SizeMap2d_PrimitiveShapesSizeMapTool.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;
using namespace MeshLib;

#include <gp_Ax22d.hxx>
#include <gp_Trsf2d.hxx>

void AutLib::Example_Region2d::Case4()
{
	Open_OutputFile_TecPlot(Plot, "Example_Region2dCase4");

	Cad2d_MakePlane Box, UpperBox;
	Box.Box(Geom_Pnt2d(-0.5, -3.0), Geom_Pnt2d(6.0, 3.0));

	gp_Ax22d A1(gp_Pnt2d(0.9, 1.0), gp_Dir2d(1.0, -0.3));
	UpperBox.Box(A1, 1.3, 0.15);

	gp_Trsf Transform;
	Transform.SetMirror(gp::OX());

	Global_Handle(Cad2d_Plane) LowerBox = UpperBox.Copy();
	LowerBox->Transform(Transform);

	Model2d_Naca4Digit Naca;
	Naca.Parameters().Init(1.0, 4, 40, 10);
	Naca.Perform();

	gp_Ax22d A(gp_Pnt2d(1.0, 0), gp_Dir2d(1.0, 0));

	Global_Handle(Cad2d_Plane) Shape = Naca.ExportAsPart(A);

	Cad2d_Plane Sum;
	Cad2d_BooleanOperators::Subtract(&Box, Shape, &Sum);
	Cad2d_BooleanOperators::Subtract(&Sum, &UpperBox, &Sum);
	Cad2d_BooleanOperators::Subtract(&Sum, LowerBox, &Sum);

	Get_Pointer(Edges) = Sum.Edges();
	Debug_Null_Pointer(Edges);

	Get_Const_Pointer(Block) = Edges->SelectBlockCurve("Default Block Edge");
	Debug_Null_Pointer(Block);

	Block->SelectCurve(1);
	Block->SelectCurve(3);
	Edges->Split("Wall");

	Edges->Print(Standard_True);

	Mesh_ReferenceValues Reference(0.5);  // 0.5

	Mesh2d_Region Region(&Reference, &Sum);

	Get_Object(Boundary) = Region.Boundaries();
	Boundary.CreateNewMap("Wall");
	Boundary.CreateNewMap("Hydrofoil");

	Get_Pointer(WallMap) = Boundary.SelectMap("Wall");
	Get_Pointer(HydroMap) = Boundary.SelectMap("Hydrofoil");

	WallMap->ImportCurvePatch("Wall");
	WallMap->MeshConditions().SetCustomSurfaceSize(Standard_True);
	WallMap->MeshConditions().SetCustomBoundaryGrowthRate(Standard_True);
	WallMap->MeshConditions().SetCustomSurfaceCurvature(Mesh_SurfaceCurvatureInfo_Custom_Values);

	WallMap->MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	WallMap->MeshValues().SurfaceSize().SetTargetSize(7);  // 7
	WallMap->MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_MODERATE);
	WallMap->CreateSizeMap();

	HydroMap->ImportCurvePatch("Default Inner Block 3");
	HydroMap->MeshConditions().SetCustomSurfaceSize(Standard_True);
	HydroMap->MeshConditions().SetCustomBoundaryGrowthRate(Standard_True);
	HydroMap->MeshConditions().SetCustomSurfaceCurvature(Mesh_SurfaceCurvatureInfo_Custom_Values);

	HydroMap->MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	HydroMap->MeshValues().SurfaceSize().SetTargetSize(2.5);  // 2.5
	HydroMap->MeshValues().SurfaceSize().SetMinSize(1);  // 1
	HydroMap->MeshValues().SurfaceCurvature().SetSpanAngle(15);  // 15
	HydroMap->MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_SLOW);
	HydroMap->CreateSizeMap();

	Get_Object(Sharp) = Region.Features();
	Sharp.CreateNewMap("Sharp Angles");

	Get_Pointer(SharpMap) = Sharp.SelectMap("Sharp Angles");

	SharpMap->ImportCurvePatch("Default Inner Block 1");
	SharpMap->ImportCurvePatch("Default Inner Block 2");
	SharpMap->MeshConditions().SetCustomSurfaceSize(Standard_True);
	SharpMap->MeshConditions().SetCustomBoundaryGrowthRate(Standard_True);
	SharpMap->MeshConditions().SetCustomSurfaceCurvature(Mesh_SurfaceCurvatureInfo_Custom_Values);

	SharpMap->MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	SharpMap->MeshValues().SurfaceSize().SetTargetSize(1.0);  // 1
	SharpMap->SetAngle(100);  // 100
	SharpMap->MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_MODERATE);
	SharpMap->CreateSizeMap();

	Cad2d_MakePlane VolumetricBox;
	VolumetricBox.Box(Geom_Pnt2d(0, -2), Geom_Pnt2d(3, 2));

	Get_Object(Primitives) = Region.Volumetrics();
	Primitives.CreateNewMap("Volumetric");

	Get_Pointer(PrimitivesMap) = Primitives.SelectMap("Volumetric");

	PrimitivesMap->ImportShape(&VolumetricBox);
	PrimitivesMap->MeshConditions().SetCustomSurfaceSize(Standard_True);
	PrimitivesMap->MeshConditions().SetCustomBoundaryGrowthRate(Standard_True);
	PrimitivesMap->MeshConditions().SetCustomSurfaceCurvature(Mesh_SurfaceCurvatureInfo_Custom_Values);

	PrimitivesMap->MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	PrimitivesMap->MeshValues().SurfaceSize().SetTargetSize(15.0); // 15
	PrimitivesMap->MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_FAST);
	PrimitivesMap->CreateSizeMap();

	Cad2d_MakePlane FreeSurfaceBox;
	FreeSurfaceBox.Box(Geom_Pnt2d(-0.55, 0.45), Geom_Pnt2d(6.05, 0.55));

	/*Sum.ExportToPlt(Plot);
	VolumetricBox.ExportToPlt(Plot);
	FreeSurfaceBox.ExportToPlt(Plot);
	return;*/

	Entity_Metric2 AnIso;
	AnIso.SetE1(Geom_Pnt2d(1, 0));
	AnIso.SetE2(Geom_Pnt2d(0, 1));
	AnIso.SetH1(1.0);
	AnIso.SetH2(0.3);

	Primitives.CreateNewMap("Free Surface");

	Get_Pointer(FreeSurfaceMap) = Primitives.SelectMap("Free Surface");

	FreeSurfaceMap->SetMetric(AnIso);
	FreeSurfaceMap->ImportShape(&FreeSurfaceBox);
	FreeSurfaceMap->MeshConditions().SetCustomSurfaceSize(Standard_True);
	FreeSurfaceMap->MeshConditions().SetCustomBoundaryGrowthRate(Standard_True);
	FreeSurfaceMap->MeshConditions().SetCustomSurfaceCurvature(Mesh_SurfaceCurvatureInfo_Custom_Values);

	FreeSurfaceMap->MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	FreeSurfaceMap->MeshValues().SurfaceSize().SetTargetSize(5); // 5
	FreeSurfaceMap->MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_FAST);
	FreeSurfaceMap->CreateSizeMap();

	Region.SetIsoSizeMapType(SizeMap2d_IsoBackSizeType_FullIntBackSize);
	Region.SetVerbosity(2);
	Region.Perform();
	
	Debug_Null_Pointer(Region.Mesh());

	Region.ExportQualityToPlt(Plot);
}