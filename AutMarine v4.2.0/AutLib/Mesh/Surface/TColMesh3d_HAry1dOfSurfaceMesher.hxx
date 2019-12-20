#pragma once
#ifndef _TColMesh3d_HAry1dOfSurfaceMesher_Header
#define _TColMesh3d_HAry1dOfSurfaceMesher_Header

#include <ADT_Ary1d.hxx>
#include <Global_Macros.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh3d_SurfaceMesher)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_MESH Mesh3d_SurfaceMesher)> TColMesh3d_HAry1dOfSurfaceMesher;
}

#endif // !_TColMesh3d_HAry1dOfSurfaceMesher_Header
