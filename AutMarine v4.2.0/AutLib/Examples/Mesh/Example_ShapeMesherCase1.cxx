#include <Examples\Mesh\Example_ShapeMesher.hxx>

#include <Cad3d_MakeSolid.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_SolidTools.hxx>
#include <Mesh3d_SolidMesher.hxx>
#include <QualityMap2d_Vlrms2Ratio.hxx>
#include <SizeMap3d_UniSize.hxx>
#include <IO_IGESRead.hxx>

#include <TopoDS_Shape.hxx>

using namespace AutLib;
using namespace MeshLib;
using namespace CadLib;
using namespace IoLib;

void AutLib::Example_ShapeMesher::Case1()
{
	Open_OutputFile_TecPlot(Plot, "Example_ShapeMesher");

	TopoDS_Shape Shape = Cad3d_MakeSolid::Sphere(Geom_Pnt3d(), 1.0);
	//IO_IGESRead::ReadFileNonDiscretized("Assem1.igs", Shape);

	Cad3d_Solid Solid;
	Solid.Make(Cad3d_SolidTools::GetSurfaces(Shape));

	SizeMap3d_UniSize Uni(0.05);

	Mesh3d_SolidMesher Mesher(Uni, Solid);
	//Mesher.SetToUseExactMetric();
	Mesher.ApplyOptimization(Standard_False);
	Mesher.ApplySmoothing(Standard_False);
	Mesher.Perform();


	//Mesher.ExportMeshToPlt(Plot);
}