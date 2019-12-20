#pragma once
#ifndef _Cad2d_CurveCurveIntersection_Header
#define _Cad2d_CurveCurveIntersection_Header

#include <Cad2d_IntersectionInfo.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_CurveOnPlane;

		class Cad2d_CurveCurveIntersection
		{

		private:

			const Global_Handle(Cad2d_CurveOnPlane) theCurve1_;
			const Global_Handle(Cad2d_CurveOnPlane) theCurve2_;

			Standard_Real theTolerance_;

			Standard_Boolean IsDone_;
			Standard_Boolean HasIntersection_;

			Cad2d_IntersectionInfo theIntersection_;

		public:

			Cad2d_CurveCurveIntersection();

			Cad2d_CurveCurveIntersection(const Global_Handle(Cad2d_CurveOnPlane) theCurve1, const Global_Handle(Cad2d_CurveOnPlane) theCurve2, const Standard_Real theTolerance);

			~Cad2d_CurveCurveIntersection();

			void Init(const Global_Handle(Cad2d_CurveOnPlane) theCurve1, const Global_Handle(Cad2d_CurveOnPlane) theCurve2, const Standard_Real theTolerance);

			Standard_Boolean IsDone() const;

			Standard_Boolean HasIntersection() const;

			const Cad2d_IntersectionInfo& Intersection() const;

			const Global_Handle(Cad2d_CurveOnPlane) Curve1() const;

			const Global_Handle(Cad2d_CurveOnPlane) Curve2() const;

			void Perform();

			void ExportToPlt(fstream& File) const;
		};
	}
}

#endif // !_Cad2d_CurveCurveIntersection_Header
