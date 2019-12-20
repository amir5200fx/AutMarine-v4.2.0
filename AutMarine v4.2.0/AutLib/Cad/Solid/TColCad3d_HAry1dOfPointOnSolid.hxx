#pragma once
#ifndef _TColCad3d_HAry1dOfPointOnSolid_Header
#define _TColCad3d_HAry1dOfPointOnSolid_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_PointOnSolid)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_CAD Cad3d_PointOnSolid)> TColCad3d_HAry1dOfPointOnSolid;
}

#endif // !_TColCad3d_HAry1dOfPointOnSolid_Header
