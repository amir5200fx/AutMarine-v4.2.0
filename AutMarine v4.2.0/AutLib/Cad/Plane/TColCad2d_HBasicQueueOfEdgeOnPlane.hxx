#pragma once
#ifndef _TColCad2d_HBasicQueueOfEdgeOnPlane_Header
#define _TColCad2d_HBasicQueueOfEdgeOnPlane_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad2d_EdgeOnPlane)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad2d_EdgeOnPlane)> TColCad2d_HBasicQueueOfEdgeOnPlane;
}

#endif // !_TColCad2d_HBasicQueueOfEdgeOnPlane_Header
