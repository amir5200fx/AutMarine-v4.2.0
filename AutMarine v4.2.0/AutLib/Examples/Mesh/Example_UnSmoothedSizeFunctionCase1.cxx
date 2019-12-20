#include <Examples\Mesh\Example_Mesh2d.hxx>

#include <Cad2d_Sketch.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_MakePlane.hxx>
#include <Cad2d_BooleanOperators.hxx>
#include <GeoMesh_TriangleMesh2d.hxx>
#include <GeoMesh_BackGroundMesh2dTools.hxx>
#include <Mesh2d_BasicAft.hxx>
#include <Mesh2d_NodeTools.hxx>
#include <Mesh2d_Domain.hxx>
#include <SizeMap2d_ModifyBackSize.hxx>
#include <SizeMap2d_FullIntBackSize.hxx>
#include <TColMesh2d_ADTree2dOfNode.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;

void AutLib::Example_Mesh2d::UnSmoothedSizeFunctionCase1()
{
	Open_OutputFile_TecPlot(Plot, "Example_UnSmoothedSizeFunctionCase1");

	Cad2d_Sketch Sketch1;
	Sketch1.CreateLine(Geom_Pnt2d(0, 0), Geom_Pnt2d(2, 0));
	Sketch1.CreateLine(Geom_Pnt2d(2, 0), Geom_Pnt2d(2, 0.9));
	Sketch1.CreateLine(Geom_Pnt2d(2, 0.9), Geom_Pnt2d(0, 0.9));
	Sketch1.CreateLine(Geom_Pnt2d(0, 0.9), Geom_Pnt2d(0, 0));

	TColGeom_BasicQueueOfPnt2d QPts1;
	QPts1.EnQueue(Geom_Pnt2d(0.1, 0.1));
	QPts1.EnQueue(Geom_Pnt2d(0.5, 0.1));
	QPts1.EnQueue(Geom_Pnt2d(1.0, 0.1));
	QPts1.EnQueue(Geom_Pnt2d(1.5, 0.1));
	QPts1.EnQueue(Geom_Pnt2d(1.9, 0.1));
	QPts1.EnQueue(Geom_Pnt2d(1.9, 0.2));
	QPts1.EnQueue(Geom_Pnt2d(1.5, 0.2));
	QPts1.EnQueue(Geom_Pnt2d(1.0, 0.2));
	QPts1.EnQueue(Geom_Pnt2d(0.5, 0.2));
	QPts1.EnQueue(Geom_Pnt2d(0.1, 0.2));
	QPts1.EnQueue(Geom_Pnt2d(0.1, 0.1));

	Cad2d_Sketch Sketch2;
	Sketch2.CreatePolygon(QPts1);

	TColGeom_BasicQueueOfPnt2d QPts2;
	QPts2.EnQueue(Geom_Pnt2d(0.1, 0.3));
	QPts2.EnQueue(Geom_Pnt2d(0.5, 0.3));
	QPts2.EnQueue(Geom_Pnt2d(1.0, 0.3));
	QPts2.EnQueue(Geom_Pnt2d(1.5, 0.3));
	QPts2.EnQueue(Geom_Pnt2d(1.9, 0.3));
	QPts2.EnQueue(Geom_Pnt2d(1.9, 0.4));
	QPts2.EnQueue(Geom_Pnt2d(1.5, 0.4));
	QPts2.EnQueue(Geom_Pnt2d(1.0, 0.4));
	QPts2.EnQueue(Geom_Pnt2d(0.5, 0.4));
	QPts2.EnQueue(Geom_Pnt2d(0.1, 0.4));
	QPts2.EnQueue(Geom_Pnt2d(0.1, 0.3));

	Cad2d_Sketch Sketch3;
	Sketch3.CreatePolygon(QPts2);

	TColGeom_BasicQueueOfPnt2d QPts3;
	QPts3.EnQueue(Geom_Pnt2d(0.1, 0.5));
	QPts3.EnQueue(Geom_Pnt2d(0.5, 0.5));
	QPts3.EnQueue(Geom_Pnt2d(1.0, 0.5));
	QPts3.EnQueue(Geom_Pnt2d(1.5, 0.5));
	QPts3.EnQueue(Geom_Pnt2d(1.9, 0.5));
	QPts3.EnQueue(Geom_Pnt2d(1.9, 0.6));
	QPts3.EnQueue(Geom_Pnt2d(1.5, 0.6));
	QPts3.EnQueue(Geom_Pnt2d(1.0, 0.6));
	QPts3.EnQueue(Geom_Pnt2d(0.5, 0.6));
	QPts3.EnQueue(Geom_Pnt2d(0.1, 0.6));
	QPts3.EnQueue(Geom_Pnt2d(0.1, 0.5));

	Cad2d_Sketch Sketch4;
	Sketch4.CreatePolygon(QPts3);

	TColGeom_BasicQueueOfPnt2d QPts4;
	QPts4.EnQueue(Geom_Pnt2d(0.1, 0.7));
	QPts4.EnQueue(Geom_Pnt2d(0.5, 0.7));
	QPts4.EnQueue(Geom_Pnt2d(1.0, 0.7));
	QPts4.EnQueue(Geom_Pnt2d(1.5, 0.7));
	QPts4.EnQueue(Geom_Pnt2d(1.9, 0.7));
	QPts4.EnQueue(Geom_Pnt2d(1.9, 0.8));
	QPts4.EnQueue(Geom_Pnt2d(1.5, 0.8));
	QPts4.EnQueue(Geom_Pnt2d(1.0, 0.8));
	QPts4.EnQueue(Geom_Pnt2d(0.5, 0.8));
	QPts4.EnQueue(Geom_Pnt2d(0.1, 0.8));
	QPts4.EnQueue(Geom_Pnt2d(0.1, 0.7));

	Cad2d_Sketch Sketch5;
	Sketch5.CreatePolygon(QPts4);

	Global_Handle(Cad2d_Plane) Box = Sketch1.MakePlane();
	Global_Handle(Cad2d_Plane) Inner1 = Sketch2.MakePlane();
	Global_Handle(Cad2d_Plane) Inner2 = Sketch3.MakePlane();
	Global_Handle(Cad2d_Plane) Inner3 = Sketch4.MakePlane();
	Global_Handle(Cad2d_Plane) Inner4 = Sketch5.MakePlane();

	Cad2d_Plane Shape;

	Cad2d_BooleanOperators::Subtract(Box, Inner1, &Shape);
	Cad2d_BooleanOperators::Subtract(&Shape, Inner2, &Shape);
	Cad2d_BooleanOperators::Subtract(&Shape, Inner4, &Shape);
	Cad2d_BooleanOperators::Subtract(&Shape, Inner3, &Shape);

	SizeMap2d_UniSize Map(2.0);

	TColMesh2d_ADTree2dOfNode Engine;
	Engine.SetCoordinateFunction(&Mesh2d_NodeTools::GetCoordOf);

	Mesh2d_BasicAft Aft(Map, &Engine);
	Aft.Import(Shape);
	Aft.SetVerbosity(1);
	Aft.LaplacianSmoothing().SetApply(Standard_False);

	Try_Exception_Handle_Exit(Aft.Perform());

	Aft.Domain(0).ExportMergedToPlt(Plot);
	Aft.ExportToPlt(Plot);
}