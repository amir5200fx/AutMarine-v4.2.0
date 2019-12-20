#pragma once
inline
Standard_Integer AutLib::GeoLib::Entity_StaticChain3d::NbPoints() const
{
	return thePts_.Length();
}

inline
Standard_Integer AutLib::GeoLib::Entity_StaticChain3d::NbEdges() const
{
	return theEdges_.Length();
}

inline
M_AUT TColGeom_Ary1dOfPnt3d & AutLib::GeoLib::Entity_StaticChain3d::Coords()
{
	return thePts_;
}

inline
M_AUT TColEntity_Ary1dOfEdgeIndex & AutLib::GeoLib::Entity_StaticChain3d::Edges()
{
	return theEdges_;
}

inline
const M_AUT TColGeom_Ary1dOfPnt3d & AutLib::GeoLib::Entity_StaticChain3d::Coords() const
{
	return thePts_;
}

inline
const M_AUT TColEntity_Ary1dOfEdgeIndex & AutLib::GeoLib::Entity_StaticChain3d::Edges() const
{
	return theEdges_;
}

inline
const Geom_Pnt3d & AutLib::GeoLib::Entity_StaticChain3d::Coord(const Standard_Integer Index) const
{
	Debug_Bad_Index_Array1(Index, thePts_);

	return thePts_[Index];
}

inline
const M_GEO Entity_EdgeIndex & AutLib::GeoLib::Entity_StaticChain3d::Edge(const Standard_Integer Index) const
{
	Debug_Bad_Index_Array1(Index, theEdges_);

	return theEdges_[Index];
}

inline
Standard_Boolean AutLib::GeoLib::Entity_StaticChain3d::IsCycle() const
{
	return IsCycle_;
}

inline
M_GEO Entity_StaticChain3d AutLib::GeoLib::Entity_StaticChain3d::Merged(const Standard_Real Resolution, const Standard_Real Radius) const
{
	Entity_StaticChain3d Copy = *this;
	Copy.Merging(Resolution, Radius);

	MOVE(Copy);
}