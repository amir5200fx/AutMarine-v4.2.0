#pragma once
inline
AutLib::MeshLib::Mesh2d_SourcePoint::Mesh2d_SourcePoint
(
	const Geom_Pnt2d & theCoord,
	const Standard_Real theValue
)
	: theCoord_(theCoord)
	, theValue_(theValue)
{
}

inline 
void AutLib::MeshLib::Mesh2d_SourcePoint::Init
(
	const Geom_Pnt2d & theCoord, 
	const Standard_Real theValue
)
{
	theCoord_ = theCoord;
	theValue_ = theValue;
}

inline 
void AutLib::MeshLib::Mesh2d_SourcePoint::SetCoord(const Geom_Pnt2d & theCoord)
{
	theCoord_ = theCoord;
}

inline 
void AutLib::MeshLib::Mesh2d_SourcePoint::SetValue(const Standard_Real Value)
{
	theValue_ = Value;
}

inline 
const Geom_Pnt2d & AutLib::MeshLib::Mesh2d_SourcePoint::Coord() const
{
	return theCoord_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh2d_SourcePoint::Value() const
{
	return theValue_;
}