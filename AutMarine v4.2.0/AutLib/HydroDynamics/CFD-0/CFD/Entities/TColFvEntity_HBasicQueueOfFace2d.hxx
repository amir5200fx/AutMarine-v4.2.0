#pragma once
#ifndef _TColFvEntity_HBasicQueueOfFace2d_Header
#define _TColFvEntity_HBasicQueueOfFace2d_Header

#include <Global_Macros.hxx>
#include <Global_Memory.hxx>
#include <ADT_BasicQueue.hxx>

M_FV_SPACE(FvEntity_Face2d)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_FV FvEntity_Face2d)> TColFvEntity_HBasicQueueOfFace2d;
}

#endif // !_TColFvEntity_HBasicQueueOfFace2d_Header
