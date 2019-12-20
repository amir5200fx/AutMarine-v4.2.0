#pragma once
#ifndef _TColMesh3d_HAry1dOfMesh_Header
#define _TColMesh3d_HAry1dOfMesh_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh3d_Mesh)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_MESH Mesh3d_Mesh)> TColMesh3d_HAry1dOfMesh;
}

#endif // !_TColMesh3d_HAry1dOfMesh_Header
