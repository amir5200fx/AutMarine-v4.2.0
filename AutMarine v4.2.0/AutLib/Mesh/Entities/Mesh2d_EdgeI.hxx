#pragma once
inline
AutLib::MeshLib::Mesh2d_Edge::Mesh2d_Edge()
	: theRight_(NULL)
	, theLeft_(NULL)
{
	theNodes_[0] = NULL;
	theNodes_[1] = NULL;
}

inline 
AutLib::MeshLib::Mesh2d_Edge::Mesh2d_Edge
(
	const Standard_Integer Index,
	const Standard_Real Length,
	const Geom_Pnt2d & Centre,
	Global_Handle(Mesh2d_Node) Node0,
	Global_Handle(Mesh2d_Node) Node1
)
	: theIndex_(Index)
	, theLength_(Length)
	, theCentre_(Centre)
	, theRight_(NULL)
	, theLeft_(NULL)
{
	theNodes_[0] = Node0;
	theNodes_[1] = Node1;
}

inline 
AutLib::MeshLib::Mesh2d_Edge::~Mesh2d_Edge()
{
}

inline 
Standard_Integer AutLib::MeshLib::Mesh2d_Edge::Index() const
{
	return theIndex_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh2d_Edge::Length() const
{
	return theLength_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh2d_Edge::SearchRadius() const
{
	return MAX(Node(0)->Radius(), Node(1)->Radius());
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_Edge::IsCavity() const
{
	return IsCavity_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_Edge::IsOnFront() const
{
	return Node(0)->IsContainAtFront(const_cast<Global_Handle(Mesh2d_Edge)>(this));
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_Edge::IsOrphan() const
{
	return theLeft_ EQUAL NULL AND theRight_ EQUAL NULL;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh2d_Edge::NbElements() const
{
	Standard_Integer NbElements = 0;
	if (theLeft_) NbElements++;
	if (theRight_) NbElements++;
	return NbElements;
}

inline 
Global_Handle(Mesh2d_Node) AutLib::MeshLib::Mesh2d_Edge::Node0() const
{
	return theNodes_[0];
}

inline 
Global_Handle(Mesh2d_Node) AutLib::MeshLib::Mesh2d_Edge::Node1() const
{
	return theNodes_[1];
}

inline 
Global_Handle(M_MESH Mesh2d_Node) AutLib::MeshLib::Mesh2d_Edge::Node(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, 1);

	return theNodes_[Index];
}

inline 
Global_Handle(M_MESH Mesh2d_Node)& AutLib::MeshLib::Mesh2d_Edge::Node(const Standard_Integer Index)
{
	Debug_Bad_Index(Index, 0, 1);

	return theNodes_[Index];
}

inline 
Global_Handle(M_MESH Mesh2d_Element) AutLib::MeshLib::Mesh2d_Edge::RightElement() const
{
	return theRight_;
}

inline 
Global_Handle(M_MESH Mesh2d_Element) AutLib::MeshLib::Mesh2d_Edge::LeftElement() const
{
	return theLeft_;
}

inline 
const Geom_Pnt2d & AutLib::MeshLib::Mesh2d_Edge::Centre() const
{
	return theCentre_;
}

inline
void AutLib::MeshLib::Mesh2d_Edge::Reverse()
{
	SWAP(theNodes_[0], theNodes_[1]);
	SWAP(theLeft_, theRight_);
}

inline 
void AutLib::MeshLib::Mesh2d_Edge::SetIndex(const Standard_Integer Index)
{
	theIndex_ = Index;
}

inline 
void AutLib::MeshLib::Mesh2d_Edge::SetLength(const Standard_Real Length)
{
	theLength_ = Length;
}

inline 
void AutLib::MeshLib::Mesh2d_Edge::SetCavity(const Standard_Boolean Cavity)
{
	IsCavity_ = Cavity;
}

inline 
void AutLib::MeshLib::Mesh2d_Edge::SetNode(const Standard_Integer Index, Global_Handle(Mesh2d_Node) Node)
{
	Debug_Bad_Index(Index, 0, 1);

	theNodes_[Index] = Node;
}

inline 
void AutLib::MeshLib::Mesh2d_Edge::SetLeftElement(Global_Handle(Mesh2d_Element) Element)
{
	theLeft_ = Element;
}

inline 
void AutLib::MeshLib::Mesh2d_Edge::SetRightElement(Global_Handle(Mesh2d_Element) Element)
{
	theRight_ = Element;
}

inline 
void AutLib::MeshLib::Mesh2d_Edge::SetCentre(const Geom_Pnt2d & Coord)
{
	theCentre_ = Coord;
}

inline 
void AutLib::MeshLib::Mesh2d_Edge::RemoveFromElements(Global_Handle(Mesh2d_Element) Element)
{
	if (theLeft_ EQUAL Element)
	{
		theLeft_ = NULL;
		return;
	}

	if (theRight_ EQUAL Element)
	{
		theRight_ = NULL;
		return;
	}

	THROW_STANDARD_EXCEPTION(" Element not found");
}