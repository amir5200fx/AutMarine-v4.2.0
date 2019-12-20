#pragma once
#ifndef _TColCad3d_HBasicQueueOfEdgeOnPlane_Header
#define _TColCad3d_HBasicQueueOfEdgeOnPlane_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Macros.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_EdgeOnPlane)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad3d_EdgeOnPlane)> TColCad3d_HBasicQueueOfEdgeOnPlane;
}

#endif // !_TColCad3d_HBasicQueueOfEdgeOnPlane_Header
