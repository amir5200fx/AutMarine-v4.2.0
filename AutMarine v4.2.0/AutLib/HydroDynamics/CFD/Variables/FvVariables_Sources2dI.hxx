#pragma once
inline
const M_FV FvVector & AutLib::FvLib::FvVariables_Sources2d::U_Component() const
{
	return theBu_;
}

inline 
const M_FV FvVector & AutLib::FvLib::FvVariables_Sources2d::V_Component() const
{
	return theBv_;
}

inline
M_FV FvVector & AutLib::FvLib::FvVariables_Sources2d::U_Component()
{
	return theBu_;
}

inline
M_FV FvVector & AutLib::FvLib::FvVariables_Sources2d::V_Component()
{
	return theBv_;
}