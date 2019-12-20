#pragma once
#ifndef _Mesh2d_MetricSourcePoint_Header
#define _Mesh2d_MetricSourcePoint_Header

#include <Geom_Pnt2d.hxx>
#include <Entity_Metric1.hxx>
#include <Mesh2d_SourcePoint.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_MetricSourcePoint : public Mesh2d_SourcePoint
		{

		private:

			M_GEO Entity_Metric1 theMetric_;

		public:

			Mesh2d_MetricSourcePoint();

			Mesh2d_MetricSourcePoint(const Geom_Pnt2d& theCoord, const M_GEO Entity_Metric1& theMetric);

			void Init(const Geom_Pnt2d& theCoord, const M_GEO Entity_Metric1& theMetric);

			void SetMetric(const M_GEO Entity_Metric1& theMetric);

			const M_GEO Entity_Metric1& Metric() const;
		};
	}
}

#include <Mesh2d_MetricSourcePointI.hxx>

#endif // !_Mesh2d_MetricSourcePoint_Header
