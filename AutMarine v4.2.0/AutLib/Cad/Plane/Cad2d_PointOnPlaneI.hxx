#pragma once
inline
Standard_Integer AutLib::CadLib::Cad2d_PointOnPlane::NbEdges() const
{
	return theEdges_.Size();
}

inline
Standard_Integer AutLib::CadLib::Cad2d_PointOnPlane::Index() const
{
	return theIndex_;
}

inline 
Standard_Boolean AutLib::CadLib::Cad2d_PointOnPlane::IsFree() const
{
	return NbEdges() EQUAL 1;
}

inline 
Standard_Boolean AutLib::CadLib::Cad2d_PointOnPlane::IsOrphan() const
{
	return theEdges_.IsEmpty();
}

inline
const Geom_Pnt2d & AutLib::CadLib::Cad2d_PointOnPlane::Coord() const
{
	return theCoord_;
}

inline 
void AutLib::CadLib::Cad2d_PointOnPlane::RetrieveEdgesTo(TColCad2d_HAry1dOfEdgeOnPlane & theEdges) const
{
	theEdges_.RetrieveTo(theEdges);
}

inline 
void AutLib::CadLib::Cad2d_PointOnPlane::ImportEdge(const Global_Handle(Cad2d_EdgeOnPlane) theEdge)
{
	theEdges_.Insert((Global_Handle(Cad2d_EdgeOnPlane))theEdge);
}