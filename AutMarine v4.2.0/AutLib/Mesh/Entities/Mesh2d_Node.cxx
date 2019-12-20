#include "Mesh2d_Node.hxx"

#include <Mesh2d_Edge.hxx>
#include <Mesh2d_NodeTools.hxx>
#include <Mesh2d_EdgeTools.hxx>
#include <Mesh2d_ElementTools.hxx>

#ifdef USE_INDEX_NUMBERING
AutLib::MeshLib::Mesh2d_Node::Mesh2d_Node()
{
	Set_Numbering(theFront_, Mesh2d_EdgeTools::IsLess);

	Set_Numbering(theEdges_, Mesh2d_EdgeTools::IsLess);

	Set_Numbering(theElements_, Mesh2d_ElementTools::IsLess);

	theFront_.SetName("Front Edges Around Node");

	theEdges_.SetName("Edges Around Node");

	theElements_.SetName("Elements Around Node");
}

AutLib::MeshLib::Mesh2d_Node::Mesh2d_Node
(
	const Standard_Integer Index,
	const Geom_Pnt2d & Coord
)
	: theIndex_(Index)
	, theCoord_(Coord)
{
	Set_Numbering(theFront_, Mesh2d_EdgeTools::IsLess);

	Set_Numbering(theEdges_, Mesh2d_EdgeTools::IsLess);

	Set_Numbering(theElements_, Mesh2d_ElementTools::IsLess);

	theFront_.SetName("Front Edges Around Node");

	theEdges_.SetName("Edges Around Node");

	theElements_.SetName("Elements Around Node");
}
#endif // USE_INDEX_NUMBERING
