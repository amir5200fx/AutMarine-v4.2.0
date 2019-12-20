#pragma once
#ifndef _TColGeoMesh_HAry1dOfBackGroundMesh3d_Header
#define _TColGeoMesh_HAry1dOfBackGroundMesh3d_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_Ary1d.hxx>

M_GEO_SPACE(GeoMesh_BackGroundMesh3d)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_GEO GeoMesh_BackGroundMesh3d)> TColGeoMesh_HAry1dOfBackGroundMesh3d;
}

#endif // !_TColGeoMesh_HAry1dOfBackGroundMesh3d_Header
