#pragma once
#ifndef _TColCad2d_HBasicQueueOfCurveOnPlane_Header
#define _TColCad2d_HBasicQueueOfCurveOnPlane_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad2d_CurveOnPlane)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad2d_CurveOnPlane)> TColCad2d_HBasicQueueOfCurveOnPlane;
}

#endif // !_TColCad2d_HBasicQueueOfCurveOnPlane_Header
