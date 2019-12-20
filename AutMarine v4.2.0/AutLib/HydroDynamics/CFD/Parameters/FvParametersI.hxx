#pragma once
inline
const AutLib::FvLib::FvSolverConfig & AutLib::FvLib::FvParameters::Velocity() const
{
	return theVelocity_;
}

inline
const AutLib::FvLib::FvSolverConfig & AutLib::FvLib::FvParameters::Pressure() const
{
	return thePressure_;
}

inline 
const AutLib::FvLib::FvParameters_TimeConfig & AutLib::FvLib::FvParameters::Time() const
{
	return theTime_;
}