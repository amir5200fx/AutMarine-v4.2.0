#pragma once
#ifndef _TColMesh3d_HBasicQueueOfFacet_Header
#define _TColMesh3d_HBasicQueueOfFacet_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh3d_Facet)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_MESH Mesh3d_Facet)> TColMesh3d_HBasicQueueOfFacet;
}

#endif // !_TColMesh3d_HBasicQueueOfFacet_Header
