#pragma once
inline
Label AutLib::FvLib::FvConnectivities_Quadruple::Size() const
{
	return (Label)4;
}

inline
Label AutLib::FvLib::FvConnectivities_Quadruple::Value(const Label theIndex) const
{
	return (&theV0_)[theIndex];
}