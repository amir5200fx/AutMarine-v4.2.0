#pragma once
#ifndef _TColMesh2d_HBasicQueueOfMetricMap_Header
#define _TColMesh2d_HBasicQueueOfMetricMap_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_BasicQueue.hxx>

M_MESH_SPACE(Mesh2d_MetricMap)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_MESH Mesh2d_MetricMap)> TColMesh2d_HBasicQueueOfMetricMap;
}

#endif // !_TColMesh2d_HBasicQueueOfMetricMap_Header
