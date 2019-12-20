#pragma once
#ifndef _IO_Tecplot_Header
#define _IO_Tecplot_Header

#include <Standard_Handle.hxx>
#include <Standard_Stream.hxx>
#include <Standard_Integer.hxx>
#include <Standard_String.hxx>
#include <TColStd_Ary1dOfReal.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <TColEntity_HAry1dOfBox2d.hxx>
#include <TColEntity_HAry1dOfBox3d.hxx>
#include <TColEntity_Ary1dOfEdgeIndex.hxx>
#include <TColEntity_Ary1dOfTriangleIndex.hxx>
#include <TColEntity_Ary1dOfTetrahedronIndex.hxx>
#include <TColgp_Array1OfPnt.hxx>
#include <Poly_Array1OfTriangle.hxx>

class TopoDS_Wire;
class TopoDS_Edge;
class TopoDS_Face;
class TopoDS_Shape;
class Geom_Curve;
class Geom2d_Curve;
class Geom_Surface;
class Poly_Triangulation;

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Box3d;
		class Entity_Triangulation2d;
		class Entity_Triangulation3d;
		class Entity_Tetrahedralization;
	}

	class Primitive_Field;

	namespace IoLib
	{

		class IO_TecPlot
		{

		public:

			static void ExportMetric(const Standard_Real H1, const Standard_Real H2, const Geom_Pnt2d& E1, const Geom_Pnt2d& E2, const Geom_Pnt2d& Centre, fstream& File);

			static void ExportACircle(const Standard_Real r, const Geom_Pnt2d& Centre, fstream& File);

			static void ExportAnEllipse(const Standard_Real a, const Standard_Real b, const Geom_Pnt2d& Centre, fstream& File);

			static void Export_I_Ordered(const TColStd_Ary1dOfReal& XCoords, const TColStd_Ary1dOfReal& YCoords, const Standard_String Variables, const Standard_String MapName, fstream& File);

			static void ExportBox(const TColEntity_HAry1dOfBox2d& Boxes, fstream & File);

			static void ExportBox(const TColEntity_HAry1dOfBox3d& Boxes, fstream & File);

			static void ExportBox(const M_GEO Entity_Box2d& Box, fstream & File);

			static void ExportBox(const M_GEO Entity_Box3d& Box, fstream & File);

			static void ExportPoint(const Geom_Pnt2d& Point, fstream & File);

			static void ExportPoint(const Geom_Pnt3d& Point, fstream & File);

			static void ExportPoints(const TColGeom_Ary1dOfPnt2d& Points, fstream& File);

			static void ExportPoints(const TColGeom_Ary1dOfPnt3d& Points, fstream& File);

			static void ExportCurve(const Geom_Pnt3d& theP0, const Geom_Pnt3d& theP1, fstream& File);

			static void ExportCurve(const TColGeom_Ary1dOfPnt2d& Points, fstream& File);

			static void ExportCurve(const TColGeom_Ary1dOfPnt3d& Points, fstream& File);

			static void ExportCurve(const Geom_Curve& Curve, const Standard_Real First, const Standard_Real Last, const Standard_Integer NbSegmets, fstream& File);

			static void ExportCurve(const Geom2d_Curve& Curve, const Standard_Real First, const Standard_Real Last, const Standard_Integer NbSegmets, fstream& File);

			static void ExportCurve(const TopoDS_Edge& Curve, const Standard_Integer NbSegmets, fstream& File);

			static void ExportCurve(const TopoDS_Shape& Body, const Standard_Integer NbSegmets, fstream& File);

			static void ExportSurface(const TopoDS_Face& Patch, fstream& File);

			static void ExportSurface(const Geom_Surface& theSurface, const Standard_Real theUmin, const Standard_Real theUmax, const Standard_Real theVmin, const Standard_Real theVmax, const Standard_Integer NbSegmetsU, const Standard_Integer NbSegmetsV, fstream& File);

			static void ExportMesh(const TColGeom_Ary1dOfPnt2d& Points, const TColEntity_Ary1dOfTriangleIndex& Triangles, fstream& File);

			static void ExportMesh(const TColGeom_Ary1dOfPnt3d& Points, const TColEntity_Ary1dOfTriangleIndex& Triangles, fstream& File);

			static void ExportMesh(const TColgp_Array1OfPnt& Points, const Poly_Array1OfTriangle& Triangles, fstream& File);

			static void ExportMesh(const TColGeom_Ary1dOfPnt2d& Points, const TColEntity_Ary1dOfEdgeIndex& Edges, fstream& File);

			static void ExportMesh(const TColGeom_Ary1dOfPnt3d& Points, const TColEntity_Ary1dOfEdgeIndex& Edges, fstream& File);

			static void ExportMesh(const TColGeom_Ary1dOfPnt3d& Points, const TColEntity_Ary1dOfTetrahedronIndex& Elements, fstream& File);

			static void ExportMesh(const Handle(Poly_Triangulation)& theTriangulation, fstream& File);

			static void ExportShape(const TopoDS_Shape& Shape, fstream& File);

			static void ExportField(const M_GEO Entity_Triangulation2d& Mesh, const Primitive_Field & Field, fstream& File);

			static void ExportField(const M_GEO Entity_Tetrahedralization& Mesh, const Primitive_Field & Field, fstream& File);

			static void ExportCellCenteredField(const M_GEO Entity_Tetrahedralization& Mesh, const Primitive_Field & Field, fstream& File);

			static void ExportCellCenteredField(const M_GEO Entity_Triangulation2d& Mesh, const Primitive_Field & Field, fstream& File);

			static void ExportCellCenteredField(const M_GEO Entity_Triangulation3d& Mesh, const Primitive_Field & Field, fstream& File);
		};
	}
}

#endif // !_IO_Tecplot_Header
