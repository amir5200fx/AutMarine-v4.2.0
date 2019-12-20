#pragma once
inline
M_GEO Entity_EdgeIndex AutLib::MeshLib::Mesh3d_EdgeTools::StaticOf(const Mesh3d_Edge & Edge)
{
	return M_GEO Entity_EdgeIndex(Edge.Node0()->Index(), Edge.Node1()->Index());
}

inline
Standard_Real AutLib::MeshLib::Mesh3d_EdgeTools::LengthOf(Global_Handle(Mesh3d_Edge) const & Edge)
{
	Debug_Null_Pointer(Edge);
	return Edge->Length();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_EdgeTools::IsLess(Global_Handle(Mesh3d_Edge) const & Edge1, Global_Handle(Mesh3d_Edge) const & Edge2)
{
	Debug_Null_Pointer(Edge1);
	Debug_Null_Pointer(Edge2);

	return Edge1->Index() < Edge2->Index();
}