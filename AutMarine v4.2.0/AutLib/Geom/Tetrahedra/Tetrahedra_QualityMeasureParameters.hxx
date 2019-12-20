#pragma once
#ifndef _Tetrahedra_QualityMeasureParameters_Header
#define _Tetrahedra_QualityMeasureParameters_Header

#include <Geom_Pnt3d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Tetrahedra_QualityMeasureParameters
		{

		private:

			Geom_Pnt3d t_;
			Geom_Pnt3d u_;
			Geom_Pnt3d v_;

			Geom_Pnt3d Na_;
			Geom_Pnt3d Nb_;
			Geom_Pnt3d Nc_;
			Geom_Pnt3d Nd_;

			Standard_Real Aa_;
			Standard_Real Ab_;
			Standard_Real Ac_;
			Standard_Real Ad_;

			Standard_Real V_;
			Standard_Real Z_;

			Standard_Real lad_;
			Standard_Real lbd_;
			Standard_Real lcd_;
			Standard_Real lab_;
			Standard_Real lbc_;
			Standard_Real lac_;

			Standard_Real lrms_;

		public:

			Tetrahedra_QualityMeasureParameters();

			Tetrahedra_QualityMeasureParameters(const Geom_Pnt3d& theP0, const Geom_Pnt3d& theP1, const Geom_Pnt3d& theP2, const Geom_Pnt3d& theP3);

			//! Calculate the volume*6 of the tetrahedron
			Standard_Real Volume() const;

			Standard_Real squareL03() const;

			Standard_Real squareL13() const;

			Standard_Real squareL23() const;

			Standard_Real squareL01() const;

			Standard_Real squareL12() const;

			Standard_Real squareL02() const;

			Standard_Real Lrms() const;

			//! Compute (2 *area)^2 for this face
			Standard_Real squareArea0() const;

			//! Compute (2 *area)^2 for this face
			Standard_Real squareArea1() const;

			//! Compute (2 *area)^2 for this face
			Standard_Real squareArea2() const;

			//! Compute (2 *area)^2 for this face
			Standard_Real squareArea3() const;

			const Geom_Pnt3d& t() const;

			const Geom_Pnt3d& u() const;

			const Geom_Pnt3d& v() const;

			const Geom_Pnt3d& N0() const;

			const Geom_Pnt3d& N1() const;

			const Geom_Pnt3d& N2() const;

			const Geom_Pnt3d& N3() const;

			void Init(const Geom_Pnt3d& theP0, const Geom_Pnt3d& theP1, const Geom_Pnt3d& theP2, const Geom_Pnt3d& theP3);

		private:

			void Perform(const Geom_Pnt3d& a, const Geom_Pnt3d& b, const Geom_Pnt3d& c, const Geom_Pnt3d& d);
		};
	}
}

#include <Tetrahedra_QualityMeasureParametersI.hxx>

#endif // !_Tetrahedra_QualityMeasureParameters_Header
