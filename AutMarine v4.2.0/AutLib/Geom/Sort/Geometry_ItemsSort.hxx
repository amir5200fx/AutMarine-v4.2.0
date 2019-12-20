#pragma once
#ifndef _Geometry_ItemsSort_Header
#define _Geometry_ItemsSort_Header

#include <Standard_Type.hxx>
#include <ADT_Ary1d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Geometry_ItemsSort
		{

		private:

			Standard_Boolean(*IsLess_)(const T&, const T&);

		public:

			Geometry_ItemsSort(Standard_Boolean(*IsLess)(const T&, const T&));

			void Peform(ADT_Ary1d<T>& theItems) const;

		private:

			static Standard_Integer left_child(const Standard_Integer i) { return 2 * i + 1; }

			void PercDown(ADT_Ary1d<T>& a, Standard_Integer i, const Standard_Integer n) const;
		};
	}
}

#include <Geometry_ItemsSortI.hxx>

#endif // !_Geometry_ItemsSort_Header
