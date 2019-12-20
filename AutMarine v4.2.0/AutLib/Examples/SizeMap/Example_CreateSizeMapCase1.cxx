#include <Examples\SizeMap\Example_SizeMap.hxx>

#include <Cad2d_EdgeOnPlane.hxx>
#include <Cad2d_BlockEdgeOnPlane.hxx>
#include <Cad2d_MakePlane.hxx>
#include <SizeMap2d_UniformCurvesSizeMapTool.hxx>
#include <Mesh_ReferenceValues.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;

void AutLib::Example_SizeMap::CreateSizeMapCase1()
{
	Open_OutputFile_TecPlot(Plot, "Example_CreateSizeMapCase1");

	Cad2d_MakePlane Box;
	Box.Box(Geom_Pnt2d(), Geom_Pnt2d(1.0, 1.0));

	Get_Pointer(Edges) = Box.Edges();
	Debug_Null_Pointer(Edges);

	Edges->Print(Standard_True);

	Get_Const_Pointer(Block) = Edges->SelectBlockCurve("Default Block Edge");
	Debug_Null_Pointer(Block);

	Block->SelectCurve(2);
	Block->SelectCurve(4);
	Edges->Split("Source");

	Edges->Print(Standard_True);

	Mesh_ReferenceValues Reference(0.25);

	SizeMap2d_UniformCurvesSizeMapTool SizeMap(&Reference, &Box);
	SizeMap.ImportCurvePatch("Source");
	SizeMap.MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	SizeMap.MeshValues().SurfaceSize().SetTargetSize(5);
	SizeMap.MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_FAST);
	SizeMap.CreateSizeMap();

	SizeMap.ExportContourToPlt(Plot);

	Debug_Null_Pointer(SizeMap.BackGroundMesh());
}