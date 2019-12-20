#pragma once
inline
AutLib::GeoLib::Entity_Edge2d::Entity_Edge2d()
	: IsOnBoundary_(Standard_False)
	, theRight_(NULL)
	, theLeft_(NULL)
{
}

inline 
AutLib::GeoLib::Entity_Edge2d::Entity_Edge2d
(
	const Standard_Integer Index,
	Global_Handle(Entity_Node2d) Node0,
	Global_Handle(Entity_Node2d) Node1
)
	: theIndex_(Index)
{
	theNodes_[0] = Node0;
	theNodes_[1] = Node1;
}

inline 
Standard_Integer AutLib::GeoLib::Entity_Edge2d::Index() const
{
	return theIndex_;
}

inline 
Standard_Boolean AutLib::GeoLib::Entity_Edge2d::IsOnBoundary() const
{
	return IsOnBoundary_;
}

inline 
Global_Handle(M_GEO Entity_Node2d) AutLib::GeoLib::Entity_Edge2d::Node(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 1);
	return theNodes_[Index];
}

inline 
Global_Handle(M_GEO Entity_Node2d)& AutLib::GeoLib::Entity_Edge2d::Node(const Standard_Integer Index)
{
	Debug_Bad_Index(Index, 0, 1);
	return theNodes_[Index];
}

inline 
Global_Handle(M_GEO Entity_Element2d) AutLib::GeoLib::Entity_Edge2d::RightElement() const
{
	return theRight_;
}

inline 
Global_Handle(M_GEO Entity_Element2d) AutLib::GeoLib::Entity_Edge2d::LeftElement() const
{
	return theLeft_;
}

inline 
void AutLib::GeoLib::Entity_Edge2d::SetIndex(const Standard_Integer Index)
{
	theIndex_ = Index;
}

inline 
void AutLib::GeoLib::Entity_Edge2d::SetNode(const Standard_Integer Index, Global_Handle(Entity_Node2d) Node)
{
	Debug_Bad_Index(Index, 0, 1);
	theNodes_[Index] = Node;
}

inline
void AutLib::GeoLib::Entity_Edge2d::SetLeftElement(Global_Handle(Entity_Element2d) Element)
{
	theLeft_ = Element;
}

inline 
void AutLib::GeoLib::Entity_Edge2d::SetRightElement(Global_Handle(Entity_Element2d) Element)
{
	theRight_ = Element;
}

inline 
void AutLib::GeoLib::Entity_Edge2d::SetAsBoundary()
{
	IsOnBoundary_ = Standard_True;
}

inline 
void AutLib::GeoLib::Entity_Edge2d::SetAsNonBoundary()
{
	IsOnBoundary_ = Standard_False;
}