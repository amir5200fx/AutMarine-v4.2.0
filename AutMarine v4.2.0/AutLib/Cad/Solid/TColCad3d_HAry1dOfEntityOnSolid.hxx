#pragma once
#ifndef _TColCad3d_HAry1dOfEntityOnSolid_Header
#define _TColCad3d_HAry1dOfEntityOnSolid_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_EntityOnSolid)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_CAD Cad3d_EntityOnSolid)> TColCad3d_HAry1dOfEntityOnSolid;
}

#endif // !_TColCad3d_HAry1dOfEntityOnSolid_Header
