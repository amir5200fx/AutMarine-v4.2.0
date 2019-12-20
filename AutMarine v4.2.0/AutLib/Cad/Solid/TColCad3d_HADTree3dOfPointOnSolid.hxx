#pragma once
#ifndef _TColCad3d_HADTree3dOfPointOnSolid_Header
#define _TColCad3d_HADTree3dOfPointOnSolid_Header

#include <Global_Memory.hxx>
#include <Geom_ADTree3d.hxx>
#include <Global_Macros.hxx>

M_CAD_SPACE(Cad3d_PointOnSolid)

namespace AutLib
{

	typedef M_GEO Geom_ADTree3d<Global_Handle(M_CAD Cad3d_PointOnSolid)> TColCad3d_HADTree3dOfPointOnSolid;
}

#endif // !_TColCad3d_HADTree3dOfPointOnSolid_Header
