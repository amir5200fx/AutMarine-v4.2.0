#pragma once
#ifndef _TColMesh2d_HAvlTreeOfElement_Header
#define _TColMesh2d_HAvlTreeOfElement_Header

#include <ADT_AvlTree.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh2d_Element)

namespace AutLib
{

	typedef ADT_AvlTree<Global_Handle(M_MESH Mesh2d_Element)> TColMesh2d_HAvlTreeOfElement;
}

#endif // !_TColMesh2d_AvlTreeOfElement_Header