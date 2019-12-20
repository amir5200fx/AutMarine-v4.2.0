#pragma once
#ifndef _TColMesh2d_HAry1dOfMetricSourcePoint_Header
#define _TColMesh2d_HAry1dOfMetricSourcePoint_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_Ary1d.hxx>

M_MESH_SPACE(Mesh2d_MetricSourcePoint)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_MESH Mesh2d_MetricSourcePoint)> TColMesh2d_HAry1dOfMetricSourcePoint;
}

#endif // !_TColMesh2d_HAry1dOfMetricSourcePoint_Header
