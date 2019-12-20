#pragma once
#ifndef _TColProp_HAry1dOfExpandedView_Header
#define _TColProp_HAry1dOfExpandedView_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_Ary1d.hxx>

M_CAD_SPACE(Prop_ExpandedView)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_CAD Prop_ExpandedView)> TColProp_HAry1dOfExpandedView;
}

#endif // !_TColProp_HAry1dOfExpandedView_Header
