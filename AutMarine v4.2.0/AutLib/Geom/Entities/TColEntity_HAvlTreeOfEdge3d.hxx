#pragma once
#ifndef _TColEntity_HAvlTreeOfEdge3d_Header
#define _TColEntity_HAvlTreeOfEdge3d_Header

#include <ADT_AvlTree.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Edge3d)

namespace AutLib
{
	typedef ADT_AvlTree<Global_Handle(M_GEO Entity_Edge3d)> TColEntity_HAvlTreeOfEdge3d;
}

#endif // !_TColEntity_HAvlTreeOfEdge3d_Header
