#pragma once
#ifndef _TColSizeMap3d_HAry1dOfPrimitiveShapeSource_Header
#define _TColSizeMap3d_HAry1dOfPrimitiveShapeSource_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_Ary1d.hxx>

M_MESH_SPACE(SizeMap3d_PrimitiveShapeSource)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_MESH SizeMap3d_PrimitiveShapeSource)> TColSizeMap3d_HAry1dOfPrimitiveShapeSource;
}


#endif // !_TColSizeMap3d_HAry1dOfPrimitiveShape_Header
