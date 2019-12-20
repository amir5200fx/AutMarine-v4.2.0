#include <Examples\Mesh\Example_Mesh2d.hxx>

#include <Cad2d_EdgeOnPlane.hxx>
#include <Cad2d_BlockEdgeOnPlane.hxx>
#include <Cad2d_MakePlane.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh2d_NodeTools.hxx>
#include <Mesh2d_BasicAft.hxx>
#include <SizeMap2d_ModifyBackSize.hxx>
#include <SizeMap2d_SharpCornersSizeMapTool.hxx>
#include <TColMesh2d_ADTree2dOfNode.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;

void AutLib::Example_Mesh2d::MeshCase4()
{
	Open_OutputFile_TecPlot(Plot, "Example_MeshCase4");

	Cad2d_MakePlane Box;
	Box.Box(Geom_Pnt2d(), Geom_Pnt2d(0.3, 1.2));

	Get_Pointer(Corners) = Box.Corners();
	Debug_Null_Pointer(Corners);

	Corners->Print(Standard_True);

	Mesh_ReferenceValues Reference(0.25);

	SizeMap2d_SharpCornersSizeMapTool SizeMap(&Reference, &Box);
	SizeMap.MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	SizeMap.MeshValues().SurfaceSize().SetTargetSize(5);
	SizeMap.MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_FAST);
	SizeMap.SetAngle(100);
	SizeMap.CreateSizeMap();

	Debug_Null_Pointer(SizeMap.BackGroundMesh());

	SizeMap2d_ModifyBackSize Map(Reference.BaseSize(), *SizeMap.BackGroundMesh());
	//Map.ExportToPlt(Plot);

	TColMesh2d_ADTree2dOfNode Engine;
	Engine.SetCoordinateFunction(&Mesh2d_NodeTools::GetCoordOf);

	Mesh2d_BasicAft Aft(Map, &Engine);
	Aft.Import(Box);
	Aft.SetVerbosity(1);
	Try_Exception_Handle_Exit(Aft.Perform());

	Aft.ExportToPlt(Plot);
}