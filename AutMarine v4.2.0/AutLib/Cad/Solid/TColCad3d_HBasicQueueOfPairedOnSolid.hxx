#pragma once
#ifndef _TColCad3d_HBasicQueueOfPairedOnSolid_Header
#define _TColCad3d_HBasicQueueOfPairedOnSolid_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_PairedOnSolid)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad3d_PairedOnSolid)> TColCad3d_HBasicQueueOfPairedOnSolid;
}

#endif // !_TColCad3d_HBasicQueueOfPairedOnSolid_Header
