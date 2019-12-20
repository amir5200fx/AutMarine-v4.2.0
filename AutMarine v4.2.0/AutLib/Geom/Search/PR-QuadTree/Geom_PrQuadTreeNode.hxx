#pragma once
#ifndef _Geom_PrQuadTreeNode_Header
#define _Geom_PrQuadTreeNode_Header

#include <Entity_Box2d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Geom_PrQuadTreeNode
		{

		public:

			Entity_Box2d theBox_;

			Geom_PrQuadTreeNode<T>* theFather_;

			Geom_PrQuadTreeNode() : theFather_(NULL) {}

			virtual ~Geom_PrQuadTreeNode() {}
		};
	}
}

#endif // !_Geom_PRQuadTreeNode_Header
