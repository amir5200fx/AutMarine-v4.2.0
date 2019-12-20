#pragma once
inline
Standard_Boolean AutLib::CadLib::Cad2d_PointOnPlaneTools::IsLess(Global_Handle(Cad2d_PointOnPlane) const & thePoint1, Global_Handle(Cad2d_PointOnPlane) const & thePoint2)
{
	Debug_Null_Pointer(thePoint1);
	Debug_Null_Pointer(thePoint2);

	return thePoint1->Index() < thePoint2->Index();
}

inline 
const Geom_Pnt2d & AutLib::CadLib::Cad2d_PointOnPlaneTools::CoordOf(Global_Handle(Cad2d_PointOnPlane) thePoint)
{
	Debug_Null_Pointer(thePoint);
	return thePoint->Coord();
}