#pragma once
#ifndef _TColFvGeom_Ary1dOfElement2d_Header
#define _TColFvGeom_Ary1dOfElement2d_Header

#include <Global_Macros.hxx>
#include <ADT_Ary1d.hxx>

M_FV_SPACE(FvGeom_Element2d)

namespace AutLib
{
	typedef ADT_Ary1d<FvLib::FvGeom_Element2d> TColFvGeom_Ary1dOfElement2d;
}

#endif // !_TColFvGeom_Ary1dOfElement2d_Header
