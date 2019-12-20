#pragma once
#ifndef _TColEntity_HBasicQueueOfBox3d_Header
#define _TColEntity_HBasicQueueOfBox3d_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Box3d)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_GEO Entity_Box3d)> TColEntity_HBasicQueueOfBox3d;
}

#endif // !_TColEntity_HBasicQueueOfBox3d_Header
