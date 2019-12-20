#pragma once
#ifndef _TColCad3d_HAdressAvlTreeOfWireOnPlane_Header
#define _TColCad3d_HAdressAvlTreeOfWireOnPlane_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_AdressAvlTree.hxx>

M_CAD_SPACE(Cad3d_WireOnPlane)

namespace AutLib
{
	typedef ADT_AdressAvlTree<Global_Handle(M_CAD Cad3d_WireOnPlane)> TColCad3d_HAdressAvlTreeOfWireOnPlane;
}

#endif // !_TColCad3d_HAdressAvlTreeOfWireOnPlane_Header
