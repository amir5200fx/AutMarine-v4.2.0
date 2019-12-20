#pragma once
#ifndef _TColEntity_HAry1dOfElement2d_Header
#define _TColEntity_HAry1dOfElement2d_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Element2d)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_GEO Entity_Element2d)> TColEntity_HAry1dOfElement2d;
}

#endif // !_TColEntity_HAry1dOfElement2d_Header
