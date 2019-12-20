#pragma once
#ifndef _TColCad3d_HNumbAvlTreeOfEdgeOnSolid_Header
#define _TColCad3d_HNumbAvlTreeOfEdgeOnSolid_Header

#include <ADT_NumbAvlTree.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_EdgeOnSolid)

namespace AutLib
{
	typedef ADT_NumbAvlTree<Global_Handle(M_CAD Cad3d_EdgeOnSolid)> TColCad3d_HNumbAvlTreeOfEdgeOnSolid;
}

#endif // !_TColCad3d_HNumbAvlTreeOfEdgeOnSolid_Header
