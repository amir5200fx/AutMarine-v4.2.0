#pragma once
#ifndef _TColMesh3d_HAvlTreeOfElement_Header
#define _TColMesh3d_HAvlTreeOfElement_Header

#include <ADT_AvlTree.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh3d_Element)

namespace AutLib
{

	typedef ADT_AvlTree<Global_Handle(M_MESH Mesh3d_Element)> TColMesh3d_HAvlTreeOfElement;
}

#endif // !_TColMesh3d_AvlTreeOfElement_Header