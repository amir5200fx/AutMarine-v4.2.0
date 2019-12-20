#pragma once
inline
Global_Handle(M_MESH Mesh3d_Node) AutLib::MeshLib::Mesh3d_CycleInfo::CreatedNode() const
{
	return theCreated_;
}

inline 
Global_Handle(M_MESH Mesh3d_Node) AutLib::MeshLib::Mesh3d_CycleInfo::ValidNode() const
{
	return theValid_;
}

inline 
Global_Handle(M_MESH Mesh3d_Facet) AutLib::MeshLib::Mesh3d_CycleInfo::Current() const
{
	return theCurrent_;
}

inline 
Global_Handle(M_MESH Mesh3d_Facet) AutLib::MeshLib::Mesh3d_CycleInfo::PairedFacet0() const
{
	return thePairedFacet0_;
}

inline 
Global_Handle(M_MESH Mesh3d_Facet) AutLib::MeshLib::Mesh3d_CycleInfo::PairedFacet1() const
{
	return thePairedFacet1_;
}

inline 
Global_Handle(M_MESH Mesh3d_Facet) AutLib::MeshLib::Mesh3d_CycleInfo::PairedFacet2() const
{
	return thePairedFacet2_;
}

inline 
Global_Handle(M_MESH Mesh3d_Facet) AutLib::MeshLib::Mesh3d_CycleInfo::CreatedFacet0() const
{
	return theCreatedFacet0_;
}

inline 
Global_Handle(M_MESH Mesh3d_Facet) AutLib::MeshLib::Mesh3d_CycleInfo::CreatedFacet1() const
{
	return theCreatedFacet1_;
}

inline 
Global_Handle(M_MESH Mesh3d_Facet) AutLib::MeshLib::Mesh3d_CycleInfo::CreatedFacet2() const
{
	return theCreatedFacet2_;
}

inline 
Global_Handle(M_MESH Mesh3d_Edge) AutLib::MeshLib::Mesh3d_CycleInfo::PairedEdge3() const
{
	return thePairedEdge3_;
}

inline 
Global_Handle(M_MESH Mesh3d_Edge) AutLib::MeshLib::Mesh3d_CycleInfo::PairedEdge4() const
{
	return thePairedEdge4_;
}

inline 
Global_Handle(M_MESH Mesh3d_Edge) AutLib::MeshLib::Mesh3d_CycleInfo::PairedEdge5() const
{
	return thePairedEdge5_;
}

inline 
Global_Handle(M_MESH Mesh3d_Edge) AutLib::MeshLib::Mesh3d_CycleInfo::CreatedEdge3() const
{
	return theCreatedEdge3_;
}

inline 
Global_Handle(M_MESH Mesh3d_Edge) AutLib::MeshLib::Mesh3d_CycleInfo::CreatedEdge4() const
{
	return theCreatedEdge4_;
}

inline 
Global_Handle(M_MESH Mesh3d_Edge) AutLib::MeshLib::Mesh3d_CycleInfo::CreatedEdge5() const
{
	return theCreatedEdge5_;
}

inline 
Global_Handle(M_MESH Mesh3d_Element) AutLib::MeshLib::Mesh3d_CycleInfo::CreatedElement() const
{
	return theCreatedElement_;
}

inline 
Global_Handle(M_MESH Mesh3d_Node)& AutLib::MeshLib::Mesh3d_CycleInfo::CreatedNode()
{
	return theCreated_;
}

inline 
Global_Handle(M_MESH Mesh3d_Facet)& AutLib::MeshLib::Mesh3d_CycleInfo::Current()
{
	return theCurrent_;
}

inline 
M_AUT TColMesh3d_HAry1dOfNode & AutLib::MeshLib::Mesh3d_CycleInfo::Neighbors0()
{
	return theNeighbors0_;
}

inline 
M_AUT TColMesh3d_HAry1dOfNode & AutLib::MeshLib::Mesh3d_CycleInfo::Neighbors1()
{
	return theNeighbors1_;
}

inline 
M_AUT TColMesh3d_HAry1dOfNode & AutLib::MeshLib::Mesh3d_CycleInfo::Neighbors2()
{
	return theNeighbors2_;
}

inline 
const M_AUT TColMesh3d_HAry1dOfNode & AutLib::MeshLib::Mesh3d_CycleInfo::Neighbors0() const
{
	return theNeighbors0_;
}

inline 
const M_AUT TColMesh3d_HAry1dOfNode & AutLib::MeshLib::Mesh3d_CycleInfo::Neighbors1() const
{
	return theNeighbors1_;
}

inline 
const M_AUT TColMesh3d_HAry1dOfNode & AutLib::MeshLib::Mesh3d_CycleInfo::Neighbors2() const
{
	return theNeighbors2_;
}

inline
const M_MESH Mesh3d_PointCondition & AutLib::MeshLib::Mesh3d_CycleInfo::Condition() const
{
	return theNewPointCondition_;
}

inline 
const M_MESH Mesh3d_AftType & AutLib::MeshLib::Mesh3d_CycleInfo::Type() const
{
	return theType_;
}

inline 
const Geom_Pnt3d & AutLib::MeshLib::Mesh3d_CycleInfo::Coord() const
{
	return theCoord_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_CycleInfo::ElementSize() const
{
	return theElementSize_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_CycleInfo::SearchRadius() const
{
	return theSearchingRadius_;
}

inline
Standard_Real AutLib::MeshLib::Mesh3d_CycleInfo::SearchRadiusLevel1() const
{
	return theSearchingRadius1_;
}

inline
Standard_Real AutLib::MeshLib::Mesh3d_CycleInfo::SearchRadiusLevel2() const
{
	return theSearchingRadius2_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_CycleInfo::MinDistanceFactor() const
{
	return theMinDistance_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_CycleInfo::MinEdgeDistanceFactor() const
{
	return theMinEdgeDistance_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_CycleInfo::IsAppended() const
{
	return IsAppendNewPoint_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_CycleInfo::IsPairedFacet0() const
{
	return thePairedFacet0_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_CycleInfo::IsPairedFacet1() const
{
	return thePairedFacet1_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_CycleInfo::IsPairedFacet2() const
{
	return thePairedFacet2_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_CycleInfo::IsCreatedFacet0() const
{
	return theCreatedFacet0_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_CycleInfo::IsCreatedFacet1() const
{
	return theCreatedFacet1_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_CycleInfo::IsCreatedFacet2() const
{
	return theCreatedFacet2_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_CycleInfo::IsPairedEdge3() const
{
	return thePairedEdge3_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_CycleInfo::IsPairedEdge4() const
{
	return thePairedEdge4_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_CycleInfo::IsPairedEdge5() const
{
	return thePairedEdge5_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_CycleInfo::IsCreatedEdge3() const
{
	return theCreatedEdge3_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_CycleInfo::IsCreatedEdge4() const
{
	return theCreatedEdge4_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_CycleInfo::IsCreatedEdge5() const
{
	return theCreatedEdge5_;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetCreatedNode(Global_Handle(Mesh3d_Node) Node)
{
	theCreated_ = Node;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetValidNode(Global_Handle(Mesh3d_Node) Node)
{
	theValid_ = Node;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetCurrent(Global_Handle(Mesh3d_Facet) Facet)
{
	theCurrent_ = Facet;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetPairedFacet0(Global_Handle(Mesh3d_Facet) Facet)
{
	thePairedFacet0_ = Facet;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetPairedFacet1(Global_Handle(Mesh3d_Facet) Facet)
{
	thePairedFacet1_ = Facet;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetPairedFacet2(Global_Handle(Mesh3d_Facet) Facet)
{
	thePairedFacet2_ = Facet;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetCreatedFacet0(Global_Handle(Mesh3d_Facet) Facet)
{
	theCreatedFacet0_ = Facet;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetCreatedFacet1(Global_Handle(Mesh3d_Facet) Facet)
{
	theCreatedFacet1_ = Facet;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetCreatedFacet2(Global_Handle(Mesh3d_Facet) Facet)
{
	theCreatedFacet2_ = Facet;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetPairedEdge3(Global_Handle(Mesh3d_Edge) Edge)
{
	thePairedEdge3_ = Edge;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetPairedEdge4(Global_Handle(Mesh3d_Edge) Edge)
{
	thePairedEdge4_ = Edge;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetPairedEdge5(Global_Handle(Mesh3d_Edge) Edge)
{
	thePairedEdge5_ = Edge;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetCreatedEdge3(Global_Handle(Mesh3d_Edge) Edge)
{
	theCreatedEdge3_ = Edge;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetCreatedEdge4(Global_Handle(Mesh3d_Edge) Edge)
{
	theCreatedEdge4_ = Edge;
}

inline
void AutLib::MeshLib::Mesh3d_CycleInfo::SetCreatedEdge5(Global_Handle(Mesh3d_Edge) Edge)
{
	theCreatedEdge5_ = Edge;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetCreatedElement(Global_Handle(Mesh3d_Element) Element)
{
	theCreatedElement_ = Element;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetCondition(Mesh3d_PointCondition Condition)
{
	theNewPointCondition_ = Condition;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetType(Mesh3d_AftType Type)
{
	theType_ = Type;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetCoord(Geom_Pnt3d & Coord)
{
	theCoord_ = Coord;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetElementSize(const Standard_Real ElementSize)
{
	THROW_STANDARD_EXCEPTION_IF(ElementSize <= 0, " Bad Element Size");
	theElementSize_ = ElementSize;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetSearchingRadius(const Standard_Real SearchingRadius)
{
	THROW_STANDARD_EXCEPTION_IF(SearchingRadius <= 0, " Bad Searching Radius");
	theSearchingRadius_ = SearchingRadius;
}

inline
void AutLib::MeshLib::Mesh3d_CycleInfo::SetSearchingRadiusLevel1(const Standard_Real SearchingRadius)
{
	THROW_STANDARD_EXCEPTION_IF(SearchingRadius <= 0, " Bad Searching Radius");
	theSearchingRadius1_ = SearchingRadius;
}

inline
void AutLib::MeshLib::Mesh3d_CycleInfo::SetSearchingRadiusLevel2(const Standard_Real SearchingRadius)
{
	THROW_STANDARD_EXCEPTION_IF(SearchingRadius <= 0, " Bad Searching Radius");
	theSearchingRadius2_ = SearchingRadius;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetMinDistanceFactor(const Standard_Real MinDistanceFactor)
{
	Debug_If_Condition(MinDistanceFactor <= 0);
	theMinDistance_ = MinDistanceFactor;
}

inline 
void AutLib::MeshLib::Mesh3d_CycleInfo::SetAppendedCondition(const Standard_Boolean AppendedCondition)
{
	IsAppendNewPoint_ = AppendedCondition;
}
