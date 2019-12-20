#pragma once
#ifndef _TColFvGeom_Ary1dOfNode2d_Header
#define _TColFvGeom_Ary1dOfNode2d_Header

#include <Global_Macros.hxx>
#include <ADT_Ary1d.hxx>

M_FV_SPACE(FvGeom_Node2d)

namespace AutLib
{
	typedef ADT_Ary1d<M_FV FvGeom_Node2d> TColFvGeom_Ary1dOfNode2d;
}

#endif // !_TColFvGeom_Ary1dOfNode2d_Header
