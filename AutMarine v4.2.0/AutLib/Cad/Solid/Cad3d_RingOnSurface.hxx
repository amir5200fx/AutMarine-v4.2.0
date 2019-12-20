#pragma once
#ifndef _Cad3d_RingOnSurface_Header
#define _Cad3d_RingOnSurface_Header

#include <Cad3d_CurveOnSurface.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_RingOnSurface : public Cad3d_CurveOnSurface
		{

		private:

			Geom_Pnt3d theCentre_;

		public:

			Cad3d_RingOnSurface();

			Cad3d_RingOnSurface(const Standard_Real First, const Standard_Real Last, const Handle(Geom_Curve)& Curve);

			virtual ~Cad3d_RingOnSurface();

			const Geom_Pnt3d& Centre() const;

			Standard_Boolean IsSameDirection(const Cad3d_RingOnSurface& theOther) const;

			void SetCentre(const Geom_Pnt3d& Centre);
		};
	}
}

#include <Cad3d_RingOnSurfaceI.hxx>

#endif // !_Cad3d_RingOnSurface_Header
