#pragma once
#ifndef _Entity_IndexedPt3d_Header
#define _Entity_IndexedPt3d_Header

#include <Geom_Pnt3d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_IndexedPt3d
		{

		private:

			Geom_Pnt3d theCoord_;

			Standard_Integer theIndex_;

		public:

			Entity_IndexedPt3d();

			Entity_IndexedPt3d(const Standard_Integer theIndex, const Geom_Pnt3d& theCoord);

			Standard_Integer Index() const;

			const Geom_Pnt3d& Coord() const;

			void SetIndex(const Standard_Integer theIndex);

			void SetCoord(const Geom_Pnt3d& theCoord);
		};
	}
}

#include <Entity_IndexedPt3dI.hxx>

#endif // !_Entity_IndexedPt3d_Header
