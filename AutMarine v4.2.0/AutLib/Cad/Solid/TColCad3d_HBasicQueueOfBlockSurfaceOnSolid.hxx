#pragma once
#ifndef _TColCad3d_HBasicQueueOfBlockSurfaceOnSolid_Header
#define _TColCad3d_HBasicQueueOfBlockSurfaceOnSolid_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_BlockSurfaceOnSolid)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad3d_BlockSurfaceOnSolid)> TColCad3d_HBasicQueueOfBlockSurfaceOnSolid;
}

#endif // !_TColCad3d_HBasicQueueOfBlockSurfaceOnSolid_Header
