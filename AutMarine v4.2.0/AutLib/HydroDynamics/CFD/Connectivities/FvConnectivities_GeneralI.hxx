#pragma once
inline
Label AutLib::FvLib::FvConnectivities_General::Size() const
{
	return theValues_.Size();
}

inline 
Label AutLib::FvLib::FvConnectivities_General::Value(const Label theIndex) const
{
	return theValues_.Value(theIndex);
}