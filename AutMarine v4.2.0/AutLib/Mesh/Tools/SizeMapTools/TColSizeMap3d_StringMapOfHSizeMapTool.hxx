#pragma once
#ifndef _TColSizeMap3d_StringMapOfHSizeMapTool_Header
#define _TColSizeMap3d_StringMapOfHSizeMapTool_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <Standard_String.hxx>

#include <map>

M_MESH_SPACE(SizeMap3d_SizeMapTool)

namespace AutLib
{
	typedef std::map<Standard_String, Global_Handle(M_MESH SizeMap3d_SizeMapTool)> TColSizeMap3d_StringMapOfHSizeMapTool;
}

#endif // !_TColSizeMap3d_StringMapOfHSizeMapTool_Header
