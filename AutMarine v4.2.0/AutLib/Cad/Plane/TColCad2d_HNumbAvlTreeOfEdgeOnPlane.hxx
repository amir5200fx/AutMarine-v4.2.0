#pragma once
#ifndef _TColCad2d_HNumbAvlTreeOfEdgeOnPlane_Header
#define _TColCad2d_HNumbAvlTreeOfEdgeOnPlane_Header

#include <ADT_NumbAvlTree.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad2d_EdgeOnPlane)

namespace AutLib
{
	typedef ADT_NumbAvlTree<Global_Handle(M_CAD Cad2d_EdgeOnPlane)> TColCad2d_HNumbAvlTreeOfEdgeOnPlane;
}

#endif // !_TColCad2d_HNumbAvlTreeOfEdgeOnPlane_Header
