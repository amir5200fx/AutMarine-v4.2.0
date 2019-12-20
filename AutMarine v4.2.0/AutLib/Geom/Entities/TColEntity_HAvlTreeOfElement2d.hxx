#pragma once
#ifndef _TColEntity_HAvlTreeOfElement2d_Header
#define _TColEntity_HAvlTreeOfElement2d_Header

#include <ADT_AvlTree.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Element2d)

namespace AutLib
{
	typedef ADT_AvlTree<Global_Handle(M_GEO Entity_Element2d)> TColEntity_HAvlTreeOfElement2d;
}

#endif // !_TColEntity_HAvlTreeOfElement2d_Header
