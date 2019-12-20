#include <Examples\Mesh\Example_SurfaceMesher.hxx>

#include <Ship_Hull.hxx>
#include <Bnd_B2d.hxx>
#include <TopoDS.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Face.hxx>

#include <Mesh3d_SurfaceMesher.hxx>
#include <SizeMap3d_UniSize.hxx>
#include <SizeMap2d_FullIntAnIsoTools.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;

void AutLib::Example_SurfaceMesher::Case3()
{
	Open_OutputFile_TecPlot(Plot, "Example_SurfaceMesherCase3");

	Ship_Hull Hull;

	Hull.Make();

	Standard_Integer K = 0;

	TopoDS_Shape Ship = Hull.Shape();
	for (TopExp_Explorer Explorer(Ship, TopAbs_FACE); Explorer.More(); Explorer.Next())
	{
		TopoDS_Face Face = TopoDS::Face(Explorer.Current());

		K++;

		//if (K <= 1) continue;

		SizeMap3d_UniSize UniSize(1.5);

		Mesh3d_SurfaceMesher Mesher(UniSize, Face);

		Mesher.SetVerbosity(1);
		//Mesher.UseExactMetric();
		Mesher.SetAnIsoSizeMap(&SizeMap2d_FullIntAnIsoTools::CreateModifiedSearchAnIsoSizeMap);
		
		try
		{
			Mesher.Perform();
		}
		catch (Global_Failure& x)
		{
			continue;
		}

		//Mesher.ExportSurfaceMeshToPlt(Plot);
		//Mesher.ExportSingularityHorizonToPlt(Plot);
		Mesher.ExportSurfaceMeshToPlt(Plot);

		
		//if (K > 1) break;
	}

}