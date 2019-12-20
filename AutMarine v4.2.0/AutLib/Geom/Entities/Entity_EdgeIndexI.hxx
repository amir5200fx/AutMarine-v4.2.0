#pragma once
#include <Global_Macros.hxx>
inline
AutLib::GeoLib::Entity_EdgeIndex::Entity_EdgeIndex()
{
}

inline
AutLib::GeoLib::Entity_EdgeIndex::Entity_EdgeIndex
(
	const Standard_Integer V1,
	const Standard_Integer V2
)
{
	theValue_[0] = V1;
	theValue_[1] = V2;
}

inline
Standard_Integer AutLib::GeoLib::Entity_EdgeIndex::Value(const Standard_Integer Index) const
{
	return theValue_[Index];
}

inline
Standard_Integer & AutLib::GeoLib::Entity_EdgeIndex::ChangeValue(const Standard_Integer Index)
{
	return theValue_[Index];
}

inline
Standard_Integer AutLib::GeoLib::Entity_EdgeIndex::V0() const
{
	return theValue_[0];
}

inline
Standard_Integer AutLib::GeoLib::Entity_EdgeIndex::V1() const
{
	return theValue_[1];
}

inline
Standard_Integer& AutLib::GeoLib::Entity_EdgeIndex::V0()
{
	return theValue_[0];
}

inline
Standard_Integer& AutLib::GeoLib::Entity_EdgeIndex::V1()
{
	return theValue_[1];
}

inline 
void AutLib::GeoLib::Entity_EdgeIndex::Reverse()
{
	Standard_Integer Temp = theValue_[0];
	theValue_[0] = theValue_[1];
	theValue_[1] = Temp;
}

inline
void AutLib::GeoLib::Entity_EdgeIndex::SetValue
(
	const Standard_Integer Index,
	const Standard_Integer Value
)
{
	theValue_[Index] = Value;
}

inline
void AutLib::GeoLib::Entity_EdgeIndex::SetV12
(
	const Standard_Integer V1,
	const Standard_Integer V2
)
{
	theValue_[0] = V1;
	theValue_[1] = V2;
}