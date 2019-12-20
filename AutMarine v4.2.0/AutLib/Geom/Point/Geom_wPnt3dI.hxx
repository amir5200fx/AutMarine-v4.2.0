#pragma once
inline
AutLib::GeoLib::Geom_wPnt3d::Geom_wPnt3d()
	: Geom_Pnt3d()
	, w(0)
{
}

inline
AutLib::GeoLib::Geom_wPnt3d::Geom_wPnt3d
(
	const Standard_Real X,
	const Standard_Real Y,
	const Standard_Real Z,
	const Standard_Real W
)
	: Geom_Pnt3d(X, Y, Z)
	, w(W)
{
}

inline
AutLib::GeoLib::Geom_wPnt3d::Geom_wPnt3d
(
	const Geom_Pnt3d & Other,
	const Standard_Real W
)
	: Geom_Pnt3d(Other.X(), Other.Y(), Other.Z())
	, w(W)
{
}

inline
Geom_wPnt3d & AutLib::GeoLib::Geom_wPnt3d::operator=(const Standard_Real Scalar)
{
	Geom_Pnt3d::X() = Scalar;
	Geom_Pnt3d::Y() = Scalar;
	Geom_Pnt3d::Z() = Scalar;
	w = Scalar;

	return *this;
}

inline
Geom_wPnt3d & AutLib::GeoLib::Geom_wPnt3d::operator+=(const Standard_Real Scalar)
{
	Geom_Pnt3d::X() += Scalar;
	Geom_Pnt3d::Y() += Scalar;
	Geom_Pnt3d::Z() += Scalar;
	w += Scalar;

	return *this;
}

inline
Geom_wPnt3d & AutLib::GeoLib::Geom_wPnt3d::operator-=(const Standard_Real Scalar)
{
	Geom_Pnt3d::X() -= Scalar;
	Geom_Pnt3d::Y() -= Scalar;
	Geom_Pnt3d::Z() -= Scalar;
	w -= Scalar;

	return *this;
}

inline
Geom_wPnt3d & AutLib::GeoLib::Geom_wPnt3d::operator*=(const Standard_Real Scalar)
{
	Geom_Pnt3d::X() *= Scalar;
	Geom_Pnt3d::Y() *= Scalar;
	Geom_Pnt3d::Z() *= Scalar;
	w *= Scalar;

	return *this;
}

inline
Geom_wPnt3d & AutLib::GeoLib::Geom_wPnt3d::operator/=(const Standard_Real Scalar)
{
	Geom_Pnt3d::X() /= Scalar;
	Geom_Pnt3d::Y() /= Scalar;
	Geom_Pnt3d::Z() /= Scalar;
	w /= Scalar;

	return *this;
}

inline
Geom_wPnt3d & AutLib::GeoLib::Geom_wPnt3d::operator+=(const Geom_wPnt3d & Other)
{
	Geom_Pnt3d::X() += Other.X();
	Geom_Pnt3d::Y() += Other.Y();
	Geom_Pnt3d::Z() += Other.Z();
	w += Other.W();

	return *this;
}

inline
Geom_wPnt3d & AutLib::GeoLib::Geom_wPnt3d::operator-=(const Geom_wPnt3d & Other)
{
	Geom_Pnt3d::X() -= Other.X();
	Geom_Pnt3d::Y() -= Other.Y();
	Geom_Pnt3d::Z() -= Other.Z();
	w -= Other.W();

	return *this;
}

inline
Geom_Pnt3d AutLib::GeoLib::Geom_wPnt3d::TransToEuclidean() const
{
	return Geom_Pnt3d(Geom_Pnt3d::X() / w, Geom_Pnt3d::Y() / w, Geom_Pnt3d::Z() / w);
}

inline
Standard_Real AutLib::GeoLib::Geom_wPnt3d::W() const
{
	return w;
}

inline
Standard_Real & AutLib::GeoLib::Geom_wPnt3d::W()
{
	return w;
}

inline
void AutLib::GeoLib::Geom_wPnt3d::Print(Standard_OStream & Out) const
{
	Geom_Pnt3d::Print(Out);

	Out << "  " << w;
}

namespace AutLib
{
	namespace GeoLib
	{

		inline Geom_wPnt3d operator+(const Geom_wPnt3d & P1, const Geom_wPnt3d & P2)
		{
			Geom_wPnt3d Temp = P1;
			Temp += P2;
			MOVE(Temp);
		}

		inline Geom_wPnt3d operator-(const Geom_wPnt3d & P1, const Geom_wPnt3d & P2)
		{
			Geom_wPnt3d Temp = P1;
			Temp -= P2;
			MOVE(Temp);
		}

		inline Geom_wPnt3d operator*(const Geom_wPnt3d & P1, const Standard_Real Scalar)
		{
			Geom_wPnt3d Temp = P1;
			Temp *= Scalar;
			MOVE(Temp);
		}

		inline Geom_wPnt3d operator*(const Standard_Real Scalar, const Geom_wPnt3d & P1)
		{
			Geom_wPnt3d Temp = P1;
			Temp *= Scalar;
			MOVE(Temp);
		}

		inline Standard_OStream & operator<<(Standard_OStream & OS, const Geom_wPnt3d & P)
		{
			OS << P.X() << "  " << P.Y() << "  " << P.Z() << "  " << P.W();

			return OS;
		}
	}
}