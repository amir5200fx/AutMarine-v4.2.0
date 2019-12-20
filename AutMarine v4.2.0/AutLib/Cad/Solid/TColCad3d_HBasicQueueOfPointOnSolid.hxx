#pragma once
#ifndef _TColCad3d_HBasicQueueOfPointOnSolid_Header
#define _TColCad3d_HBasicQueueOfPointOnSolid_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_PointOnSolid)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad3d_PointOnSolid)> TColCad3d_HBasicQueueOfPointOnSolid;
}

#endif // !_TColCad3d_HBasicQueueOfPointOnSolid_Header
