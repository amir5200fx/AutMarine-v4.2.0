#pragma once
#ifndef _TColEntity_HAry1dOfFacet_Header
#define _TColEntity_HAry1dOfFacet_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Facet)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_GEO Entity_Facet)> TColEntity_HAry1dOfFacet;
}

#endif // !_TColEntity_HAry1dOfFacet_Header
