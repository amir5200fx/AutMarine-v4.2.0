#pragma once
#ifndef _TColSizeMap2d_StringMapOfHAdaptiveCurvesSizeMapTool_Header
#define _TColSizeMap2d_StringMapOfHAdaptiveCurvesSizeMapTool_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <Standard_String.hxx>

#include <map>

M_MESH_SPACE(SizeMap2d_AdaptiveCurvesSizeMapTool)

namespace AutLib
{
	typedef std::map<Standard_String, Global_Handle(M_MESH SizeMap2d_AdaptiveCurvesSizeMapTool)> TColSizeMap2d_StringMapOfHAdaptiveCurvesSizeMapTool;
}

#endif // !_TColSizeMap2d_StringMapOfHAdaptiveCurvesSizeMapTool_Header
