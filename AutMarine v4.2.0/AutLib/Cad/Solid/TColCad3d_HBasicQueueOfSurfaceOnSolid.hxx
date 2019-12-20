#pragma once
#ifndef _TColCad3d_HBasicQueueOfSurfaceOnSolid_Header
#define _TColCad3d_HBasicQueueOfSurfaceOnSolid_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_SurfaceOnSolid)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad3d_SurfaceOnSolid)> TColCad3d_HBasicQueueOfSurfaceOnSolid;
}

#endif // !_TColCad3d_HBasicQueueOfSurfaceOnSolid_Header
