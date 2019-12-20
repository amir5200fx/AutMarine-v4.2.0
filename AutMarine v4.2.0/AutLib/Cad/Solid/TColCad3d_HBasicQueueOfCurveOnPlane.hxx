#pragma once
#ifndef _TColCad3d_HBasicQueueOfCurveOnPlane_Header
#define _TColCad3d_HBasicQueueOfCurveOnPlane_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_CurveOnPlane)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad3d_CurveOnPlane)> TColCad3d_HBasicQueueOfCurveOnPlane;
}

#endif // !_TColCad3d_HBasicQueueOfCurveOnPlane_Header
