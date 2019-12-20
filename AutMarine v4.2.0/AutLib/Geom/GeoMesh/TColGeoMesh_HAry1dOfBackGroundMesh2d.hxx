#pragma once
#ifndef _TColGeoMesh_HAry1dOfBackGroundMesh2d_Header
#define _TColGeoMesh_HAry1dOfBackGroundMesh2d_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_Ary1d.hxx>

M_GEO_SPACE(GeoMesh_BackGroundMesh2d)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_GEO GeoMesh_BackGroundMesh2d)> TColGeoMesh_HAry1dOfBackGroundMesh2d;
}

#endif // !_TColGeoMesh_HAry1dOfBackGroundMesh2d_Header
