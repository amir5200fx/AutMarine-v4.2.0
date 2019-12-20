#pragma once
#ifndef _TColGeoMesh_HBasicQueueOfBackGroundMesh3d_Header
#define _TColGeoMesh_HBasicQueueOfBackGroundMesh3d_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_BasicQueue.hxx>

M_GEO_SPACE(GeoMesh_BackGroundMesh3d)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_GEO GeoMesh_BackGroundMesh3d)> TColGeoMesh_HBasicQueueOfBackGroundMesh3d;
}

#endif // !_TColGeoMesh_HBasicQueueOfBackGroundMesh3d_Header
