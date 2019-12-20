#pragma once
#ifndef _TColMesh3d_HAry1dOfFaceDiscrete_Header
#define _TColMesh3d_HAry1dOfFaceDiscrete_Header

#include <Global_Macros.hxx>
#include <Global_Memory.hxx>
#include <ADT_Ary1d.hxx>

M_MESH_SPACE(Mesh3d_FaceDiscrete)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_MESH Mesh3d_FaceDiscrete)> TColMesh3d_HAry1dOfFaceDiscrete;
}

#endif // !_TColMesh3d_HAry1dOfFaceDiscrete_Header
