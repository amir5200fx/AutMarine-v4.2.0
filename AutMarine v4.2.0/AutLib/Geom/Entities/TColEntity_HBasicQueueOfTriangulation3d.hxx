#pragma once
#ifndef _TColEntity_HBasicQueueOfTriangulation3d_Header
#define _TColEntity_HBasicQueueOfTriangulation3d_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>
#include <Global_Macros.hxx>

M_GEO_SPACE(Entity_Triangulation3d)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_GEO Entity_Triangulation3d)> TColEntity_HBasicQueueOfTriangulation3d;
}

#endif // !_TColEntity_HBasicQueueOfTriangulation3d_Header
