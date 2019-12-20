#pragma once
#ifndef _Geom_PrQuadTreeSingleObjectLeaf_Header
#define _Geom_PrQuadTreeSingleObjectLeaf_Header

#include <Geom_PrQuadTreeNode.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Geom_PrQuadTreeSingleObjectLeaf : public Geom_PrQuadTreeNode<T>
		{

		public:

			T theObject_;

			Geom_PrQuadTreeSingleObjectLeaf() {}

			virtual ~Geom_PrQuadTreeSingleObjectLeaf() {}
		};
	}
}

#endif // !_Geom_PrQuadTreeSingleObjectLeaf_Header
