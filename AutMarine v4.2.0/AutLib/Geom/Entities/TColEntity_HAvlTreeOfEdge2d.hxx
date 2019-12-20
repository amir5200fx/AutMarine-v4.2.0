#pragma once
#ifndef _TColEntity_HAvlTreeOfEdge2d_Header
#define _TColEntity_HAvlTreeOfEdge2d_Header

#include <ADT_AvlTree.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Edge2d)

namespace AutLib
{
	typedef ADT_AvlTree<Global_Handle(M_GEO Entity_Edge2d)> TColEntity_HAvlTreeOfEdge2d;
}

#endif // !_TColEntity_HAvlTreeOfEdge2d_Header
