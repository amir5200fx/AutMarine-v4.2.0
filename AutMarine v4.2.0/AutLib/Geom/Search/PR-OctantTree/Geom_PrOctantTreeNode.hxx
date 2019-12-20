#pragma once
#ifndef _Geom_PrOctantTreeNode_Header
#define _Geom_PrOctantTreeNode_Header

#include <Entity_Box3d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Geom_PrOctantTreeNode
		{

		public:

			Entity_Box3d theBox_;

			virtual ~Geom_PrOctantTreeNode() {}
		};
	}
}

#endif // !_Geom_PrOctantTreeNode_Header
