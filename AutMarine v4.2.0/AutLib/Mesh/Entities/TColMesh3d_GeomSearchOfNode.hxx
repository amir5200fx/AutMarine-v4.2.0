#pragma once
#ifndef _TColMesh3d_GeomSearchOfNode_Header
#define _TColMesh3d_GeomSearchOfNode_Header

#include <Geom_Search3d.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh3d_Node)

namespace AutLib
{
	typedef M_GEO Geom_Search3d<Global_Handle(M_MESH Mesh3d_Node)> TColMesh3d_GeomSearchOfNode;
}

#endif // !_TColMesh3d_GeomSearchOfNode_Header
