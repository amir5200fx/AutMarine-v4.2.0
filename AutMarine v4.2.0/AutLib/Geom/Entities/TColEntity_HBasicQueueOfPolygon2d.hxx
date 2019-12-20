#pragma once
#ifndef _TColEntity_HBasicQueueOfPolygon2d_Header
#define _TColEntity_HBasicQueueOfPolygon2d_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Polygon2d)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_GEO Entity_Polygon2d)> TColEntity_HBasicQueueOfPolygon2d;
}

#endif // !_TColEntity_HBasicQueueOfPolygon2d_Header
