#pragma once
#ifndef _Geom_PrQuadTreeLeaf_Header
#define _Geom_PrQuadTreeLeaf_Header

#include <Geom_PrQuadTreeNode.hxx>
#include <Geom_PrQuadTreeBucket.hxx>
#include <ADT_BasicQueue.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Geom_PrQuadTreeLeaf : public Geom_PrQuadTreeNode<T>
		{

		public:

			Geom_PrQuadTreeBucket<T> theBucket_;

			ADT_BasicQueue<Geom_PrQuadTreeLeaf<T>*> theSNeighbors_;
			ADT_BasicQueue<Geom_PrQuadTreeLeaf<T>*> theENeighbors_;
			ADT_BasicQueue<Geom_PrQuadTreeLeaf<T>*> theNNeighbors_;
			ADT_BasicQueue<Geom_PrQuadTreeLeaf<T>*> theWNeighbors_;

			//Geom_Box2d theBox_;

			Geom_PrQuadTreeLeaf(const Standard_Integer MaxBucketSize) : theBucket_(MaxBucketSize){}

			virtual ~Geom_PrQuadTreeLeaf() {}
		};
	}
}

#endif // !_Geom_PrQuadTreeLeaf_Header
