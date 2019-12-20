#pragma once
#ifndef _TColSubDivide_HBasicQueueOfBalancedOctreeNode_Header
#define _TColSubDivide_HBasicQueueOfBalancedOctreeNode_Header

#include <Global_Memory.hxx>
#include <ADT_BasicQueue.hxx>
#include <SubDivide_BalancedOctreeNode.hxx>

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_GEO SubDivide_BalancedOctreeNode)> TColSubDivide_HBasicQueueOfBalancedOctreeNode;
}

#endif // !_TColSubDivide_HBasicQueueOfBalancedOctreeNode_Header
