#pragma once
#ifndef _Cad3d_RegisterDatum_Header
#define _Cad3d_RegisterDatum_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <Geom_ADTree3d.hxx>

M_CAD_SPACE(Cad3d_Datum);

namespace AutLib
{
	typedef M_GEO Geom_ADTree3d<Global_Handle(M_CAD Cad3d_Datum)> Cad3d_RegisterDatum;
}

#endif // !_Cad3d_RegisterDatum_Header
