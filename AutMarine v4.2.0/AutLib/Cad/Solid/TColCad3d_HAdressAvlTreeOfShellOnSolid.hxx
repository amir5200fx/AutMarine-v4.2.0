#pragma once
#ifndef _TColCad3d_HAdressAvlTreeOfShellOnSolid_Header
#define _TColCad3d_HAdressAvlTreeOfShellOnSolid_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_AdressAvlTree.hxx>

M_CAD_SPACE(Cad3d_ShellOnSolid)

namespace AutLib
{
	typedef ADT_AdressAvlTree<Global_Handle(M_CAD Cad3d_ShellOnSolid)> TColCad3d_HAdressAvlTreeOfShellOnSolid;
}

#endif // !_TColCad3d_HAdressAvlTreeOfShellOnSolid_Header
