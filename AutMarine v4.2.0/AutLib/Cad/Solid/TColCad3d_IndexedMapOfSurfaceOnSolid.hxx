#pragma once
#ifndef _TColCad3d_IndexedMapOfSurfaceOnSolid_Header
#define _TColCad3d_IndexedMapOfSurfaceOnSolid_Header

#include <Standard_Integer.hxx>
#include <Global_Memory.hxx>
#include <Global_Macros.hxx>

#include <map>

M_CAD_SPACE(Cad3d_SurfaceOnSolid)

namespace AutLib
{
	typedef std::map<Standard_Integer, Global_Handle(M_CAD Cad3d_SurfaceOnSolid)> TColCad3d_IndexedMapOfSurfaceOnSolid;
}

#endif // !_TColCad3d_IndexedMapOfSurfaceOnSolid_Header
