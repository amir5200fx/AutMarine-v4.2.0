#pragma once
#ifndef _TColMesh3d_HeapOfEdge_Header
#define _TColMesh3d_HeapOfEdge_Header

#include <Geometry_Heap.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh3d_Edge)

namespace AutLib
{

	typedef M_GEO Geometry_Heap<Global_Handle(M_MESH Mesh3d_Edge)> TColMesh3d_HeapOfEdge;
}

#endif // !_TColMesh3d_HeapOfEdge3d_Header
