#include <FvReferences_Info.hxx>

Geom_Pnt2d AutLib::FvLib::FvReferences_Info::Gravity()
{
	return Geom_Pnt2d(0, -9.806);
}

Standard_Real AutLib::FvLib::FvReferences_Info::Pressure()
{
	return (Standard_Real)101325.0;
}