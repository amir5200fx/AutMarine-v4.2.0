#pragma once
inline
AutLib::GeoLib::Geom_wPnt2d::Geom_wPnt2d()
	: Geom_Pnt2d()
	, w(0)
{
}

inline
AutLib::GeoLib::Geom_wPnt2d::Geom_wPnt2d
(
	const Standard_Real X,
	const Standard_Real Y,
	const Standard_Real W
)
	: Geom_Pnt2d(X * W, Y * W)
	, w(W)
{
}

inline
AutLib::GeoLib::Geom_wPnt2d::Geom_wPnt2d
(
	const Geom_Pnt2d & Other,
	const Standard_Real W
)
	: Geom_Pnt2d(Other.X() * W, Other.Y() * W)
	, w(W)
{
}

inline
Geom_wPnt2d & AutLib::GeoLib::Geom_wPnt2d::operator=(const Standard_Real Scalar)
{
	Geom_Pnt2d::X() = Scalar;
	Geom_Pnt2d::Y() = Scalar;
	w = Scalar;

	return *this;
}

inline
Geom_wPnt2d & AutLib::GeoLib::Geom_wPnt2d::operator+=(const Standard_Real Scalar)
{
	Geom_Pnt2d::X() += Scalar;
	Geom_Pnt2d::Y() += Scalar;
	w += Scalar;

	return *this;
}

inline
Geom_wPnt2d & AutLib::GeoLib::Geom_wPnt2d::operator-=(const Standard_Real Scalar)
{
	Geom_Pnt2d::X() -= Scalar;
	Geom_Pnt2d::Y() -= Scalar;
	w -= Scalar;

	return *this;
}

inline
Geom_wPnt2d & AutLib::GeoLib::Geom_wPnt2d::operator*=(const Standard_Real Scalar)
{
	Geom_Pnt2d::X() *= Scalar;
	Geom_Pnt2d::Y() *= Scalar;
	w *= Scalar;

	return *this;
}

inline
Geom_wPnt2d & AutLib::GeoLib::Geom_wPnt2d::operator/=(const Standard_Real Scalar)
{
	Geom_Pnt2d::X() /= Scalar;
	Geom_Pnt2d::Y() /= Scalar;
	w /= Scalar;

	return *this;
}

inline
Geom_wPnt2d & AutLib::GeoLib::Geom_wPnt2d::operator+=(const Geom_wPnt2d & Other)
{
	Geom_Pnt2d::X() += Other.X();
	Geom_Pnt2d::Y() += Other.Y();
	w += Other.W();

	return *this;
}

inline
Geom_wPnt2d & AutLib::GeoLib::Geom_wPnt2d::operator-=(const Geom_wPnt2d & Other)
{
	Geom_Pnt2d::X() -= Other.X();
	Geom_Pnt2d::Y() -= Other.Y();
	w -= Other.W();

	return *this;
}

inline
Geom_Pnt2d AutLib::GeoLib::Geom_wPnt2d::TransToEuclidean() const
{
	return Geom_Pnt2d(Geom_Pnt2d::X() / w, Geom_Pnt2d::Y() / w);
}

inline
Standard_Real AutLib::GeoLib::Geom_wPnt2d::W() const
{
	return w;
}

inline
Standard_Real & AutLib::GeoLib::Geom_wPnt2d::W()
{
	return w;
}

inline
void AutLib::GeoLib::Geom_wPnt2d::Print(Standard_OStream & Out) const
{
	Geom_Pnt2d::Print(Out);

	Out << "  " << w;
}

namespace AutLib
{
	namespace GeoLib
	{

		inline Geom_wPnt2d operator+(const Geom_wPnt2d & P1, const Geom_wPnt2d & P2)
		{
			Geom_wPnt2d Temp = P1;
			Temp += P2;
			MOVE(Temp);
		}

		inline Geom_wPnt2d operator-(const Geom_wPnt2d & P1, const Geom_wPnt2d & P2)
		{
			Geom_wPnt2d Temp = P1;
			Temp -= P2;
			MOVE(Temp);
		}

		inline Geom_wPnt2d operator*(const Geom_wPnt2d & P1, const Standard_Real Scalar)
		{
			Geom_wPnt2d Temp = P1;
			Temp *= Scalar;
			MOVE(Temp);
		}

		inline Geom_wPnt2d operator*(const Standard_Real Scalar, const Geom_wPnt2d & P1)
		{
			Geom_wPnt2d Temp = P1;
			Temp *= Scalar;
			MOVE(Temp);
		}

		inline Standard_OStream & operator<<(Standard_OStream & OS, const Geom_wPnt2d & P)
		{
			OS << P.X() << "  " << P.Y() << "  " << P.W();

			return OS;
		}
	}
}