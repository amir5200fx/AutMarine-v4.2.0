#pragma once
#ifndef _TColMesh3d_HBasicQueueOfSourcePoint_Header
#define _TColMesh3d_HBasicQueueOfSourcePoint_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Macros.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh3d_SourcePoint)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_MESH Mesh3d_SourcePoint)> TColMesh3d_HBasicQueueOfSourcePoint;
}

#endif // !_TColMesh3d_HBasicQueueOfSourcePoint_Header
