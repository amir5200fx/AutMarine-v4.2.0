#pragma once
#ifndef _TColEntity_HBasicQueueOfEdge2d_Header
#define _TColEntity_HBasicQueueOfEdge2d_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Edge2d)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_GEO Entity_Edge2d)> TColEntity_HBasicQueueOfEdge2d;
}

#endif // !_TColEntity_HBasicQueueOfEdge_Header
