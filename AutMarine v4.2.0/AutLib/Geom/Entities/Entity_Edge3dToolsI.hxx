#pragma once
inline
Standard_Boolean AutLib::GeoLib::Entity_Edge3dTools::IsLess(Global_Handle(Entity_Edge3d) const & Edge0, Global_Handle(Entity_Edge3d) const & Edge1)
{
	Debug_Null_Pointer(Edge0);
	Debug_Null_Pointer(Edge1);

	return Edge0->Index() < Edge1->Index();
}