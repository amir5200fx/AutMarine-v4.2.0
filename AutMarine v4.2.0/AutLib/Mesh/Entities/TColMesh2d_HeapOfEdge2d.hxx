#pragma once
#ifndef _TColMesh2d_HeapOfEdge2d_Header
#define _TColMesh2d_HeapOfEdge2d_Header

#include <Geometry_Heap.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh2d_Edge)

namespace AutLib
{

	typedef M_GEO Geometry_Heap<Global_Handle(M_MESH Mesh2d_Edge)> TColMesh2d_HeapOfEdge2d;
}

#endif // !_TColMesh2d_HeapOfEdge2d_Header
