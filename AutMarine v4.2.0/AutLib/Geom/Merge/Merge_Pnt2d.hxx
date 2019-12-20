#pragma once
#ifndef _Merge_Pnt2d_Header
#define _Merge_Pnt2d_Header

#include <Merge_Merge2dParameter.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <TColStd_Ary1dOfInteger.hxx>
#include <TColMerge_Ary1dOfMerge2dNode.hxx>
#include <TColMerge_HAry1dOfBasicQueueOfMerge2dNode.hxx>
#include <Global_Memory.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Merge_Pnt2d
		{

			typedef TColMerge_HAry1dOfBasicQueueOfMerge2dNode Merge2dTable;

		private:

			Merge_Merge2dParameter theParams_;

			Standard_Real theResolution_;
			Standard_Real theRadius_;

			const Global_Handle(TColGeom_Ary1dOfPnt2d) thePoints_;
			TColStd_Ary1dOfInteger theIndices_;

		public:

			Merge_Pnt2d();

			Merge_Pnt2d(const Standard_Real Resolution, const Standard_Real Radius);

			const TColStd_Ary1dOfInteger& Indices() const;

			TColGeom_Ary1dOfPnt2d CompactPoints() const;

			TColStd_Ary1dOfInteger CompactIndices() const;

			void SetCoords(const Global_Handle(TColGeom_Ary1dOfPnt2d) Points);

			// Throw an exception
			void Perform();

		private:

			TColMerge_Ary1dOfMerge2dNode Search(const Standard_Real Xo, const Standard_Real Yo, const Merge2dTable& Grid) const;

			void Resolution(const TColMerge_Ary1dOfMerge2dNode& Nodes);

			void Merging(const TColMerge_Ary1dOfMerge2dNode& Nodes, TColStd_Ary1dOfInteger & Indices);
		};
	}
}

#endif // !_Merge_Pnt2d_Header
