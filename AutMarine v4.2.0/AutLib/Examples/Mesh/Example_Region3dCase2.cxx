#include <Examples\Mesh\Example_Region3d.hxx>

#include <Entity_Tetrahedralization.hxx>
#include <Entity_TetrahedralizationTools.hxx>
#include <IO_IGESRead.hxx>
#include <Mesh3d_Region.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_MakeSolid.hxx>
#include <Cad3d_SolidTools.hxx>
#include <Cad3d_BlockEntityOnSolid.hxx>
#include <SizeMap3d_UniSize.hxx>
#include <SizeMap3d_PrimitiveShapeSource.hxx>
#include <SizeMap3d_UniformSurfacesSizeMapTool.hxx>
#include <SizeMap3d_PrimitiveShapesSizeMapTool.hxx>
#include <Mesh3d_SolidMesher.hxx>
#include <Mesh3d_Volume.hxx>
#include <Mesh_ReferenceValues.hxx>

#include <TopoDS_Shape.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace MeshLib;
using namespace IoLib;
using namespace CadLib;

void AutLib::Example_Region3d::Case2()
{
	/*Cad3d_SolidTools::ExportToPlt(Ship, Plot);

	TopoDS_Shape BoxShape = Cad3d_MakeSolid::Box(Geom_Pnt3d(40, -50, -30), Geom_Pnt3d(260, 50, 30));
	Cad3d_SolidTools::Triangulation(BoxShape);
	Cad3d_SolidTools::ExportToPlt(BoxShape, Plot);

	TopoDS_Shape FreeShape = Cad3d_MakeSolid::Box(Geom_Pnt3d(-10, -100, -6), Geom_Pnt3d(460, 100, 6));
	Cad3d_SolidTools::Triangulation(FreeShape);
	Cad3d_SolidTools::ExportToPlt(FreeShape, Plot);

	return;*/

	Open_OutputFile_TecPlot(Plot, "Example_Region3dCase2");

	TopoDS_Shape Ship;
	IO_IGESRead::ReadFileNonDiscretized("MyShip.IGS", Ship);

	Cad3d_SolidTools::Triangulation(Ship, 0.1, 0.5);
	
	Cad3d_Solid Solid;
	Solid.Make(Cad3d_SolidTools::GetSurfaces(Ship));
	Solid.SetName("MyShip");

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

	Block->SelectEntity(10);
	Surfaces->Split("Deck");

	Block = Surfaces->SelectBlockEntity("Default Block Surface");
	Surfaces->RenameBlock("Hull");

	Surfaces->Print(Standard_True);
	return;

	Mesh_ReferenceValues Reference(30.0);

	Mesh3d_Region Region(&Reference, &Solid);

	SizeMap3d_PrimitiveShapeSource Box;
	Box.Box(Geom_Pnt3d(40, -50, -30), Geom_Pnt3d(260, 50, 30));

	Get_Object(Boundary) = Region.Boundaries();
	Boundary.CreateNewMap("DeckMap");
	Boundary.CreateNewMap("HullMap");

	Get_Object(Volumetric) = Region.Volumetric();
	Volumetric.CreateNewMap("InnerMap");

	Get_Pointer(InnerMap) = Volumetric.SelectMap("InnerMap");

	InnerMap->ImportSource(&Box);
	InnerMap->MeshConditions().SetCustomSurfaceSize(Standard_True);
	InnerMap->MeshConditions().SetCustomBoundaryGrowthRate(Standard_True);
	InnerMap->MeshConditions().SetCustomSurfaceCurvature(Mesh_SurfaceCurvatureInfo_Custom_Values);

	InnerMap->MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	InnerMap->MeshValues().SurfaceSize().SetTargetSize(20);
	InnerMap->MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_MODERATE);
	InnerMap->CreateSizeMap();

	Get_Pointer(DeckMap) = Boundary.SelectMap("DeckMap");

	DeckMap->ImportEntityPatch("Deck");
	DeckMap->MeshConditions().SetCustomSurfaceSize(Standard_True);
	DeckMap->MeshConditions().SetCustomBoundaryGrowthRate(Standard_True);
	DeckMap->MeshConditions().SetCustomSurfaceCurvature(Mesh_SurfaceCurvatureInfo_Custom_Values);

	DeckMap->MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	DeckMap->MeshValues().SurfaceSize().SetTargetSize(8);
	DeckMap->MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_SLOW);
	DeckMap->CreateSizeMap();

	Get_Pointer(HullMap) = Boundary.SelectMap("HullMap");

	HullMap->ImportEntityPatch("Hull");
	HullMap->MeshConditions().SetCustomSurfaceSize(Standard_True);
	HullMap->MeshConditions().SetCustomBoundaryGrowthRate(Standard_True);
	HullMap->MeshConditions().SetCustomSurfaceCurvature(Mesh_SurfaceCurvatureInfo_Custom_Values);

	HullMap->MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	HullMap->MeshValues().SurfaceSize().SetTargetSize(4);
	HullMap->MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_SLOW);
	HullMap->CreateSizeMap();

	Volumetric.CreateNewMap("FreeSurfaceMap");

	Get_Pointer(FreeSurfaceMap) = Volumetric.SelectMap("FreeSurfaceMap");

	SizeMap3d_PrimitiveShapeSource FreeSurface;
	FreeSurface.Box(Geom_Pnt3d(-10, -100, -6), Geom_Pnt3d(460, 100, 6));

	FreeSurfaceMap->ImportSource(&FreeSurface);
	FreeSurfaceMap->MeshConditions().SetCustomSurfaceSize(Standard_True);
	FreeSurfaceMap->MeshConditions().SetCustomBoundaryGrowthRate(Standard_True);
	FreeSurfaceMap->MeshConditions().SetCustomSurfaceCurvature(Mesh_SurfaceCurvatureInfo_Custom_Values);

	FreeSurfaceMap->MeshValues().SurfaceSize().SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	FreeSurfaceMap->MeshValues().SurfaceSize().SetTargetSize(6);
	FreeSurfaceMap->MeshValues().SetBoundaryGrowthRate(Mesh_VariationRateInfo_MODERATE);
	FreeSurfaceMap->CreateSizeMap();

	Region.SetVerbosity(3);
	Region.SetToUseExactMetricForSurfaceMeshing();
	//Region.SetToSurfaceMeshOnly();
	Region.Perform();
	//Region.Mesh()->ExportIndependentPatchesToPlt(Plot);
	//Region.Mesh()->ExportToPlt(Plot);

	//Region.Mesh()->ExportDomainToPlt(Plot);

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
		Entity_TetrahedralizationTools::yCoord_Split(5.9797, Tetrahedralization, Left, Right);

		Left.ExportToPlt(Plot);
		Right.ExportToPlt(Plot);

		Entity_TetrahedralizationTools::zCoord_Split(9.8, Tetrahedralization, Left, Right);

		Left.ExportToPlt(Plot);
		Right.ExportToPlt(Plot);

		Entity_TetrahedralizationTools::xCoord_Split(100.0, Tetrahedralization, Left, Right);

		Left.ExportToPlt(Plot);
		Right.ExportToPlt(Plot);

		Entity_TetrahedralizationTools::xCoord_Split(200.0, Tetrahedralization, Left, Right);

		Left.ExportToPlt(Plot);
		Right.ExportToPlt(Plot);
	}
}