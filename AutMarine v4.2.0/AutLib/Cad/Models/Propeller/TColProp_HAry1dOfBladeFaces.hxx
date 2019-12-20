#pragma once
#ifndef _TColProp_HAry1dOfBladeFaces_Header
#define _TColProp_HAry1dOfBladeFaces_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_Ary1d.hxx>

M_CAD_SPACE(Prop_BladeFaces)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_CAD Prop_BladeFaces)> TColProp_HAry1dOfBladeFaces;
}

#endif // !_TColProp_HAry1dOfBladeFaces_Header
