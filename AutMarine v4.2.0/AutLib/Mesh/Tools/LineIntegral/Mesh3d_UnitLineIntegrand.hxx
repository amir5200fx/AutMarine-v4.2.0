#pragma once
#ifndef _Mesh3d_UnitLineIntegrand_Header
#define _Mesh3d_UnitLineIntegrand_Header

#include <Geom_Pnt3d.hxx>
#include <Mesh3d_SizeMap.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_UnitLineIntegrand
		{

		private:

			const Mesh3d_SizeMap * theSize_;

			const Geom_Pnt3d& theStart_;
			const Geom_Pnt3d& theEnd_;

		public:

			Mesh3d_UnitLineIntegrand(const Geom_Pnt3d& Start_Point, const Geom_Pnt3d& End_Point, const Mesh3d_SizeMap * SizeMap);

			static Standard_Real Integrand(const Standard_Real Parameter, const Mesh3d_UnitLineIntegrand& LineIntegrand);

		private:

			Geom_Pnt3d CalcPoint(const Standard_Real Parameter) const;

			Geom_Pnt3d theVector_;
		};
	}
}

#include <Mesh3d_UnitLineIntegrandI.hxx>

#endif // !_Mesh3d_UnitLineIntegrand_Header
