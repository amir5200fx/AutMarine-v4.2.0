#pragma once
inline
Standard_Boolean AutLib::CadLib::Cad3d_EdgeOnSolidTools::IsLess(Global_Handle(Cad3d_EdgeOnSolid) const & theEdge1, Global_Handle(Cad3d_EdgeOnSolid) const & theEdge2)
{
	return theEdge1->Index() < theEdge2->Index();
}
