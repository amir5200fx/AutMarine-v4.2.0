#pragma once
inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_EdgeTools::IsOnBoundary(const Global_Handle(Mesh2d_Edge) theEdge)
{
	return Global_DownCast(Mesh2d_Edge, (Global_Handle(Mesh2d_BoundaryEdge))theEdge);
}

inline
Standard_Boolean AutLib::MeshLib::Mesh2d_EdgeTools::IsLess
(
	Global_Handle(Mesh2d_Edge) const & theEdge1,
	Global_Handle(Mesh2d_Edge) const & theEdge2
)
{
	Debug_Null_Pointer(theEdge1);
	Debug_Null_Pointer(theEdge2);
	return theEdge1->Index() < theEdge2->Index();
}

inline 
Standard_Real AutLib::MeshLib::Mesh2d_EdgeTools::LengthOf(Global_Handle(Mesh2d_Edge) const & theEdge)
{
	Debug_Null_Pointer(theEdge);
	return theEdge->Length();
}

inline 
M_GEO Entity_EdgeIndex AutLib::MeshLib::Mesh2d_EdgeTools::StaticOf(const Mesh2d_Edge & Edge)
{
	return M_GEO Entity_EdgeIndex(Edge.Node(0)->Index(), Edge.Node(1)->Index());
}