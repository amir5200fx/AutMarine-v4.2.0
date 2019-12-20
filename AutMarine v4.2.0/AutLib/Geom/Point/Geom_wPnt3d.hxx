#pragma once
#ifndef _Geom_wPnt3d_Header
#define _Geom_wPnt3d_Header

#include <Geom_Pnt3d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Geom_wPnt3d : public Geom_Pnt3d
		{

		private:

			Standard_Real w;

		public:

			Geom_wPnt3d();

			Geom_wPnt3d(const Standard_Real X, const Standard_Real Y, const Standard_Real Z, const Standard_Real W);

			Geom_wPnt3d(const Geom_Pnt3d& Other, const Standard_Real W);

			Geom_wPnt3d& operator=(const Standard_Real Scalar);

			Geom_wPnt3d& operator+=(const Standard_Real Scalar);

			Geom_wPnt3d& operator-=(const Standard_Real Scalar);

			Geom_wPnt3d& operator*=(const Standard_Real Scalar);

			Geom_wPnt3d& operator/=(const Standard_Real Scalar);

			Geom_wPnt3d& operator+=(const Geom_wPnt3d& Other);

			Geom_wPnt3d& operator-=(const Geom_wPnt3d& Other);

			Geom_Pnt3d TransToEuclidean() const;

			Standard_Real W() const;

			Standard_Real& W();

			void Print(Standard_OStream & Out = cout) const;

			friend Geom_wPnt3d operator+(const Geom_wPnt3d& P1, const Geom_wPnt3d& P2);

			friend Geom_wPnt3d operator-(const Geom_wPnt3d& P1, const Geom_wPnt3d& P2);

			friend Geom_wPnt3d operator*(const Geom_wPnt3d& P1, const Standard_Real Scalar);

			friend Geom_wPnt3d operator*(const Standard_Real Scalar, const Geom_wPnt3d& P1);

			friend Standard_OStream& operator<<(Standard_OStream& OS, const Geom_wPnt3d& P);
		};
	}
}

using AutLib::GeoLib::Geom_wPnt3d;

#include <Geom_wPnt3dI.hxx>

#endif // !_Geom_wPnt3d_Header
