#pragma once
#ifndef _Entity_TriangleIndexTools_Header
#define _Entity_TriangleIndexTools_Header

#include <TColEntity_Ary1dOfTriangleIndex.hxx>
#include <TColEntity_Ary1dOfEdgeIndex.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		class Entity_TriangleIndexTools
		{

		public:

			static void FormEdgesOfElements(const TColEntity_Ary1dOfTriangleIndex& Elements, TColEntity_Ary1dOfEdgeIndex& Edges);
		};
	}
}

#endif // !_Entity_TriangleIndexTools_Header
