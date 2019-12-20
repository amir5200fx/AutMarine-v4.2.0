#pragma once
inline
const AutLib::FvLib::FvVector & AutLib::FvLib::FvInterpolation2d::FaceVector() const
{
	return thePhif_;
}

inline 
const AutLib::FvLib::FvVector & AutLib::FvLib::FvInterpolation2d::CellVector() const
{
	return thePhi_;
}