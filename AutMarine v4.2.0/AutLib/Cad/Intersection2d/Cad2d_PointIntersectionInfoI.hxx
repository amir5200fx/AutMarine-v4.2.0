#pragma once
inline
Standard_Real AutLib::CadLib::Cad2d_PointIntersectionInfo::Parameter1() const
{
	return theParameter1_;
}

inline 
Standard_Real AutLib::CadLib::Cad2d_PointIntersectionInfo::Parameter2() const
{
	return theParameter2_;
}

inline 
const Geom_Pnt2d & AutLib::CadLib::Cad2d_PointIntersectionInfo::Point() const
{
	return thePoint_;
}