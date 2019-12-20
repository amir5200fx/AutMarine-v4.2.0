#pragma once
template<typename T>
inline AutLib::FvLib::FvField2d_Function<T>::FvField2d_Function(T(*theValueFunction)(const Geom_Pnt2d &))
	: theValueFunction_(theValueFunction)
{
}

template<typename T>
inline T AutLib::FvLib::FvField2d_Function<T>::Value(const Geom_Pnt2d & theCoord) const
{
	return theValueFunction_(theCoord);
}