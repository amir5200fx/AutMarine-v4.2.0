#pragma once
#ifndef _TColCad2d_HAry1dOfPlane_Header
#define _TColCad2d_HAry1dOfPlane_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad2d_Plane)

namespace AutLib
{

	typedef ADT_Ary1d<Global_Handle(M_CAD Cad2d_Plane)> TColCad2d_HAry1dOfPlane;
}

#endif // !_TColCad2d_HAry1dOfPlane_Header
