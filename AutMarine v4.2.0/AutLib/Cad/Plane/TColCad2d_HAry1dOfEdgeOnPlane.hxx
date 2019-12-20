#pragma once
#ifndef _TColCad2d_HAry1dOfEdgeOnPlane_Header
#define _TColCad2d_HAry1dOfEdgeOnPlane_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad2d_EdgeOnPlane)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_CAD Cad2d_EdgeOnPlane)> TColCad2d_HAry1dOfEdgeOnPlane;
}

#endif // !_TColCad2d_HAry1dOfEdgeOnPlane_Header
