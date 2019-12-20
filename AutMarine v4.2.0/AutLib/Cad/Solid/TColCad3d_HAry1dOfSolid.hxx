#pragma once
#ifndef _TColCad3d_HAry1dOfSolid_Header
#define _TColCad3d_HAry1dOfSolid_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>
#include <Global_Macros.hxx>

M_CAD_SPACE(Cad3d_Solid)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_CAD Cad3d_Solid)> TColCad3d_HAry1dOfSolid;
}

#endif // !_TColCad3d_HAry1dOfSolid_Header
