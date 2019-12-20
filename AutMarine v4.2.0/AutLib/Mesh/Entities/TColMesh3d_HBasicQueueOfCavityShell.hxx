#pragma once
#ifndef _TColMesh3d_HBasicQueueOfCavityShell_Header
#define _TColMesh3d_HBasicQueueOfCavityShell_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>
#include <Global_Macros.hxx>

M_MESH_SPACE(Mesh3d_CavityShell)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_MESH Mesh3d_CavityShell)> TColMesh3d_HBasicQueueOfCavityShell;
}

#endif // !_TColMesh3d_HBasicQueueOfCavityShell_Header
