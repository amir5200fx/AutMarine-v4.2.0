#pragma once
#ifndef _Mesh3d_QualityMapIsotropicMinSine_Header
#define _Mesh3d_QualityMapIsotropicMinSine_Header

#include <Mesh3d_QualityMap.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_QualityMapIsotropicMinSine : public Mesh3d_QualityMap
		{

		private:

		public:

			Mesh3d_QualityMapIsotropicMinSine();

			Standard_Real CalcQuality(const Geom_Pnt3d& theP0, const Geom_Pnt3d& theP1, const Geom_Pnt3d& theP2, const Geom_Pnt3d& theP3) const;

			//Standard_Real CalcVolume(const Geom_Pnt3d& theP0, const Geom_Pnt3d& theP1, const Geom_Pnt3d& theP2, const Geom_Pnt3d& theP3) const;

		};
	}
}

#endif // !_Mesh3d_QualityMapIsotropicMinSine_Header
