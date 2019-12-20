#pragma once
#ifndef _TColFvSources_HBasicQueueOfSources2d_Header
#define _TColFvSources_HBasicQueueOfSources2d_Header

#include <Global_Macros.hxx>
#include <Global_Memory.hxx>
#include <ADT_BasicQueue.hxx>

M_FV_SPACE(FvSources2d)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_FV FvSources2d)> TColFvSources_HBasicQueueOfSources2d;
}

#endif // !_TColFvSources_HBasicQueueOfSources2d_Header
