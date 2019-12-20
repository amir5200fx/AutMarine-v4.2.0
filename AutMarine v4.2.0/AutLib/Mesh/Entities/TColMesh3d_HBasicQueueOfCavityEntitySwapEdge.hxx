#pragma once
#ifndef _TColMesh3d_HBasicQueueOfCavityEntitySwapEdge_Header
#define _TColMesh3d_HBasicQueueOfCavityEntitySwapEdge_Header

#include <Global_Macros.hxx>
#include <Global_Memory.hxx>
#include <ADT_BasicQueue.hxx>

M_MESH_SPACE(Mesh3d_CavityEntitySwapEdge)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_MESH Mesh3d_CavityEntitySwapEdge)> TColMesh3d_HBasicQueueOfCavityEntitySwapEdge;
}

#endif // !_TColMesh3d_HBasicQueueOfCavityEntitySwapEdge_Header
