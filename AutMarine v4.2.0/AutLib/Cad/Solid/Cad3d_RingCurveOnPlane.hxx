#pragma once
#ifndef _Cad3d_RingCurveOnPlane_Header
#define _Cad3d_RingCurveOnPlane_Header

#include <Cad3d_CurveOnPlane.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_RingCurveOnPlane : public Cad3d_CurveOnPlane
		{

		private:

		public:

			Cad3d_RingCurveOnPlane();

			Cad3d_RingCurveOnPlane(const Standard_Real theFirstParameter, const Standard_Real theLastParameter, const Handle(Geom2d_Curve)& theCurve);

			virtual ~Cad3d_RingCurveOnPlane();

			virtual void Init(const Standard_Real theFirstParameter, const Standard_Real theLastParameter, const Handle(Geom2d_Curve)& theCurve);

			virtual Global_Handle(Cad3d_RingCurveOnPlane) Copy() const;
		};
	}
}

#endif // !_Cad3d_RingCurveOnPlane_Header
