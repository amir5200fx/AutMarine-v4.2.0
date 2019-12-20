#pragma once
inline
Standard_Integer AutLib::MeshLib::Mesh3d_NodeTools::GetIndexOf(Global_Handle(Mesh3d_Node) Node)
{
	Debug_Null_Pointer(Node);
	return Node->Index();
}

inline 
const Geom_Pnt3d & AutLib::MeshLib::Mesh3d_NodeTools::GetCoordOf(Global_Handle(Mesh3d_Node) Node)
{
	Debug_Null_Pointer(Node);
	return Node->Coord();
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_NodeTools::IsLess(Global_Handle(Mesh3d_Node) const & Node1, Global_Handle(Mesh3d_Node) const & Node2)
{
	Debug_Null_Pointer(Node1);
	Debug_Null_Pointer(Node2);

	return Node1->Index() < Node2->Index();
}