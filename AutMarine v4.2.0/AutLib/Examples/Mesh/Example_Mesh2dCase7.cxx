#include <Examples\Mesh\Example_Mesh2d.hxx>

#include <Cad2d_MakePlane.hxx>
#include <Cad2d_BooleanOperators.hxx>
#include <Cad2d_EdgeOnPlane.hxx>
#include <Cad2d_BlockEdgeOnPlane.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh2d_NodeTools.hxx>
#include <Mesh2d_BasicAft.hxx>
#include <SizeMap2d_UniSize.hxx>
#include <SizeMap2d_UniSizeTools.hxx>
#include <SizeMap2d_ModifyBackSize.hxx>
#include <SizeMap2d_CorrectSizeMapTool.hxx>
#include <SizeMap2d_UniformCurvesSizeMapTool.hxx>
#include <TColMesh2d_ADTree2dOfNode.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;
using namespace MeshLib;

#include <gp_Ax22d.hxx>

void AutLib::Example_Mesh2d::MeshCase7()
{
	Open_OutputFile_TecPlot(Plot, "Example_MeshCase7");

	Cad2d_MakePlane Box, Circle;
	Box.Box(Geom_Pnt2d(), Geom_Pnt2d(0.3, 1.2));
	Circle.Circle(gp_Ax2d(Geom_Pnt2d(0.4, 0.5), gp_Dir2d(1.0, 0)), 0.5);

	Cad2d_Plane Sum;
	Cad2d_BooleanOperators::Union(&Box, &Circle, &Sum);

	Entity_Box2d BoundingBox = Sum.BoundingBox();

	Get_Pointer(Edges) = Sum.Edges();
	Debug_Null_Pointer(Edges);

	Get_Const_Pointer(Block) = Edges->SelectBlockCurve("Default Block Edge");
	Debug_Null_Pointer(Block);

	Block->SelectCurve(4);
	Edges->Split("Source");

	SizeMap2d_UniSize UniSize(0.08);

	SizeMap2d_CorrectSizeMapTool Correct(&Sum, SizeMap2d_UniSizeTools::GetBackMeshFrom(UniSize, BoundingBox.OffsetBox(0.25*BoundingBox.Diameter())));
	Correct.Perform();

	SizeMap2d_ModifyBackSize Map(1.0, *Correct.Modified());

	TColMesh2d_ADTree2dOfNode Engine;
	Engine.SetCoordinateFunction(&Mesh2d_NodeTools::GetCoordOf);

	Mesh2d_BasicAft Aft(Map, &Engine);
	Aft.Import(Sum);
	Aft.SetVerbosity(1);
	Try_Exception_Handle_Exit(Aft.Perform());

	Aft.ExportToPlt(Plot);
}