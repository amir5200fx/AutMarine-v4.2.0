#pragma once
#ifndef _TColCad3d_IndexedMapOfPointOnSolid_Header
#define _TColCad3d_IndexedMapOfPointOnSolid_Header

#include <Standard_Integer.hxx>
#include <Global_Memory.hxx>
#include <Global_Macros.hxx>

#include <map>

M_CAD_SPACE(Cad3d_PointOnSolid)

namespace AutLib
{
	typedef std::map<Standard_Integer, Global_Handle(M_CAD Cad3d_PointOnSolid)> TColCad3d_IndexedMapOfPointOnSolid;
}

#endif // !_TColCad3d_IndexedMapOfPointOnSolid_Header
