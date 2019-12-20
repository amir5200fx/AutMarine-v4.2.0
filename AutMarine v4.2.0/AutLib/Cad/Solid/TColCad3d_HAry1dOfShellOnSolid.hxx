#pragma once
#ifndef _TColCad3d_HAry1dOfShellOnSolid_Header
#define _TColCad3d_HAry1dOfShellOnSolid_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_ShellOnSolid)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_CAD Cad3d_ShellOnSolid)> TColCad3d_HAry1dOfShellOnSolid;
}

#endif // !_TColCad3d_HAry1dOfShellOnSolid_Header
