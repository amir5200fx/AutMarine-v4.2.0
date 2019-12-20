#pragma once
#ifndef _Tetrahedra_QualityMeasure_Header
#define _Tetrahedra_QualityMeasure_Header

#include <Tetrahedra_QualityMeasureParameters.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Tetrahedra_QualityMeasure
		{

		private:

			mutable Tetrahedra_QualityMeasureParameters theParameters_;

		public:

			Tetrahedra_QualityMeasure();

			Standard_Real CalcMinSineQuality(const Geom_Pnt3d& theP0, const Geom_Pnt3d& theP1, const Geom_Pnt3d& theP2, const Geom_Pnt3d& theP3) const;
		};
	}
}

#endif // !_Tetrahedra_QualityMeasure_Header
