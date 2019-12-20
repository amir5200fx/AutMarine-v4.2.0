#pragma once
#include <Geometry_Intersect.hxx>
#include <IO_TecPlot.hxx>

template<typename T>
inline AutLib::GeoLib::SubDivide_QuadTree<T>::SubDivide_QuadTree()
	: theRoot_(0)
{
}

template<typename T>
inline AutLib::GeoLib::SubDivide_QuadTree<T>::SubDivide_QuadTree
(
	const Entity_Box2d & Domain,
	const Global_Handle(T) Object, 
	Standard_Boolean(*Subdivider)(const Entity_Box2d &, const Global_Handle(T))
)
	: theDomain_(Domain)
	, theObject_(Object)
	, theSubdivider(Subdivider)
	, theRoot_(0)
	, theMin_Level_(3)
	, theMax_Level_(7)
{
}

template<typename T>
inline AutLib::GeoLib::SubDivide_QuadTree<T>::~SubDivide_QuadTree()
{
	Clear(theRoot_);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_QuadTree<T>::SetDomain(const Entity_Box2d & Domain)
{
	theDomain_ = Domain;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_QuadTree<T>::SetObject(const Global_Handle(T) Object)
{
	theObject_ = Object;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_QuadTree<T>::SetSubDivider(Standard_Boolean(*Subdivider)(const Entity_Box2d &, const Global_Handle(T)))
{
	theSubdivider = Subdivider;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_QuadTree<T>::SetMaxLevel(const Standard_Integer Value)
{
	theMax_Level_ = Value;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_QuadTree<T>::SetMinLevel(const Standard_Integer Value)
{
	theMin_Level_ = Value;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_QuadTree<T>::Init()
{
	theRoot_ = CreateNode(0, theDomain_);

	theRoot_->SetFather(0);

	ForceDivide(theRoot_);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_QuadTree<T>::Perform(const TColSubDivide_HArray1OfQuadTreeNode & Nodes)
{
	Debug_If_Condition(NOT theSubdivider);

	forThose(Index, 0, MaxIndexOf(Nodes))
	{
		SubDivide(Nodes[Index]);
	}
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_QuadTree<T>::Perform()
{
	TColSubDivide_HArray1OfQuadTreeNode Nodes;

	RetrieveTo(Nodes);

	Debug_If_Condition(NOT theSubdivider);

	forThose
	(
		Index, 
		0, 
		MaxIndexOf(Nodes)
	)
	{
		SubDivide(Nodes[Index]);
	}
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_QuadTree<T>::RetrieveTo(TColEntity_HAry1dOfBox2d & Boxes) const
{
	TColSubDivide_HBasicQueueOfQuadTreeNode QNodes;

	RetrieveTo(theRoot_, QNodes);

	Global_Handle(SubDivide_QuadTreeNode) NodePtr(0);

	Boxes.Resize(QNodes.Size());

	Standard_Integer K = 0;

	while (QNodes.DeQueue(NodePtr))
	{
		Boxes[K++] = const_cast<Global_Handle(Entity_Box2d)>(&NodePtr->Box());
	}
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_QuadTree<T>::RetrieveTo(TColSubDivide_HArray1OfQuadTreeNode & Nodes) const
{
	TColSubDivide_HBasicQueueOfQuadTreeNode QNodes;

	RetrieveTo(theRoot_, QNodes);

	QNodes.RetrieveTo(Nodes);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_QuadTree<T>::Search
(
	const Entity_Box2d & Box,
	TColSubDivide_HArray1OfQuadTreeNode & Nodes
) const
{
	TColSubDivide_HBasicQueueOfQuadTreeNode QNodes;

	Search(Box, theRoot_, QNodes);

	QNodes.RetrieveTo(Nodes);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_QuadTree<T>::ExportToPlt(fstream & File) const
{
	TColEntity_HAry1dOfBox2d Boxes;

	RetrieveTo(Boxes);

	M_IO IO_TecPlot::ExportBox(Boxes, File);
}

template<typename T>
inline Global_Handle(M_GEO SubDivide_QuadTreeNode) AutLib::GeoLib::SubDivide_QuadTree<T>::CreateNode
(
	const Standard_Integer Level,
	const Entity_Box2d & Box
) const
{
	return new SubDivide_QuadTreeNode(Level, Box);
}

template<typename T>
inline Standard_Integer AutLib::GeoLib::SubDivide_QuadTree<T>::Quadrant(Global_Handle(SubDivide_QuadTreeNode) Pointer) const
{
	Global_Handle(SubDivide_QuadTreeNode) Father = Pointer->Father();

	if (NOT Father)
		return -1;

	if (Father->SwPointer() == Pointer)
		return SubDivide_QuadTreeQuadrant_SW;
	if (Father->SePointer() == Pointer)
		return SubDivide_QuadTreeQuadrant_SE;
	if (Father->NwPointer() == Pointer)
		return SubDivide_QuadTreeQuadrant_NW;
	if (Father->NePointer() == Pointer)
		return SubDivide_QuadTreeQuadrant_NE;

	CloseProgram(" Failed Identify Quadrant");

	return 0;  // Prevent compiler warning
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_QuadTree<T>::Balance(Global_Handle(SubDivide_QuadTreeNode)& Node)
{
	const Standard_Integer Quad = Quadrant(Node);

	Global_Handle(SubDivide_QuadTreeNode) UnBalanced = 0;

	while (Node->Father())
	{
		Node = Node->Father();

		if (Quad NOT_EQUAL Quadrant(Node))
		{
			UnBalanced = Node;

			break;
		}
	}

	if (UnBalanced)
	{
		Standard_Integer Level = UnBalanced->Level();

		Get_Const_Object(Box) = UnBalanced->Box();

		if (Quad == SubDivide_QuadTreeQuadrant_SW)
		{
			Debug_If_Condition(UnBalanced->SwPointer());

			UnBalanced->SetSwPointer(CreateNode(Level + 1, Box.SwQuarter()));
			UnBalanced->SwPointer()->SetFather(UnBalanced);
		}

		if (Quad == SubDivide_QuadTreeQuadrant_SE)
		{
			Debug_If_Condition(UnBalanced->SwPointer());

			UnBalanced->SetSePointer(CreateNode(Level + 1, Box.SeQuarter()));
			UnBalanced->SePointer()->SetFather(UnBalanced);
		}

		if (Quad == SubDivide_QuadTreeQuadrant_NW)
		{
			Debug_If_Condition(UnBalanced->NwPointer());

			UnBalanced->SetNwPointer(CreateNode(Level + 1, Box.NwQuarter()));
			UnBalanced->NwPointer()->SetFather(UnBalanced);
		}

		if (Quad == SubDivide_QuadTreeQuadrant_NE)
		{
			Debug_If_Condition(UnBalanced->NePointer());

			UnBalanced->SetNePointer(CreateNode(Level + 1, Box.NeQuarter()));
			UnBalanced->NePointer()->SetFather(UnBalanced);
		}
	}
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_QuadTree<T>::SubDivide(Global_Handle(SubDivide_QuadTreeNode)& Node)
{
	if (Node->Level() > theMax_Level_)
		return;

	if (theSubdivider(Node->Box(), theObject_))
	{
		Standard_Integer Level = Node->Level();

		Get_Const_Object(Box) = Node->Box();

		Node->SetSwPointer(CreateNode(Level + 1, Box.SwQuarter()));
		Node->SwPointer()->SetFather(Node);

		SubDivide(Node->SwPointer());

		Node->SetSePointer(CreateNode(Level + 1, Box.SeQuarter()));
		Node->SePointer()->SetFather(Node);

		SubDivide(Node->SePointer());

		Node->SetNwPointer(CreateNode(Level + 1, Box.NwQuarter()));
		Node->NwPointer()->SetFather(Node);

		SubDivide(Node->NwPointer());

		Node->SetNePointer(CreateNode(Level + 1, Box.NeQuarter()));
		Node->NePointer()->SetFather(Node);

		SubDivide(Node->NePointer());
	}
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_QuadTree<T>::ForceDivide(Global_Handle(SubDivide_QuadTreeNode)& Node)
{
	if (Node->Level() > theMin_Level_)
		return;

	Standard_Integer Level = Node->Level();

	Get_Const_Object(Box) = Node->Box();

	Node->SetSwPointer(CreateNode(Level + 1, Box.SwQuarter()));
	Node->SwPointer()->SetFather(Node);

	ForceDivide(Node->SwPointer());

	Node->SetSePointer(CreateNode(Level + 1, Box.SeQuarter()));
	Node->SePointer()->SetFather(Node);

	ForceDivide(Node->SePointer());

	Node->SetNwPointer(CreateNode(Level + 1, Box.NwQuarter()));
	Node->NwPointer()->SetFather(Node);

	ForceDivide(Node->NwPointer());

	Node->SetNePointer(CreateNode(Level + 1, Box.NeQuarter()));
	Node->NePointer()->SetFather(Node);

	ForceDivide(Node->NePointer());
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_QuadTree<T>::Search
(
	const Entity_Box2d & Box, 
	Global_Handle(SubDivide_QuadTreeNode) Pointer,
	TColSubDivide_HBasicQueueOfQuadTreeNode & Nodes
) const
{
	if (Geom_Intersect::IsIntersect(Box, Pointer->Box()))
	{
		if (Pointer->SwPointer()) Search(Box, Pointer->SwPointer(), Nodes);
		if (Pointer->SePointer()) Search(Box, Pointer->SePointer(), Nodes);
		if (Pointer->NwPointer()) Search(Box, Pointer->NwPointer(), Nodes);
		if (Pointer->NePointer()) Search(Box, Pointer->NePointer(), Nodes);

		if (IsNULL(Pointer->SwPointer()) AND IsNULL(Pointer->SePointer()) AND IsNULL(Pointer->NwPointer()) AND IsNULL(Pointer->NePointer()))
			Nodes.EnQueue(Pointer);
	}
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_QuadTree<T>::RetrieveTo
(
	Global_Handle(SubDivide_QuadTreeNode) Pointer,
	TColSubDivide_HBasicQueueOfQuadTreeNode & Nodes
) const
{
	if (Pointer->SwPointer()) RetrieveTo(Pointer->SwPointer(), Nodes);
	if (Pointer->SePointer()) RetrieveTo(Pointer->SePointer(), Nodes);
	if (Pointer->NwPointer()) RetrieveTo(Pointer->NwPointer(), Nodes);
	if (Pointer->NePointer()) RetrieveTo(Pointer->NePointer(), Nodes);

	if (IsNULL(Pointer->SwPointer()) AND IsNULL(Pointer->SePointer()) AND IsNULL(Pointer->NwPointer()) AND IsNULL(Pointer->NePointer()))
		Nodes.EnQueue(Pointer);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_QuadTree<T>::Clear(Global_Handle(SubDivide_QuadTreeNode)& Pointer)
{
	if (Pointer)
	{
		Clear(Pointer->SwPointer());
		Clear(Pointer->SePointer());
		Clear(Pointer->NwPointer());
		Clear(Pointer->NePointer());
		
		Delete_Pointer(Pointer);
	}
}