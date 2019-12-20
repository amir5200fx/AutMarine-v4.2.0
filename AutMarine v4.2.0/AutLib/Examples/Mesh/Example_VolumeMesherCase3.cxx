#include <Examples\Mesh\Example_VolumeMesher.hxx>

#include <IO_IGESRead.hxx>
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
#include <Mesh3d_SolidMesher.hxx>

#include <TopoDS_Shape.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;
using namespace GeoLib;
using namespace IoLib;

void AutLib::Example_VolumeMesher::Case3()
{
	Open_OutputFile_TecPlot(Plot, "Example_VolumeMesherCase3");

	TopoDS_Shape Rod;
	IO_IGESRead::ReadFileNonDiscretized("rod.IGS", Rod);

	Cad3d_Solid Solid;
	Solid.Make(Cad3d_SolidTools::GetSurfaces(Rod));

	SizeMap3d_UniSize Map(1.0);

	Mesh3d_SolidMesher SolidMesher(Map, Solid);
	//SolidMesher.UseExactMetric();
	SolidMesher.SetVerbosity(2);
	SolidMesher.Perform();

	SolidMesher.ExportMeshToPlt(Plot);
	return;
}