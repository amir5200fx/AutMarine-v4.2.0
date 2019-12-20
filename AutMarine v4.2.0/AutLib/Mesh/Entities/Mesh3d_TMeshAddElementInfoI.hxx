#pragma once
#include <Global_Macros.hxx>
inline
Global_Handle(M_MESH Mesh3d_Node) AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::ValidNode() const
{
	return theValid_;
}

inline
Global_Handle(M_MESH Mesh3d_Facet) AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::Current() const
{
	return theCurrent_;
}

inline
Global_Handle(M_MESH Mesh3d_Facet) AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::PairedFacet0() const
{
	return thePairedFacet0_;
}

inline
Global_Handle(M_MESH Mesh3d_Facet) AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::PairedFacet1() const
{
	return thePairedFacet1_;
}

inline
Global_Handle(M_MESH Mesh3d_Facet) AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::PairedFacet2() const
{
	return thePairedFacet2_;
}

inline
Global_Handle(M_MESH Mesh3d_Facet) AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::CreatedFacet0() const
{
	return theCreatedFacet0_;
}

inline
Global_Handle(M_MESH Mesh3d_Facet) AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::CreatedFacet1() const
{
	return theCreatedFacet1_;
}

inline
Global_Handle(M_MESH Mesh3d_Facet) AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::CreatedFacet2() const
{
	return theCreatedFacet2_;
}

inline
Global_Handle(M_MESH Mesh3d_Edge) AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::PairedEdge3() const
{
	return thePairedEdge3_;
}

inline
Global_Handle(M_MESH Mesh3d_Edge) AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::PairedEdge4() const
{
	return thePairedEdge4_;
}

inline
Global_Handle(M_MESH Mesh3d_Edge) AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::PairedEdge5() const
{
	return thePairedEdge5_;
}

inline
Global_Handle(M_MESH Mesh3d_Edge) AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::CreatedEdge3() const
{
	return theCreatedEdge3_;
}

inline
Global_Handle(M_MESH Mesh3d_Edge) AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::CreatedEdge4() const
{
	return theCreatedEdge4_;
}

inline
Global_Handle(M_MESH Mesh3d_Edge) AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::CreatedEdge5() const
{
	return theCreatedEdge5_;
}

inline
Global_Handle(M_MESH Mesh3d_Element) AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::CreatedElement() const
{
	return theCreatedElement_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::IsPairedFacet0() const
{
	return thePairedFacet0_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::IsPairedFacet1() const
{
	return thePairedFacet1_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::IsPairedFacet2() const
{
	return thePairedFacet2_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::IsCreatedFacet0() const
{
	return theCreatedFacet0_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::IsCreatedFacet1() const
{
	return theCreatedFacet1_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::IsCreatedFacet2() const
{
	return theCreatedFacet2_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::IsPairedEdge3() const
{
	return thePairedEdge3_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::IsPairedEdge4() const
{
	return thePairedEdge4_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::IsPairedEdge5() const
{
	return thePairedEdge5_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::IsCreatedEdge3() const
{
	return theCreatedEdge3_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::IsCreatedEdge4() const
{
	return theCreatedEdge4_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::IsCreatedEdge5() const
{
	return theCreatedEdge5_;
}

inline
void AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::SetValidNode(Global_Handle(Mesh3d_Node) Node)
{
	theValid_ = Node;
}

inline
void AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::SetCurrent(Global_Handle(Mesh3d_Facet) Facet)
{
	theCurrent_ = Facet;
}

inline
void AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::SetPairedFacet0(Global_Handle(Mesh3d_Facet) Facet)
{
	thePairedFacet0_ = Facet;
}

inline
void AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::SetPairedFacet1(Global_Handle(Mesh3d_Facet) Facet)
{
	thePairedFacet1_ = Facet;
}

inline
void AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::SetPairedFacet2(Global_Handle(Mesh3d_Facet) Facet)
{
	thePairedFacet2_ = Facet;
}

inline
void AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::SetCreatedFacet0(Global_Handle(Mesh3d_Facet) Facet)
{
	theCreatedFacet0_ = Facet;
}

inline
void AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::SetCreatedFacet1(Global_Handle(Mesh3d_Facet) Facet)
{
	theCreatedFacet1_ = Facet;
}

inline
void AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::SetCreatedFacet2(Global_Handle(Mesh3d_Facet) Facet)
{
	theCreatedFacet2_ = Facet;
}

inline
void AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::SetPairedEdge3(Global_Handle(Mesh3d_Edge) Edge)
{
	thePairedEdge3_ = Edge;
}

inline
void AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::SetPairedEdge4(Global_Handle(Mesh3d_Edge) Edge)
{
	thePairedEdge4_ = Edge;
}

inline
void AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::SetPairedEdge5(Global_Handle(Mesh3d_Edge) Edge)
{
	thePairedEdge5_ = Edge;
}

inline
void AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::SetCreatedEdge3(Global_Handle(Mesh3d_Edge) Edge)
{
	theCreatedEdge3_ = Edge;
}

inline
void AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::SetCreatedEdge4(Global_Handle(Mesh3d_Edge) Edge)
{
	theCreatedEdge4_ = Edge;
}

inline
void AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::SetCreatedEdge5(Global_Handle(Mesh3d_Edge) Edge)
{
	theCreatedEdge5_ = Edge;
}

inline
void AutLib::MeshLib::Mesh3d_TMeshAddElementInfo::SetCreatedElement(Global_Handle(Mesh3d_Element) Element)
{
	theCreatedElement_ = Element;
}