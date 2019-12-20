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
#include <SizeMap3d_UniformSurfacesSizeMapTool.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh3d_NodeTools.hxx>
#include <Mesh3d_BasicAft.hxx>
#include <Mesh3d_CavityRemover.hxx>

#include <TopoDS_Shape.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;
using namespace GeoLib;

void AutLib::Example_VolumeMesher::Case2()
{
	Open_OutputFile_TecPlot(Plot, "Example_VolumeMesherCase2");

	TopoDS_Shape Cone = Cad3d_MakeSolid::Cone(1.0, 0.25, 3);

	Cad3d_Solid Solid;
	Solid.Make(Cad3d_SolidTools::GetSurfaces(Cone));
	
	Global_Handle(Cad3d_EntitiesOnSolid) Surfaces = Solid.Surfaces();
	Surfaces->Print(Standard_True);

	Debug_Null_Pointer(Surfaces);

	Global_Handle(Cad3d_BlockEntityOnSolid) Block;
	Block = Surfaces->SelectBlockEntity("Default Block Surface");
	Debug_Null_Pointer(Block);

	Block->SelectEntity(2);
	Block->SelectEntity(3);

	Surfaces->Split("My Surfaces 1");

	Surfaces->Print(Standard_True);

	Mesh_ReferenceValues Reference(0.15);

	SizeMap3d_UniformSurfacesSizeMapTool SizeMap(&Reference, &Solid);
	SizeMap.ImportEntityPatch("My Surfaces 1");

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
	Aft.Import(Solid);

	Try_Exception_Handle_Exit(Aft.Perform());

	Aft.ExportDomainToPlt(Plot);

	forThose(Index, 0, Aft.NbMeshes() - 1)
	{
		Entity_Tetrahedralization Tetrahedralization = Aft.Mesh(Index)->Static();

		Entity_Tetrahedralization Left, Right;
		Entity_TetrahedralizationTools::xCoord_Split(0, Tetrahedralization, Left, Right);

		Left.ExportToPlt(Plot);
		Right.ExportToPlt(Plot);
	}
}