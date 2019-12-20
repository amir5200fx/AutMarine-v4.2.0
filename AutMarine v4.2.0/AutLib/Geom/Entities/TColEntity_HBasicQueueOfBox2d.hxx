#pragma once
#ifndef _TColEntity_HBasicQueueOfBox2d_Header
#define _TColEntity_HBasicQueueOfBox2d_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Box2d)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_GEO Entity_Box2d)> TColEntity_HBasicQueueOfBox2d;
}

#endif // !_TColEntity_HBasicQueueOfBox2d_Header
