#pragma once
#ifndef _TColMesh2d_HAry1dOfMetricMap_Header
#define _TColMesh2d_HAry1dOfMetricMap_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_Ary1d.hxx>

M_MESH_SPACE(Mesh2d_MetricMap)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_MESH Mesh2d_MetricMap)> TColMesh2d_HAry1dOfMetricMap;
}

#endif // !_TColMesh2d_HAry1dOfMetricMap_Header
