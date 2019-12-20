#include <Examples\Mesh\Example_VolumeMesher.hxx>

#include <Geom_ADTree3d.hxx>
#include <Entity_Tetrahedralization.hxx>
#include <Entity_TetrahedralizationTools.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_SolidTools.hxx>
#include <Cad3d_MakeSolid.hxx>
#include <Cad3d_EntitiesOnSolid.hxx>
#include <Cad3d_BlockEntityOnSolid.hxx>
#include <SizeMap3d_UniSize.hxx>
#include <SizeMap3d_ModifyBackSize.hxx>
#include <SizeMap3d_UniformCurvesSizeMapTool.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh3d_NodeTools.hxx>
#include <Mesh3d_BasicAft.hxx>
#include <Mesh3d_CavityRemover.hxx>
#include <Mesh3d_Optimization.hxx>
#include <QualityMap3d_Vlrms3Ratio.hxx>
#include <QualityMap3d_MinSine.hxx>

#include <TopoDS_Shape.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;
using namespace GeoLib;

void AutLib::Example_VolumeMesher::Case4()
{
	Open_OutputFile_TecPlot(Plot, "Example_VolumeMesherCase4");

	TopoDS_Shape Cone = Cad3d_MakeSolid::Cone(1.0, 0.25, 3);

	Cad3d_Solid Solid;
	Solid.Make(Cad3d_SolidTools::GetSurfaces(Cone));

	Global_Handle(Cad3d_EntitiesOnSolid) Edges = Solid.PairedEdges();
	Edges->Print(Standard_True);

	Debug_Null_Pointer(Edges);

	Global_Handle(Cad3d_BlockEntityOnSolid) Block;
	Block = Edges->SelectBlockEntity("Default Block Edge");
	Debug_Null_Pointer(Block);

	Block->SelectEntity(2);
	Block->SelectEntity(3);

	Edges->Split("My Edges 1");

	Edges->Print(Standard_True);

	Mesh_ReferenceValues Reference(0.25);

	SizeMap3d_UniformCurvesSizeMapTool SizeMap(&Reference, &Solid);
	SizeMap.ImportEntityPatch("My Edges 1");

	SizeMap.MeshConditions().SetCustomBoundaryGrowthRate(Standard_True);
	SizeMap.MeshConditions().SetCustomSurfaceSize(Standard_True);
	SizeMap.MeshConditions().SetCustomSurfaceCurvature(Mesh_SurfaceCurvatureInfo_Custom_Values);

	SizeMap.MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	SizeMap.MeshValues().SurfaceSize().SetTargetSize(10);
	SizeMap.MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_MODERATE);
	SizeMap.CreateSizeMap();

	Debug_Null_Pointer(SizeMap.BackGroundMesh());

	SizeMap3d_ModifyBackSize Map(Reference.BaseSize(), *SizeMap.BackGroundMesh());

	Geom_ADTree3d<Global_Handle(Mesh3d_Node)> Engine;
	Engine.SetCoordinateFunction(&Mesh3d_NodeTools::GetCoordOf);
	Engine.SetRegion(Solid.BoundingBox());

	Mesh3d_CavityRemover Aft(Map, &Engine);
	Aft.SetVerbosity(2);
	Aft.SetToUseExactMetricForSurfaceMesh();
	Aft.Import(Solid);

	Try_Exception_Handle_Exit(Aft.Perform());

	//Aft.ExportQualityToPlt(Plot, QualityMap3d_TypesInfo::QualityMap3d_VLRMS3RATIO);
	Aft.ReportQuality(QualityMap3d_TypesInfo::QualityMap3d_VLRMS3RATIO);

	QualityMap3d_Vlrms3Ratio QualityMap;

	Mesh3d_Optimization Optimization(QualityMap, Map, Aft);
	Optimization.SetVerbosity(2);
	Optimization.Perform();

	Aft.ReportQuality();
	Aft.ExportQualityToPlt(Plot, QualityMap3d_TypesInfo::QualityMap3d_VLRMS3RATIO);


	return;
	forThose(Index, 0, Aft.NbMeshes() - 1)
	{
		Entity_Tetrahedralization Tetrahedralization = Aft.Mesh(Index)->Static();

		Entity_Tetrahedralization Left, Right;
		Entity_TetrahedralizationTools::xCoord_Split(0, Tetrahedralization, Left, Right);

		Left.ExportToPlt(Plot);
		Right.ExportToPlt(Plot);
	}
}