#pragma once
inline
Global_Handle(M_CAD Cad2d_EdgesOnPlane) AutLib::CadLib::Cad2d_Plane::Edges() const
{
	return theEdges_;
}

inline
Global_Handle(M_CAD Cad2d_PointsOnPlane) AutLib::CadLib::Cad2d_Plane::Corners() const
{
	return theCorners_;
}

inline
Standard_Integer AutLib::CadLib::Cad2d_Plane::NbEdges() const
{
	Debug_Null_Pointer(theEdges_);
	return theEdges_->Size();
}

inline
Standard_Integer AutLib::CadLib::Cad2d_Plane::NbCorners() const
{
	Debug_Null_Pointer(theCorners_);
	return theCorners_->Size();
}

inline Standard_Integer AutLib::CadLib::Cad2d_Plane::NbHoles() const
{
	return theInnerWires_.Size();
}

inline
void AutLib::CadLib::Cad2d_Plane::RetrieveCornersTo(TColCad2d_HAry1dOfPointOnPlane & theCorners) const
{
	Debug_Null_Pointer(theCorners_);
	theCorners_->RetrieveTo(theCorners);
}

inline
void AutLib::CadLib::Cad2d_Plane::RetrieveEdgesTo(TColCad2d_HAry1dOfEdgeOnPlane & theEdges) const
{
	Debug_Null_Pointer(theEdges_);
	theEdges_->RetrieveTo(theEdges);
}