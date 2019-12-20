#include <Mesh3d_Front.hxx>

#include <Mesh3d_FacetTools.hxx>
#include <Mesh3d_NodeTools.hxx>

AutLib::MeshLib::Mesh3d_Front::Mesh3d_Front()
	: theLevelNb_(0)
	, theLevelMaxIndex_(0)
{
	theSortedFacets_.SetFunction(&Mesh3d_FacetTools::AreaOf);

	//Set_Numbering(theFacets_, Mesh3d_FacetTools::IsLess);

	//Set_Numbering(theNodes_, Mesh3d_NodeTools::IsLess);

	Set_Numbering(theCurrentLevels_, Mesh3d_FacetTools::IsLess);

	Set_Numbering(theNextLevels_, Mesh3d_FacetTools::IsLess);

	//theFacets_.SetName(" Front Tree- Facets");

	//theNodes_.SetName(" Front Tree- Nodes");

	theCurrentLevels_.SetName(" Front Tree- Current Levels");

	theNextLevels_.SetName(" Front Tree- Next Levels");
}