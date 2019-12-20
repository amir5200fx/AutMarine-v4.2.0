#pragma once
#ifndef _MetricMap2d_MetricMapTool_Header
#define _MetricMap2d_MetricMapTool_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <Standard_TypeDef.hxx>
#include <Standard_Stream.hxx>
#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class GeoMesh_BackGroundMetric2d;
		class Entity_Metric1;
	}

	namespace MeshLib
	{

		class MetricMap2d_MetricMapTool
		{

		protected:

			Global_Handle(M_GEO GeoMesh_BackGroundMetric2d) theBackMetric_;

			GeoLib::Entity_Metric1(*InterSection)(const M_GEO Entity_Metric1&, const M_GEO Entity_Metric1&);

			Standard_Real theH1_;
			Standard_Real theH2_;

			Geom_Pnt2d theE1_;
			Geom_Pnt2d theE2_;

		public:

			~MetricMap2d_MetricMapTool();

			Global_Handle(M_GEO GeoMesh_BackGroundMetric2d) Metric() const;

			void SetH1(const Standard_Real theH1);

			void SetH2(const Standard_Real theH2);

			void SetE1(const Geom_Pnt2d& theE1);

			void SetE2(const Geom_Pnt2d& theE2);

			void SetIntersection(GeoLib::Entity_Metric1(*theInterSection)(const M_GEO Entity_Metric1&, const M_GEO Entity_Metric1&));

			void ExportToPlt(fstream& File) const;

		protected:

			MetricMap2d_MetricMapTool();
		};
	}
}

#include <MetricMap2d_MetricMapToolI.hxx>

#endif // !_MetricMap2d_MetricMapTool_Header
