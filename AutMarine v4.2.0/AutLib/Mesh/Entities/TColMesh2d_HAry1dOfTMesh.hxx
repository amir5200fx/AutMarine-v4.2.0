#pragma once
#ifndef _TColMesh2d_HAry1dOfTMesh_Header
#define _TColMesh2d_HAry1dOfTMesh_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh2d_TMesh)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_MESH Mesh2d_TMesh)> TColMesh2d_HAry1dOfTMesh;
}

#endif // !_TColMesh2d_HAry1dOfTMesh_Header