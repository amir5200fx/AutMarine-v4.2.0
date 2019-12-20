#pragma once
#ifndef _Merge_Pnt3dNode_Header
#define _Merge_Pnt3dNode_Header

#include <Geom_Pnt3d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Merge_Pnt3dNode
		{

		private:

			Standard_Integer theIndex_;

			Geom_Pnt3d theCoord_;

		public:

			Merge_Pnt3dNode();

			Merge_Pnt3dNode(const Standard_Integer Index, const Geom_Pnt3d& Coord);

			Standard_Integer Index() const;

			const Geom_Pnt3d& Coord() const;

			void SetIndex(const Standard_Integer Index);

			void SetCoord(const Geom_Pnt3d& Coord);
		};
	}
}

#include <Merge_Pnt3dNodeI.hxx>

#endif // !_Merge_Pnt3dNode_Header
