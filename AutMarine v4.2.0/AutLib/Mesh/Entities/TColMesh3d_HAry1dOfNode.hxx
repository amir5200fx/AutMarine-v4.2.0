#pragma once
#ifndef _TColMesh3d_HAry1dOfNode_Header
#define _TColMesh3d_HAry1dOfNode_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh3d_Node)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_MESH Mesh3d_Node)> TColMesh3d_HAry1dOfNode;
}

#endif // !_TColMesh3d_Ary1dOfNode_Header