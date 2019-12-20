#pragma once
#ifndef _TColCad2d_HAry1dOfBlockEdgeOnPlane_Header
#define _TColCad2d_HAry1dOfBlockEdgeOnPlane_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad2d_BlockEdgeOnPlane)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_CAD Cad2d_BlockEdgeOnPlane)> TColCad2d_HAry1dOfBlockEdgeOnPlane;
}

#endif // !_TColCad2d_HAry1dOfBlockEdgeOnPlane_Header
