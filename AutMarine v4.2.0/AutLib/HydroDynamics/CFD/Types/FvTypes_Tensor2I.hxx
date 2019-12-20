#pragma once
inline
void AutLib::FvLib::FvTypes_Tensor2::SetValue(const Tensor2 & theValue)
{
	theValue_ = theValue;
}

inline 
const Tensor2 & AutLib::FvLib::FvTypes_Tensor2::Value() const
{
	return theValue_;
}