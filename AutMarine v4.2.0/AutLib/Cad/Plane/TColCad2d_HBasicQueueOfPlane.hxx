#pragma once
#ifndef _TColCad2d_HBasicQueueOfPlane_Header
#define _TColCad2d_HBasicQueueOfPlane_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad2d_Plane)

namespace AutLib
{

	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad2d_Plane)> TColCad2d_HBasicQueueOfPlane;
}

#endif // !_TColCad2d_HBasicQueueOfPlane_Header
