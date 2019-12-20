#pragma once
#ifndef _TColCad3d_StringMapOfHBlockSurfaceOnSolid_Header
#define _TColCad3d_StringMapOfHBlockSurfaceOnSolid_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <Standard_String.hxx>

#include <map>

M_CAD_SPACE(Cad3d_BlockSurfaceOnSolid)

namespace AutLib
{
	typedef std::map<Standard_String, Global_Handle(M_CAD Cad3d_BlockSurfaceOnSolid)> TColCad3d_StringMapOfHBlockSurfaceOnSolid;
}

#endif // !_TColCad3d_StringMapOfHBlockSurfaceOnSolid_Header
