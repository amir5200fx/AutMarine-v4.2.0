#pragma once
#ifndef _TColMetricMap_HAry1dOfSingleMap2d_Header
#define _TColMetricMap_HAry1dOfSingleMap2d_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_Ary1d.hxx>

M_MESH_SPACE(MetricMap_SingleMap2d)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_MESH MetricMap_SingleMap2d)> TColMetricMap_HAry1dOfSingleMap2d;
}

#endif // !_TColMetricMap_HAry1dOfSingleMap2d_Header
