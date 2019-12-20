#pragma once
#ifndef _Geom_Point2d_Header
#define _Geom_Point2d_Header

#include <gp_Pnt2d.hxx>
#include <Standard_OStream.hxx>
#include <Standard_IStream.hxx>
#include <Global_Macros.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Geom_Pnt2d : public gp_Pnt2d
		{

		public:

			Geom_Pnt2d();

			Geom_Pnt2d(const Standard_Real Xp, const Standard_Real Yp);

			Geom_Pnt2d(const gp_Pnt2d& Other);

			Geom_Pnt2d(const gp_XY& XY);

			//Geom_Pnt2d& operator=(const gp_Pnt2d& Other);

			Geom_Pnt2d& operator+=(const Geom_Pnt2d& Other);

			Geom_Pnt2d& operator-=(const Geom_Pnt2d& Other);

			Geom_Pnt2d& operator*=(const Geom_Pnt2d& Other);

			Geom_Pnt2d& operator=(const Standard_Real Scalar);

			Geom_Pnt2d& operator+=(const Standard_Real Scalar);

			Geom_Pnt2d& operator-=(const Standard_Real Scalar);

			Geom_Pnt2d& operator*=(const Standard_Real Scalar);

			Geom_Pnt2d& operator/=(const Standard_Real Scalar);

			Geom_Pnt2d& operator+();

			Geom_Pnt2d operator-();

			void Rotate90ccw();

			Standard_Real X() const;

			Standard_Real Y() const;

			Standard_Real &X();

			Standard_Real &Y();

			Geom_Pnt2d UnitLength() const;

			Standard_Real TwoNorm() const;

			Standard_Real TwoNormSQ() const;

			void Get(Standard_Real& theX, Standard_Real& theY) const;

			void Print(Standard_OStream& Out = cout) const;

			friend Geom_Pnt2d operator+(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2);

			friend Geom_Pnt2d operator-(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2);

			friend Geom_Pnt2d operator+(const Geom_Pnt2d& P1, const Standard_Real Scalar);

			friend Geom_Pnt2d operator+(const Standard_Real Scalar, const Geom_Pnt2d& P1);

			friend Geom_Pnt2d operator-(const Geom_Pnt2d& P1, const Standard_Real Scalar);

			friend Geom_Pnt2d operator-(const Standard_Real Scalar, const Geom_Pnt2d& P1);

			friend Geom_Pnt2d operator*(const Geom_Pnt2d& P1, const Standard_Real Scalar);

			friend Geom_Pnt2d operator*(const Standard_Real Scalar, const Geom_Pnt2d& P1);

			friend Geom_Pnt2d operator/(const Geom_Pnt2d& P1, const Standard_Real Scalar);

			friend Standard_Real Distance(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2);

			friend Standard_Real DistanceSQ(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2);

			friend Standard_Real DotProduct(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2);

			friend Standard_Real CrossProduct(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2);

			friend Standard_Boolean areParallel(const Geom_Pnt2d& P1, const Geom_Pnt2d& P2, const Standard_Real Tolerance);

			friend Standard_OStream& operator<<(Standard_OStream& Ostream, const Geom_Pnt2d& P);

			friend Standard_IStream& operator>>(Standard_IStream& Ostream, Geom_Pnt2d& P);
		};
	}
}

using AutLib::GeoLib::Geom_Pnt2d;

#include <Geom_Pnt2dI.hxx>

#endif // !_Geom_Point2d_Header
