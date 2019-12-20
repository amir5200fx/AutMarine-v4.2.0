#pragma once
#ifndef _TColFvEntity_HAry1dOfElement2d_Header
#define _TColFvEntity_HAry1dOfElement2d_Header

#include <Global_Macros.hxx>
#include <Global_Memory.hxx>
#include <ADT_Ary1d.hxx>

M_FV_SPACE(FvEntity_Element2d)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_FV FvEntity_Element2d)> TColFvEntity_HAry1dOfElement2d;
}

#endif // !_TColFvEntity_HAry1dOfElement2d_Header
