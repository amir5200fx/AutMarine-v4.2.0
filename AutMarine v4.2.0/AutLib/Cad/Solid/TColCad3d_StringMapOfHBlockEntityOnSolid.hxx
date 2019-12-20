#pragma once
#ifndef _TColCad3d_StringMapOfHBlockEntityOnSolid_Header
#define _TColCad3d_StringMapOfHBlockEntityOnSolid_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <Standard_String.hxx>

#include <map>

M_CAD_SPACE(Cad3d_BlockEntityOnSolid)

namespace AutLib
{
	typedef std::map<Standard_String, Global_Handle(M_CAD Cad3d_BlockEntityOnSolid)> TColCad3d_StringMapOfHBlockEntityOnSolid;
}

#endif // !_TColCad3d_StringMapOfHBlockEntityOnSolid_Header
