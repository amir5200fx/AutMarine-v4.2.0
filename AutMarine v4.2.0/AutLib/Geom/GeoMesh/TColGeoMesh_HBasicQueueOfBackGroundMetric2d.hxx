#pragma once
#ifndef _TColGeoMesh_HBasicQueueOfBackGroundMetric2d_Header
#define _TColGeoMesh_HBasicQueueOfBackGroundMetric2d_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_BasicQueue.hxx>

M_GEO_SPACE(GeoMesh_BackGroundMetric2d)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_GEO GeoMesh_BackGroundMetric2d)> TColGeoMesh_HBasicQueueOfBackGroundMetric2d;
}

#endif // !_TColGeoMesh_HBasicQueueOfBackGroundMetric2d_Header
