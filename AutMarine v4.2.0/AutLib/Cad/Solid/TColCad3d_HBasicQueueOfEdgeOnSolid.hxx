#pragma once
#ifndef _TColCad3d_HBasicQueueOfEdgeOnSolid_Header
#define _TColCad3d_HBasicQueueOfEdgeOnSolid_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_EdgeOnSolid)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad3d_EdgeOnSolid)> TColCad3d_HBasicQueueOfEdgeOnSolid;
}

#endif // !_TColCad3d_HBasicQueueOfEdgeOnSolid_Header
