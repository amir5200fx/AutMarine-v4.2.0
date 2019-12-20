#pragma once
#ifndef _TColSubDivide_HBasicQueueOfQuadTreeNode_Header
#define _TColSubDivide_HBasicQueueOfQuadTreeNode_Header

#include <ADT_BasicQueue.hxx>
#include <SubDivide_QuadTreeNode.hxx>

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_GEO SubDivide_QuadTreeNode)> TColSubDivide_HBasicQueueOfQuadTreeNode;
}

#endif // !_TColSubDivide_BasicQueueOfQuadTreeNode_Header
