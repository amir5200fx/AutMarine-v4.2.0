#pragma once
inline
AutLib::FvLib::FvBC_Physics AutLib::FvLib::FvBC_Boundary::Physics() const
{
	return thePhysics_;
}

inline 
AutLib::FvLib::FvBC_Type AutLib::FvLib::FvBC_Boundary::Type() const
{
	return theType_;
}