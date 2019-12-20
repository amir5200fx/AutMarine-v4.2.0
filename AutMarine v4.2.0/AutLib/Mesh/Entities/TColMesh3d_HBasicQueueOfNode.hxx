#pragma once
#ifndef _TColMesh3d_HBasicQueueOfNode_Header
#define _TColMesh3d_HBasicQueueOfNode_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh3d_Node)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_MESH Mesh3d_Node)> TColMesh3d_HBasicQueueOfNode;
}

#endif // !_TColMesh3d_HBasicQueueOfNode_Header