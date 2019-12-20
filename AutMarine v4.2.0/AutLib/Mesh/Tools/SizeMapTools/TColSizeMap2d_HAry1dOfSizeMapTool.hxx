#pragma once
#ifndef _TColSizeMap2d_HAry1dOfSizeMapTool_Header
#define _TColSizeMap2d_HAry1dOfSizeMapTool_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_Ary1d.hxx>

M_MESH_SPACE(SizeMap2d_SizeMapTool)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_MESH SizeMap2d_SizeMapTool)> TColSizeMap2d_HAry1dOfSizeMapTool;
}

#endif // !_TColSizeMap2d_HAry1dOfSizeMapTool_Header
