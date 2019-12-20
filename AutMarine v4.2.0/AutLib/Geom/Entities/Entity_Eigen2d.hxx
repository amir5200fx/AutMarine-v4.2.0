#pragma once
#ifndef _Entity_Eigen2d_Header
#define _Entity_Eigen2d_Header

#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Metric1;

		class Entity_Eigen2d
		{

		private:

			Geom_Pnt2d theE1_;
			Geom_Pnt2d theE2_;

			Standard_Real theH1_;
			Standard_Real theH2_;

			Standard_Real theLamda1_;
			Standard_Real theLamda2_;

			Standard_Boolean IsDone_;

		public:

			Entity_Eigen2d();

			const Geom_Pnt2d& E1() const;

			const Geom_Pnt2d& E2() const;

			Standard_Real H1() const;

			Standard_Real H2() const;

			Standard_Real Lamda1() const;

			Standard_Real Lamda2() const;

			void CalcEigen(const Entity_Metric1& M);

			void CalcGenEigen(const Entity_Metric1& A, const Entity_Metric1& B);

			void ExportToPlt(fstream& File) const;

			void ExportToPlt(const Geom_Pnt2d& Centre, fstream& File) const;

			void Print(Standard_OStream& Ostream) const;
		};
	}
}

#include <Entity_Eigen2dI.hxx>

#endif // !_Entity_Eigen2d_Header
