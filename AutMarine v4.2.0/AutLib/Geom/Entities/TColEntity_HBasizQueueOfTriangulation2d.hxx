#pragma once
#ifndef _TColEntity_HBasizQueueOfTriangulation2d_Header
#define _TColEntity_HBasizQueueOfTriangulation2d_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>
#include <Global_Macros.hxx>

M_GEO_SPACE(Entity_Triangulation2d)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_GEO Entity_Triangulation2d)> TColEntity_HBasizQueueOfTriangulation2d;
}

#endif // !_TColEntity_HBasizQueueOfTriangulation2d_Header