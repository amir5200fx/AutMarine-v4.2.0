#pragma once
inline
Standard_Boolean AutLib::MeshLib::Mesh2d_ElementTools::IsLess
(
	Global_Handle(Mesh2d_Element) const & theElement1,
	Global_Handle(Mesh2d_Element) const & theElement2
)
{
	Debug_Null_Pointer(theElement1);
	Debug_Null_Pointer(theElement2);
	return theElement1->Index() < theElement2->Index();
}

inline 
M_GEO Entity_TriangleIndex AutLib::MeshLib::Mesh2d_ElementTools::StaticOf(const Mesh2d_Element & Element)
{
	return M_GEO Entity_TriangleIndex(Element.Node0()->Index(), Element.Node1()->Index(), Element.Node2()->Index());
}