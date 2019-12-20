#pragma once
#ifndef _TColSubDivide_HBasicQueueOfOctreeNode_Header
#define _TColSubDivide_HBasicQueueOfOctreeNode_Header

#include <ADT_BasicQueue.hxx>
#include <SubDivide_OctreeNode.hxx>

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_GEO SubDivide_OctreeNode)> TColSubDivide_HBasicQueueOfOctreeNode;
}

#endif // !_TColSubDivide_HBasicQueueOfOctreeNode_Header
