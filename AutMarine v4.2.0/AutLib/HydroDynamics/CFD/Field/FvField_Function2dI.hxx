#pragma once
template<typename Type_>
inline AutLib::FvLib::FvField_Function2d<Type_>::FvField_Function2d(Type_(*theValueFunction)(const Geom_Pnt2d &theCoord))
	: theValueFunction_(theValueFunction)
{
}

template<typename Type_>
inline Type_ AutLib::FvLib::FvField_Function2d<Type_>::Value(const Geom_Pnt2d & theCoord) const
{
	return theValueFunction_(theCoord);
}