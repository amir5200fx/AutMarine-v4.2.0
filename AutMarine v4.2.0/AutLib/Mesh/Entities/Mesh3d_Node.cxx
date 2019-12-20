#include <Mesh3d_Node.hxx>

#include <Mesh3d_EdgeTools.hxx>
#include <Mesh3d_FacetTools.hxx>
#include <Mesh3d_ElementTools.hxx>

#ifdef USE_INDEX_NUMBERING
AutLib::MeshLib::Mesh3d_Node::Mesh3d_Node()
{
	Set_Numbering(theEdges_, Mesh3d_EdgeTools::IsLess);
	Set_Numbering(theFacets_, Mesh3d_FacetTools::IsLess);
	Set_Numbering(theElements_, Mesh3d_ElementTools::IsLess);

	Set_Numbering(theFrontEdges_, Mesh3d_EdgeTools::IsLess);
	Set_Numbering(theFrontFacets_, Mesh3d_FacetTools::IsLess);

	theFrontEdges_.SetName(" Front Edges Around Node");
	theFrontFacets_.SetName(" Front Facets Around Node");

	theEdges_.SetName(" Edges Around Node");
	theFacets_.SetName(" Facets Around Node");
	theElements_.SetName(" Elements Around Node");
}


AutLib::MeshLib::Mesh3d_Node::Mesh3d_Node
(
	const Standard_Integer Index,
	const Geom_Pnt3d & Coord
)
	: theIndex_(Index)
	, theCoord_(Coord)
{
	Set_Numbering(theEdges_, Mesh3d_EdgeTools::IsLess);
	Set_Numbering(theFacets_, Mesh3d_FacetTools::IsLess);
	Set_Numbering(theElements_, Mesh3d_ElementTools::IsLess);

	Set_Numbering(theFrontEdges_, Mesh3d_EdgeTools::IsLess);
	Set_Numbering(theFrontFacets_, Mesh3d_FacetTools::IsLess);

	theFrontEdges_.SetName(" Front Edges Around Node");
	theFrontFacets_.SetName(" Front Facets Around Node");

	theEdges_.SetName(" Edges Around Node");
	theFacets_.SetName(" Facets Around Node");
	theElements_.SetName(" Elements Around Node");
}
#endif