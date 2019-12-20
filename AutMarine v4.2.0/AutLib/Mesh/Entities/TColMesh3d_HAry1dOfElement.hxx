#pragma once
#ifndef _TColMesh3d_HAry1dOfElement_Header
#define _TColMesh3d_HAry1dOfElement_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_MESH_SPACE(Mesh3d_Element)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_MESH Mesh3d_Element)> TColMesh3d_HAry1dOfElement;
}

#endif // !_TColMesh3d_HAry1dOfElement_Header