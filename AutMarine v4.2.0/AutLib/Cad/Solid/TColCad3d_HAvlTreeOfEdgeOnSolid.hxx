#pragma once
#ifndef _TColCad3d_HAvlTreeOfEdgeOnSolid_Header
#define _TColCad3d_HAvlTreeOfEdgeOnSolid_Header

#include <ADT_AvlTree.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_EdgeOnSolid)

namespace AutLib
{
	typedef ADT_AvlTree<Global_Handle(M_CAD Cad3d_EdgeOnSolid)> TColCad3d_HAvlTreeOfEdgeOnSolid;
}

#endif // !_TColCad3d_HAvlTreeOfEdgeOnSolid_Header
