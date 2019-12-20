#pragma once
#ifndef _Cad2d_MakeCurveOnPlane_Header
#define _Cad2d_MakeCurveOnPlane_Header

#include <Cad2d_CurveOnPlane.hxx>

class gp_Ax22d;
class gp_Ax2d;

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_MakeCurveOnPlane : public Cad2d_CurveOnPlane
		{

		public:

			void LineSegment(const Geom_Pnt2d& thePoint1, const Geom_Pnt2d& thePoint2);

			void CircularArc(const gp_Ax22d& A, const Standard_Real Radius, const Standard_Real theDeg0, const Standard_Real theDeg1);

			void CircularArc(const gp_Ax2d& A, const Standard_Real Radius, const Standard_Real theDeg0, const Standard_Real theDeg1, const Standard_Boolean Sense = Standard_True);

			void Ellipse(const gp_Ax2d& MajorAxis, const Standard_Real MajorRadius, const Standard_Real MinorRadius, const Standard_Boolean Sense = Standard_True);

			void Ellipse(const gp_Ax22d& Axis, const Standard_Real MajorRadius, const Standard_Real MinorRadius);
		};
	}
}

#endif // !_Cad2d_MakeCurveOnPlane_Header
