#pragma once
#ifndef _TColCad2d_StringMapOfHBlockPointOnPlane_Header
#define _TColCad2d_StringMapOfHBlockPointOnPlane_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <Standard_String.hxx>

#include <map>

M_CAD_SPACE(Cad2d_BlockPointOnPlane)

namespace AutLib
{
	namespace CadLib
	{
		typedef std::map<Standard_String, Global_Handle(M_CAD Cad2d_BlockPointOnPlane)> TColCad2d_StringMapOfHBlockPointOnPlane;
	}
}

#endif // !_TColCad2d_StringMapOfHBlockPointOnPlane_Header
