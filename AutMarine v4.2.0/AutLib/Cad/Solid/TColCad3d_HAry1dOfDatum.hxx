#pragma once
#ifndef _TColCad3d_HAry1dOfDatum_Header
#define _TColCad3d_HAry1dOfDatum_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_Ary1d.hxx>

M_CAD_SPACE(Cad3d_Datum)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_CAD Cad3d_Datum)> TColCad3d_HAry1dOfDatum;
}

#endif // !_TColCad3d_HAry1dOfDatum_Header
