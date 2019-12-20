#pragma once
inline
AutLib::GeoLib::SubDivide_OctreeNode::SubDivide_OctreeNode()
	: theBwd_NePointer_(NULL)
	, theBwd_NwPointer_(NULL)
	, theBwd_SePointer_(NULL)
	, theBwd_SwPointer_(NULL)
	, theFwd_NePointer_(NULL)
	, theFwd_NwPointer_(NULL)
	, theFwd_SePointer_(NULL)
	, theFwd_SwPointer_(NULL)
{
}

inline 
AutLib::GeoLib::SubDivide_OctreeNode::SubDivide_OctreeNode
(
	const Standard_Integer Level,
	const Entity_Box3d & Box
)
	: theLevel_(Level)
	, theBox_(Box)
	, theBwd_NePointer_(NULL)
	, theBwd_NwPointer_(NULL)
	, theBwd_SePointer_(NULL)
	, theBwd_SwPointer_(NULL)
	, theFwd_NePointer_(NULL)
	, theFwd_NwPointer_(NULL)
	, theFwd_SePointer_(NULL)
	, theFwd_SwPointer_(NULL)
{
}

inline 
Global_Handle(M_GEO SubDivide_OctreeNode) AutLib::GeoLib::SubDivide_OctreeNode::Bwd_SwPointer() const
{
	return theBwd_SwPointer_;
}

inline 
Global_Handle(M_GEO SubDivide_OctreeNode) AutLib::GeoLib::SubDivide_OctreeNode::Bwd_SePointer() const
{
	return theBwd_SePointer_;
}

inline 
Global_Handle(M_GEO SubDivide_OctreeNode) AutLib::GeoLib::SubDivide_OctreeNode::Bwd_NePointer() const
{
	return theBwd_NePointer_;
}

inline 
Global_Handle(M_GEO SubDivide_OctreeNode) AutLib::GeoLib::SubDivide_OctreeNode::Bwd_NwPointer() const
{
	return theBwd_NwPointer_;
}

inline
Global_Handle(M_GEO SubDivide_OctreeNode) AutLib::GeoLib::SubDivide_OctreeNode::Fwd_SwPointer() const
{
	return theFwd_SwPointer_;
}

inline
Global_Handle(M_GEO SubDivide_OctreeNode) AutLib::GeoLib::SubDivide_OctreeNode::Fwd_SePointer() const
{
	return theFwd_SePointer_;
}

inline
Global_Handle(M_GEO SubDivide_OctreeNode) AutLib::GeoLib::SubDivide_OctreeNode::Fwd_NePointer() const
{
	return theFwd_NePointer_;
}

inline
Global_Handle(M_GEO SubDivide_OctreeNode) AutLib::GeoLib::SubDivide_OctreeNode::Fwd_NwPointer() const
{
	return theFwd_NwPointer_;
}

inline
Global_Handle(M_GEO SubDivide_OctreeNode)& AutLib::GeoLib::SubDivide_OctreeNode::Bwd_SwPointer()
{
	return theBwd_SwPointer_;
}

inline
Global_Handle(M_GEO SubDivide_OctreeNode)& AutLib::GeoLib::SubDivide_OctreeNode::Bwd_SePointer()
{
	return theBwd_SePointer_;
}

inline
Global_Handle(M_GEO SubDivide_OctreeNode)& AutLib::GeoLib::SubDivide_OctreeNode::Bwd_NePointer()
{
	return theBwd_NePointer_;
}

inline
Global_Handle(M_GEO SubDivide_OctreeNode)& AutLib::GeoLib::SubDivide_OctreeNode::Bwd_NwPointer()
{
	return theBwd_NwPointer_;
}

inline
Global_Handle(M_GEO SubDivide_OctreeNode)& AutLib::GeoLib::SubDivide_OctreeNode::Fwd_SwPointer()
{
	return theFwd_SwPointer_;
}

inline
Global_Handle(M_GEO SubDivide_OctreeNode)& AutLib::GeoLib::SubDivide_OctreeNode::Fwd_SePointer()
{
	return theFwd_SePointer_;
}

inline
Global_Handle(M_GEO SubDivide_OctreeNode)& AutLib::GeoLib::SubDivide_OctreeNode::Fwd_NePointer()
{
	return theFwd_NePointer_;
}

inline
Global_Handle(M_GEO SubDivide_OctreeNode)& AutLib::GeoLib::SubDivide_OctreeNode::Fwd_NwPointer()
{
	return theFwd_NwPointer_;
}

inline 
Standard_Integer AutLib::GeoLib::SubDivide_OctreeNode::Level() const
{
	return theLevel_;
}

inline 
const M_GEO Entity_Box3d & AutLib::GeoLib::SubDivide_OctreeNode::Box() const
{
	return theBox_;
}

inline 
void AutLib::GeoLib::SubDivide_OctreeNode::SetBox(const Entity_Box3d & Box)
{
	theBox_ = Box;
}

inline
void AutLib::GeoLib::SubDivide_OctreeNode::SetLevel(const Standard_Integer Value)
{
	theLevel_ = Value;
}

inline 
void AutLib::GeoLib::SubDivide_OctreeNode::Init
(
	Global_Handle(SubDivide_OctreeNode) theBwd_SwPointer,
	Global_Handle(SubDivide_OctreeNode) theBwd_SePointer,
	Global_Handle(SubDivide_OctreeNode) theBwd_NePointer,
	Global_Handle(SubDivide_OctreeNode) theBwd_NwPointer,
	Global_Handle(SubDivide_OctreeNode) theFwd_SwPointer,
	Global_Handle(SubDivide_OctreeNode) theFwd_SePointer,
	Global_Handle(SubDivide_OctreeNode) theFwd_NePointer,
	Global_Handle(SubDivide_OctreeNode) theFwd_NwPointer
)
{
	theBwd_NePointer_ = theBwd_NePointer;
	theBwd_NwPointer_ = theBwd_NwPointer;
	theBwd_SePointer_ = theBwd_SePointer;
	theBwd_SwPointer_ = theBwd_SwPointer;

	theFwd_NePointer_ = theFwd_NePointer;
	theFwd_NwPointer_ = theFwd_NwPointer;
	theFwd_SePointer_ = theFwd_SePointer;
	theFwd_SwPointer_ = theFwd_SwPointer;
}

inline
void AutLib::GeoLib::SubDivide_OctreeNode::SetBwd_SwPointer(Global_Handle(SubDivide_OctreeNode) thePointer)
{
	theBwd_SwPointer_ = thePointer;
}

inline 
void AutLib::GeoLib::SubDivide_OctreeNode::SetBwd_SePointer(Global_Handle(SubDivide_OctreeNode) thePointer)
{
	theBwd_SePointer_ = thePointer;
}

inline 
void AutLib::GeoLib::SubDivide_OctreeNode::SetBwd_NePointer(Global_Handle(SubDivide_OctreeNode) thePointer)
{
	theBwd_NePointer_ = thePointer;
}

inline 
void AutLib::GeoLib::SubDivide_OctreeNode::SetBwd_NwPointer(Global_Handle(SubDivide_OctreeNode) thePointer)
{
	theBwd_NwPointer_ = thePointer;
}

inline
void AutLib::GeoLib::SubDivide_OctreeNode::SetFwd_SwPointer(Global_Handle(SubDivide_OctreeNode) thePointer)
{
	theFwd_SwPointer_ = thePointer;
}

inline
void AutLib::GeoLib::SubDivide_OctreeNode::SetFwd_SePointer(Global_Handle(SubDivide_OctreeNode) thePointer)
{
	theFwd_SePointer_ = thePointer;
}

inline
void AutLib::GeoLib::SubDivide_OctreeNode::SetFwd_NePointer(Global_Handle(SubDivide_OctreeNode) thePointer)
{
	theFwd_NePointer_ = thePointer;
}

inline
void AutLib::GeoLib::SubDivide_OctreeNode::SetFwd_NwPointer(Global_Handle(SubDivide_OctreeNode) thePointer)
{
	theFwd_NwPointer_ = thePointer;
}