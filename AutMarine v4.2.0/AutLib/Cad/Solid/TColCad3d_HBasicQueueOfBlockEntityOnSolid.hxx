#pragma once
#ifndef _TColCad3d_HBasicQueueOfBlockEntityOnSolid_Header
#define _TColCad3d_HBasicQueueOfBlockEntityOnSolid_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_BlockEntityOnSolid)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad3d_BlockEntityOnSolid)> TColCad3d_HBasicQueueOfBlockEntityOnSolid;
}

#endif // !_TColCad3d_HBasicQueueOfBlockEntityOnSolid_Header
