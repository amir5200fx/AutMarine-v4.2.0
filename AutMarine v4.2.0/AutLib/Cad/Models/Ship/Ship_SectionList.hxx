#pragma once
#ifndef _Ship_SectionList_Header
#define _Ship_SectionList_Header

#include <Global_Macros.hxx>
#include <Global_Memory.hxx>
#include <ADT_Ary1d.hxx>

M_CAD_SPACE(Ship_SectionControlPoints)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_CAD Ship_SectionControlPoints)> Ship_SectionList;
}

#endif // !_Ship_SectionList_Header
