#pragma once
#ifndef _TColGeom_HAry1dOfPnt3d_Header
#define _TColGeom_HAry1dOfPnt3d_Header

#include <Geom_Pnt3d.hxx>
#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(Geom_Pnt3d)> TColGeom_HAry1dOfPnt3d;
}

#endif // !_TColGeom_HAry1dOfPnt3d_Header
