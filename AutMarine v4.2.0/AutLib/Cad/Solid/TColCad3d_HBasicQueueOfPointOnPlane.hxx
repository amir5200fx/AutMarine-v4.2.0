#pragma once
#ifndef _TColCad3d_HBasicQueueOfPointOnPlane_Header
#define _TColCad3d_HBasicQueueOfPointOnPlane_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_PointOnPlane)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad3d_PointOnPlane)> TColCad3d_HBasicQueueOfPointOnPlane;
}

#endif // !_TColCad3d_HBasicQueueOfPointOnPlane_Header
