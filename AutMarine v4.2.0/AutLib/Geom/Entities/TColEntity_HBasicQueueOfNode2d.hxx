#pragma once
#ifndef _TColEntity_HBasicQueueOfNode2d_Header
#define _TColEntity_HBasicQueueOfNode2d_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Node2d)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_GEO Entity_Node2d)> TColEntity_HBasicQueueOfNode2d;
}

#endif // !_TColEntity_HBasicQueueOfNode2d_Header
