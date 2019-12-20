#include <Examples\Mesh\Example_Region3d.hxx>

#include <Entity_Tetrahedralization.hxx>
#include <Entity_TetrahedralizationTools.hxx>
#include <IO_IGESRead.hxx>
#include <Mesh3d_Region.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_SolidTools.hxx>
#include <Cad3d_BlockEntityOnSolid.hxx>
#include <SizeMap3d_UniSize.hxx>
#include <SizeMap3d_UniformSurfacesSizeMapTool.hxx>
#include <Mesh3d_SolidMesher.hxx>
#include <Mesh3d_Volume.hxx>
#include <Mesh_ReferenceValues.hxx>

#include <TopoDS_Shape.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace MeshLib;
using namespace IoLib;
using namespace CadLib;

void AutLib::Example_Region3d::Case1()
{
	Open_OutputFile_TecPlot(Plot, "Example_Region3dCase1");

	TopoDS_Shape Propeller;
	IO_IGESRead::ReadFileNonDiscretized("Example_MakeCfdPropellerCase1.igs", Propeller);

	Cad3d_SolidTools::Triangulation(Propeller, 0.05, 0.5);

	Cad3d_Solid Solid;
	Solid.Make(Cad3d_SolidTools::GetSurfaces(Propeller));
	Solid.SetName("MyPropeller");

	Get_Pointer(Surfaces) = Solid.Surfaces();
	Debug_Null_Pointer(Surfaces);

	Get_Pointer(Block) = Surfaces->SelectBlockEntity("Default Block Surface");
	Debug_Null_Pointer(Block);

	Block->SelectEntity(1);
	Block->SelectEntity(2);
	Block->SelectEntity(3);
	Block->SelectEntity(4);
	Block->SelectEntity(5);
	Block->SelectEntity(6);
	Surfaces->Split("Outter");

	Block = Surfaces->SelectBlockEntity("Default Block Surface");

	Block->SelectEntity(13);
	Block->SelectEntity(16);
	Block->SelectEntity(19);
	Block->SelectEntity(22);
	Block->SelectEntity(25);
	Block->SelectEntity(28);
	Surfaces->Split("Trail");

	Block = Surfaces->SelectBlockEntity("Default Block Surface");

	Block->SelectEntity(30);
	Block->SelectEntity(31);
	Block->SelectEntity(32);
	Block->SelectEntity(33);
	Block->SelectEntity(34);
	Block->SelectEntity(35);
	Surfaces->Split("Tip");

	Block = Surfaces->SelectBlockEntity("Default Block Surface");

	Block->SelectEntity(29);
	Surfaces->Split("Apex");

	Block = Surfaces->SelectBlockEntity("Default Block Surface");
	Surfaces->RenameBlock("Inner");

	Surfaces->Print(Standard_True);

	//Solid.ExportBlockSurfacesToPlt(Plot);

	Mesh_ReferenceValues Reference(1.2);

	Mesh3d_Region Region(&Reference, &Solid);

	Get_Object(Boundary) = Region.Boundaries();
	Boundary.CreateNewMap("InnerMap");
	Boundary.CreateNewMap("TipMap");
	Boundary.CreateNewMap("TrailMap");
	Boundary.CreateNewMap("ApexMap");

	Get_Pointer(InnerMap) = Boundary.SelectMap("InnerMap");

	InnerMap->ImportEntityPatch("Inner");
	InnerMap->MeshConditions().SetCustomSurfaceSize(Standard_True);
	InnerMap->MeshConditions().SetCustomBoundaryGrowthRate(Standard_True);
	InnerMap->MeshConditions().SetCustomSurfaceCurvature(Mesh_SurfaceCurvatureInfo_Custom_Values);

	InnerMap->MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	InnerMap->MeshValues().SurfaceSize().SetTargetSize(12);
	InnerMap->MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_SLOW);
	InnerMap->CreateSizeMap();

	Get_Pointer(TipMap) = Boundary.SelectMap("TipMap");

	TipMap->ImportEntityPatch("Tip");
	TipMap->MeshConditions().SetCustomSurfaceSize(Standard_True);
	TipMap->MeshConditions().SetCustomBoundaryGrowthRate(Standard_True);
	TipMap->MeshConditions().SetCustomSurfaceCurvature(Mesh_SurfaceCurvatureInfo_Custom_Values);

	TipMap->MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	TipMap->MeshValues().SurfaceSize().SetTargetSize(2.5);
	TipMap->MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_VerySLOW);
	TipMap->CreateSizeMap();

	Get_Pointer(TrailMap) = Boundary.SelectMap("TrailMap");

	TrailMap->ImportEntityPatch("Trail");
	TrailMap->MeshConditions().SetCustomSurfaceSize(Standard_True);
	TrailMap->MeshConditions().SetCustomBoundaryGrowthRate(Standard_True);
	TrailMap->MeshConditions().SetCustomSurfaceCurvature(Mesh_SurfaceCurvatureInfo_Custom_Values);

	TrailMap->MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	TrailMap->MeshValues().SurfaceSize().SetTargetSize(2.5);
	TrailMap->MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_VerySLOW);
	TrailMap->CreateSizeMap();

	Get_Pointer(ApexMap) = Boundary.SelectMap("ApexMap");

	ApexMap->ImportEntityPatch("Apex");
	ApexMap->MeshConditions().SetCustomSurfaceSize(Standard_True);
	ApexMap->MeshConditions().SetCustomBoundaryGrowthRate(Standard_True);
	ApexMap->MeshConditions().SetCustomSurfaceCurvature(Mesh_SurfaceCurvatureInfo_Custom_Values);

	ApexMap->MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	ApexMap->MeshValues().SurfaceSize().SetTargetSize(5);
	ApexMap->MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_VerySLOW);
	ApexMap->CreateSizeMap();

	Region.SetVerbosity(3);
	//Region.SetToSurfaceMeshOnly();
	Region.Perform();

	Debug_Null_Pointer(Region.Mesh());

	//Region.ExportNormalsOfSurfaces(Plot);

	Get_Const_Object(Mesh) = *Region.Mesh();
	Mesh.ExportIndependentPatchesToPlt(Plot);

	forThose
	(
		Index,
		0,
		Mesh.NbMeshes() - 1
	)
	{
		Entity_Tetrahedralization Tetrahedralization = Mesh.Mesh(Index)->Static();

		Entity_Tetrahedralization Left, Right;
		Entity_TetrahedralizationTools::yCoord_Split(0.0, Tetrahedralization, Left, Right);

		Left.ExportToPlt(Plot);
		Right.ExportToPlt(Plot);
	}

	//Region.ExportSizeMap(Plot);

	/*SizeMap3d_UniSize UniSizeMap(0.25);

	Mesh3d_SolidMesher SolidMesher(UniSizeMap, Solid);
	SolidMesher.UseExactMetric();
	SolidMesher.SetVerbosity(2);
	SolidMesher.Perform();

	SolidMesher.ExportMeshToPlt(Plot);*/
}