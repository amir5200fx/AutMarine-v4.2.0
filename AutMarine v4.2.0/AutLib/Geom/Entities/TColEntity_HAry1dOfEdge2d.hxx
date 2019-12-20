#pragma once
#ifndef _TColEntity_HAry1dOfEdge2d_Header
#define _TColEntity_HAry1dOfEdge2d_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_Edge2d)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_GEO Entity_Edge2d)> TColEntity_HAry1dOfEdge2d;
}

#endif // !_TColEntity_HAry1dOfEdge2d_Header
