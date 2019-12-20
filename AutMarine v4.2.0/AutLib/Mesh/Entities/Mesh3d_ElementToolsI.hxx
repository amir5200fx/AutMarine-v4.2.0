#pragma once
inline 
Global_Handle(AutLib::MeshLib::Mesh3d_Facet) AutLib::MeshLib::Mesh3d_ElementTools::CommonFacet
(
	const Mesh3d_Element & theElement0,
	const Mesh3d_Element & theElement1
)
{
	Standard_Integer Node0 = theElement0.OppositeVertexIndex(&theElement1);
	Standard_Integer Node1 = theElement1.OppositeVertexIndex(&theElement0);

	if (Node0 < 0) { return NULL; }
	if (Node1 < 0) { return NULL; }

	Global_Handle(Mesh3d_Facet) Facet0 = theElement0.Facet(Node0);
	Global_Handle(Mesh3d_Facet) Facet1 = theElement0.Facet(Node1);

	if (Facet0 NOT_EQUAL Facet1) { THROW_STANDARD_EXCEPTION("Contractory Data"); }

	return Facet0;
}

inline
M_GEO Entity_TetrahedronIndex AutLib::MeshLib::Mesh3d_ElementTools::StaticOf(const Mesh3d_Element & Element)
{
	return M_GEO Entity_TetrahedronIndex(Element.Node(0)->Index(), Element.Node(1)->Index(), Element.Node(2)->Index(), Element.Node(3)->Index());
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_ElementTools::IsLess(Global_Handle(Mesh3d_Element) const & Element1, Global_Handle(Mesh3d_Element) const & Element2)
{
	return Element1->Index() < Element2->Index();
}