#pragma once
#ifndef _Cad2d_MakePlane_Header
#define _Cad2d_MakePlane_Header

#include <Cad2d_Plane.hxx>
#include <Geom_Pnt2d.hxx>

class gp_Ax2d;
class gp_Ax22d;

namespace AutLib
{
	namespace CadLib
	{

		class Cad2d_MakePlane : public Cad2d_Plane
		{

		public:

			void Box(const GeoLib::Geom_Pnt2d& Corner, const Standard_Real Dx, const Standard_Real Dy);

			void Box(const GeoLib::Geom_Pnt2d& Corner0, const GeoLib::Geom_Pnt2d& Corner1);

			void Box(const gp_Ax22d& A, const Standard_Real Dx, const Standard_Real Dy);

			void Box(const gp_Ax2d& A, const Standard_Real Dx, const Standard_Real Dy, const Standard_Boolean Sense = Standard_True);

			//! Constructs a circle
			//! of radius Radius, where the coordinate system A
			//! locates the circle and defines its orientation in the plane such that:
			//! - the center of the circle is the origin of A,
			//! - the orientation (direct or indirect) of A gives the
			//! orientation of the circle.
			void Circle(const gp_Ax22d& A, const Standard_Real Radius);

			//! Constructs a circle of radius Radius, whose center is the origin of axis
			//! A; A is the "X Axis" of the local coordinate system
			//! of the circle; this coordinate system is direct if
			//! Sense is true (default value) or indirect if Sense is false.
			//! Note: It is possible to create a circle where Radius is equal to 0.0.
			//! Exceptions Standard_ConstructionError if Radius is negative.
			void Circle(const gp_Ax2d& A, const Standard_Real Radius, const Standard_Boolean Sense = Standard_True);

		};
	}
}

#endif // !_Cad2d_MakePlane_Header
