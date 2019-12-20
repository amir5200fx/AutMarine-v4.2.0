#pragma once
#ifndef _MetricMap_SingleMap2d_Header
#define _MetricMap_SingleMap2d_Header

#include <Geom_Pnt2d.hxx>
#include <Entity_Metric1.hxx>
#include <Entity_Metric2.hxx>
#include <Entity_Box2d.hxx>
#include <Mesh2d_MetricMap.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class MetricMap_SingleMap2d : public Mesh2d_MetricMap
		{

		private:

			M_GEO Entity_Metric1 theM_;

			M_GEO Entity_Metric2 theM2_;	

		public:

			MetricMap_SingleMap2d();

			MetricMap_SingleMap2d(const Standard_Real theH1, const Standard_Real theH2, const gp_Dir2d& theE1, const gp_Dir2d& theE2);

			MetricMap_SingleMap2d(const Standard_Real theH1, const Standard_Real theH2, const gp_Dir2d& theE1, const gp_Dir2d& theE2, const M_GEO Entity_Box2d& theBox);

			void Init(const Standard_Real theH1, const Standard_Real theH2, const gp_Dir2d& theE1, const gp_Dir2d& theE2);

			void Init(const Standard_Real theH1, const Standard_Real theH2, const gp_Dir2d& theE1, const gp_Dir2d& theE2, const M_GEO Entity_Box2d& theBox);

			virtual M_GEO Entity_Metric1 MetricAt(const GeoLib::Geom_Pnt2d& theCoord) const;

			virtual Standard_Real ElementQuality(const GeoLib::Geom_Pnt2d& theP0, const GeoLib::Geom_Pnt2d& theP1, const GeoLib::Geom_Pnt2d& theP2, const Mesh2d_QualityMap & theQualityMap) const;

			void SetH1(const Standard_Real theH1);

			void SetH2(const Standard_Real theH2);

			void SetE1(const gp_Dir2d& theE1);

			void SetE2(const gp_Dir2d& theE2);

		private:

			void CalcMetric();

		};
	}
}

#include <MetricMap_SingleMap2dI.hxx>

#endif // !_MetricMap_SingleMap2d_Header
