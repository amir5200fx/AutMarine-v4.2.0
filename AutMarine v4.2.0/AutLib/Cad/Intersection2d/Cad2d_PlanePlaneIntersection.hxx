#pragma once
#ifndef _Cad2d_PlanePlaneIntersection_Header
#define _Cad2d_PlanePlaneIntersection_Header

#include <TColCad2d_HAry1dOfEdgeEdgeIntersection.hxx>
#include <TColCad2d_HAry1dOfCurveCurveIntersection.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_Plane;

		class Cad2d_PlanePlaneIntersection
		{

		private:

			const Global_Handle(Cad2d_Plane) thePlane1_;
			const Global_Handle(Cad2d_Plane) thePlane2_;

			Standard_Real theTolerance_;

			Standard_Boolean IsDone_;
			Standard_Boolean HasIntersection_;

			TColCad2d_HAry1dOfEdgeEdgeIntersection theIntersection_;

		public:

			Cad2d_PlanePlaneIntersection();

			Cad2d_PlanePlaneIntersection(const Global_Handle(Cad2d_Plane) thePlane1, const Global_Handle(Cad2d_Plane) thePlane2);

			~Cad2d_PlanePlaneIntersection();

			void Init(const Global_Handle(Cad2d_Plane) thePlane1, const Global_Handle(Cad2d_Plane) thePlane2);

			Standard_Boolean IsDone() const;

			Standard_Boolean HasIntersection() const;

			const TColCad2d_HAry1dOfEdgeEdgeIntersection& Intersections() const;

			void Perform();

			void ExportToPlt(fstream& File) const;
		};
	}
}

#endif // !_Cad2d_PlanePlaneIntersection_Header
