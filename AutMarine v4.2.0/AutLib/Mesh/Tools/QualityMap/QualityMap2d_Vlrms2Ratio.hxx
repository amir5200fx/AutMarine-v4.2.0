#pragma once
#ifndef _QualityMap2d_Vlrms2Ratio_Header
#define _QualityMap2d_Vlrms2Ratio_Header

#include <Mesh2d_QualityMap.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class QualityMap2d_Vlrms2Ratio : public Mesh2d_QualityMap
		{

		private:


		public:

			QualityMap2d_Vlrms2Ratio();

			virtual Standard_Real CalcQuality(const Geom_Pnt2d& theP0, const Geom_Pnt2d& theP1, const Geom_Pnt2d& theP2) const;
		};
	}
}

#endif // !_QualityMap2d_Vlrms2Ratio_Header
