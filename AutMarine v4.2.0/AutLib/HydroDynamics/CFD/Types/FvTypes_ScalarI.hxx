#pragma once
inline
void AutLib::FvLib::FvTypes_Scalar::SetValue(const Scalar theValue)
{
	theValue_ = theValue;
}

inline 
Scalar AutLib::FvLib::FvTypes_Scalar::Value() const
{
	return theValue_;
}