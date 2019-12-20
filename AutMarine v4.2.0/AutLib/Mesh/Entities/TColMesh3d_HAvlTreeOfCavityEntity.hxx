#pragma once
#ifndef _TColMesh3d_HAvlTreeOfCavityEntity_Header
#define _TColMesh3d_HAvlTreeOfCavityEntity_Header

#include <ADT_AvlTree.hxx>
#include <Global_Memory.hxx>
#include <Global_Macros.hxx>

M_MESH_SPACE(Mesh3d_CavityEntity)

namespace AutLib
{
	typedef ADT_AvlTree<Global_Handle(M_MESH Mesh3d_CavityEntity)> TColMesh3d_HAvlTreeOfCavityEntity;
}

#endif // !_TColMesh3d_HAvlTreeOfCavityEntity_Header
