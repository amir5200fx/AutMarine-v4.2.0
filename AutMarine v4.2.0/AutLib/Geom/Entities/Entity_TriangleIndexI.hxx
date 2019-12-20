#pragma once
inline
AutLib::GeoLib::Entity_TriangleIndex::Entity_TriangleIndex()
{
}

inline
AutLib::GeoLib::Entity_TriangleIndex::Entity_TriangleIndex
(
	const Standard_Integer V0,
	const Standard_Integer V1,
	const Standard_Integer V2
)
{
	theValue_[0] = V0;
	theValue_[1] = V1;
	theValue_[2] = V2;
}

inline
Standard_Integer& AutLib::GeoLib::Entity_TriangleIndex::Value(const Standard_Integer Index)
{
	Debug_Bad_Index(Index, 0, 2);

	return theValue_[Index];
}

inline
Standard_Integer AutLib::GeoLib::Entity_TriangleIndex::Value(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 2);

	return theValue_[Index];
}

inline
Standard_Integer AutLib::GeoLib::Entity_TriangleIndex::V0() const
{
	return theValue_[0];
}

inline
Standard_Integer AutLib::GeoLib::Entity_TriangleIndex::V1() const
{
	return theValue_[1];
}

inline
Standard_Integer AutLib::GeoLib::Entity_TriangleIndex::V2() const
{
	return theValue_[2];
}

inline
Standard_Integer& AutLib::GeoLib::Entity_TriangleIndex::V0()
{
	return theValue_[0];
}

inline
Standard_Integer& AutLib::GeoLib::Entity_TriangleIndex::V1()
{
	return theValue_[1];
}

inline
Standard_Integer& AutLib::GeoLib::Entity_TriangleIndex::V2()
{
	return theValue_[2];
}

inline
void AutLib::GeoLib::Entity_TriangleIndex::SetV0(const Standard_Integer Value)
{
	theValue_[0] = Value;
}

inline
void AutLib::GeoLib::Entity_TriangleIndex::SetV1(const Standard_Integer Value)
{
	theValue_[1] = Value;
}

inline
void AutLib::GeoLib::Entity_TriangleIndex::SetV2(const Standard_Integer Value)
{
	theValue_[2] = Value;
}

inline
void AutLib::GeoLib::Entity_TriangleIndex::SetValue
(
	const Standard_Integer V0,
	const Standard_Integer V1,
	const Standard_Integer V2
)
{
	theValue_[0] = V0;
	theValue_[1] = V1;
	theValue_[2] = V2;
}

inline
Standard_OStream & AutLib::GeoLib::operator<<(Standard_OStream & Stream, const Entity_TriangleIndex & Triangle)
{
	Stream
		<< Triangle.theValue_[0]
		<< "  "
		<< Triangle.theValue_[1]
		<< "  "
		<< Triangle.theValue_[2];

	return Stream;
}

inline
Standard_IStream & AutLib::GeoLib::operator>>(Standard_IStream & Stream, Entity_TriangleIndex & Triangle)
{
	Stream
		>> Triangle.theValue_[0]
		>> Triangle.theValue_[1]
		>> Triangle.theValue_[2];

	return Stream;
}