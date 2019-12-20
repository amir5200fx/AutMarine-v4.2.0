#pragma once
#ifndef _TColMesh3d_HeapOfFacet_Header
#define _TColMesh3d_HeapOfFacet_Header

#include <Geometry_Heap.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh3d_Facet)

namespace AutLib
{

	typedef M_GEO Geometry_Heap<Global_Handle(M_MESH Mesh3d_Facet)> TColMesh3d_HeapOfFacet;
}

#endif // !_TColMesh3d_HeapOfFacet_Header
