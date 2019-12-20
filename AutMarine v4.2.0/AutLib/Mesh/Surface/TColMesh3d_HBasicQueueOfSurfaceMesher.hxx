#pragma once
#ifndef _TColMesh3d_HBasicQueueOfSurfaceMesher_Header
#define _TColMesh3d_HBasicQueueOfSurfaceMesher_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Macros.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh3d_SurfaceMesher)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_MESH Mesh3d_SurfaceMesher)> TColMesh3d_HBasicQueueOfSurfaceMesher;
}

#endif // !_TColMesh3d_HBasicQueueOfSurfaceMesher_Header
