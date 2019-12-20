#pragma once
#ifndef _Entity_EdgeIndexTools_Header
#define _Entity_EdgeIndexTools_Header

#include <TColEntity_Ary1dOfEdgeIndex.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_EdgeIndexTools
		{

		public:

			static TColEntity_Ary1dOfEdgeIndex OrderedList(const Standard_Integer NbEdges);

			static TColEntity_Ary1dOfEdgeIndex DiscreteOrderedList(const Standard_Integer NbEdges);
		};
	}
}

#endif // !_Entity_EdgeIndexTools_Header
