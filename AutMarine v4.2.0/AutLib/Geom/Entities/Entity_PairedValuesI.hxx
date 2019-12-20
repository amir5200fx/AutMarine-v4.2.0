#pragma once
template<typename T>
inline AutLib::GeoLib::Entity_PairedValues<T>::Entity_PairedValues()
{
}

template<typename T>
inline AutLib::GeoLib::Entity_PairedValues<T>::Entity_PairedValues
(
	T theX1,
	T theX2
)
	: theX1_(theX1)
	, theX2_(theX2)
{
}

template<typename T>
inline T AutLib::GeoLib::Entity_PairedValues<T>::X1() const
{
	return theX1_;
}

template<typename T>
inline T AutLib::GeoLib::Entity_PairedValues<T>::X2() const
{
	return theX2_;
}

template<typename T>
inline T & AutLib::GeoLib::Entity_PairedValues<T>::X1()
{
	return theX1_;
}

template<typename T>
inline T & AutLib::GeoLib::Entity_PairedValues<T>::X2()
{
	return theX2_;
}