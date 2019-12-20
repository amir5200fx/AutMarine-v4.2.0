#pragma once
#ifndef _TCOlCad3d_StringMapOfHBlockPointOnSolid_Header
#define _TCOlCad3d_StringMapOfHBlockPointOnSolid_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <Standard_String.hxx>

#include <map>

M_CAD_SPACE(Cad3d_BlockPointOnSolid)

namespace AutLib
{
	typedef std::map<Standard_String, Global_Handle(M_CAD Cad3d_BlockPointOnSolid)> TColCad3d_StringMapOfHBlockPointOnSolid;
}

#endif // !_TCOlCad3d_StringMapOfHBlockPointOnSolid_Header
