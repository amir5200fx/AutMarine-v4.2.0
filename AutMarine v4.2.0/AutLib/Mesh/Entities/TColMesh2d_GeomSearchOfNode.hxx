#pragma once
#ifndef _TColMesh2d_GeomSearchOfNode_Header
#define _TColMesh2d_GeomSearchOfNode_Header

#include <Geom_Search2d.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh2d_Node)

namespace AutLib
{
	typedef M_GEO Geom_Search2d<Global_Handle(M_MESH Mesh2d_Node)> TColMesh2d_GeomSearchOfNode;
}

#endif // !_TColMesh2d_GeomSearchOfNode_Header
