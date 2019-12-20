#pragma once
inline
AutLib::GeoLib::Geom_Pnt2d::Geom_Pnt2d()
	: gp_Pnt2d()
{
}

inline
AutLib::GeoLib::Geom_Pnt2d::Geom_Pnt2d(const Standard_Real Xp, const Standard_Real Yp)
	: gp_Pnt2d(Xp, Yp)
{
}

inline 
AutLib::GeoLib::Geom_Pnt2d::Geom_Pnt2d(const gp_Pnt2d & Other)
	: gp_Pnt2d(Other)
{
}

inline 
AutLib::GeoLib::Geom_Pnt2d::Geom_Pnt2d(const gp_XY & XY)
	: gp_Pnt2d(XY)
{
}

//inline 
//Geom_Pnt2d & AutLib::GeoLib::Geom_Pnt2d::operator=(const gp_Pnt2d & Other)
//{
//	coord = Other.coord;
//	return *this;
//}

inline
AutLib::GeoLib::Geom_Pnt2d & AutLib::GeoLib::Geom_Pnt2d::operator+=(const Geom_Pnt2d & Other)
{
	coord.X() += Other.coord.X();
	coord.Y() += Other.coord.Y();

	return *this;
}

inline
AutLib::GeoLib::Geom_Pnt2d & AutLib::GeoLib::Geom_Pnt2d::operator-=(const Geom_Pnt2d & Other)
{
	coord.X() -= Other.coord.X();
	coord.Y() -= Other.coord.Y();

	return *this;
}

inline
AutLib::GeoLib::Geom_Pnt2d & AutLib::GeoLib::Geom_Pnt2d::operator*=(const Geom_Pnt2d & Other)
{
	coord.X() *= Other.coord.X();
	coord.Y() *= Other.coord.Y();

	return *this;
}

inline
AutLib::GeoLib::Geom_Pnt2d & AutLib::GeoLib::Geom_Pnt2d::operator=(const Standard_Real Scalar)
{
	coord.X() = Scalar;
	coord.Y() = Scalar;

	return *this;
}

inline
AutLib::GeoLib::Geom_Pnt2d & AutLib::GeoLib::Geom_Pnt2d::operator+=(const Standard_Real Scalar)
{
	coord.X() += Scalar;
	coord.Y() += Scalar;

	return *this;
}

inline
AutLib::GeoLib::Geom_Pnt2d & AutLib::GeoLib::Geom_Pnt2d::operator-=(const Standard_Real Scalar)
{
	coord.X() -= Scalar;
	coord.Y() -= Scalar;

	return *this;
}

inline
AutLib::GeoLib::Geom_Pnt2d & AutLib::GeoLib::Geom_Pnt2d::operator*=(const Standard_Real Scalar)
{
	coord.X() *= Scalar;
	coord.Y() *= Scalar;

	return *this;
}

inline
AutLib::GeoLib::Geom_Pnt2d & AutLib::GeoLib::Geom_Pnt2d::operator/=(const Standard_Real Scalar)
{
	coord.X() /= Scalar;
	coord.Y() /= Scalar;

	return *this;
}

inline
AutLib::GeoLib::Geom_Pnt2d & AutLib::GeoLib::Geom_Pnt2d::operator+()
{
	return *this;
}

inline
AutLib::GeoLib::Geom_Pnt2d AutLib::GeoLib::Geom_Pnt2d::operator-()
{
	Geom_Pnt2d Zero;

	return Zero - (*this);
}

inline
void AutLib::GeoLib::Geom_Pnt2d::Rotate90ccw()
{
	Standard_Real Temp = X();
	X() = -Y();
	Y() = Temp;
}

inline
Standard_Real AutLib::GeoLib::Geom_Pnt2d::X() const
{
	return coord.X();
}

inline
Standard_Real AutLib::GeoLib::Geom_Pnt2d::Y() const
{
	return coord.Y();
}

inline
Standard_Real & AutLib::GeoLib::Geom_Pnt2d::X()
{
	return coord.X();
}

inline
Standard_Real & AutLib::GeoLib::Geom_Pnt2d::Y()
{
	return coord.Y();
}

inline
Geom_Pnt2d AutLib::GeoLib::Geom_Pnt2d::UnitLength() const
{
	Standard_Real S = 1.0 / TwoNorm();

	return Geom_Pnt2d(X()*S, Y()*S);
}

inline
Standard_Real AutLib::GeoLib::Geom_Pnt2d::TwoNorm() const
{
	return sqrt(X()*X() + Y()*Y());
}

inline
Standard_Real AutLib::GeoLib::Geom_Pnt2d::TwoNormSQ() const
{
	return X()*X() + Y()*Y();
}

inline 
void AutLib::GeoLib::Geom_Pnt2d::Get
(
	Standard_Real & theX,
	Standard_Real & theY
) const
{
	theX = coord.X();
	theY = coord.Y();
}

inline
void AutLib::GeoLib::Geom_Pnt2d::Print(Standard_OStream & Out) const
{
	Out << coord.X() << "  " << coord.Y();
}

namespace AutLib
{
	namespace GeoLib
	{
		inline Geom_Pnt2d operator+(const Geom_Pnt2d & P1, const Geom_Pnt2d & P2)
		{
			Geom_Pnt2d Temp = P1;
			Temp += P2;

			MOVE(Temp);
		}

		inline Geom_Pnt2d operator-(const Geom_Pnt2d & P1, const Geom_Pnt2d & P2)
		{
			Geom_Pnt2d Temp = P1;
			Temp -= P2;

			MOVE(Temp);
		}

		inline Geom_Pnt2d operator+(const Geom_Pnt2d & P1, const Standard_Real Scalar)
		{
			Geom_Pnt2d Temp = P1;
			Temp += Scalar;

			MOVE(Temp);
		}

		inline Geom_Pnt2d operator+(const Standard_Real Scalar, const Geom_Pnt2d & P1)
		{
			Geom_Pnt2d Temp = P1;
			Temp += Scalar;

			MOVE(Temp);
		}

		inline Geom_Pnt2d operator-(const Geom_Pnt2d & P1, const Standard_Real Scalar)
		{
			Geom_Pnt2d Temp = P1;
			Temp -= Scalar;

			MOVE(Temp);
		}

		inline Geom_Pnt2d operator-(const Standard_Real Scalar, const Geom_Pnt2d & P1)
		{
			Geom_Pnt2d Temp(Scalar, Scalar);
			Temp -= P1;

			MOVE(Temp);
		}

		inline Geom_Pnt2d operator*(const Geom_Pnt2d & P1, const Standard_Real Scalar)
		{
			Geom_Pnt2d Temp = P1;
			Temp *= Scalar;

			MOVE(Temp);
		}

		inline Geom_Pnt2d operator*(const Standard_Real Scalar, const Geom_Pnt2d & P1)
		{
			Geom_Pnt2d Temp = P1;
			Temp *= Scalar;

			MOVE(Temp);
		}

		inline Geom_Pnt2d operator/(const Geom_Pnt2d & P1, const Standard_Real Scalar)
		{
			Geom_Pnt2d Temp = P1;
			Temp /= Scalar;

			MOVE(Temp);
		}

		inline Standard_Real Distance(const Geom_Pnt2d & P1, const Geom_Pnt2d & P2)
		{
			return P1.Distance(P2);
		}

		inline Standard_Real DistanceSQ(const Geom_Pnt2d & P1, const Geom_Pnt2d & P2)
		{
			return P1.SquareDistance(P2);
		}

		inline Standard_Real DotProduct(const Geom_Pnt2d & P1, const Geom_Pnt2d & P2)
		{
			return P1.X()*P2.X() + P1.Y()*P2.Y();
		}

		inline Standard_Real CrossProduct(const Geom_Pnt2d & P1, const Geom_Pnt2d & P2)
		{
			return P1.X()*P2.Y() - P2.X()*P1.Y();
		}

		inline Standard_Boolean areParallel(const Geom_Pnt2d & P1, const Geom_Pnt2d & P2, const Standard_Real Tolerance)
		{
			return ABS(CrossProduct(P1, P2)) <= Tolerance;
		}

		inline Standard_OStream & operator<<(Standard_OStream & Ostream, const Geom_Pnt2d & P)
		{
			Ostream << P.X() << "  " << P.Y();
			return Ostream;
		}

		inline Standard_IStream & operator>>(Standard_IStream & Ostream, Geom_Pnt2d & P)
		{
			Standard_Real X, Y;

			Ostream >> X >> Y;

			P.SetCoord(X, Y);

			return Ostream;
		}
	}
}