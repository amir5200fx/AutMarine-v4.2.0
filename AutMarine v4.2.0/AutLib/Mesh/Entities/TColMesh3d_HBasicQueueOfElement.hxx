#pragma once
#ifndef _TColMesh3d_HBasicQueueOfElement_Header
#define _TColMesh3d_HBasicQueueOfElement_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh3d_Element)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_MESH Mesh3d_Element)> TColMesh3d_HBasicQueueOfElement;
}

#endif // !_TColMesh3d_HBasicQueueOfElement_Header