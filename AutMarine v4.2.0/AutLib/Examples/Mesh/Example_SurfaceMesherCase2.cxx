#include <Examples\Mesh\Example_SurfaceMesher.hxx>

#include <Bnd_B2d.hxx>
#include <TopoDS.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Face.hxx>
#include <Cad3d_MakeSolid.hxx>
#include <Mesh3d_SurfaceMesher.hxx>
#include <SizeMap3d_UniSize.hxx>
#include <SizeMap2d_FullIntAnIsoTools.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;

static TopoDS_Face GetSphereSurface()
{
	TopoDS_Shape Sphere = Cad3d_MakeSolid::Sphere(Geom_Pnt3d(0, 0, 0), 1.0);

	TopoDS_Face Face;
	for (TopExp_Explorer Explorer(Sphere, TopAbs_FACE); Explorer.More(); Explorer.Next())
	{
		Face = TopoDS::Face(Explorer.Current());

		return Face;
	}
	return Face;
}

void AutLib::Example_SurfaceMesher::Case2()
{
	Open_OutputFile_TecPlot(Plot, "Example_SurfaceMesherCase2");

	SizeMap3d_UniSize UniSize(0.05);

	TopoDS_Face Face = ::GetSphereSurface();

	Mesh3d_SurfaceMesher Mesher(UniSize, Face);

	Mesher.SetVerbosity(1);
	//Mesher.UseExactMetric();
	Mesher.SetAnIsoSizeMap(&SizeMap2d_FullIntAnIsoTools::CreateModifiedSearchAnIsoSizeMap);
	Mesher.Perform();

	Mesher.ExportSurfaceMeshToPlt(Plot);
}