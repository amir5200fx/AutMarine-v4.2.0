#pragma once
#ifndef _TColGeoMesh_HAry1dOfTetrahedronMesh_Header
#define _TColGeoMesh_HAry1dOfTetrahedronMesh_Header

#include <Global_Macros.hxx>
#include <Global_Memory.hxx>
#include <ADT_Ary1d.hxx>

M_GEO_SPACE(GeoMesh_TetrahedronMesh)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_GEO GeoMesh_TetrahedronMesh)> TColGeoMesh_HAry1dOfTetrahedronMesh;
}

#endif // !_TColGeoMesh_HAry1dOfTetrahedronMesh_Header
