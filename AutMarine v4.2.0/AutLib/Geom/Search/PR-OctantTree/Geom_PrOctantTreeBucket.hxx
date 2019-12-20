#pragma once
#ifndef _Geom_PrOctantTreeBucket_Header
#define _Geom_PrOctantTreeBucket_Header

#include <ADT_BasicQueue.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Geom_PrOctantTreeBucket
		{

		private:

			ADT_BasicQueue<T> theBucket_;

			Standard_Integer theMaxItems_;

		public:

			Geom_PrOctantTreeBucket(const Standard_Integer MaxItems = 4);

			Standard_Boolean IsEmpty() const;

			Standard_Boolean IsFull() const;

			Standard_Integer NbItems() const;

			Standard_Boolean Insert(T Object);

			Standard_Boolean Remove(T Object);

			void RetrieveTo(ADT_Ary1d<T>& Items) const;
		};
	}
}

#include <Geom_PrOctantTreeBucketI.hxx>

#endif // !_Geom_PrOctantTreeBucket_Header
