#include <Global_Macros.hxx>
#include <Standard_TypeDef.hxx>
#include <iostream>
#include <fstream>
#include <memory>

#include <Examples\Cad\Example_Plane.hxx>
#include <Examples\Cad\Example_Intersection.hxx>
#include <Examples\Cad\Example_Solid.hxx>
#include <Examples\SizeMap\Example_SizeMap.hxx>
#include <Examples\Mesh\Example_Mesh2d.hxx>
#include <Examples\Mesh\Example_AnIsoMesh2d.hxx>
#include <Examples\Mesh\Example_SurfaceMesher.hxx>
#include <Examples\Mesh\Example_SolidMesher.hxx>
#include <Examples\Mesh\Example_VolumeMesher.hxx>
#include <Examples\Mesh\Example_CavityRemover.hxx>
#include <Examples\Mesh\Example_Region2d.hxx>
#include <Examples\Mesh\Example_Region3d.hxx>
#include <Examples\Mesh\Example_ShapeMesher.hxx>

using namespace AutLib;

#include <Geom\Shewchuk\predicates.h>
//#include <vld.h>

#include <Entity_TriangulatedShape2d.hxx>

#include <Numeric_Eigen.hxx>

using namespace GeoLib;

Standard_Integer main()
{
	exactinit(1);
	//Example_SizeMap::CreateSizeMapCase1();
	//Example_Intersection::PlanePlaneBooleanCase1();
	//Example_Mesh2d::UnSmoothedSizeFunctionCase1();
	//Example_Plane::SharpCornersCase1();
	//Example_Plane::NacaCase1();
	//Example_Mesh2d::MeshCase6();
	//Example_Plane::CreateCurveCase1();
	//Example_Solid::MakePropellerCase1();
	//Example_Solid::OpenIGES();
	//Example_AnIsoMesh2d::Case1();
	//Example_SurfaceMesher::Case2();
	//Example_SolidMesher::Case1();
	//Example_Solid::MakeCfdPropellerCase1();
	Example_VolumeMesher::Case4();
	//Example_CavityRemover::Case1();
	//Example_Region3d::Case2();
	//Example_Solid::MakeCfdShipCase1();
	//Example_ShapeMesher::Case1();
	//Example_Solid::MakeDuctCase1();
	//Example_Mesh2d::MeshCase1();
	//Example_Region2d::Case4();

	/*TColStd_Ary2dOfReal mat(2, 2);
	TColStd_Ary1dOfReal eVals1(2);
	TColStd_Ary2dOfReal eVecs1(2, 2);

	mat[0][0] = 0;
	mat[0][1] = 1;
	mat[1][0] = -2;
	mat[1][1] = -3;

	NumLib::Numeric_Eigen::CalcEigen(mat, eVals1, eVecs1, 1.0e-6);

	cout << std::endl;
	cout << std::endl;
	cout << eVals1[0] << "  " << eVals1[1] << std::endl;
	cout << std::endl;
	cout << eVecs1[0][0] << "  " << eVecs1[1][0] << std::endl;
	cout << eVecs1[0][1] << "  " << eVecs1[1][1] << std::endl;*/

	/*Open_OutputFile_TecPlot(Plot, "Plot");
	Entity_TriangulatedShape2d Circle;
	Circle.MakeCircle(Geom_Pnt2d(0.3, 0.8), 0.45, 40);
	Circle.ExportToPlt(Plot);*/

	PAUSE;
}