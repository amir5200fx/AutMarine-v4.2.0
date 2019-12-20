#pragma once
#ifndef _TColMesh2d_HBasicQueueOfSourcePoint_Header
#define _TColMesh2d_HBasicQueueOfSourcePoint_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Macros.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh2d_SourcePoint)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_MESH Mesh2d_SourcePoint)> TColMesh2d_HBasicQueueOfSourcePoint;
}

#endif // !_TColMesh2d_HBasicQueueOfSourcePoint_Header
