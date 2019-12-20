#pragma once
#ifndef _TColMesh2d_HAvlTreeOfEdge_Header
#define _TColMesh2d_HAvlTreeOfEdge_Header

#include <ADT_AvlTree.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh2d_Edge)

namespace AutLib
{
	
	typedef ADT_AvlTree<Global_Handle(M_MESH Mesh2d_Edge)> TColMesh2d_HAvlTreeOfEdge;
}

#endif // !_TColMesh2d_AvlTreeOfNode_Header