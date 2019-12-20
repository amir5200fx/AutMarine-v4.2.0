#pragma once
#ifndef _Mesh2d_UnitLineIntegral_Header
#define _Mesh2d_UnitLineIntegral_Header

#include <Geom_Pnt2d.hxx>
#include <Mesh2d_SizeMap.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		
		class Mesh2d_UnitLineIntegrand
		{

		private:

			const Mesh2d_SizeMap * theSize_;

			const Geom_Pnt2d& theStart_;
			const Geom_Pnt2d& theEnd_;

		public:

			Mesh2d_UnitLineIntegrand(const Geom_Pnt2d& Start_Point, const Geom_Pnt2d& End_Point, const Mesh2d_SizeMap * SizeMap);

			static Standard_Real Integrand(const Standard_Real Parameter, const Mesh2d_UnitLineIntegrand& LineIntegrand);

		private:

			Geom_Pnt2d CalcPoint(const Standard_Real Parameter) const;

			Geom_Pnt2d theVector_;
		};
	}
}

#include <Mesh2d_UnitLineIntegrandI.hxx>

#endif // !_Mesh2d_UnitLineIntegral_Header
