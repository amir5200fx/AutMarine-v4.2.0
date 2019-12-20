#pragma once
#ifndef _TColBC_HBasicQueueOfBoundary_Header
#define _TColBC_HBasicQueueOfBoundary_Header

#include <Global_Macros.hxx>
#include <Global_Memory.hxx>
#include <ADT_BasicQueue.hxx>

M_FV_SPACE(FvBC_Boundary)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_FV FvBC_Boundary)> TColBC_HBasicQueueOfBoundary;
}

#endif // !_TColBC_HBasicQueueOfBoundary_Header
