#pragma once
#ifndef _TColGeoMesh_HBasicQueueOfBackGroundMesh2d_Header
#define _TColGeoMesh_HBasicQueueOfBackGroundMesh2d_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_BasicQueue.hxx>

M_GEO_SPACE(GeoMesh_BackGroundMesh2d)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_GEO GeoMesh_BackGroundMesh2d)> TColGeoMesh_HBasicQueueOfBackGroundMesh2d;
}

#endif // !_TColGeoMesh_HBasicQueueOfBackGroundMesh2d_Header
