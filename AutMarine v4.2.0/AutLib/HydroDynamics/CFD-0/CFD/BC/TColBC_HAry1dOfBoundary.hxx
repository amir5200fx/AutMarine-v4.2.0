#pragma once
#ifndef _TColBC_HAry1dOfBoundary_Header
#define _TColBC_HAry1dOfBoundary_Header

#include <Global_Macros.hxx>
#include <Global_Memory.hxx>
#include <ADT_Ary1d.hxx>

M_FV_SPACE(FvBC_Boundary)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_FV FvBC_Boundary)> TColBC_HAry1dOfBoundary;
}

#endif // !_TColBC_HAry1dOfBoundary_Header
