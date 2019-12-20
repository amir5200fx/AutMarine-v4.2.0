#pragma once
#ifndef _TColEntity_HAvlTreeOfFacet_Header
#define _TColEntity_HAvlTreeOfFacet_Header

#include <ADT_AvlTree.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Facet)

namespace AutLib
{
	typedef ADT_AvlTree<Global_Handle(M_GEO Entity_Facet)> TColEntity_HAvlTreeOfFacet;
}

#endif // !_TColEntity_HAvlTreeOfFacet_Header
