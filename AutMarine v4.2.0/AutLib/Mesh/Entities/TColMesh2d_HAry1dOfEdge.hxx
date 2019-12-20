#pragma once
#ifndef _TColMesh2d_HAry1dOfEdge_Header
#define _TColMesh2d_HAry1dOfEdge_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh2d_Edge)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_MESH Mesh2d_Edge)> TColMesh2d_HAry1dOfEdge;
}

#endif // !_TColMesh2d_HAry1dOfEdge_Header
