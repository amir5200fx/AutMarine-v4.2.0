#pragma once
#ifndef _FvGeom_Node2d_Header
#define _FvGeom_Node2d_Header

#include <FvPrimitives_Label.hxx>
#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvGeom_Node2d
		{

		private:

			Label theIndex_;

			Geom_Pnt2d theCoord_;

		public:

			FvGeom_Node2d();

			FvGeom_Node2d(const Label theIndex, const Geom_Pnt2d& theCoord);

			Label Index() const;

			const Geom_Pnt2d& Coord() const;

			void Import(fstream& File);

			friend fstream& operator>>(fstream& File, FvGeom_Node2d& theNode);
		};
	}
}

#include <FvGeom_Node2dI.hxx>

#endif // !_FvGeom_Node2d_Header
