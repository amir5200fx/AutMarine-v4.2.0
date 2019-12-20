#pragma once
inline
Standard_Boolean AutLib::GeoLib::Entity_Element2dTools::IsLess(Global_Handle(Entity_Element2d) const & Element0, Global_Handle(Entity_Element2d) const & Element1)
{
	return Element0->Index() < Element1->Index();
}