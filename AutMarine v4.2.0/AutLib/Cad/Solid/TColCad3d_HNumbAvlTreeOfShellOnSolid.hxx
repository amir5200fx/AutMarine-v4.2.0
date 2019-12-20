#pragma once
#ifndef _TColCad3d_HNumbAvlTreeOfShellOnSolid_Header
#define _TColCad3d_HNumbAvlTreeOfShellOnSolid_Header

#include <Global_Memory.hxx>
#include <Global_Macros.hxx>
#include <ADT_NumbAvlTree.hxx>

M_CAD_SPACE(Cad3d_ShellOnSolid)

namespace AutLib
{
	typedef ADT_NumbAvlTree<Global_Handle(M_CAD Cad3d_ShellOnSolid)> TColCad3d_HNumbAvlTreeOfShellOnSolid;
}

#endif // !_TColCad3d_HNumbAvlTreeOfShellOnSolid_Header
