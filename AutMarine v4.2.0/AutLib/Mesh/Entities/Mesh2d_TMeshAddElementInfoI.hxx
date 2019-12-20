#pragma once
#include <Global_Macros.hxx>
inline
Global_Handle(M_MESH Mesh2d_Node) AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::ValidNode() const
{
	return theValid_;
}

inline
Global_Handle(M_MESH Mesh2d_Edge) AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::Current() const
{
	return theCurrent_;
}

inline
Global_Handle(M_MESH Mesh2d_Edge) AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::PairedEdge0() const
{
	return thePairedEdge0_;
}

inline
Global_Handle(M_MESH Mesh2d_Edge) AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::PairedEdge1() const
{
	return thePairedEdge1_;
}

inline
Global_Handle(M_MESH Mesh2d_Edge) AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::CreatedEdge0() const
{
	return theCreatedEdge0_;
}

inline
Global_Handle(M_MESH Mesh2d_Edge) AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::CreatedEdge1() const
{
	return theCreatedEdge1_;
}

inline
Global_Handle(M_MESH Mesh2d_Element) AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::CreatedElement() const
{
	return theCreatedElement_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::IsPairedEdge0() const
{
	return thePairedEdge0_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::IsPairedEdge1() const
{
	return thePairedEdge1_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::IsCreatedEdge0() const
{
	return theCreatedEdge0_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::IsCreatedEdge1() const
{
	return theCreatedEdge1_;
}

inline
void AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::SetValidNode(Global_Handle(Mesh2d_Node) Node)
{
	theValid_ = Node;
}

inline
void AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::SetCurrent(Global_Handle(Mesh2d_Edge) Edge)
{
	theCurrent_ = Edge;
}

inline
void AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::SetPairedEdge0(Global_Handle(Mesh2d_Edge) Edge)
{
	thePairedEdge0_ = Edge;
}

inline
void AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::SetPairedEdge1(Global_Handle(Mesh2d_Edge) Edge)
{
	thePairedEdge1_ = Edge;
}

inline
void AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::SetCreatedEdge0(Global_Handle(Mesh2d_Edge) Edge)
{
	theCreatedEdge0_ = Edge;
}

inline
void AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::SetCreatedEdge1(Global_Handle(Mesh2d_Edge) Edge)
{
	theCreatedEdge1_ = Edge;
}

inline
void AutLib::MeshLib::Mesh2d_TMeshAddElementInfo::SetCreatedElement(Global_Handle(Mesh2d_Element) Element)
{
	theCreatedElement_ = Element;
}