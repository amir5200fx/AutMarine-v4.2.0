#pragma once
#ifndef _TColMesh3d_HAry1dOfTMesh_Header
#define _TColMesh3d_HAry1dOfTMesh_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh3d_TMesh)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_MESH Mesh3d_TMesh)> TColMesh3d_HAry1dOfTMesh;
}

#endif // !_TColMesh3d_HAry1dOfTMesh_Header
