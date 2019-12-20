#pragma once
inline
AutLib::GeoLib::Geom_Pnt3d::Geom_Pnt3d()
{
}

inline 
AutLib::GeoLib::Geom_Pnt3d::Geom_Pnt3d(const gp_Pnt & Other)
	: gp_Pnt(Other)
{
}

inline
AutLib::GeoLib::Geom_Pnt3d::Geom_Pnt3d
(
	const Standard_Real Xp,
	const Standard_Real Yp,
	const Standard_Real Zp
)
	: gp_Pnt(Xp, Yp, Zp)
{
}

inline
M_GEO Geom_Pnt3d & AutLib::GeoLib::Geom_Pnt3d::operator+=(const Geom_Pnt3d & Other)
{
	coord.X() += Other.X();
	coord.Y() += Other.Y();
	coord.Z() += Other.Z();

	return *this;
}

inline
M_GEO Geom_Pnt3d & AutLib::GeoLib::Geom_Pnt3d::operator-=(const Geom_Pnt3d & Other)
{
	coord.X() -= Other.X();
	coord.Y() -= Other.Y();
	coord.Z() -= Other.Z();

	return *this;
}

inline
M_GEO Geom_Pnt3d & AutLib::GeoLib::Geom_Pnt3d::operator*=(const Geom_Pnt3d & Other)
{
	coord.X() *= Other.X();
	coord.Y() *= Other.Y();
	coord.Z() *= Other.Z();

	return *this;
}

inline
M_GEO Geom_Pnt3d & AutLib::GeoLib::Geom_Pnt3d::operator=(const Standard_Real Scalar)
{
	coord.X() = Scalar;
	coord.Y() = Scalar;
	coord.Z() = Scalar;

	return *this;
}

inline
M_GEO Geom_Pnt3d & AutLib::GeoLib::Geom_Pnt3d::operator+=(const Standard_Real Scalar)
{
	coord.X() += Scalar;
	coord.Y() += Scalar;
	coord.Z() += Scalar;

	return *this;
}

inline
M_GEO Geom_Pnt3d & AutLib::GeoLib::Geom_Pnt3d::operator-=(const Standard_Real Scalar)
{
	coord.X() -= Scalar;
	coord.Y() -= Scalar;
	coord.Z() -= Scalar;

	return *this;
}

inline
M_GEO Geom_Pnt3d & AutLib::GeoLib::Geom_Pnt3d::operator*=(const Standard_Real Scalar)
{
	coord.X() *= Scalar;
	coord.Y() *= Scalar;
	coord.Z() *= Scalar;

	return *this;
}

inline
M_GEO Geom_Pnt3d & AutLib::GeoLib::Geom_Pnt3d::operator/=(const Standard_Real Scalar)
{
	coord.X() /= Scalar;
	coord.Y() /= Scalar;
	coord.Z() /= Scalar;

	return *this;
}

inline
M_GEO Geom_Pnt3d & AutLib::GeoLib::Geom_Pnt3d::operator+()
{
	return *this;
}

inline
M_GEO Geom_Pnt3d AutLib::GeoLib::Geom_Pnt3d::operator-()
{
	Geom_Pnt3d Zero;

	return Zero - *this;
}

inline
M_GEO Geom_Pnt3d AutLib::GeoLib::Geom_Pnt3d::UnitLength() const
{
	Standard_Real S = 1.0 / TwoNorm();
	return Geom_Pnt3d(X()*S, Y()*S, Z()*S);
}

inline
Standard_Real AutLib::GeoLib::Geom_Pnt3d::X() const
{
	return coord.X();
}

inline
Standard_Real AutLib::GeoLib::Geom_Pnt3d::Y() const
{
	return coord.Y();
}

inline
Standard_Real AutLib::GeoLib::Geom_Pnt3d::Z() const
{
	return coord.Z();
}

inline
Standard_Real & AutLib::GeoLib::Geom_Pnt3d::X()
{
	return coord.X();
}

inline
Standard_Real & AutLib::GeoLib::Geom_Pnt3d::Y()
{
	return coord.Y();
}

inline
Standard_Real & AutLib::GeoLib::Geom_Pnt3d::Z()
{
	return coord.Z();
}

inline
Standard_Real AutLib::GeoLib::Geom_Pnt3d::TwoNorm() const
{
	return sqrt(TwoNormSQ());
}

inline
Standard_Real AutLib::GeoLib::Geom_Pnt3d::TwoNormSQ() const
{
	return X()*X() + Y()*Y() + Z()*Z();
}

inline 
void AutLib::GeoLib::Geom_Pnt3d::Get
(
	Standard_Real & theX,
	Standard_Real & theY,
	Standard_Real & theZ
) const
{
	theX = coord.X();
	theY = coord.Y();
	theZ = coord.Z();
}

inline
void AutLib::GeoLib::Geom_Pnt3d::Print(Standard_OStream & Out) const
{
	Out << coord.X() << "  " << coord.Y() << "  " << coord.Z();
}

namespace AutLib
{
	namespace GeoLib
	{

		inline Geom_Pnt3d operator+(const Geom_Pnt3d & P1, const Geom_Pnt3d & P2)
		{
			Geom_Pnt3d Temp = P1;
			Temp += P2;

			MOVE(Temp);
		}

		inline Geom_Pnt3d operator-(const Geom_Pnt3d & P1, const Geom_Pnt3d & P2)
		{
			Geom_Pnt3d Temp = P1;
			Temp -= P2;

			MOVE(Temp);
		}

		inline Geom_Pnt3d operator+(const Geom_Pnt3d & P1, const Standard_Real Scalar)
		{
			Geom_Pnt3d Temp = P1;
			Temp += Scalar;

			MOVE(Temp);
		}

		inline Geom_Pnt3d operator+(const Standard_Real Scalar, const Geom_Pnt3d & P1)
		{
			Geom_Pnt3d Temp = P1;
			Temp += Scalar;

			MOVE(Temp);
		}

		inline Geom_Pnt3d operator-(const Geom_Pnt3d & P1, const Standard_Real Scalar)
		{
			Geom_Pnt3d Temp = P1;
			Temp -= Scalar;

			MOVE(Temp);
		}

		inline Geom_Pnt3d operator-(const Standard_Real Scalar, const Geom_Pnt3d & P1)
		{
			Geom_Pnt3d Temp(Scalar, Scalar, Scalar);
			Temp -= P1;

			MOVE(Temp);
		}

		inline Geom_Pnt3d operator*(const Geom_Pnt3d & P1, const Standard_Real Scalar)
		{
			Geom_Pnt3d Temp = P1;
			Temp *= Scalar;

			MOVE(Temp);
		}

		inline Geom_Pnt3d operator*(const Standard_Real Scalar, const Geom_Pnt3d & P1)
		{
			Geom_Pnt3d Temp = P1;
			Temp *= Scalar;

			MOVE(Temp);
		}

		inline Geom_Pnt3d operator/(const Geom_Pnt3d & P1, const Standard_Real Scalar)
		{
			Geom_Pnt3d Temp = P1;
			Temp /= Scalar;

			MOVE(Temp);
		}

		inline Standard_Real Distance(const Geom_Pnt3d & P1, const Geom_Pnt3d & P2)
		{
			return P1.Distance(P2);
		}

		inline Standard_Real DistanceSQ(const Geom_Pnt3d & P1, const Geom_Pnt3d & P2)
		{
			return P1.SquareDistance(P2);
		}

		inline Standard_Real DotProduct(const Geom_Pnt3d & P1, const Geom_Pnt3d & P2)
		{
			return P1.X()*P2.X() + P1.Y()*P2.Y() + P1.Z()*P2.Z();
		}

		inline Geom_Pnt3d AutLib::GeoLib::CrossProduct(const Geom_Pnt3d & v1, const Geom_Pnt3d & v2)
		{
			return Geom_Pnt3d(v1.Y()*v2.Z() - v2.Y()*v1.Z(), v1.Z()*v2.X() - v1.X()*v2.Z(), v1.X()*v2.Y() - v2.X()*v1.Y());
		}

		inline Standard_OStream & operator<<(Standard_OStream & Ostream, const Geom_Pnt3d & P)
		{
			Ostream << P.X() << "  " << P.Y() << "  " << P.Z();
			return Ostream;
		}

		inline Standard_IStream & operator>>(Standard_IStream & Ostream, Geom_Pnt3d & P)
		{
			Standard_Real X, Y, Z;

			Ostream >> X >> Y >> Z;

			P.SetCoord(X, Y, Z);

			return Ostream;
		}
	}
}