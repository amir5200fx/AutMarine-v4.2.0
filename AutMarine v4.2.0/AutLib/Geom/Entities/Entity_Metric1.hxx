#pragma once
#ifndef _Entity_Metric1_Header
#define _Entity_Metric1_Header

#include <Standard_Real.hxx>
#include <Standard_OStream.hxx>
#include <Armadillo.hxx>
#include <TColStd_Ary2dOfReal.hxx>

namespace AutLib
{
	namespace GeoLib
	{
		class Geom_Pnt2d;

		class Entity_Metric1
		{

		private:

			Standard_Real theA_;
			Standard_Real theB_;
			Standard_Real theC_;

		public:

			Entity_Metric1();

			Entity_Metric1(const Standard_Real A, const Standard_Real B, const Standard_Real C);

			Entity_Metric1& operator*=(const Standard_Real Scalar);

			Entity_Metric1 Inversed() const;

			Standard_Real Determinant() const;

			mat22 GetArma() const;

			TColStd_Ary2dOfReal GetMatrix() const;

			Standard_Real A() const;

			Standard_Real B() const;

			Standard_Real C() const;

			Standard_Real& A();

			Standard_Real& B();

			Standard_Real& C();

			Standard_Boolean IsSingular(const Standard_Real Epsilon) const;

			Geom_Pnt2d Multiplied(const Geom_Pnt2d& theU) const;

			Entity_Metric1 SQRT() const;

			void Inverse();

			void RemoveDegeneracy(const Standard_Real Epsilon);

			void ExportToPlt(fstream& File) const;

			void ExportToPlt(const Geom_Pnt2d& Centre, fstream& File) const;

			void Print(Standard_OStream& Ostream = cout) const;

			friend Entity_Metric1 operator*(const Entity_Metric1& Metric, const Standard_Real Scalar);

			friend Entity_Metric1 operator*(const Standard_Real Scalar, const Entity_Metric1& Metric);

			friend Entity_Metric1 operator+(const Entity_Metric1& theMetric1, const Entity_Metric1& theMetric2);
		};
	}
}

#include <Entity_Metric1I.hxx>

#endif // !_Entity_Metric1_Header
