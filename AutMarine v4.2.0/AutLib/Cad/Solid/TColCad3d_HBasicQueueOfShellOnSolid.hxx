#pragma once
#ifndef _TColCad3d_HBasicQueueOfShellOnSolid_Header
#define _TColCad3d_HBasicQueueOfShellOnSolid_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_ShellOnSolid)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_CAD Cad3d_ShellOnSolid)> TColCad3d_HBasicQueueOfShellOnSolid;
}

#endif // !_TColCad3d_HBasicQueueOfShellOnSolid_Header
