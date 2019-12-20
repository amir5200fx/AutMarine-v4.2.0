#pragma once
inline
const AutLib::FvLib::FvGradient2d_Pressure & AutLib::FvLib::FvGradient2d_Variables::Pressure() const
{
	return thePressure_;
}

inline 
const AutLib::FvLib::FvGradient2d_xVelocity & AutLib::FvLib::FvGradient2d_Variables::xVelocity() const
{
	return thexVelocity_;
}

inline 
const AutLib::FvLib::FvGradient2d_yVelocity & AutLib::FvLib::FvGradient2d_Variables::yVelocity() const
{
	return theyVelocity_;
}