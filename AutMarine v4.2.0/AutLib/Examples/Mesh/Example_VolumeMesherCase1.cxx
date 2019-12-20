#include <Examples\Mesh\Example_VolumeMesher.hxx>

#include <Entity_Tetrahedralization.hxx>
#include <Entity_TetrahedralizationTools.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_MakeSolid.hxx>
#include <Cad3d_SolidTools.hxx>
#include <Cad3d_BooleanOperators.hxx>
#include <SizeMap3d_UniSize.hxx>
#include <Mesh3d_SolidMesher.hxx>
#include <Mesh3d_BasicAft.hxx>
#include <Mesh3d_NodeTools.hxx>
#include <IO_IGESRead.hxx>
#include <IO_STEPRead.hxx>
#include <TColMesh3d_ADTree3dOfNode.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;
using namespace GeoLib;

#include <gp_Ax2.hxx>
#include <TopoDS_Shape.hxx>

void AutLib::Example_VolumeMesher::Case1()
{
	Open_OutputFile_TecPlot(Plot, "Example_VolumeMesherCase1");

	/*TopoDS_Shape Box = Cad3d_MakeSolid::Box(Geom_Pnt3d(-1, -6, -2), Geom_Pnt3d(10, 6, 2));	
	TopoDS_Shape Torus = Cad3d_MakeSolid::Torus(3, 1);

	TopoDS_Shape Sum = Cad3d_BooleanOperators::Union(Box, Torus);

	TopoDS_Shape Cylinder1 = Cad3d_MakeSolid::Cylinder(gp_Ax2(gp_Pnt(2, -3, -3), gp_Dir(0, 0, 1)), 1.0, 6);
	TopoDS_Shape Cylinder2 = Cad3d_MakeSolid::Cylinder(gp_Ax2(gp_Pnt(2, 3, -3), gp_Dir(0, 0, 1)), 1.0, 6);
	TopoDS_Shape Cylinder3 = Cad3d_MakeSolid::Cylinder(gp_Ax2(gp_Pnt(8, -3, -3), gp_Dir(0, 0, 1)), 1.0, 6);
	TopoDS_Shape Cylinder4 = Cad3d_MakeSolid::Cylinder(gp_Ax2(gp_Pnt(8, 3, -3), gp_Dir(0, 0, 1)), 1.0, 6);

	Sum = Cad3d_BooleanOperators::Subtract(Sum, Cylinder1);
	Sum = Cad3d_BooleanOperators::Subtract(Sum, Cylinder2);
	Sum = Cad3d_BooleanOperators::Subtract(Sum, Cylinder3);
	Sum = Cad3d_BooleanOperators::Subtract(Sum, Cylinder4);

	Sum = Cad3d_SolidTools::RepairWithIGES(Sum);

	Cad3d_SolidTools::Triangulation(Sum);*/

	TopoDS_Shape Sum;
	//M_IO IO_IGESRead::ReadFileNonDiscretized("Sitting Woman V1.igs", Sum);
	M_IO IO_STEPRead::ReadFileNonDiscretized("Sitting Woman v1.step", Sum);

	Cad3d_Solid Solid;
	Solid.Make(Cad3d_SolidTools::GetSurfaces(Sum));

	SizeMap3d_UniSize UniSizeMap(0.02);

	//Mesh3d_SolidMesher SolidMesher(UniSizeMap, Solid);
	////SolidMesher.UseExactMetric();
	//SolidMesher.SetVerbosity(2);
	//SolidMesher.Perform();

	//SolidMesher.ExportMeshToPlt(Plot);
	//return;

	/*Cad3d_Solid Solid2;
	Solid2.Make(Cad3d_SolidTools::GetSurfaces(Shape2));

	Cad3d_Solid Solid3;
	Solid3.Make(Cad3d_SolidTools::GetSurfaces(Shape4));*/

	//Solid.ExportToPlt(Plot);
	//Solid2.ExportToPlt(Plot);
	//Solid3.ExportToPlt(Plot);

	/*Cad3d_Solid Solid;
	Solid.Make(Cad3d_SolidTools::GetSurfaces(Shape));

	SizeMap3d_UniSize UniSizeMap(0.035);*/

	TColMesh3d_ADTree3dOfNode Engine;
	Engine.SetCoordinateFunction(&Mesh3d_NodeTools::GetCoordOf);

	Mesh3d_BasicAft Aft(UniSizeMap, &Engine);
	Aft.Import(Solid);
	Aft.SetVerbosity(2);
	//Aft.SetToUseExactMetricForSurfaceMesh();
	Try_Exception_Handle_Exit(Aft.Perform());

	Aft.ExportDomainToPlt(Plot);
	Aft.ExportToPlt(Plot);

	forThose
	(
		Index,
		0, 
		Aft.NbMeshes() - 1
	)
	{
		Entity_Tetrahedralization Tetrahedralization = Aft.Mesh(Index)->Static();

		Entity_Tetrahedralization Left, Right;
		Entity_TetrahedralizationTools::yCoord_Split(1, Tetrahedralization, Left, Right);

		Left.ExportToPlt(Plot);
		Right.ExportToPlt(Plot);
	}
}