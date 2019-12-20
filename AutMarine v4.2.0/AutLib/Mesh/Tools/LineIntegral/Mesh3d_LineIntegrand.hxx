#pragma once
#ifndef _Mesh3d_LineIntegrand_Header
#define _Mesh3d_LineIntegrand_Header

#include <Geom_Pnt3d.hxx>
#include <Mesh3d_SizeMap.hxx>

namespace AutLib
{
	namespace MeshLib
	{

		class Mesh3d_LineIntegrand
		{

		private:

			const Mesh3d_SizeMap * theSize_;

			const Geom_Pnt3d& theStart_;
			const Geom_Pnt3d& theEnd_;

			Geom_Pnt3d theVector_;

		public:

			Mesh3d_LineIntegrand(const Geom_Pnt3d& Start_Point, const Geom_Pnt3d& End_Point, const Mesh3d_SizeMap * SizeMap);

			static Standard_Real Integrand(const Standard_Real Parameter, const Mesh3d_LineIntegrand& LineIntegrand);

		private:

			Geom_Pnt3d CalcPoint(const Standard_Real Parameter) const;
		};
	}
}

#include <Mesh3d_LineIntegrandI.hxx>

#endif // !_Mesh3d_LineIntegrand_Header
