#pragma once
#ifndef _Geom_PrQuadTreeBucket_Header
#define _Geom_PrQuadTreeBucket_Header

#include <ADT_BasicQueue.hxx>
//#include <ADT_AvlTree.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Geom_PrQuadTreeBucket
		{

		private:

			ADT_BasicQueue<T> theBucket_;
			//ADT_AvlTree<T> theBucket_;

			Standard_Integer theMaxItems_;

		public:

			Geom_PrQuadTreeBucket(const Standard_Integer MaxItems = 4);

			Standard_Boolean IsEmpty() const;

			Standard_Boolean IsFull() const;

			Standard_Integer NbItems() const;

			Standard_Boolean Insert(T Object);

			Standard_Boolean Remove(T Object);

			void RetrieveTo(ADT_Ary1d<T>& Items) const;
		};
	}
}

#include <Geom_PrQuadTreeBucketI.hxx>

#endif // !_Geom_PrQuadTreeBucket_Header
