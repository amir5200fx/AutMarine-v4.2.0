#pragma once
#ifndef _TColCad3d_HBasicQueueOfEntityOnSolid_Header
#define _TColCad3d_HBasicQueueOfEntityOnSolid_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_EntityOnSolid)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad3d_EntityOnSolid)> TColCad3d_HBasicQueueOfEntityOnSolid;
}

#endif // !_TColCad3d_HBasicQueueOfEntityOnSolid_Header
