#pragma once
inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_NodeTools::IsOnBoundary(const Global_Handle(Mesh2d_Node) theNode)
{
	return Global_DownCast(Mesh2d_Node, (Global_Handle(Mesh2d_BoundaryNode)) theNode);
}

inline
Standard_Boolean AutLib::MeshLib::Mesh2d_NodeTools::IsLess
(
	Global_Handle(Mesh2d_Node) const & theNode1,
	Global_Handle(Mesh2d_Node) const & theNode2
)
{
	Debug_Null_Pointer(theNode1);
	Debug_Null_Pointer(theNode2);

	return theNode1->Index() < theNode2->Index();
}

inline
const Geom_Pnt2d & AutLib::MeshLib::Mesh2d_NodeTools::GetCoordOf(Global_Handle(Mesh2d_Node) Node)
{
	Debug_Null_Pointer(Node);

	return Node->Coord();
}