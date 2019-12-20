#pragma once
#ifndef _TColCad2d_HBasicQueueOfPointOnPlane_Header
#define _TColCad2d_HBasicQueueOfPointOnPlane_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad2d_PointOnPlane)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad2d_PointOnPlane)> TColCad2d_HBasicQueueOfPointOnPlane;
}

#endif // !_TColCad2d_HBasicQueueOfPointOnPlane_Header
