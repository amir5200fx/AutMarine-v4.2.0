#pragma once
#ifndef _TColMesh2d_HAry1dOfNode_Header
#define _TColMesh2d_HAry1dOfNode_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh2d_Node)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_MESH Mesh2d_Node)> TColMesh2d_HAry1dOfNode;
}

#endif // !_TColMesh2d_Ary1dOfNode_Header
