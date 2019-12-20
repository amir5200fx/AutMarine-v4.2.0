#pragma once
#ifndef _TColMesh2d_ADTree2dOfNode_Header
#define _TColMesh2d_ADTree2dOfNode_Header

#include <Geom_ADTree2d.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh2d_Node)

namespace AutLib
{
	typedef M_GEO Geom_ADTree2d<Global_Handle(M_MESH Mesh2d_Node)> TColMesh2d_ADTree2dOfNode;
}

#endif // !_TColMesh2d_ADTree2dOfNode_Header
