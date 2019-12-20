#pragma once
inline
Standard_Boolean AutLib::GeoLib::Entity_FacetTools::IsLess(Global_Handle(Entity_Facet) const & Element0, Global_Handle(Entity_Facet) const & Element1)
{
	Debug_Null_Pointer(Element0);
	Debug_Null_Pointer(Element1);

	return Element0->Index() < Element1->Index();
}