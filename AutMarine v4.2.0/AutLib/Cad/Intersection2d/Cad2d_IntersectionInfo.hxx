#pragma once
#ifndef _Cad2d_IntersectionInfo_Header
#define _Cad2d_IntersectionInfo_Header

#include <TColCad2d_HAry1dOfPointIntersectionInfo.hxx>
#include <TColCad2d_HAry1dOfSegmentIntersectionInfo.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_CurveOnPlane;

		class Cad2d_IntersectionInfo
		{

		private:

			TColCad2d_HAry1dOfPointIntersectionInfo thePoints_;

			TColCad2d_HAry1dOfSegmentIntersectionInfo theSegments_;

		public:

			Cad2d_IntersectionInfo();

			Cad2d_IntersectionInfo(const TColCad2d_HAry1dOfPointIntersectionInfo& thePoints, const TColCad2d_HAry1dOfSegmentIntersectionInfo& theSegments);

			~Cad2d_IntersectionInfo();

			void Init(const TColCad2d_HAry1dOfPointIntersectionInfo& thePoints, const TColCad2d_HAry1dOfSegmentIntersectionInfo& theSegments);

			const TColCad2d_HAry1dOfPointIntersectionInfo& Points() const;

			const TColCad2d_HAry1dOfSegmentIntersectionInfo& Segments() const;

			Standard_Integer NbPoints() const;

			Standard_Integer NbSegments() const;

			const Cad2d_PointIntersectionInfo& Point(const Standard_Integer theIndex) const;

			const Cad2d_SegmentIntersectionInfo& Segment(const Standard_Integer theIndex) const;

			void ExportToPlt(fstream& File) const;
		};
	}
}

#include <Cad2d_IntersectionInfoI.hxx>

#endif // !_Cad2d_IntersectionInfo_Header
