#pragma once
inline
AutLib::GeoLib::SubDivide_QuadTreeNode::SubDivide_QuadTreeNode()
{
}

inline 
AutLib::GeoLib::SubDivide_QuadTreeNode::SubDivide_QuadTreeNode
(
	const Standard_Integer Level, 
	const Entity_Box2d & Box
)
	: theLevel_(Level)
	, theBox_(Box)
	, theNePointer_(0)
	, theNwPointer_(0)
	, theSePointer_(0)
	, theSwPointer_(0)
{
}

inline 
Global_Handle(M_GEO SubDivide_QuadTreeNode) AutLib::GeoLib::SubDivide_QuadTreeNode::SwPointer() const
{
	return theSwPointer_;
}

inline 
Global_Handle(M_GEO SubDivide_QuadTreeNode) AutLib::GeoLib::SubDivide_QuadTreeNode::SePointer() const
{
	return theSePointer_;
}

inline 
Global_Handle(M_GEO SubDivide_QuadTreeNode) AutLib::GeoLib::SubDivide_QuadTreeNode::NwPointer() const
{
	return theNwPointer_;
}

inline 
Global_Handle(M_GEO SubDivide_QuadTreeNode) AutLib::GeoLib::SubDivide_QuadTreeNode::NePointer() const
{
	return theNePointer_;
}

inline 
Global_Handle(M_GEO SubDivide_QuadTreeNode) AutLib::GeoLib::SubDivide_QuadTreeNode::Father() const
{
	return theFather_;
}

inline
Global_Handle(M_GEO SubDivide_QuadTreeNode)& AutLib::GeoLib::SubDivide_QuadTreeNode::SwPointer()
{
	return theSwPointer_;
}

inline
Global_Handle(M_GEO SubDivide_QuadTreeNode)& AutLib::GeoLib::SubDivide_QuadTreeNode::SePointer() 
{
	return theSePointer_;
}

inline
Global_Handle(M_GEO SubDivide_QuadTreeNode)& AutLib::GeoLib::SubDivide_QuadTreeNode::NwPointer()
{
	return theNwPointer_;
}

inline
Global_Handle(M_GEO SubDivide_QuadTreeNode)& AutLib::GeoLib::SubDivide_QuadTreeNode::NePointer()
{
	return theNePointer_;
}

inline 
Global_Handle(M_GEO SubDivide_QuadTreeNode)& AutLib::GeoLib::SubDivide_QuadTreeNode::Father()
{
	return theFather_;
}

inline 
Standard_Integer AutLib::GeoLib::SubDivide_QuadTreeNode::Level() const
{
	return theLevel_;
}

inline 
const M_GEO Entity_Box2d & AutLib::GeoLib::SubDivide_QuadTreeNode::Box() const
{
	return theBox_;
}

inline 
void AutLib::GeoLib::SubDivide_QuadTreeNode::SetBox(const Entity_Box2d & Box)
{
	theBox_ = Box;
}

inline 
void AutLib::GeoLib::SubDivide_QuadTreeNode::SetLevel(const Standard_Integer Value)
{
	theLevel_ = Value;
}

inline 
void AutLib::GeoLib::SubDivide_QuadTreeNode::SetPointers
(
	Global_Handle(SubDivide_QuadTreeNode) Sw, 
	Global_Handle(SubDivide_QuadTreeNode) Se,
	Global_Handle(SubDivide_QuadTreeNode) Nw,
	Global_Handle(SubDivide_QuadTreeNode) Ne
)
{
	theSwPointer_ = Sw;
	theSePointer_ = Se;
	theNwPointer_ = Nw;
	theNePointer_ = Ne;
}

inline 
void AutLib::GeoLib::SubDivide_QuadTreeNode::SetSwPointer(Global_Handle(SubDivide_QuadTreeNode) Pointer)
{
	theSwPointer_ = Pointer;
}

inline 
void AutLib::GeoLib::SubDivide_QuadTreeNode::SetSePointer(Global_Handle(SubDivide_QuadTreeNode) Pointer)
{
	theSePointer_ = Pointer;
}

inline 
void AutLib::GeoLib::SubDivide_QuadTreeNode::SetNwPointer(Global_Handle(SubDivide_QuadTreeNode) Pointer)
{
	theNwPointer_ = Pointer;
}

inline 
void AutLib::GeoLib::SubDivide_QuadTreeNode::SetNePointer(Global_Handle(SubDivide_QuadTreeNode) Pointer)
{
	theNePointer_ = Pointer;
}

inline 
void AutLib::GeoLib::SubDivide_QuadTreeNode::SetFather(Global_Handle(SubDivide_QuadTreeNode) Pointer)
{
	theFather_ = Pointer;
}