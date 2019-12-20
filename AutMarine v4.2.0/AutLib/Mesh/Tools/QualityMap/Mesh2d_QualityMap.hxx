#pragma once
#ifndef _Mesh2d_QualityMap_Header
#define _Mesh2d_QualityMap_Header

#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh2d_QualityMap
		{

		public:

			virtual Standard_Real CalcQuality(const Geom_Pnt2d& theP0, const Geom_Pnt2d& theP1, const Geom_Pnt2d& theP2) const = 0;
		};
	}
}

#endif // !_Mesh2d_QualityMap_Header
