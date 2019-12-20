#pragma once
inline
Standard_Boolean AutLib::CadLib::Cad2d_EdgeOnPlaneTools::IsLess(Global_Handle(Cad2d_EdgeOnPlane) const & theEdge1, Global_Handle(Cad2d_EdgeOnPlane) const & theEdge2)
{
	Debug_Null_Pointer(theEdge1);
	Debug_Null_Pointer(theEdge2);

	return theEdge1->Index() < theEdge2->Index();
}