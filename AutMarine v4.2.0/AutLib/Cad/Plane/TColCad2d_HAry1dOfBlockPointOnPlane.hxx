#pragma once
#ifndef _TColCad2d_HAry1dOfBlockPointOnPlane_Header
#define _TColCad2d_HAry1dOfBlockPointOnPlane_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad2d_BlockPointOnPlane)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_CAD Cad2d_BlockPointOnPlane)> TColCad2d_HAry1dOfBlockPointOnPlane;
}

#endif // !_TColCad2d_HAry1dOfBlockPointOnPlane_Header
