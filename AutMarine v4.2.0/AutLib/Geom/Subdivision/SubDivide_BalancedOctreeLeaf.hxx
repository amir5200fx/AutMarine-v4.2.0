#pragma once
#ifndef _SubDivide_BalancedOctreeLeaf_Header
#define _SubDivide_BalancedOctreeLeaf_Header

#include <ADT_BasicQueue.hxx>
#include <Entity_Box3d.hxx>
#include <SubDivide_BalancedOctreeNode.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		
		class SubDivide_BalancedOctreeLeaf : public SubDivide_BalancedOctreeNode
		{

		public:

			Entity_Box3d theBox_;

			ADT_BasicQueue<SubDivide_BalancedOctreeLeaf*> theSNeighbors_;
			ADT_BasicQueue<SubDivide_BalancedOctreeLeaf*> theENeighbors_;
			ADT_BasicQueue<SubDivide_BalancedOctreeLeaf*> theNNeighbors_;
			ADT_BasicQueue<SubDivide_BalancedOctreeLeaf*> theWNeighbors_;
			ADT_BasicQueue<SubDivide_BalancedOctreeLeaf*> theFNeighbors_;
			ADT_BasicQueue<SubDivide_BalancedOctreeLeaf*> theBNeighbors_;

			SubDivide_BalancedOctreeNode* theFather_;

		public:

			SubDivide_BalancedOctreeLeaf(const Standard_Integer theLevel, const Entity_Box3d& theBox);

			virtual ~SubDivide_BalancedOctreeLeaf();
		};
	}
}

#include <SubDivide_BalancedOctreeLeafI.hxx>

#endif // !_SubDivide_BalancedOctreeLeaf_Header
