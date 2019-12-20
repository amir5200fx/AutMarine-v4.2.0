#pragma once
inline
void AutLib::FvLib::FvTypes_Vec2::SetValue(const Vec2 & theValue)
{
	theValue_ = theValue;
}

inline 
const Vec2 & AutLib::FvLib::FvTypes_Vec2::Value() const
{
	return theValue_;
}