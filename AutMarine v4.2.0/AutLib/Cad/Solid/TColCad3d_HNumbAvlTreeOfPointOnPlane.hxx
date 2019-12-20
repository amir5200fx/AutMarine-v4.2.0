#pragma once
#ifndef _TColCad3d_HNumbAvlTreeOfPointOnPlane_Header
#define _TColCad3d_HNumbAvlTreeOfPointOnPlane_Header

#include <ADT_NumbAvlTree.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_PointOnPlane)

namespace AutLib
{
	typedef ADT_NumbAvlTree<Global_Handle(M_CAD Cad3d_PointOnPlane)> TColCad3d_HNumbAvlTreeOfPointOnPlane;
}

#endif // !_TColCad3d_HNumbAvlTreeOfPointOnPlane_Header
