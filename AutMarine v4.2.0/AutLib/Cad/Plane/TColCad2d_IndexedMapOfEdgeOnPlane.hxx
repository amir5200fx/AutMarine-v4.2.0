#pragma once
#ifndef _TColCad2d_IndexedMapOfEdgeOnPlane_Header
#define _TColCad2d_IndexedMapOfEdgeOnPlane_Header

#include <Standard_Integer.hxx>
#include <Global_Memory.hxx>
#include <Global_Macros.hxx>

#include <map>

M_CAD_SPACE(Cad2d_EdgeOnPlane)

namespace AutLib
{
	typedef std::map<Standard_Integer, Global_Handle(M_CAD Cad2d_EdgeOnPlane)> TColCad2d_IndexedMapOfEdgeOnPlane;
}

#endif // !_TColCad2d_IndexedMapOfEdgeOnPlane_Header
