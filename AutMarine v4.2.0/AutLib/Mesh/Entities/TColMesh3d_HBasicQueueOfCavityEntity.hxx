#pragma once
#ifndef _TColMesh3d_HBasicQueueOfCavityEntity_Header
#define _TColMesh3d_HBasicQueueOfCavityEntity_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>
#include <Global_Macros.hxx>

M_MESH_SPACE(Mesh3d_CavityEntity)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_MESH Mesh3d_CavityEntity)> TColMesh3d_HBasicQueueOfCavityEntity;
}

#endif // !_TColMesh3d_HBasicQueueOfCavityEntity_Header
