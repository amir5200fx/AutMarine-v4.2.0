#include <Entity_FacetTools.hxx>

using namespace AutLib;

TColEntity_Ary1dOfTriangleIndex AutLib::GeoLib::Entity_FacetTools::StaticOf(const TColEntity_HAry1dOfFacet & Facets)
{
	TColEntity_Ary1dOfTriangleIndex Indices(Facets.Size());
	forThose(Index, 0, MaxIndexOf(Facets))
		Indices[Index].SetValue
		(
			Facets[Index]->Node0()->Index(), 
			Facets[Index]->Node1()->Index(),
			Facets[Index]->Node2()->Index()
		);
	MOVE(Indices);
}