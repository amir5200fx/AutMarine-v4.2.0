#pragma once
inline
const Geom_Pnt3d & AutLib::MeshLib::Mesh3d_SourcePointTools::CoordinateOf(Global_Handle(Mesh3d_SourcePoint) theSource)
{
	return theSource->Coord();
}