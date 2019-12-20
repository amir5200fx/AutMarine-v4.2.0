#include <Examples\Mesh\Example_SurfaceMesher.hxx>

#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include <BRepMesh_FastDiscret.hxx>
#include <TopoDS_Face.hxx>
#include <Geom_BSplineCurve.hxx>
#include <GeomAPI_PointsToBSpline.hxx>
#include <BRepPrimAPI_MakeRevolution.hxx>
#include <IO_Tecplot.hxx>
#include <Mesh3d_SurfaceMesher.hxx>
#include <SizeMap3d_UniSize.hxx>
#include <TColGeom_BasicQueueOfPnt3d.hxx>

using namespace AutLib;
using namespace IoLib;
using namespace MeshLib;

void AutLib::Example_SurfaceMesher::Case1()
{
	Open_OutputFile_TecPlot(Plot, "Example_SurfaceMesherCase1");

	TColGeom_BasicQueueOfPnt3d Qpoints;
	Qpoints.EnQueue(Geom_Pnt3d(0.1, 0, 0));
	Qpoints.EnQueue(Geom_Pnt3d(0.12, 0, 0.1));
	Qpoints.EnQueue(Geom_Pnt3d(0.14, 0, 0.2));
	Qpoints.EnQueue(Geom_Pnt3d(0.18, 0, 0.3));
	Qpoints.EnQueue(Geom_Pnt3d(0.19, 0, 0.35));
	Qpoints.EnQueue(Geom_Pnt3d(0.195, 0, 0.4));
	Qpoints.EnQueue(Geom_Pnt3d(0.2, 0, 0.55));
	Qpoints.EnQueue(Geom_Pnt3d(0.195, 0, 0.6));
	Qpoints.EnQueue(Geom_Pnt3d(0.15, 0, 0.65));
	Qpoints.EnQueue(Geom_Pnt3d(0.1, 0, 0.7));
	Qpoints.EnQueue(Geom_Pnt3d(0.12, 0, 0.8));
	Qpoints.EnQueue(Geom_Pnt3d(0.15, 0, 1.0));

	Standard_Integer K = 1;
	Geom_Pnt3d Point;
	TColgp_Array1OfPnt Points(1, Qpoints.Size());
	while (Qpoints.DeQueue(Point))
	{
		Points.SetValue(K++, Point);
	}

	GeomAPI_PointsToBSpline Interpolation(Points, 3, 3);
	
	Debug_If_Condition_Message(NOT Interpolation.IsDone(), "Interpolation is not performed");

	Handle(Geom_BSplineCurve) Curve = Interpolation.Curve();

	BRepPrimAPI_MakeRevolution Rev(Curve, Curve->FirstParameter(), Curve->LastParameter(), 2 * M_PI);

	Debug_If_Condition_Message(NOT Rev.IsDone(), "Revolution is not performed");

	TopoDS_Face Face = Rev.Face();

	/*BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.015;
	Params.Angle = 0.025;

	Bnd_Box Box;
	BRepBndLib::Add(Face, Box);
	BRepMesh_FastDiscret Mesh(Box, Params);

	Mesh.Perform(Face);

	IO_TecPlot::ExportSurface(Face, Plot);
	return;*/
	SizeMap3d_UniSize UniSize(0.025);

	Mesh3d_SurfaceMesher Mesher(UniSize, Face);
	//Mesher.UseExactMetric();
	Mesher.SetVerbosity(1);
	Mesher.Perform();

	Mesher.ExportSurfaceMeshToPlt(Plot);
}