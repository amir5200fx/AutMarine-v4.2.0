#pragma once
#ifndef _TColEntity_HBasicQueueOfElement3d_Header
#define _TColEntity_HBasicQueueOfElement3d_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Element3d)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_GEO Entity_Element3d)> TColEntity_HBasicQueueOfElement3d;
}

#endif // !_TColEntity_HBasicQueueOfElement3d_Header
