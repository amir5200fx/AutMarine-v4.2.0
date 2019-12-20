#pragma once
#ifndef _TColMesh3d_HAvlTreeOfEdge_Header
#define _TColMesh3d_HAvlTreeOfEdge_Header

#include <ADT_AvlTree.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh3d_Edge)

namespace AutLib
{

	typedef ADT_AvlTree<Global_Handle(M_MESH Mesh3d_Edge)> TColMesh3d_HAvlTreeOfEdge;
}

#endif // !_TColMesh3d_AvlTreeOfEdge_Header