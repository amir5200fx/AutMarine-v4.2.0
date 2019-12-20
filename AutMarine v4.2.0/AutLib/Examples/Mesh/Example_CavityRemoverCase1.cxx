#include <Examples\Mesh\Example_CavityRemover.hxx>

#include <Entity_Tetrahedralization.hxx>
#include <Entity_TetrahedralizationTools.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_MakeSolid.hxx>
#include <Cad3d_SolidTools.hxx>
#include <SizeMap3d_UniSize.hxx>
#include <Mesh3d_NodeTools.hxx>
#include <Mesh3d_CavityRemover.hxx>
#include <Mesh3d_SolidMesher.hxx>
#include <TColMesh3d_ADTree3dOfNode.hxx>

#include <TopoDS_Shape.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;
using namespace MeshLib;

void AutLib::Example_CavityRemover::Case1()
{
	Open_OutputFile_TecPlot(Plot, "Example_CavityRemoverCase1");

	TopoDS_Shape Box = Cad3d_MakeSolid::Box(Geom_Pnt3d(0, 0, 0), Geom_Pnt3d(1, 0.5, 1));

	Cad3d_Solid Solid;
	Solid.Make(Cad3d_SolidTools::GetSurfaces(Box));

	SizeMap3d_UniSize UniSizeMap(0.02);

	/*Mesh3d_SolidMesher SolidMesher(UniSizeMap, Solid);
	SolidMesher.SetVerbosity(2);
	SolidMesher.Perform();
	SolidMesher.ExportMergedMeshToPlt(Plot);
	return;*/

	TColMesh3d_ADTree3dOfNode Engine;
	Engine.SetCoordinateFunction(&Mesh3d_NodeTools::GetCoordOf);

	Mesh3d_CavityRemover Aft(UniSizeMap, &Engine);
	Aft.Import(Solid);
	Aft.SetVerbosity(2);
	//Aft.SetToUseExactMetricForSurfaceMesh();
	Try_Exception_Handle_Exit(Aft.Perform());

	/*Aft.ExportToPlt(Plot);
	Aft.ExportCavitiesToPlt(Plot);
	return;*/

	forThose
	(
		Index,
		0,
		Aft.NbMeshes() - 1
	)
	{
		Entity_Tetrahedralization Tetrahedralization = Aft.Mesh(Index)->Static();

		Entity_Tetrahedralization Left, Right;
		Entity_TetrahedralizationTools::xCoord_Split(0.5, Tetrahedralization, Left, Right);

		Left.ExportToPlt(Plot);
		Right.ExportToPlt(Plot);

		Entity_TetrahedralizationTools::yCoord_Split(0.25, Tetrahedralization, Left, Right);

		Left.ExportToPlt(Plot);
		Right.ExportToPlt(Plot);
	}

	//Aft.ExportDomainToPlt(Plot);
	//Aft.ExportToPlt(Plot);
}