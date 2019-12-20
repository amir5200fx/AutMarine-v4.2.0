#pragma once
#ifndef _Cad3d_RingOnPlane_Header
#define _Cad3d_RingOnPlane_Header

#include <Cad3d_EdgeOnPlane.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad3d_RingOnPlane : public Cad3d_EdgeOnPlane
		{

		private:


		public:

			Cad3d_RingOnPlane();

			Cad3d_RingOnPlane(const Standard_Integer theIndex, const Global_Handle(Cad3d_PointOnPlane) thePoint, Global_Handle(Cad3d_CurveOnPlane) theCurve);

			virtual ~Cad3d_RingOnPlane();

			virtual void Init(const Standard_Integer theIndex, const Global_Handle(Cad3d_PointOnPlane) thePoint, Global_Handle(Cad3d_CurveOnPlane) theCurve);

			virtual Global_Handle(Cad3d_RingOnPlane) Copy() const;
		};
	}
}

#endif // !_Cad3d_RingOnPlane_Header
