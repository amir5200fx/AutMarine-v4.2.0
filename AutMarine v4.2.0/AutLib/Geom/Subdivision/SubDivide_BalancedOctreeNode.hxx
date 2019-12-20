#pragma once
#ifndef _SubDivide_BalancedOctreeNode_Header
#define _SubDivide_BalancedOctreeNode_Header

#include <Standard_TypeDef.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class SubDivide_BalancedOctreeNode
		{

		public:

			Standard_Integer theLevel_;

			virtual ~SubDivide_BalancedOctreeNode();

		protected:

			SubDivide_BalancedOctreeNode(const Standard_Integer Level);
			
		};
	}
}

#include <SubDivide_BalancedOctreeNodeI.hxx>

#endif // !_SubDivide_BalancedOctreeNode_Header
