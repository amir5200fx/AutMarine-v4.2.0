#pragma once
inline 
const Geom_Pnt2d & AutLib::MeshLib::Mesh2d_MetricSourcePointTools::CoordinateOf(Global_Handle(Mesh2d_MetricSourcePoint) theSource)
{
	Debug_Null_Pointer(theSource);
	return theSource->Coord();
}