#pragma once
#ifndef _TColCad3d_HAvlTreeOfSurfaceOnSolid_Header
#define _TColCad3d_HAvlTreeOfSurfaceOnSolid_Header

#include <ADT_AvlTree.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_SurfaceOnSolid)

namespace AutLib
{
	typedef ADT_AvlTree<Global_Handle(M_CAD Cad3d_SurfaceOnSolid)> TColCad3d_HAvlTreeOfSurfaceOnSolid;
}

#endif // !_TColCad3d_HAvlTreeOfSurfaceOnSolid_Header
