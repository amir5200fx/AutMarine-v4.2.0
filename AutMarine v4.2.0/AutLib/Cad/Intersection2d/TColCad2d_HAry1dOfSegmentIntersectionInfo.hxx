#pragma once
#ifndef _TColCad2d_HAry1dOfSegmentIntersectionInfo_Header
#define _TColCad2d_HAry1dOfSegmentIntersectionInfo_Header

#include <ADT_Ary1d.hxx>
#include <Global_Memory.hxx>
#include <Global_Macros.hxx>

M_CAD_SPACE(Cad2d_SegmentIntersectionInfo)

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(M_CAD Cad2d_SegmentIntersectionInfo)> TColCad2d_HAry1dOfSegmentIntersectionInfo;
}

#endif // !_TColCad2d_HAry1dOfSegmentIntersectionInfo_Header
