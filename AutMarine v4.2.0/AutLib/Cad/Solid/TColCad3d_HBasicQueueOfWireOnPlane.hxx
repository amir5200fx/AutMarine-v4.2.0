#pragma once
#ifndef _TColCad3d_HBasicQueueOfWireOnPlane_Header
#define _TColCad3d_HBasicQueueOfWireOnPlane_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>
#include <Global_Macros.hxx>

M_CAD_SPACE(Cad3d_WireOnPlane)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad3d_WireOnPlane)> TColCad3d_HBasicQueueOfWireOnPlane;
}

#endif // !_TColCad3d_HBasicQueueOfWireOnPlane_Header
