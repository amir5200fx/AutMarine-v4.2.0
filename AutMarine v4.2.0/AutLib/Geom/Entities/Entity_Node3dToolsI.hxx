#pragma once
inline
Standard_Boolean AutLib::GeoLib::Entity_Node3dTools::IsLess(Global_Handle(Entity_Node3d) const & Node0, Global_Handle(Entity_Node3d) const & Node1)
{
	Debug_Null_Pointer(Node0);
	Debug_Null_Pointer(Node1);

	return Node0->Index() < Node1->Index();
}