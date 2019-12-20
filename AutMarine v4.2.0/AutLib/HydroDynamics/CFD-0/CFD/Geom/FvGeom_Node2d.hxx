#pragma once
#ifndef _FvGeom_Node2d_Header
#define _FvGeom_Node2d_Header

#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvGeom_Node2d
		{

		private:

			Standard_Integer theIndex_;

			Geom_Pnt2d theCoord_;

		public:

			FvGeom_Node2d();

			FvGeom_Node2d(const Standard_Integer theIndex, const Geom_Pnt2d& theCoord);

			Standard_Integer Index() const;

			const Geom_Pnt2d& Coord() const;

			void Import(fstream& File);
		};
	}
}

#include <FvGeom_Node2dI.hxx>

#endif // !_FvGeom_Node2d_Header
