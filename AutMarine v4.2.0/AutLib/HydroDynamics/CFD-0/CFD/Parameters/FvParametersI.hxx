#pragma once
inline
AutLib::FvLib::FvParameters_SolverConfig & AutLib::FvLib::FvParameters::Velocity()
{
	return theVelocity_;
}

inline 
AutLib::FvLib::FvParameters_SolverConfig & AutLib::FvLib::FvParameters::Pressure()
{
	return thePressure_;
}

inline
const AutLib::FvLib::FvParameters_SolverConfig & AutLib::FvLib::FvParameters::Velocity() const
{
	return theVelocity_;
}

inline
const AutLib::FvLib::FvParameters_SolverConfig & AutLib::FvLib::FvParameters::Pressure() const
{
	return thePressure_;
}

inline 
const AutLib::FvLib::FvParameters_TimeConfig & AutLib::FvLib::FvParameters::Time() const
{
	return theTime_;
}