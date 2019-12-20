#pragma once
#ifndef _Geom_wPnt2d_Header
#define _Geom_wPnt2d_Header

#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Geom_wPnt2d : public Geom_Pnt2d
		{

		private:

			Standard_Real w;

		public:

			Geom_wPnt2d();

			Geom_wPnt2d(const Standard_Real X, const Standard_Real Y, const Standard_Real W);

			Geom_wPnt2d(const Geom_Pnt2d& Other, const Standard_Real W);

			Geom_wPnt2d& operator=(const Standard_Real Scalar);

			Geom_wPnt2d& operator+=(const Standard_Real Scalar);

			Geom_wPnt2d& operator-=(const Standard_Real Scalar);

			Geom_wPnt2d& operator*=(const Standard_Real Scalar);

			Geom_wPnt2d& operator/=(const Standard_Real Scalar);

			Geom_wPnt2d& operator+=(const Geom_wPnt2d& Other);

			Geom_wPnt2d& operator-=(const Geom_wPnt2d& Other);

			Geom_Pnt2d TransToEuclidean() const;

			Standard_Real W() const;

			Standard_Real& W();

			void Print(Standard_OStream & Out = cout) const;

			friend Geom_wPnt2d operator+(const Geom_wPnt2d& P1, const Geom_wPnt2d& P2);

			friend Geom_wPnt2d operator-(const Geom_wPnt2d& P1, const Geom_wPnt2d& P2);

			friend Geom_wPnt2d operator*(const Geom_wPnt2d& P1, const Standard_Real Scalar);

			friend Geom_wPnt2d operator*(const Standard_Real Scalar, const Geom_wPnt2d& P1);

			friend Standard_OStream& operator<<(Standard_OStream& OS, const Geom_wPnt2d& P);
		};


	}
}

using AutLib::GeoLib::Geom_wPnt2d;

#include <Geom_wPnt2dI.hxx>

#endif // !_Geom_wPnt2d_Header
