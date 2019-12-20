#pragma once
#ifndef _TColCad3d_HNumbAvlTreeOfSurfaceOnSolid_Header
#define _TColCad3d_HNumbAvlTreeOfSurfaceOnSolid_Header

#include <ADT_NumbAvlTree.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_SurfaceOnSolid)

namespace AutLib
{
	typedef ADT_NumbAvlTree<Global_Handle(M_CAD Cad3d_SurfaceOnSolid)> TColCad3d_HNumbAvlTreeOfSurfaceOnSolid;
}

#endif // !_TColCad3d_HNumbAvlTreeOfSurfaceOnSolid_Header
