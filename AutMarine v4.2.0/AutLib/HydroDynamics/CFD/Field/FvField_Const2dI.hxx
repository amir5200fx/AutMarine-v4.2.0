#pragma once
template<typename Type_>
inline AutLib::FvLib::FvField_Const2d<Type_>::FvField_Const2d(const Type_ & theValue)
	: theValue_(theValue)
{
}

template<typename Type_>
inline const Type_ & AutLib::FvLib::FvField_Const2d<Type_>::Value(const Geom_Pnt2d & theCoord) const
{
	return theValue_;
}