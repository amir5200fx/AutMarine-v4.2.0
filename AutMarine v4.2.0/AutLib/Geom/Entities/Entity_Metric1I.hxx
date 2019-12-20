#pragma once
inline
AutLib::GeoLib::Entity_Metric1::Entity_Metric1()
{
}

inline
AutLib::GeoLib::Entity_Metric1::Entity_Metric1
(
	const Standard_Real A,
	const Standard_Real B,
	const Standard_Real C
)
	: theA_(A)
	, theB_(B)
	, theC_(C)
{
}

inline
AutLib::GeoLib::Entity_Metric1 & AutLib::GeoLib::Entity_Metric1::operator*=(const Standard_Real Scalar)
{
	theA_ *= Scalar;
	theB_ *= Scalar;
	theC_ *= Scalar;

	return *this;
}

inline 
M_GEO Entity_Metric1 AutLib::GeoLib::Entity_Metric1::Inversed() const
{
	Entity_Metric1 M = *this;
	M.Inverse();
	MOVE(M);
}

inline
Standard_Real AutLib::GeoLib::Entity_Metric1::Determinant() const
{
	return theA_*theC_ - theB_*theB_;
}

inline
mat22 AutLib::GeoLib::Entity_Metric1::GetArma() const
{
	mat22 Metric;

	Metric(0, 0) = theA_;
	Metric(0, 1) = Metric(1, 0) = theB_;
	Metric(1, 1) = theC_;

	MOVE(Metric);
}

inline 
M_AUT TColStd_Ary2dOfReal AutLib::GeoLib::Entity_Metric1::GetMatrix() const
{
	TColStd_Ary2dOfReal M(2, 2);

	M[0][0] = theA_;
	M[0][1] = M[1][0] = theB_;
	M[1][1] = theC_;

	MOVE(M);
}

inline
Standard_Real AutLib::GeoLib::Entity_Metric1::A() const
{
	return theA_;
}

inline
Standard_Real AutLib::GeoLib::Entity_Metric1::B() const
{
	return theB_;
}

inline
Standard_Real AutLib::GeoLib::Entity_Metric1::C() const
{
	return theC_;
}

inline
Standard_Real& AutLib::GeoLib::Entity_Metric1::A()
{
	return theA_;
}

inline
Standard_Real& AutLib::GeoLib::Entity_Metric1::B()
{
	return theB_;
}

inline
Standard_Real& AutLib::GeoLib::Entity_Metric1::C()
{
	return theC_;
}

inline 
Standard_Boolean AutLib::GeoLib::Entity_Metric1::IsSingular(const Standard_Real Epsilon) const
{
	return Determinant() <= Epsilon;
}

inline 
void AutLib::GeoLib::Entity_Metric1::Inverse()
{
	Standard_Real D = 1.0 / Determinant();
	SWAP(theA_, theC_);

	theB_ *= -D;
	theA_ *= D;
	theC_ *= D;
}

inline 
void AutLib::GeoLib::Entity_Metric1::RemoveDegeneracy(const Standard_Real Epsilon)
{
	if (theA_ < Epsilon) theA_ = Epsilon;
	if (theC_ < Epsilon) theC_ = Epsilon;
}

namespace AutLib
{
	namespace GeoLib
	{
		inline Entity_Metric1 operator*(const Entity_Metric1 & Metric, const Standard_Real Scalar)
		{
			Entity_Metric1 M = Metric;
			M *= Scalar;
			return std::move(M);
		}

		inline Entity_Metric1 operator*(const Standard_Real Scalar, const Entity_Metric1 & Metric)
		{
			Entity_Metric1 M = Metric;
			M *= Scalar;
			return std::move(M);
		}

		inline Entity_Metric1 AutLib::GeoLib::operator+(const Entity_Metric1 & theMetric1, const Entity_Metric1 & theMetric2)
		{
			return Entity_Metric1(theMetric1.A() + theMetric2.A(), theMetric1.B() + theMetric2.B(), theMetric1.C() + theMetric2.C());
		}
	}
}