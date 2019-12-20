#pragma once
#ifndef _TColEntity_HBasicQueueOfEdge3d_Header
#define _TColEntity_HBasicQueueOfEdge3d_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Edge3d)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_GEO Entity_Edge3d)> TColEntity_HBasicQueueOfEdge3d;
}

#endif // !_TColEntity_HBasicQueueOfEdge3d_Header
