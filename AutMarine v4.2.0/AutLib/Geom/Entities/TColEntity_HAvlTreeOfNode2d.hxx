#pragma once
#ifndef _TColEntity_HAvlTreeOfNode2d_Header
#define _TColEntity_HAvlTreeOfNode2d_Header

#include <ADT_AvlTree.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Node2d)

namespace AutLib
{
	typedef ADT_AvlTree<Global_Handle(M_GEO Entity_Node2d)> TColEntity_HAvlTreeOfNode2d;
}

#endif // !_TColEntity_HAvlTreeOfNode2d_Header
