#pragma once
inline
AutLib::MeshLib::Mesh3d_SourcePoint::Mesh3d_SourcePoint
(
	const Geom_Pnt3d & theCoord,
	const Standard_Real Value
)
	: theCoord_(theCoord)
	, theValue_(Value)
{
}

inline 
void AutLib::MeshLib::Mesh3d_SourcePoint::Init
(
	const Geom_Pnt3d & theCoord, 
	const Standard_Real Value
)
{
	theCoord_ = theCoord;
	theValue_ = Value;
}

inline 
void AutLib::MeshLib::Mesh3d_SourcePoint::SetCoord(const Geom_Pnt3d & theCoord)
{
	theCoord_ = theCoord;
}

inline 
void AutLib::MeshLib::Mesh3d_SourcePoint::SetValue(const Standard_Real Value)
{
	theValue_ = Value;
}

inline 
const Geom_Pnt3d & AutLib::MeshLib::Mesh3d_SourcePoint::Coord() const
{
	return theCoord_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_SourcePoint::Value() const
{
	return theValue_;
}