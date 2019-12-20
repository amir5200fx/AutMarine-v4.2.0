#pragma once
#ifndef _TColSizeMap3d_HBasicQueueOfPrimitiveShapeSource_Header
#define _TColSizeMap3d_HBasicQueueOfPrimitiveShapeSource_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_BasicQueue.hxx>

M_MESH_SPACE(SizeMap3d_PrimitiveShapeSource)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_MESH SizeMap3d_PrimitiveShapeSource)> TColSizeMap3d_HBasicQueueOfPrimitiveShapeSource;
}

#endif // !_TColSizeMap3d_HBasicQueueOfPrimitiveShapeSource_Header
