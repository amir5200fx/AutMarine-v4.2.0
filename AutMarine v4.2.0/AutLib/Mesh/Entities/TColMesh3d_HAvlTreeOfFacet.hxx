#pragma once
#ifndef _TColMesh3d_HAvlTreeOfFacet_Header
#define _TColMesh3d_HAvlTreeOfFacet_Header

#include <ADT_AvlTree.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh3d_Facet)

namespace AutLib
{

	typedef ADT_AvlTree<Global_Handle(M_MESH Mesh3d_Facet)> TColMesh3d_HAvlTreeOfFacet;
}

#endif // !_TColMesh3d_AvlTreeOfFacet_Header