#pragma once
inline
Standard_Boolean AutLib::GeoLib::Entity_Node2dTools::IsLess(Global_Handle(Entity_Node2d) const & Node0, Global_Handle(Entity_Node2d) const & Node1)
{
	Debug_Null_Pointer(Node0);
	Debug_Null_Pointer(Node1);

	return Node0->Index() < Node1->Index();
}