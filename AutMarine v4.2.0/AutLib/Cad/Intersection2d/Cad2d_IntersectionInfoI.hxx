#pragma once
inline
const  M_AUT TColCad2d_HAry1dOfPointIntersectionInfo & AutLib::CadLib::Cad2d_IntersectionInfo::Points() const
{
	return thePoints_;
}

inline 
const M_AUT TColCad2d_HAry1dOfSegmentIntersectionInfo & AutLib::CadLib::Cad2d_IntersectionInfo::Segments() const
{
	return theSegments_;
}

inline 
Standard_Integer AutLib::CadLib::Cad2d_IntersectionInfo::NbPoints() const
{
	return thePoints_.Size();
}

inline 
Standard_Integer AutLib::CadLib::Cad2d_IntersectionInfo::NbSegments() const
{
	return theSegments_.Size();
}

inline 
const M_CAD Cad2d_PointIntersectionInfo & AutLib::CadLib::Cad2d_IntersectionInfo::Point(const Standard_Integer theIndex) const
{
	if (NOT INSIDE(theIndex, 0, MaxIndexOf(thePoints_))) { THROW_STANDARD_EXCEPTION("Bad Index"); }
	return *thePoints_[theIndex];
}

inline 
const M_CAD Cad2d_SegmentIntersectionInfo & AutLib::CadLib::Cad2d_IntersectionInfo::Segment(const Standard_Integer theIndex) const
{
	if (NOT INSIDE(theIndex, 0, MaxIndexOf(theSegments_))) { THROW_STANDARD_EXCEPTION("Bad Index"); }
	return *theSegments_[theIndex];
}