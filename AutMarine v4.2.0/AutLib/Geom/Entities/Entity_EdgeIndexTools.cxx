#include <Entity_EdgeIndexTools.hxx>

using namespace AutLib;
using namespace GeoLib;

TColEntity_Ary1dOfEdgeIndex AutLib::GeoLib::Entity_EdgeIndexTools::OrderedList(const Standard_Integer NbEdges)
{
	TColEntity_Ary1dOfEdgeIndex Edges(NbEdges);

	forThose(Index, 0, MaxIndexOf(Edges))
	{
		Edges[Index].SetV12(Index + 1, Index + 2);
	}

	MOVE(Edges);
}

TColEntity_Ary1dOfEdgeIndex AutLib::GeoLib::Entity_EdgeIndexTools::DiscreteOrderedList(const Standard_Integer NbEdges)
{
	TColEntity_Ary1dOfEdgeIndex Edges(NbEdges);

	forThose(Index, 0, MaxIndexOf(Edges))
	{
		Edges[Index].SetV12(Index * 2 + 1, Index * 2 + 2);
	}

	MOVE(Edges);
}