#pragma once
#ifndef _Cad2d_EdgeEdgeIntersection_Header
#define _Cad2d_EdgeEdgeIntersection_Header

#include <Cad2d_IntersectionInfo.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_EdgeOnPlane;

		class Cad2d_EdgeEdgeIntersection
		{

		private:

			const Global_Handle(Cad2d_EdgeOnPlane) theEdge1_;
			const Global_Handle(Cad2d_EdgeOnPlane) theEdge2_;

			Standard_Real theTolerance_;

			Standard_Boolean IsDone_;
			Standard_Boolean HasIntersection_;

			Cad2d_IntersectionInfo theIntersection_;

		public:

			Cad2d_EdgeEdgeIntersection();

			Cad2d_EdgeEdgeIntersection(const Global_Handle(Cad2d_EdgeOnPlane) theCurve1, const Global_Handle(Cad2d_EdgeOnPlane) theCurve2, const Standard_Real theTolerance);

			~Cad2d_EdgeEdgeIntersection();

			void Init(const Global_Handle(Cad2d_EdgeOnPlane) theCurve1, const Global_Handle(Cad2d_EdgeOnPlane) theCurve2, const Standard_Real theTolerance);

			Standard_Boolean IsDone() const;

			Standard_Boolean HasIntersection() const;

			const Cad2d_IntersectionInfo& Intersection() const;

			const Global_Handle(Cad2d_EdgeOnPlane) Edge1() const;

			const Global_Handle(Cad2d_EdgeOnPlane) Edge2() const;

			void Perform();

			void ExportToPlt(fstream& File) const;
		};
	}
}

#endif // !_Cad2d_EdgeEdgeIntersection_Header
