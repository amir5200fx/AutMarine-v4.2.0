#pragma once
template<typename T>
inline AutLib::FvLib::FvField2d_Const<T>::FvField2d_Const(const T& theValue)
	: theValue_(theValue)
{
}

template<typename T>
inline T AutLib::FvLib::FvField2d_Const<T>::Value(const Geom_Pnt2d & theCoord) const
{
	return theValue_;
}