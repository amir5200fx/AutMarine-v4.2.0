#pragma once
#ifndef _TColMesh3d_HAry1dOfCavityShell_Header
#define _TColMesh3d_HAry1dOfCavityShell_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>
#include <Global_Macros.hxx>

M_MESH_SPACE(Mesh3d_CavityShell)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_MESH Mesh3d_CavityShell)> TColMesh3d_HAry1dOfCavityShell;
}

#endif // !_TColMesh3d_HAry1dOfCavityShell_Header
