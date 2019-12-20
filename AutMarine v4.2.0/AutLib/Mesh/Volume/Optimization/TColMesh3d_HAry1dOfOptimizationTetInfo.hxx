#pragma once
#ifndef _TColMesh3d_HAry1dOfOptimizationTetInfo_Header
#define _TColMesh3d_HAry1dOfOptimizationTetInfo_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_Ary1d.hxx>

M_MESH_SPACE(Mesh3d_OptimizationTetInfo)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_MESH Mesh3d_OptimizationTetInfo)> TColMesh3d_HAry1dOfOptimizationTetInfo;
}

#endif // !_TColMesh3d_HAry1dOfOptimizationTetInfo_Header

