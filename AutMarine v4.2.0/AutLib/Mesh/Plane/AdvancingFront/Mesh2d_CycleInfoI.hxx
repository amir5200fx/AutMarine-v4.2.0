#pragma once
inline
Global_Handle(M_MESH Mesh2d_Node) AutLib::MeshLib::Mesh2d_CycleInfo::CreatedNode() const
{
	return theCreated_;
}

inline 
Global_Handle(M_MESH Mesh2d_Node) AutLib::MeshLib::Mesh2d_CycleInfo::ValidNode() const
{
	return theValid_;
}

inline 
Global_Handle(M_MESH Mesh2d_Edge) AutLib::MeshLib::Mesh2d_CycleInfo::Current() const
{
	return theCurrent_;
}

inline 
Global_Handle(M_MESH Mesh2d_Edge) AutLib::MeshLib::Mesh2d_CycleInfo::PairedEdge0() const
{
	return thePairedEdge0_;
}

inline 
Global_Handle(M_MESH Mesh2d_Edge) AutLib::MeshLib::Mesh2d_CycleInfo::PairedEdge1() const
{
	return thePairedEdge1_;
}

inline 
Global_Handle(M_MESH Mesh2d_Edge) AutLib::MeshLib::Mesh2d_CycleInfo::CreatedEdge0() const
{
	return theCreatedEdge0_;
}

inline 
Global_Handle(M_MESH Mesh2d_Edge) AutLib::MeshLib::Mesh2d_CycleInfo::CreatedEdge1() const
{
	return theCreatedEdge1_;
}

inline 
Global_Handle(M_MESH Mesh2d_Element) AutLib::MeshLib::Mesh2d_CycleInfo::CreatedElement() const
{
	return theCreatedElement_;
}

inline 
Global_Handle(M_MESH Mesh2d_Node)& AutLib::MeshLib::Mesh2d_CycleInfo::CreatedNode()
{
	return theCreated_;
}

inline 
Global_Handle(M_MESH Mesh2d_Edge)& AutLib::MeshLib::Mesh2d_CycleInfo::Current()
{
	return theCurrent_;
}

inline 
const M_MESH Mesh2d_PointCondition & AutLib::MeshLib::Mesh2d_CycleInfo::Condition() const
{
	return theNewPointCondition_;
}

inline 
const M_MESH Mesh2d_AftType & AutLib::MeshLib::Mesh2d_CycleInfo::Type() const
{
	return theType_;
}

inline 
const Geom_Pnt2d & AutLib::MeshLib::Mesh2d_CycleInfo::Coord() const
{
	return theCoord_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh2d_CycleInfo::ElementSize() const
{
	return theElementSize_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh2d_CycleInfo::SearchRadius() const
{
	return theSearchingRadius_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh2d_CycleInfo::SearchRadiusLevel1() const
{
	return theSearchingRadius1_;
}

inline
Standard_Real AutLib::MeshLib::Mesh2d_CycleInfo::SearchRadiusLevel2() const
{
	return theSearchingRadius2_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh2d_CycleInfo::MinDistanceFactor() const
{
	return theMinDistance_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_CycleInfo::IsAppended() const
{
	return IsAppendNewPoint_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_CycleInfo::IsPairedEdge0() const
{
	return thePairedEdge0_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_CycleInfo::IsPairedEdge1() const
{
	return thePairedEdge1_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_CycleInfo::IsCreatedEdge0() const
{
	return theCreatedEdge0_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_CycleInfo::IsCreatedEdge1() const
{
	return theCreatedEdge1_;
}

inline 
void AutLib::MeshLib::Mesh2d_CycleInfo::SetCreatedNode(Global_Handle(Mesh2d_Node) Node)
{
	theCreated_ = Node;
}

inline 
void AutLib::MeshLib::Mesh2d_CycleInfo::SetValidNode(Global_Handle(Mesh2d_Node) Node)
{
	theValid_ = Node;
}

inline
void AutLib::MeshLib::Mesh2d_CycleInfo::SetCurrent(Global_Handle(Mesh2d_Edge) Edge)
{
	theCurrent_ = Edge;
}

inline 
void AutLib::MeshLib::Mesh2d_CycleInfo::SetPairedEdge0(Global_Handle(Mesh2d_Edge) Edge)
{
	thePairedEdge0_ = Edge;
}

inline 
void AutLib::MeshLib::Mesh2d_CycleInfo::SetPairedEdge1(Global_Handle(Mesh2d_Edge) Edge)
{
	thePairedEdge1_ = Edge;
}

inline 
void AutLib::MeshLib::Mesh2d_CycleInfo::SetCreatedEdge0(Global_Handle(Mesh2d_Edge) Edge)
{
	theCreatedEdge0_ = Edge;
}

inline 
void AutLib::MeshLib::Mesh2d_CycleInfo::SetCreatedEdge1(Global_Handle(Mesh2d_Edge) Edge)
{
	theCreatedEdge1_ = Edge;
}

inline 
void AutLib::MeshLib::Mesh2d_CycleInfo::SetCreatedElement(Global_Handle(Mesh2d_Element) Element)
{
	theCreatedElement_ = Element;
}

inline 
void AutLib::MeshLib::Mesh2d_CycleInfo::SetCondition(Mesh2d_PointCondition Condition)
{
	theNewPointCondition_ = Condition;
}

inline 
void AutLib::MeshLib::Mesh2d_CycleInfo::SetType(Mesh2d_AftType Type)
{
	theType_ = Type;
}

inline 
void AutLib::MeshLib::Mesh2d_CycleInfo::SetCoord(Geom_Pnt2d & Coord)
{
	theCoord_ = Coord;
}

inline 
void AutLib::MeshLib::Mesh2d_CycleInfo::SetElementSize(const Standard_Real ElementSize)
{
	THROW_STANDARD_EXCEPTION_IF(ElementSize <= 0, " Bad Element Size");
	theElementSize_ = ElementSize;
}

inline 
void AutLib::MeshLib::Mesh2d_CycleInfo::SetSearchingRadius(const Standard_Real SearchingRadius)
{
	THROW_STANDARD_EXCEPTION_IF(SearchingRadius <= 0, " Bad Searching Radius");
	theSearchingRadius_ = SearchingRadius;
}

inline 
void AutLib::MeshLib::Mesh2d_CycleInfo::SetSearchingRadiusLevel1(const Standard_Real SearchingRadius)
{
	THROW_STANDARD_EXCEPTION_IF(SearchingRadius <= 0, " Bad Searching Radius");
	theSearchingRadius1_ = SearchingRadius;
}

inline
void AutLib::MeshLib::Mesh2d_CycleInfo::SetSearchingRadiusLevel2(const Standard_Real SearchingRadius)
{
	THROW_STANDARD_EXCEPTION_IF(SearchingRadius <= 0, " Bad Searching Radius");
	theSearchingRadius2_ = SearchingRadius;
}

inline 
void AutLib::MeshLib::Mesh2d_CycleInfo::SetMinDistanceFactor(const Standard_Real MinDistanceFactor)
{
	Debug_If_Condition(MinDistanceFactor <= 0);
	theMinDistance_ = MinDistanceFactor;
}

inline 
void AutLib::MeshLib::Mesh2d_CycleInfo::SetAppendedCondition(const Standard_Boolean AppendedCondition)
{
	IsAppendNewPoint_ = AppendedCondition;
}