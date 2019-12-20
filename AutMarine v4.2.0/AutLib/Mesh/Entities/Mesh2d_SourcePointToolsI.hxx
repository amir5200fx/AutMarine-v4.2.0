#pragma once
inline
const Geom_Pnt2d & AutLib::MeshLib::Mesh2d_SourcePointTools::CoordinateOf(Global_Handle(Mesh2d_SourcePoint) theSource)
{
	return theSource->Coord();
}