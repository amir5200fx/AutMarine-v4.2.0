#pragma once
#ifndef _Entity_PolygonShape2d_Header
#define _Entity_PolygonShape2d_Header

#include <Entity_Polygon2d.hxx>

class gp_Ax22d;
class gp_Ax2d;

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_PolygonShape2d : public Entity_Polygon2d
		{

		public:

			Entity_PolygonShape2d();

			void MakeBox(const gp_Ax22d& A, const Standard_Real Dx, const Standard_Real Dy);

			void MakeBox(const gp_Ax2d& A, const Standard_Real Dx, const Standard_Real Dy, const Standard_Boolean Sense = Standard_True);

			void MakeCircle(const Geom_Pnt2d& theCentre, const Standard_Real theRadius, const Standard_Integer theNbSegments = 40);
		};
	}
}

#endif // !_Entity_PolygonShape2d_Header
