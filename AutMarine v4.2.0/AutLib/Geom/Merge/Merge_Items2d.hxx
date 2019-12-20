#pragma once
#ifndef _Merge_Items2d_Header
#define _Merge_Items2d_Header

#include <Global_Memory.hxx>
#include <ADT_BasicQueue.hxx>
#include <Merge_Pnt2d.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>
#include <TColStd_Ary1dOfInteger.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Merge_Items2d
		{

		private:

			const Global_Handle(ADT_Ary1d<T>) theItems_;

			const Geom_Pnt2d& (*theCoordinateFunction_)(T);

			Standard_Boolean IsDone_;

			ADT_Ary1d<T> theMerged_;

		public:

			Merge_Items2d();

			Merge_Items2d(const Global_Handle(ADT_Ary1d<T>) Items, const Geom_Pnt2d& (*CoordinateFunction)(T));

			void Init(const Global_Handle(ADT_Ary1d<T>) Items, const Geom_Pnt2d& (*CoordinateFunction)(T));

			void SetItems(const Global_Handle(ADT_Ary1d<T>) Items);

			void SetCoordinateFunction(const Geom_Pnt2d& (*CoordinateFunction)(T));

			void Perform();

			ADT_Ary1d<T> CompactItems() const;

			Standard_Boolean IsDone() const;

		private:

			TColGeom_Ary1dOfPnt2d GetCoordinates() const;
		};
	}
}

#include <Merge_Items2dI.hxx>

#endif // !_Merge_Items2d_Header
