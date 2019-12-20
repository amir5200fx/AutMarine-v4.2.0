#pragma once
#ifndef _TColMesh3d_HAvlTreeOfNode_Header
#define _TColMesh3d_HAvlTreeOfNode_Header

#include <ADT_AvlTree.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh3d_Node)

namespace AutLib
{

	typedef ADT_AvlTree<Global_Handle(M_MESH Mesh3d_Node)> TColMesh3d_HAvlTreeOfNode;
}

#endif // !_TColMesh3d_AvlTreeOfNode_Header