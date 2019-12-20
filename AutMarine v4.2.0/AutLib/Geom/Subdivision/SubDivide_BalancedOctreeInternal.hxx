#pragma once
#ifndef _SubDivide_BalancedOctreeInternal_Header
#define _SubDivide_BalancedOctreeInternal_Header

#include <SubDivide_BalancedOctreeNode.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class SubDivide_BalancedOctreeInternal : public SubDivide_BalancedOctreeNode
		{

		public:

			SubDivide_BalancedOctreeNode* theFwd_SwPtr_;
			SubDivide_BalancedOctreeNode* theFwd_SePtr_;
			SubDivide_BalancedOctreeNode* theFwd_NePtr_;
			SubDivide_BalancedOctreeNode* theFwd_NwPtr_;
			SubDivide_BalancedOctreeNode* theBwd_SwPtr_;
			SubDivide_BalancedOctreeNode* theBwd_SePtr_;
			SubDivide_BalancedOctreeNode* theBwd_NePtr_;
			SubDivide_BalancedOctreeNode* theBwd_NwPtr_;

			SubDivide_BalancedOctreeInternal(const Standard_Integer theLevel);

			virtual ~SubDivide_BalancedOctreeInternal();
		};
	}
}

#include <SubDivide_BalancedOctreeInternalI.hxx>

#endif // !_SubDivide_BalancedOctreeInternal_Header
