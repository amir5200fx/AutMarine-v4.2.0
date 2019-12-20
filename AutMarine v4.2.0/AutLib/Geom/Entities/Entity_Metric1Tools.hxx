#pragma once
#ifndef _Entity_Metric1Tools_Header
#define _Entity_Metric1Tools_Header

#include <Entity_Metric1.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Geom_Pnt2d;

		class Entity_Metric1Tools
		{

		public:

			static Entity_Metric1 CalcMetric(const Standard_Real Lamda1, const Standard_Real Lamda2, const Geom_Pnt2d& E1, const Geom_Pnt2d& E2);

			static Entity_Metric1 Avg(const Entity_Metric1& M1, const Entity_Metric1& M2);

			static Entity_Metric1 IntersectionSR(const Entity_Metric1& M1, const Entity_Metric1& M2);

			static Entity_Metric1 IntersectionPD(const Entity_Metric1& M1, const Entity_Metric1& M2);

			static Entity_Metric1 InterpolationSMR(const Standard_Real t, const Entity_Metric1& M1, const Entity_Metric1& M2);

			static Entity_Metric1 InterpolationIM(const Standard_Real t, const Entity_Metric1& M1, const Entity_Metric1& M2);

			static Entity_Metric1 InterpolationIM(const Standard_Real c1, const Standard_Real c2, const Standard_Real c3, const Entity_Metric1& M1, const Entity_Metric1& M2, const Entity_Metric1& M3);

			static Entity_Metric1 InterpolationIM1(const Standard_Real c1, const Standard_Real c2, const Standard_Real c3, const Entity_Metric1& M1, const Entity_Metric1& M2, const Entity_Metric1& M3);
		};
	}
}

#include <Entity_Metric1ToolsI.hxx>

#endif // !_Entity_Metric1Tools_Header
