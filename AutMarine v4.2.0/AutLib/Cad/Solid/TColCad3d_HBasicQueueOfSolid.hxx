#pragma once
#ifndef _TColCad3d_HBasicQueueOfSolid_Header
#define _TColCad3d_HBasicQueueOfSolid_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>
#include <Global_Macros.hxx>

M_CAD_SPACE(Cad3d_Solid)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad3d_Solid)> TColCad3d_HBasicQueueOfSolid;
}

#endif // !_TColCad3d_HBasicQueueOfSolid_header
