#pragma once
#ifndef _Geom_Sort_Header
#define _Geom_Sort_Header

#include <TColStd_Ary1dOfInteger.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Geometry_Sort
		{

		public:

			static void Sort(ADT_Ary1d<T>& a, TColStd_Ary1dOfInteger & s);

			static void Sort(ADT_Ary1d<T>& a);

		private:

			static Standard_Integer left_child(const Standard_Integer i) { return 2 * i + 1; }

			static void PercDown(ADT_Ary1d<T>& a, TColStd_Ary1dOfInteger & s, Standard_Integer i, const Standard_Integer n);

			static void PercDown(ADT_Ary1d<T>& a, Standard_Integer i, const Standard_Integer n);
		};
	}
}

#include <Geometry_SortI.hxx>

#endif // !_Geom_Sort_Header
