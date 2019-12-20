#pragma once
#ifndef _TColEntity_HAry1dOfTriangulation2d_Header
#define _TColEntity_HAry1dOfTriangulation2d_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>
#include <Global_Macros.hxx>

M_GEO_SPACE(Entity_Triangulation2d)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_GEO Entity_Triangulation2d)> TColEntity_HAry1dOfTriangulation2d;
}

#endif // !_TColEntity_HAry1dOfTriangulation2d_Header