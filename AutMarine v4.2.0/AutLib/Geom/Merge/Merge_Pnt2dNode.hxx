#pragma once
#ifndef _Merge_Pnt2dNode_Header
#define _Merge_Pnt2dNode_Header

#include <Geom_Pnt2d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Merge_Pnt2dNode
		{

		private:

			Standard_Integer theIndex_;

			Geom_Pnt2d theCoord_;

		public:

			Merge_Pnt2dNode();

			Merge_Pnt2dNode(const Standard_Integer Index, const Geom_Pnt2d& Coord);

			Standard_Integer Index() const;

			const Geom_Pnt2d& Coord() const;

			void SetIndex(const Standard_Integer Index);

			void SetCoord(const Geom_Pnt2d& Coord);
		};
	}
}

#include <Merge_Pnt2dNodeI.hxx>

#endif // !_Merge_Pnt2dNode_Header
