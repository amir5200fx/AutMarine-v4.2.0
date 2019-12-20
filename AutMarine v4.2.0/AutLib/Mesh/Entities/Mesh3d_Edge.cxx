#include <Mesh3d_Edge.hxx>

#include <Mesh3d_FacetTools.hxx>
#include <Mesh3d_ElementTools.hxx>

#ifdef USE_INDEX_NUMBERING
AutLib::MeshLib::Mesh3d_Edge::Mesh3d_Edge()
	: theIndex_(0)
	, theLength_(0)
	, IsCavity_(Standard_False)
{
	theNodes_[0] = NULL;
	theNodes_[1] = NULL;

	Set_Numbering(theFacets_, Mesh3d_FacetTools::IsLess);
	Set_Numbering(theElements_, Mesh3d_ElementTools::IsLess);

	Set_Numbering(theFrontFacet_, Mesh3d_FacetTools::IsLess);
}

AutLib::MeshLib::Mesh3d_Edge::Mesh3d_Edge
(
	const Standard_Integer Index,
	const Standard_Real Length,
	Global_Handle(Mesh3d_Node) Node0,
	Global_Handle(Mesh3d_Node) Node1
)
	: theIndex_(Index)
	, theLength_(Length)
	, IsCavity_(Standard_False)
{
	theNodes_[0] = Node0;
	theNodes_[1] = Node1;

	Set_Numbering(theFacets_, Mesh3d_FacetTools::IsLess);
	Set_Numbering(theElements_, Mesh3d_ElementTools::IsLess);

	Set_Numbering(theFrontFacet_, Mesh3d_FacetTools::IsLess);
}
#endif