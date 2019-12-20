#pragma once
#ifndef _TColCad3d_HAry1dOfEdgeOnPlane_Header
#define _TColCad3d_HAry1dOfEdgeOnPlane_Header

#include <ADT_Ary1d.hxx>
#include <Global_Macros.hxx>
#include <Global_Memory.hxx>

M_CAD_SPACE(Cad3d_EdgeOnPlane)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_CAD Cad3d_EdgeOnPlane)> TColCad3d_HAry1dOfEdgeOnPlane;
}

#endif // !_TColCad3d_HAry1dOfEdgeOnPlane_Header
