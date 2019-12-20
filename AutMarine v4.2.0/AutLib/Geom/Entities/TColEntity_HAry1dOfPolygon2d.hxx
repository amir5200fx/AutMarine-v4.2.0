#pragma once
#ifndef _TColEntity_HAry1dOfPolygon2d_Header
#define _TColEntity_HAry1dOfPolygon2d_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Polygon2d)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_GEO Entity_Polygon2d)> TColEntity_HAry1dOfPolygon2d;
}

#endif // !_TColEntity_HAry1dOfPolygon2d_Header
