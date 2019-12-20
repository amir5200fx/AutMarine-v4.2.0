#pragma once
#ifndef _TColCad2d_HBasicQueueOfPointIntersectionInfo_Header
#define _TColCad2d_HBasicQueueOfPointIntersectionInfo_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>
#include <Global_Macros.hxx>

M_CAD_SPACE(Cad2d_PointIntersectionInfo)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad2d_PointIntersectionInfo)> TColCad2d_HBasicQueueOfPointIntersectionInfo;
}

#endif // !_TColCad2d_HBasicQueueOfPointIntersectionInfo_Header
