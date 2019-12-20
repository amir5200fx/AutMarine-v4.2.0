#pragma once
#ifndef _Cad2d_RingOnPlane_Header
#define _Cad2d_RingOnPlane_Header

#include <Cad2d_EdgeOnPlane.hxx>

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_RingOnPlane : public Cad2d_EdgeOnPlane
		{

		private:


		public:

			Cad2d_RingOnPlane();

			Cad2d_RingOnPlane(const Standard_Integer theIndex, const Global_Handle(Cad2d_PointOnPlane) thePoint, Global_Handle(Cad2d_CurveOnPlane) theCurve);

			virtual ~Cad2d_RingOnPlane();

			virtual void Init(const Standard_Integer theIndex, const Global_Handle(Cad2d_PointOnPlane) thePoint, Global_Handle(Cad2d_CurveOnPlane) theCurve);

			virtual Global_Handle(Cad2d_RingOnPlane) Copy() const;
		};
	}
}

#endif // !_Cad2d_RingOnPlane_Header
