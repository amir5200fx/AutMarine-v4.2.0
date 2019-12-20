#pragma once
inline
AutLib::MeshLib::Mesh3d_BoundaryFacet::Mesh3d_BoundaryFacet()
{
}

inline 
AutLib::MeshLib::Mesh3d_BoundaryFacet::Mesh3d_BoundaryFacet(const Standard_Integer Index)
	: Mesh3d_Facet(Index)
{
}

inline 
AutLib::MeshLib::Mesh3d_BoundaryFacet::Mesh3d_BoundaryFacet
(
	const Standard_Integer Index,
	Global_Handle(Mesh3d_Node) theNode0,
	Global_Handle(Mesh3d_Node) theNode1, 
	Global_Handle(Mesh3d_Node) theNode2
)
	: Mesh3d_Facet(Index, theNode0, theNode1, theNode2)
{
}

inline 
AutLib::MeshLib::Mesh3d_BoundaryFacet::Mesh3d_BoundaryFacet
(
	const Standard_Integer Index,
	Global_Handle(Mesh3d_Node) theNode0,
	Global_Handle(Mesh3d_Node) theNode1,
	Global_Handle(Mesh3d_Node) theNode2,
	Global_Handle(Mesh3d_Edge) theEdge0,
	Global_Handle(Mesh3d_Edge) theEdge1,
	Global_Handle(Mesh3d_Edge) theEdge2
)
	: Mesh3d_Facet(Index, theNode0, theNode1, theNode2, theEdge0, theEdge1, theEdge2)
{
}

inline 
AutLib::MeshLib::Mesh3d_BoundaryFacet::~Mesh3d_BoundaryFacet()
{
}