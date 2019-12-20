#pragma once
#ifndef _TColMesh2d_HBasicQueueOfElement_Header
#define _TColMesh2d_HBasicQueueOfElement_Header

#include <ADT_BasicQueue.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh2d_Element)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_MESH Mesh2d_Element)> TColMesh2d_HBasicQueueOfElement;
}

#endif // !_TColMesh2d_HBasicQueueOfElement_Header
