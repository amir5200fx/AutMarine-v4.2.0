#pragma once
#ifndef _Entity_Metric2_Header
#define _Entity_Metric2_Header

#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_Metric2
		{

		private:

			Geom_Pnt2d theE1_;
			Geom_Pnt2d theE2_;

			Standard_Real theH1_;
			Standard_Real theH2_;

		public:

			Entity_Metric2();

			Entity_Metric2(const Standard_Real H1, const Standard_Real H2, const Geom_Pnt2d& E1, const Geom_Pnt2d& E2);

			Standard_Real H1() const;

			Standard_Real H2() const;

			Standard_Real& H1();

			Standard_Real& H2();

			const Geom_Pnt2d& E1() const;

			const Geom_Pnt2d& E2() const;

			Geom_Pnt2d& E1();

			Geom_Pnt2d& E2();

			Standard_Boolean IsDegenerate(const Standard_Real Tolerance) const;

			void SetH1(const Standard_Real Value);

			void SetH2(const Standard_Real Value);

			void SetE1(const Geom_Pnt2d& E1);

			void SetE2(const Geom_Pnt2d& E2);

			void Normalize();
		};
	}
}

#include <Entity_Metric2I.hxx>

#endif // !_Entity_Metric2_Header
