#pragma once
inline
Standard_Boolean AutLib::CadLib::Cad3d_SurfaceOnSolidTools::IsLess
(
	Global_Handle(Cad3d_SurfaceOnSolid) const & theSurface1,
	Global_Handle(Cad3d_SurfaceOnSolid) const & theSurface2
)
{
	return theSurface1->Index() < theSurface2->Index();
}