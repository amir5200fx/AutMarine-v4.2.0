#pragma once
inline
Label AutLib::FvLib::FvConnectivities_Triple::Size() const
{
	return (Label)3;
}

inline 
Label AutLib::FvLib::FvConnectivities_Triple::Value(const Label theIndex) const
{
	return (&theV0_)[theIndex];
}