#pragma once
#ifndef _Geom_Pnt3d_Header
#define _Geom_Pnt3d_Header

#include <gp_Pnt.hxx>
#include <Standard_IStream.hxx>
#include <Standard_OStream.hxx>
#include <Global_Macros.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Geom_Pnt3d : public gp_Pnt
		{

		public:

			Geom_Pnt3d();

			Geom_Pnt3d(const gp_Pnt& Other);

			Geom_Pnt3d(const Standard_Real Xp, const Standard_Real Yp, const Standard_Real Zp);

			Geom_Pnt3d& operator+=(const Geom_Pnt3d& Other);

			Geom_Pnt3d& operator-=(const Geom_Pnt3d& Other);

			Geom_Pnt3d& operator*=(const Geom_Pnt3d& Other);

			Geom_Pnt3d& operator=(const Standard_Real Scalar);

			Geom_Pnt3d& operator+=(const Standard_Real Scalar);

			Geom_Pnt3d& operator-=(const Standard_Real Scalar);

			Geom_Pnt3d& operator*=(const Standard_Real Scalar);

			Geom_Pnt3d& operator/=(const Standard_Real Scalar);

			Geom_Pnt3d& operator+();

			Geom_Pnt3d operator-();

			Geom_Pnt3d UnitLength() const;

			Standard_Real X() const;

			Standard_Real Y() const;

			Standard_Real Z() const;

			Standard_Real &X();

			Standard_Real &Y();

			Standard_Real &Z();

			Standard_Real TwoNorm() const;

			Standard_Real TwoNormSQ() const;

			void Get(Standard_Real& theX, Standard_Real& theY, Standard_Real& theZ) const;

			void Print(Standard_OStream& Out = cout) const;

			friend Geom_Pnt3d operator+(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2);

			friend Geom_Pnt3d operator-(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2);

			friend Geom_Pnt3d operator+(const Geom_Pnt3d& P1, const Standard_Real Scalar);

			friend Geom_Pnt3d operator+(const Standard_Real Scalar, const Geom_Pnt3d& P1);

			friend Geom_Pnt3d operator-(const Geom_Pnt3d& P1, const Standard_Real Scalar);

			friend Geom_Pnt3d operator-(const Standard_Real Scalar, const Geom_Pnt3d& P1);

			friend Geom_Pnt3d operator*(const Geom_Pnt3d& P1, const Standard_Real Scalar);

			friend Geom_Pnt3d operator*(const Standard_Real Scalar, const Geom_Pnt3d& P1);

			friend Geom_Pnt3d operator/(const Geom_Pnt3d& P1, const Standard_Real Scalar);

			friend Standard_Real Distance(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2);

			friend Standard_Real DistanceSQ(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2);

			friend Standard_Real DotProduct(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2);

			friend Geom_Pnt3d CrossProduct(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2);

			friend Standard_Boolean areParallel(const Geom_Pnt3d& P1, const Geom_Pnt3d& P2, const Standard_Real Tolerance);

			friend Standard_OStream& operator<<(Standard_OStream& Ostream, const Geom_Pnt3d& P);

			friend Standard_IStream& operator>>(Standard_IStream& Ostream, Geom_Pnt3d& P);
		};
	}
}

using AutLib::GeoLib::Geom_Pnt3d;

#include <Geom_Pnt3dI.hxx>

#endif // !_Geom_Pnt3d_Header
