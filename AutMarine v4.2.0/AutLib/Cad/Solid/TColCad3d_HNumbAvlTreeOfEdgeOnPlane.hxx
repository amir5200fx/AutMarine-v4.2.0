#pragma once
#ifndef _TColCad3d_HNumbAvlTreeOfEdgeOnPlane_Header
#define _TColCad3d_HNumbAvlTreeOfEdgeOnPlane_Header

#include <ADT_NumbAvlTree.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_EdgeOnPlane)

namespace AutLib
{
	typedef ADT_NumbAvlTree<Global_Handle(M_CAD Cad3d_EdgeOnPlane)> TColCad3d_HNumbAvlTreeOfEdgeOnPlane;
}

#endif // !_TColCad3d_HNumbAvlTreeOfEdgeOnPlane_Header
