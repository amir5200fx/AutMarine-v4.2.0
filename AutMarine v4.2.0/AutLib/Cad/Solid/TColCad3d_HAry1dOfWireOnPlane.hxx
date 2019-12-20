#pragma once
#ifndef _TColCad3d_HAry1dOfWireOnPlane_Header
#define _TColCad3d_HAry1dOfWireOnPlane_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>
#include <Global_Macros.hxx>

M_CAD_SPACE(Cad3d_WireOnPlane)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_CAD Cad3d_WireOnPlane)> TColCad3d_HAry1dOfWireOnPlane;
}

#endif // !_TColCad3d_HAry1dOfWireOnPlane_Header
