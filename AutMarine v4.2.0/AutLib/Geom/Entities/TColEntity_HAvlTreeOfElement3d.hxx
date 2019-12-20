#pragma once
#ifndef _TColEntity_HAvlTreeOfElement3d_Header
#define _TColEntity_HAvlTreeOfElement3d_Header

#include <ADT_AvlTree.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Element3d)

namespace AutLib
{
	typedef ADT_AvlTree<Global_Handle(M_GEO Entity_Element3d)> TColEntity_HAvlTreeOfElement3d;
}

#endif // !_TColEntity_HAvlTreeOfElement3d_Header
