#pragma once
inline
const M_FV FvVector & AutLib::FvLib::FvVariables_Primitives2d::U_Component() const
{
	return theU_;
}

inline 
const M_FV FvVector & AutLib::FvLib::FvVariables_Primitives2d::V_Component() const
{
	return theV_;
}

inline 
const M_FV FvVector & AutLib::FvLib::FvVariables_Primitives2d::Pressure() const
{
	return theP_;
}

inline 
M_FV FvVector & AutLib::FvLib::FvVariables_Primitives2d::U_Component()
{
	return theU_;
}

inline 
M_FV FvVector & AutLib::FvLib::FvVariables_Primitives2d::V_Component()
{
	return theV_;
}

inline 
M_FV FvVector & AutLib::FvLib::FvVariables_Primitives2d::Pressure()
{
	return theP_;
}