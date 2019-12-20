#pragma once
#ifndef _TColMesh3d_HBasicQueueOfEdge_Header
#define _TColMesh3d_HBasicQueueOfEdge_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh3d_Edge)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_MESH Mesh3d_Edge)> TColMesh3d_HBasicQueueOfEdge;
}

#endif // !_TColMesh3d_HBasicQueueOfEdge_Header