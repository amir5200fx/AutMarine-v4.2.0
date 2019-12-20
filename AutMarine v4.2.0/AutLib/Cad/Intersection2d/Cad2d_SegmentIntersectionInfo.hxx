#pragma once
#ifndef _Cad2d_SegmentIntersectionInfo_Header
#define _Cad2d_SegmentIntersectionInfo_Header

#include <Global_Memory.hxx>
#include <Standard_Stream.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_CurveOnPlane;

		class Cad2d_SegmentIntersectionInfo
		{

		private:

			Global_Handle(Cad2d_CurveOnPlane) theCurve1_;
			Global_Handle(Cad2d_CurveOnPlane) theCurve2_;

		public:

			Cad2d_SegmentIntersectionInfo();

			Cad2d_SegmentIntersectionInfo(Global_Handle(Cad2d_CurveOnPlane) theCurve1, Global_Handle(Cad2d_CurveOnPlane) theCurve2);

			~Cad2d_SegmentIntersectionInfo();

			void Init(Global_Handle(Cad2d_CurveOnPlane) theCurve1, Global_Handle(Cad2d_CurveOnPlane) theCurve2);

			Global_Handle(Cad2d_CurveOnPlane) Curve1() const;

			Global_Handle(Cad2d_CurveOnPlane) Curve2() const;

			void ExportToPlt(fstream& File) const;
		};
	}
}

#include <Cad2d_SegmentIntersectionInfoI.hxx>

#endif // !_Cad2d_SegmentIntersectionInfo_Header
