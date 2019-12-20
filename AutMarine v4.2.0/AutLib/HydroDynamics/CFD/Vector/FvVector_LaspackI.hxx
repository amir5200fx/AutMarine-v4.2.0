#pragma once
inline
Label AutLib::FvLib::FvVector_Laspack::Size() const
{
	return (Label)V_GetDim((Vector*)&theVector_);
}

inline 
Scalar AutLib::FvLib::FvVector_Laspack::Value(const Label theIndex) const
{
	return V_GetCmp((Vector*)&theVector_, (size_t)theIndex);
}

inline 
Scalar AutLib::FvLib::FvVector_Laspack::operator[](const Label theIndex) const
{
	return V_GetCmp((Vector*)&theVector_, (size_t)theIndex);
}

inline
Scalar AutLib::FvLib::FvVector_Laspack::operator()(const Label theIndex) const
{
	return V_GetCmp((Vector*)&theVector_, (size_t)theIndex);
}

inline
void AutLib::FvLib::FvVector_Laspack::SetValue
(
	const Label theIndex, 
	const Scalar theValue
)
{
	V_SetCmp((Vector*)&theVector_, (size_t)theIndex, (Real)theValue);
}

inline 
void AutLib::FvLib::FvVector_Laspack::AddValue
(
	const Label theIndex, 
	const Scalar theValue
)
{
	V_AddCmp((Vector*)&theVector_, (size_t)theIndex, (Real)theValue);
}