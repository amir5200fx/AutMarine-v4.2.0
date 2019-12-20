#pragma once
#ifndef _TColMesh2d_HBasicQueueOfNode_Header
#define _TColMesh2d_HBasicQueueOfNode_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh2d_Node)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_MESH Mesh2d_Node)> TColMesh2d_HBasicQueueOfNode;
}

#endif // !_TColMesh2d_HBasicQueueOfNode_Header
