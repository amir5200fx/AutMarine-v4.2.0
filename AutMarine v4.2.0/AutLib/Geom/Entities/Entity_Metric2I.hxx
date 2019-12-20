#pragma once
inline
AutLib::GeoLib::Entity_Metric2::Entity_Metric2()
{
}

inline
AutLib::GeoLib::Entity_Metric2::Entity_Metric2
(
	const Standard_Real H1,
	const Standard_Real H2,
	const Geom_Pnt2d & E1,
	const Geom_Pnt2d & E2
)
	: theH1_(H1)
	, theH2_(H2)
	, theE1_(E1)
	, theE2_(E2)
{
}

inline
Standard_Real AutLib::GeoLib::Entity_Metric2::H1() const
{
	return theH1_;
}

inline
Standard_Real AutLib::GeoLib::Entity_Metric2::H2() const
{
	return theH2_;
}

inline
Standard_Real& AutLib::GeoLib::Entity_Metric2::H1()
{
	return theH1_;
}

inline
Standard_Real& AutLib::GeoLib::Entity_Metric2::H2()
{
	return theH2_;
}

inline
const Geom_Pnt2d & AutLib::GeoLib::Entity_Metric2::E1() const
{
	return theE1_;
}

inline
const Geom_Pnt2d & AutLib::GeoLib::Entity_Metric2::E2() const
{
	return theE2_;
}

inline
Geom_Pnt2d & AutLib::GeoLib::Entity_Metric2::E1()
{
	return theE1_;
}

inline
Geom_Pnt2d & AutLib::GeoLib::Entity_Metric2::E2()
{
	return theE2_;
}

inline
Standard_Boolean AutLib::GeoLib::Entity_Metric2::IsDegenerate(const Standard_Real Tolerance) const
{
	return (1.0 - ABS(DotProduct(theE1_, theE2_))) <= Tolerance;
}

inline
void AutLib::GeoLib::Entity_Metric2::SetH1(const Standard_Real Value)
{
	theH1_ = Value;
}

inline
void AutLib::GeoLib::Entity_Metric2::SetH2(const Standard_Real Value)
{
	theH2_ = Value;
}

inline
void AutLib::GeoLib::Entity_Metric2::SetE1(const Geom_Pnt2d & E1)
{
	theE1_ = E1;
}

inline
void AutLib::GeoLib::Entity_Metric2::SetE2(const Geom_Pnt2d & E2)
{
	theE2_ = E2;
}

inline
void AutLib::GeoLib::Entity_Metric2::Normalize()
{
	theE1_ = theE1_.UnitLength();
	theE2_ = theE2_.UnitLength();
}