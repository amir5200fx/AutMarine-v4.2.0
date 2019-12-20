#pragma once
#ifndef _Cad3d_SurfaceOnSolid_Header
#define _Cad3d_SurfaceOnSolid_Header

#include <Standard_Handle.hxx>
#include <Standard_Type.hxx>
#include <Geom_Pnt2d.hxx>
#include <Geom_Pnt3d.hxx>
#include <Cad3d_EntityOnSolid.hxx>
#include <Cad3d_SurfaceOrientationInfo.hxx>
#include <TColCad3d_HAry1dOfEdgeOnSolid.hxx>
#include <TColCad3d_HAry1dOfEdgeOnPlane.hxx>
#include <TColCad3d_HAry1dOfCurveOnPlane.hxx>

class Geom_Surface;
class Poly_Triangulation;

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Box3d;
		class Entity_Box2d;
		class Entity_Triangulation2d;
		class Entity_StaticChain3d;
	}

	namespace CadLib
	{
		class Cad2d_Plane;
		class Cad3d_Plane;

		class Cad3d_SurfaceOnSolid : public Cad3d_EntityOnSolid
		{

		private:

			Handle(Geom_Surface) theGeom_;
			Handle(Poly_Triangulation) theTriangulation_;

			Global_Handle(Cad3d_Plane) thePlane_;

			TColCad3d_HAry1dOfEdgeOnSolid theEdges_;

			Standard_Real theUmin_;
			Standard_Real theUmax_;
			Standard_Real theVmin_;
			Standard_Real theVmax_;

			Cad3d_SurfaceOrientationInfo theOrientation_;

			Standard_Real theParametricTolerance_;

		public:

			Cad3d_SurfaceOnSolid();

			~Cad3d_SurfaceOnSolid();

			void Init(const Standard_Integer Index, const Handle(Geom_Surface)& Geometry, const TColCad3d_HAry1dOfEdgeOnSolid& Edges);

			void SetGeometry(const Handle(Geom_Surface)& Geometry);

			void SetEdges(const TColCad3d_HAry1dOfEdgeOnSolid& Edges);

			void SetTriangulation(const Handle(Poly_Triangulation)& Triangulation);

			void SetOrientation(const Cad3d_SurfaceOrientationInfo theOrientation);

			void RetrieveParametricCurvesTo(TColCad3d_HAry1dOfCurveOnPlane& Curves) const;

			void GetParametricPlane(Cad2d_Plane& Plane) const;

			void CalcBoundingParameters();

			void GetParametricTriangulation(GeoLib::Entity_Triangulation2d& Triangulation) const;

			void UpdateOrientation();

			void UReverseOrientation();

			Standard_Integer NbEdges() const;

			Standard_Real Umin() const;

			Standard_Real Umax() const;

			Standard_Real Vmin() const;

			Standard_Real Vmax() const;

			Standard_Boolean HasTriangulation() const;

			Standard_Boolean HasFreeEdge() const;

			Cad3d_SurfaceOrientationInfo Orientation() const;

			Geom_Pnt3d Value(const Geom_Pnt2d& theParameter) const;

			Geom_Pnt3d NormalAt(const Geom_Pnt2d& theParameter) const;

			Geom_Pnt3d NormalAt(const Geom_Pnt2d& theParameter, Geom_Pnt3d& theCoord) const;

			GeoLib::Entity_Box3d BoundingBox(const Standard_Real Offset = 0.0) const;

			GeoLib::Entity_Box2d ParametricBoundingBox(const Standard_Real Offset = 0.0) const;

			GeoLib::Entity_StaticChain3d GetGeometricNormals(const Standard_Real theCoeff = 0.01) const;

			GeoLib::Entity_StaticChain3d GetTriangulationNormals(const Standard_Real theCoeff = 0.01) const;

			const Handle(Geom_Surface)& Geometry() const;

			const Handle(Poly_Triangulation)& Triangulation() const;

			Global_Handle(Cad3d_Plane) Plane() const;

			const TColCad3d_HAry1dOfEdgeOnSolid& Edges() const;

			void ExportTriangulationToPlt(fstream& File) const;

			void ExportParametricCurvesToPlt(fstream& File) const;

			void ExportCurveToPlt(fstream& File) const;

			void ExportTopologyToPlt(fstream& File) const;

			void ExportRopologyFromParametricPlaneToPlt(fstream& File) const;

			void ExportGeometryNormalsToPlt(fstream& File, const Standard_Real theCoeff = 0.01) const;

			void ExportTriangulationNormalsToPlt(fstream& File) const;

			virtual void ExportToPlt(fstream& File) const;

		private:

			void ReleaseMemory();

			void UReverseTriangulation();

			void CreatePlane();
		};
	}
}

#include <Cad3d_SurfaceOnSolidI.hxx>

#endif // !_Cad3d_SurfaceOnSolid_Header
