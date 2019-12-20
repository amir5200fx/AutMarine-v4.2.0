#pragma once
#ifndef _TColMesh3d_ADTree3dOfNode_Header
#define _TColMesh3d_ADTree3dOfNode_Header

#include <Geom_ADTree3d.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh3d_Node)

namespace AutLib
{
	typedef M_GEO Geom_ADTree3d<Global_Handle(M_MESH Mesh3d_Node)> TColMesh3d_ADTree3dOfNode;
}

#endif // !_TColMesh3d_ADTree3dOfNode_Header
