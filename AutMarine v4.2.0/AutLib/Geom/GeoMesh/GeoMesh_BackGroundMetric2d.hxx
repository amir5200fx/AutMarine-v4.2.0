#pragma once
#ifndef _GeoMesh_BackGroundMetric2d_Header
#define _GeoMesh_BackGroundMetric2d_Header

#include <GeoMesh_TriangleMesh2d.hxx>
#include <TColEntity_Ary1dOfMetric1.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Box2d;

		class GeoMesh_BackGroundMetric2d
		{

		private:

			GeoMesh_TriangleMesh2d theMesh_;

			mutable TColEntity_Ary1dOfMetric1 theSources_;

			mutable Global_Handle(Entity_Element2d) theCurrentElement_;

			Global_Handle(Entity_Box2d) theBoundingBox_;

			Standard_Real theTolerance_;

			Entity_Metric1(*InterSection_)(const M_GEO Entity_Metric1&, const M_GEO Entity_Metric1&);

		public:

			GeoMesh_BackGroundMetric2d();

			GeoMesh_BackGroundMetric2d(const GeoMesh_TriangleMesh2d& StaticMesh);

			~GeoMesh_BackGroundMetric2d();

			Entity_Metric1 MetricAt(const Geom_Pnt2d& Coord) const;

			Entity_Metric1 MetricAt(const Geom_Pnt2d& Coord, Standard_Boolean & Sense) const;

			TColEntity_Ary1dOfMetric1& Sources() const;

			GeoMesh_TriangleMesh2d& Mesh();

			const GeoMesh_TriangleMesh2d& Mesh() const;

			const Global_Handle(Entity_Box2d) BoundingBox() const;

			void SetBoundingBox(const Entity_Box2d& theBoundingBox);

			void SetIntersection(Entity_Metric1(*InterSection)(const M_GEO Entity_Metric1&, const M_GEO Entity_Metric1&));

			void HvCorrection(const Standard_Real Factor, const Standard_Integer MaxInnerIteration = 3);

			void LaplacianSmoothing(const Standard_Integer NbIterations = 3, const Standard_Real MaxRatio = 5.0, const Standard_Real Factor = 0.3);

			void InitiateCurrentElement() const;

			void SetCurrentElement(const Global_Handle(Entity_Element2d) theElement) const;

			void ExportToPlt(fstream & File) const;

			void ExportToPlt(fstream & File, const Standard_Real theElementSize) const;

			void ExportMeshToPlt(fstream& File) const;

			void ExportMetricDeterminantToPlt(fstream& File) const;

		};
	}
}

#include <GeoMesh_BackGroundMetric2dI.hxx>

#endif // !_GeoMesh_BackGroundMetric2d_Header
