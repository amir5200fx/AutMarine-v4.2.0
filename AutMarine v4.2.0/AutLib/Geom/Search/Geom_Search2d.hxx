#pragma once
#ifndef _Geom_Search2d_Header
#define _Geom_Search2d_Header

#include <Standard_Integer.hxx>
#include <ADT_Ary1d.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Entity_Box2d;

		template<typename T>
		class Geom_Search2d
		{

		public:

			//virtual ~Geom_Search2d() = 0;

			virtual Standard_Integer Size() const = 0;

			virtual Standard_Boolean IsEmpty() const = 0;

			virtual const Entity_Box2d& BoundingBox() const = 0;

			virtual void Insert(const T& Item) = 0;

			virtual void Insert(const ADT_Ary1d<T>& Items) = 0;

			virtual void Remove(const T& Item) = 0;

			virtual void RetrieveTo(ADT_Ary1d<T>& Items) const = 0;

			virtual void SetRegion(const Entity_Box2d& Region) = 0;

			virtual void Search(const Entity_Box2d& Region, ADT_Ary1d<T>& Items) const = 0;
		};
	}
}

#endif // !_Geom_Search2d_Header
