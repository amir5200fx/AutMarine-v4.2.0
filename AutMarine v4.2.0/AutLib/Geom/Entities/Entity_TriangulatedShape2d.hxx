#pragma once
#ifndef _Entity_TriangulatedShape2d_Header
#define _Entity_TriangulatedShape2d_Header

#include <Entity_Triangulation2d.hxx>

class gp_Ax22d;
class gp_Ax2d;

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_TriangulatedShape2d : public Entity_Triangulation2d
		{

		public:

			Entity_TriangulatedShape2d();

			void MakeBox(const gp_Ax22d& A, const Standard_Real Dx, const Standard_Real Dy);

			void MakeBox(const gp_Ax2d& A, const Standard_Real Dx, const Standard_Real Dy, const Standard_Boolean Sense = Standard_True);

			void MakeCircle(const Geom_Pnt2d& theCentre, const Standard_Real theRadius, const Standard_Integer theNbSegments = 40);
		};
	}
}

#endif // !_Entity_TriangulatedShape2d_Header
