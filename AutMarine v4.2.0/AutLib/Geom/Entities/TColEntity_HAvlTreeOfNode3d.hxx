#pragma once
#ifndef _TColEntity_HAvlTreeOfNode3d_Header
#define _TColEntity_HAvlTreeOfNode3d_Header

#include <ADT_AvlTree.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Node3d)

namespace AutLib
{
	typedef ADT_AvlTree<Global_Handle(M_GEO Entity_Node3d)> TColEntity_HAvlTreeOfNode3d;
}

#endif // !_TColEntity_HAvlTreeOfNode3d_Header
