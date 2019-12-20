#pragma once
#ifndef _TColGeom_HAry1dOfPnt2d_Header
#define _TColGeom_HAry1dOfPnt2d_Header

#include <Geom_Pnt2d.hxx>
#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(Geom_Pnt2d)> TColGeom_HAry1dOfPnt2d;
}

#endif // !_TColGeom_HAry1dOfPnt2d_Header