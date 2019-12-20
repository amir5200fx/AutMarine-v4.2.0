#pragma once
#ifndef _TColMetricMap_HBasicQueueOfSingleMap2d_Header
#define _TColMetricMap_HBasicQueueOfSingleMap2d_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_BasicQueue.hxx>

M_MESH_SPACE(MetricMap_SingleMap2d)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_MESH MetricMap_SingleMap2d)> TColMetricMap_HBasicQueueOfSingleMap2d;
}

#endif // !_TColMetricMap_HBasicQueueOfSingleMap2d_Header
