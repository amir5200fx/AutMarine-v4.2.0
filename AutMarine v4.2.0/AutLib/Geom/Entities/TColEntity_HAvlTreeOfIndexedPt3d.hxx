#pragma once
#ifndef _TColEntity_HAvlTreeOfIndexedPt3d_Header
#define _TColEntity_HAvlTreeOfIndexedPt3d_Header

#include <ADT_AvlTree.hxx>
#include <Global_Macros.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_IndexedPt3d)

namespace AutLib
{
	typedef ADT_AvlTree<Global_Handle(M_GEO Entity_IndexedPt3d)> TColEntity_HAvlTreeOfIndexedPt3d;
}

#endif // !_TColEntity_HAvlTreeOfIndexedPt3d_Header
