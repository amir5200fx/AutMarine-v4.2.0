#pragma once
#ifndef _TColEntity_HBasicQueueOfElement2d_Header
#define _TColEntity_HBasicQueueOfElement2d_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Element2d)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_GEO Entity_Element2d)> TColEntity_HBasicQueueOfElement2d;
}

#endif // !_TColEntity_HBasicQueueOfElement2d_Header
