#pragma once
#ifndef _TColSizeMap2d_StringMapOfHSharpCornersSizeMapTool_Header
#define _TColSizeMap2d_StringMapOfHSharpCornersSizeMapTool_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <Standard_String.hxx>

#include <map>

M_MESH_SPACE(SizeMap2d_SharpCornersSizeMapTool)

namespace AutLib
{
	typedef std::map<Standard_String, Global_Handle(M_MESH SizeMap2d_SharpCornersSizeMapTool)> TColSizeMap2d_StringMapOfHSharpCornersSizeMapTool;
}

#endif // !_TColSizeMap2d_StringMapOfHSharpCornersSizeMapTool_Header
