#pragma once
#ifndef _TColCad2d_HNumbAvlTreeOfWireOnPlane_Header
#define _TColCad2d_HNumbAvlTreeOfWireOnPlane_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_NumbAvlTree.hxx>

M_CAD_SPACE(Cad2d_WireOnPlane)

namespace AutLib
{
	typedef ADT_NumbAvlTree<Global_Handle(M_CAD Cad2d_WireOnPlane)> TColCad2d_HNumbAvlTreeOfWireOnPlane;
}

#endif // !_TColCad2d_HNumbAvlTreeOfWireOnPlane_Header
