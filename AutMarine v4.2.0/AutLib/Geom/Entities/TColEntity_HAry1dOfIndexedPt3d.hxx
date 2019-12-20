#pragma once
#ifndef _TColEntity_HAry1dOfIndexedPt3d_Header
#define _TColEntity_HAry1dOfIndexedPt3d_Header

#include <ADT_Ary1d.hxx>
#include <Global_Macros.hxx>
#include <Global_Memory.hxx>

M_GEO_SPACE(Entity_IndexedPt3d)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_GEO Entity_IndexedPt3d)> TColEntity_HAry1dOfIndexedPt3d;
}

#endif // !_TColEntity_HAry1dOfIndexedPt3d_Header
