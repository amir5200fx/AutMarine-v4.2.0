#pragma once
#ifndef _Geom_PrOctantTreeLeaf_Header
#define _Geom_PrOctantTreeLeaf_Header

#include <Geom_PrOctantTreeBucket.hxx>
#include <Geom_PrOctantTreeNode.hxx>
#include <ADT_BasicQueue.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Geom_PrOctantTreeLeaf : public Geom_PrOctantTreeNode<T>
		{

		public:

			Geom_PrOctantTreeBucket<T> theBucket_;

			ADT_BasicQueue<Geom_PrOctantTreeLeaf<T>*> theSNeighbors_;
			ADT_BasicQueue<Geom_PrOctantTreeLeaf<T>*> theENeighbors_;
			ADT_BasicQueue<Geom_PrOctantTreeLeaf<T>*> theNNeighbors_;
			ADT_BasicQueue<Geom_PrOctantTreeLeaf<T>*> theWNeighbors_;
			ADT_BasicQueue<Geom_PrOctantTreeLeaf<T>*> theFNeighbors_;
			ADT_BasicQueue<Geom_PrOctantTreeLeaf<T>*> theBNeighbors_;

			Geom_PrOctantTreeLeaf(const Standard_Integer MaxBucketSize) : theBucket_(MaxBucketSize) {}

			virtual ~Geom_PrOctantTreeLeaf() {}
		};
	}
}

#endif // !_Geom_PrOctantTreeLeaf_Header
