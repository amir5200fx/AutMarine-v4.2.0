#pragma once
#ifndef _TColSizeMap2d_HBasicQueueOfSizeMapTool_Header
#define _TColSizeMap2d_HBasicQueueOfSizeMapTool_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_BasicQueue.hxx>

M_MESH_SPACE(SizeMap2d_SizeMapTool)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_MESH SizeMap2d_SizeMapTool)> TColSizeMap2d_HBasicQueueOfSizeMapTool;
}

#endif // !_TColSizeMap2d_HBasicQueueOfSizeMapTool_Header
