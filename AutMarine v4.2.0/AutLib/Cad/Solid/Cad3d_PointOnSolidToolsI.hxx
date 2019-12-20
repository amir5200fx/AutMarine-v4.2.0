#pragma once
inline
Standard_Boolean AutLib::CadLib::Cad3d_PointOnSolidTools::IsLess
(
	Global_Handle(Cad3d_PointOnSolid) const thePoint1,
	Global_Handle(Cad3d_PointOnSolid) const thePoint2
)
{
	return thePoint1->Index() < thePoint2->Index();
}

inline
const Geom_Pnt3d& AutLib::CadLib::Cad3d_PointOnSolidTools::CoordOf(Global_Handle(Cad3d_PointOnSolid) Point)
{
	return Point->Coord();
}