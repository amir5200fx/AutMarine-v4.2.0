#pragma once
inline
AutLib::GeoLib::Merge_Pnt3dNode::Merge_Pnt3dNode()
{
}

inline AutLib::GeoLib::Merge_Pnt3dNode::Merge_Pnt3dNode
(
	const Standard_Integer Index,
	const Geom_Pnt3d & Coord
)
	: theIndex_(Index)
	, theCoord_(Coord)
{
}

inline
Standard_Integer AutLib::GeoLib::Merge_Pnt3dNode::Index() const
{
	return theIndex_;
}

inline
const Geom_Pnt3d & AutLib::GeoLib::Merge_Pnt3dNode::Coord() const
{
	return theCoord_;
}

inline
void AutLib::GeoLib::Merge_Pnt3dNode::SetIndex(const Standard_Integer Index)
{
	theIndex_ = Index;
}

inline
void AutLib::GeoLib::Merge_Pnt3dNode::SetCoord(const Geom_Pnt3d & Coord)
{
	theCoord_ = Coord;
}