#pragma once
#ifndef _Merge_Pnt3d_Header
#define _Merge_Pnt3d_Header

#include <Merge_Merge3dParameter.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <TColStd_Ary1dOfInteger.hxx>
#include <TColMerge_Ary1dOfMerge3dNode.hxx>
#include <TColMerge_HAry1dOfBasicQueueOfMerge3dNode.hxx>
#include <Global_Memory.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Merge_Pnt3d
		{

			typedef TColMerge_HAry1dOfBasicQueueOfMerge3dNode Merge3dTable;

		private:

			Merge_Merge3dParameter theParams_;

			Standard_Real theResolution_;
			Standard_Real theRadius_;

			const Global_Handle(TColGeom_Ary1dOfPnt3d) thePoints_;
			TColStd_Ary1dOfInteger theIndices_;

		public:

			Merge_Pnt3d();

			Merge_Pnt3d(const Standard_Real Resolution, const Standard_Real Radius);

			const TColStd_Ary1dOfInteger& Indices() const;

			TColGeom_Ary1dOfPnt3d CompactPoints() const;

			TColStd_Ary1dOfInteger CompactIndices() const;

			void SetCoords(const Global_Handle(TColGeom_Ary1dOfPnt3d) Points);

			// Throw an exception
			void Perform();

		private:

			TColMerge_Ary1dOfMerge3dNode Search(const Standard_Real Xo, const Standard_Real Yo, const Standard_Real Zo, const Merge3dTable& Grid) const;

			void Resolution(const TColMerge_Ary1dOfMerge3dNode& Nodes);

			void Merging(const TColMerge_Ary1dOfMerge3dNode& Nodes, TColStd_Ary1dOfInteger & Indices);
		};
	}
}

#endif // !_Merge_Pnt3d_Header
