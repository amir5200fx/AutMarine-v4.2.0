#pragma once
#ifndef _Duct_SectionList_Header
#define _Duct_SectionList_Header

#include <Global_Macros.hxx>
#include <Global_Memory.hxx>
#include <ADT_Ary1d.hxx>

M_CAD_SPACE(Duct_SectionControlPoints)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_CAD Duct_SectionControlPoints)> Duct_SectionList;
}

#endif // !_Duct_SectionList_Header
