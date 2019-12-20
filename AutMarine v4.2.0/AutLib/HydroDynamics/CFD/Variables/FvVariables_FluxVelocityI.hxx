#pragma once
inline
M_FV FvVector & AutLib::FvLib::FvVariables_FluxVelocity::Velocity()
{
	return theU_;
}

inline 
const M_FV FvVector & AutLib::FvLib::FvVariables_FluxVelocity::Velocity() const
{
	return theU_;
}