#pragma once
#ifndef _Mesh2d_LineIntegrand_Header
#define _Mesh2d_LineIntegrand_Header

#include <Geom_Pnt2d.hxx>
#include <Mesh2d_SizeMap.hxx>

namespace AutLib
{
	namespace MeshLib
	{
		
		class Mesh2d_LineIntegrand
		{

		private:

			const Mesh2d_SizeMap * theSize_;

			const Geom_Pnt2d& theStart_;
			const Geom_Pnt2d& theEnd_;

			Geom_Pnt2d theVector_;

		public:

			Mesh2d_LineIntegrand(const Geom_Pnt2d& Start_Point, const Geom_Pnt2d& End_Point, const Mesh2d_SizeMap * SizeMap);

			static Standard_Real Integrand(const Standard_Real Parameter, const Mesh2d_LineIntegrand& LineIntegrand);

		private:

			Geom_Pnt2d CalcPoint(const Standard_Real Parameter) const;

		};
	}
}

#include <Mesh2d_LineIntegrandI.hxx>

#endif // !_Mesh2d_LineIntegrand_Header
