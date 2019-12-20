#pragma once
#ifndef _TColMesh2d_HBasicQueueOfEdge_Header
#define _TColMesh2d_HBasicQueueOfEdge_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh2d_Edge)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_MESH Mesh2d_Edge)> TColMesh2d_HBasicQueueOfEdge;
}

#endif // !_TColMesh2d_HBasicQueueOfEdge_Header
