#pragma once
#ifndef _TColCad2d_HNumbAvlTreeOfPointOnPlane_Header
#define _TColCad2d_HNumbAvlTreeOfPointOnPlane_Header

#include <ADT_NumbAvlTree.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad2d_PointOnPlane)

namespace AutLib
{
	typedef ADT_NumbAvlTree<Global_Handle(M_CAD Cad2d_PointOnPlane)> TColCad2d_HNumbAvlTreeOfPointOnPlane;
}

#endif // !_TColCad2d_HNumbAvlTreeOfPointOnPlane_Header
