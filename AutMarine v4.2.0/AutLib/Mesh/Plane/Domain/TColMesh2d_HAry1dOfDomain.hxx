#pragma once
#ifndef _TColMesh2d_HAry1dOfDomain_Header
#define _TColMesh2d_HAry1dOfDomain_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>
#include <Global_Macros.hxx>

M_MESH_SPACE(Mesh2d_Domain)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_MESH Mesh2d_Domain)> TColMesh2d_HAry1dOfDomain;
}

#endif // !_TColMesh2d_HAry1dOfDomain_Header
