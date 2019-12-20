#pragma once
inline
AutLib::MeshLib::Mesh2d_SourcePoint2::Mesh2d_SourcePoint2
(
	const Geom_Pnt2d & theCoord,
	const Standard_Real theValue,
	const Standard_Real theRadius
)
	: Mesh2d_SourcePoint(theCoord, theValue)
	, theRadius_(theRadius)
{
}

inline 
void AutLib::MeshLib::Mesh2d_SourcePoint2::Init
(
	const Geom_Pnt2d & theCoord, 
	const Standard_Real theValue, 
	const Standard_Real theRadius
)
{
	theCoord_ = theCoord;
	theValue_ = theValue;
	theRadius_ = theRadius;
}

inline 
void AutLib::MeshLib::Mesh2d_SourcePoint2::SetRadius(const Standard_Real theRadius)
{
	theRadius_ = theRadius;
}

inline 
Standard_Real AutLib::MeshLib::Mesh2d_SourcePoint2::Radius() const
{
	return theRadius_;
}