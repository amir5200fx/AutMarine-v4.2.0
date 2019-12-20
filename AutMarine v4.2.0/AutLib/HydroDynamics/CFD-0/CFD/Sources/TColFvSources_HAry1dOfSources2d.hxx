#pragma once
#ifndef _TColFvSources_HAry1dOfSources2d_Header
#define _TColFvSources_HAry1dOfSources2d_Header

#include <Global_Macros.hxx>
#include <Global_Memory.hxx>
#include <ADT_Ary1d.hxx>

M_FV_SPACE(FvSources2d)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_FV FvSources2d)> TColFvSources_HAry1dOfSources2d;
}

#endif // !_TColFvSources_HAry1dOfSources2d_Header
