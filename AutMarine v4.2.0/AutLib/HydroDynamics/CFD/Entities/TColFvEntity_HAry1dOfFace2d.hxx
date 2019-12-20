#pragma once
#ifndef _TColFvEntity_HAry1dOfFace2d_Header
#define _TColFvEntity_HAry1dOfFace2d_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_Ary1d.hxx>

M_FV_SPACE(FvEntity_Face2d)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_FV FvEntity_Face2d)> TColFvEntity_HAry1dOfFace2d;
}

#endif // !_TColFvEntity_HAry1dOfFace2d_Header
