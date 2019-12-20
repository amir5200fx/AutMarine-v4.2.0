#pragma once
#ifndef _TColCad3d_HAry1dOfSurfaceOnSolid_Header
#define _TColCad3d_HAry1dOfSurfaceOnSolid_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_SurfaceOnSolid)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_CAD Cad3d_SurfaceOnSolid)> TColCad3d_HAry1dOfSurfaceOnSolid;
}

#endif // !_TColCad3d_HAry1dOfSurfaceOnSolid_Header
