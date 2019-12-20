#pragma once
inline
AutLib::GeoLib::Merge_Pnt2dNode::Merge_Pnt2dNode()
{
}

inline AutLib::GeoLib::Merge_Pnt2dNode::Merge_Pnt2dNode
(
	const Standard_Integer Index,
	const Geom_Pnt2d & Coord
)
	: theIndex_(Index)
	, theCoord_(Coord)
{
}

inline
Standard_Integer AutLib::GeoLib::Merge_Pnt2dNode::Index() const
{
	return theIndex_;
}

inline
const Geom_Pnt2d & AutLib::GeoLib::Merge_Pnt2dNode::Coord() const
{
	return theCoord_;
}

inline
void AutLib::GeoLib::Merge_Pnt2dNode::SetIndex(const Standard_Integer Index)
{
	theIndex_ = Index;
}

inline
void AutLib::GeoLib::Merge_Pnt2dNode::SetCoord(const Geom_Pnt2d & Coord)
{
	theCoord_ = Coord;
}