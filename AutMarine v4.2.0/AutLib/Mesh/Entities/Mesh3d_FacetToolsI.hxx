#pragma once
#include <ADT_AdressAvlTree.hxx>

inline
M_GEO Entity_TriangleIndex AutLib::MeshLib::Mesh3d_FacetTools::StaticOf(const Mesh3d_Facet & Facet)
{
	return M_GEO Entity_TriangleIndex(Facet.Node0()->Index(), Facet.Node1()->Index(), Facet.Node2()->Index());
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_FacetTools::IsLess(Global_Handle(Mesh3d_Facet) const & Facet1, Global_Handle(Mesh3d_Facet) const & Facet2)
{
	Debug_Null_Pointer(Facet1);
	Debug_Null_Pointer(Facet2);

	return Facet1->Index() < Facet2->Index();
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_FacetTools::AreaOf(Global_Handle(Mesh3d_Facet) const & Facet)
{
	return Facet->Area();
}
