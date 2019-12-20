#pragma once
inline
AutLib::GeoLib::Entity_TetrahedronIndex::Entity_TetrahedronIndex()
{
}

inline
AutLib::GeoLib::Entity_TetrahedronIndex::Entity_TetrahedronIndex
(
	const Standard_Integer V0,
	const Standard_Integer V1,
	const Standard_Integer V2,
	const Standard_Integer V3
)
{
	theValue_[0] = V0;
	theValue_[1] = V1;
	theValue_[2] = V2;
	theValue_[3] = V3;
}

inline
Standard_Integer & AutLib::GeoLib::Entity_TetrahedronIndex::Value(const Standard_Integer Index)
{
	Debug_Bad_Index(Index, 0, 3);

	return theValue_[Index];
}

inline
Standard_Integer AutLib::GeoLib::Entity_TetrahedronIndex::Value(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 3);

	return theValue_[Index];
}

inline
Standard_Integer AutLib::GeoLib::Entity_TetrahedronIndex::V0() const
{
	return theValue_[0];
}

inline
Standard_Integer AutLib::GeoLib::Entity_TetrahedronIndex::V1() const
{
	return theValue_[1];
}

inline
Standard_Integer AutLib::GeoLib::Entity_TetrahedronIndex::V2() const
{
	return theValue_[2];
}

inline
Standard_Integer AutLib::GeoLib::Entity_TetrahedronIndex::V3() const
{
	return theValue_[3];
}

inline
Standard_Integer& AutLib::GeoLib::Entity_TetrahedronIndex::V0()
{
	return theValue_[0];
}

inline
Standard_Integer& AutLib::GeoLib::Entity_TetrahedronIndex::V1()
{
	return theValue_[1];
}

inline
Standard_Integer& AutLib::GeoLib::Entity_TetrahedronIndex::V2()
{
	return theValue_[2];
}

inline
Standard_Integer& AutLib::GeoLib::Entity_TetrahedronIndex::V3()
{
	return theValue_[3];
}

inline
void AutLib::GeoLib::Entity_TetrahedronIndex::SetV0(const Standard_Integer Value)
{
	theValue_[0] = Value;
}

inline
void AutLib::GeoLib::Entity_TetrahedronIndex::SetV1(const Standard_Integer Value)
{
	theValue_[1] = Value;
}

inline
void AutLib::GeoLib::Entity_TetrahedronIndex::SetV2(const Standard_Integer Value)
{
	theValue_[2] = Value;
}

inline
void AutLib::GeoLib::Entity_TetrahedronIndex::SetV3(const Standard_Integer Value)
{
	theValue_[3] = Value;
}

inline
void AutLib::GeoLib::Entity_TetrahedronIndex::SetValue
(
	const Standard_Integer V0,
	const Standard_Integer V1,
	const Standard_Integer V2,
	const Standard_Integer V3
)
{
	theValue_[0] = V0;
	theValue_[1] = V1;
	theValue_[2] = V2;
	theValue_[3] = V3;
}

inline 
void AutLib::GeoLib::Entity_TetrahedronIndex::GetValue
(
	Standard_Integer & V0,
	Standard_Integer & V1, 
	Standard_Integer & V2,
	Standard_Integer & V3
) const
{
	V0 = theValue_[0];
	V1 = theValue_[1];
	V2 = theValue_[2];
	V3 = theValue_[3];
}

inline
Standard_OStream & AutLib::GeoLib::operator<<(Standard_OStream & Stream, const Entity_TetrahedronIndex & Tet)
{
	Stream
		<< Tet.theValue_[0]
		<< "  "
		<< Tet.theValue_[1]
		<< "  "
		<< Tet.theValue_[2]
		<< "  "
		<< Tet.theValue_[3];

	return Stream;
}

inline
Standard_IStream & AutLib::GeoLib::operator>>(Standard_IStream & Stream, Entity_TetrahedronIndex & Tet)
{
	Stream
		>> Tet.theValue_[0]
		>> Tet.theValue_[1]
		>> Tet.theValue_[2]
		>> Tet.theValue_[3];

	return Stream;
}