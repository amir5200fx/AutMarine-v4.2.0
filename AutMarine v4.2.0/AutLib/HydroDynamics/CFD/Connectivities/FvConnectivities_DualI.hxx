#pragma once
inline
Label AutLib::FvLib::FvConnectivities_Dual::Size() const
{
	return (Label)2;
}

inline
Label AutLib::FvLib::FvConnectivities_Dual::Value(const Label theIndex) const
{
	return (&theV0_)[theIndex];
}