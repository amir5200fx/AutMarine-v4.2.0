#pragma once
#ifndef _TColCad2d_HBasicQueueOfTPlane_Header
#define _TColCad2d_HBasicQueueOfTPlane_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>
#include <Global_Macros.hxx>

M_CAD_SPACE(Cad2d_TPlane)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad2d_TPlane)> TColCad2d_HBasicQueueOfTPlane;
}

#endif // !_TColCad2d_HBasicQueueOfTPlane_Header
