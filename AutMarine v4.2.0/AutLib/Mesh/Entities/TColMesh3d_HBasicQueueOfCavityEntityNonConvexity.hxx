#pragma once
#ifndef _TColMesh3d_HBasicQueueOfCavityEntityNonConvexity_Header
#define _TColMesh3d_HBasicQueueOfCavityEntityNonConvexity_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>
#include <Global_Macros.hxx>

M_MESH_SPACE(Mesh3d_CavityEntityNonConvexity)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_MESH Mesh3d_CavityEntityNonConvexity)> TColMesh3d_HBasicQueueOfCavityEntityNonConvexity;
}

#endif // !_TColMesh3d_HBasicQueueOfCavityEntityNonConvexity_Header
