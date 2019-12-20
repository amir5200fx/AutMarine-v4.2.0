#pragma once
#ifndef _TColCad2d_HAdressAvlTreeOfWireOnPlane_Header
#define _TColCad2d_HAdressAvlTreeOfWireOnPlane_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_AdressAvlTree.hxx>

M_CAD_SPACE(Cad2d_WireOnPlane)

namespace AutLib
{
	typedef ADT_AdressAvlTree<Global_Handle(M_CAD Cad2d_WireOnPlane)> TColCad2d_HAdressAvlTreeOfWireOnPlane;
}

#endif // !_TColCad2d_HAdressAvlTreeOfWireOnPlane_Header
