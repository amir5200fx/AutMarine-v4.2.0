#pragma once
#ifndef _TColMesh2d_HAry1dOfMeshCurve_Header
#define _TColMesh2d_HAry1dOfMeshCurve_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh2d_Curve)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_MESH Mesh2d_Curve)> TColMesh2d_HAry1dOfMeshCurve;
}

#endif // !_TColMesh2d_HAry1dOfMeshCurve_Header
