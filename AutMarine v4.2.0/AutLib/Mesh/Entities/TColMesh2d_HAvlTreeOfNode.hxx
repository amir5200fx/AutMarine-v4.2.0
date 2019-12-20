#pragma once
#ifndef _TColMesh2d_HAvlTreeOfNode_Header
#define _TColMesh2d_HAvlTreeOfNode_Header

#include <ADT_AvlTree.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh2d_Node)

namespace AutLib
{

	typedef ADT_AvlTree<Global_Handle(M_MESH Mesh2d_Node)> TColMesh2d_HAvlTreeOfNode;
}

#endif // !_TColMesh2d_AvlTreeOfNode_Header