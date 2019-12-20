#pragma once
#ifndef _TColProp_HAry1dOfWrappedSection_Header
#define _TColProp_HAry1dOfWrappedSection_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_Ary1d.hxx>

M_CAD_SPACE(Prop_WrappedSection)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_CAD Prop_WrappedSection)> TColProp_HAry1dOfWrappedSection;
}

#endif // !_TColProp_HAry1dOfWrappedSection_header
