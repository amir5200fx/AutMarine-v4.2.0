#pragma once
#include <Geometry_Intersect.hxx>
#include <IO_Tecplot.hxx>

template<typename T>
inline AutLib::GeoLib::SubDivide_BalancedQuadTree<T>::SubDivide_BalancedQuadTree()
	: theRoot_(0)
	, theMin_Level_(3)
	, theMax_Level_(7)
{
}

template<typename T>
inline AutLib::GeoLib::SubDivide_BalancedQuadTree<T>::~SubDivide_BalancedQuadTree()
{
	Clear(theRoot_);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedQuadTree<T>::SetDomain(const Entity_Box2d & Domain)
{
	theDomain_ = Domain;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedQuadTree<T>::SetObject(const Global_Handle(T) Object)
{
	theObject_ = Object;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedQuadTree<T>::SetSubDivider(Standard_Boolean(*Subdivider)(const Entity_Box2d &, const Global_Handle(T)))
{
	theSubdivider = Subdivider;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedQuadTree<T>::SetMaxLevel(const Standard_Integer Value)
{
	theMax_Level_ = Value;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedQuadTree<T>::SetMinLevel(const Standard_Integer Value)
{
	theMin_Level_ = Value;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedQuadTree<T>::Init()
{
	theRoot_ = new SubDivide_QuadTreeNode(0, theDomain_);

	theRoot_->SetFather(0);

	ForceDivide(theRoot_);

	TColSubDivide_HArray1OfQuadTreeNode Nodes;

	RetrieveTo(Nodes);

	forThose(Index, 0, MaxIndexOf(Nodes))
		theTerminals_.EnQueue(Nodes[Index]);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedQuadTree<T>::Perform()
{
	Global_Handle(SubDivide_QuadTreeNode) Node(0);

	while (theTerminals_.DeQueue(Node))
	{
		if (Node->Level() > theMax_Level_)
			continue;

		Get_Const_Object(Box) = Node->Box();

		if (NOT Node->SwPointer())
		{
			if (theSubdivider(Box.SwQuarter(), theObject_))
			{
				CreateQuadrant(Node, SubDivide_QuadTreeQuadrant_SW);
			}
		}

		if (NOT Node->SePointer())
		{
			if (theSubdivider(Box.SeQuarter(), theObject_))
			{
				CreateQuadrant(Node, SubDivide_QuadTreeQuadrant_SE);
			}
		}

		if (NOT Node->NwPointer())
		{
			if (theSubdivider(Box.NwQuarter(), theObject_))
			{
				CreateQuadrant(Node, SubDivide_QuadTreeQuadrant_NW);
			}
		}

		if (NOT Node->NePointer())
		{
			if (theSubdivider(Box.NeQuarter(), theObject_))
			{
				CreateQuadrant(Node, SubDivide_QuadTreeQuadrant_NE);
			}
		}
	}
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedQuadTree<T>::ExportToPlt(fstream & File) const
{
	TColEntity_HAry1dOfBox2d Boxes;

	RetrieveTo(Boxes);

	M_IO IO_TecPlot::ExportBox(Boxes, File);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedQuadTree<T>::RetrieveTo(TColEntity_HAry1dOfBox2d & Boxes) const
{
	TColEntity_HBasicQueueOfBox2d Q;
	RetrieveTo(theRoot_, Q);

	Q.RetrieveTo(Boxes);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedQuadTree<T>::RetrieveTo(TColSubDivide_HArray1OfQuadTreeNode & Nodes) const
{
	TColSubDivide_HBasicQueueOfQuadTreeNode QNodes;

	RetrieveTo(theRoot_, QNodes);

	QNodes.RetrieveTo(Nodes);
}

template<typename T>
inline Standard_Integer AutLib::GeoLib::SubDivide_BalancedQuadTree<T>::FindQuadrant(Global_Handle(SubDivide_QuadTreeNode) Pointer) const
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
inline void AutLib::GeoLib::SubDivide_BalancedQuadTree<T>::ForceDivide(Global_Handle(SubDivide_QuadTreeNode)& Node)
{
	if (Node->Level() > theMin_Level_)
		return;

	const Standard_Integer Level = Node->Level();

	Get_Const_Object(Box) = Node->Box();

	Node->SwPointer() = new SubDivide_QuadTreeNode(Level + 1, Box.SwQuarter());
	Node->SwPointer()->SetFather(Node);

	ForceDivide(Node->SwPointer());

	Node->SePointer() = new SubDivide_QuadTreeNode(Level + 1, Box.SeQuarter());
	Node->SePointer()->SetFather(Node);

	ForceDivide(Node->SePointer());

	Node->NePointer() = new SubDivide_QuadTreeNode(Level + 1, Box.NeQuarter());
	Node->NePointer()->SetFather(Node);

	ForceDivide(Node->NePointer());

	Node->NwPointer() = new SubDivide_QuadTreeNode(Level + 1, Box.NwQuarter());
	Node->NwPointer()->SetFather(Node);

	ForceDivide(Node->NwPointer());
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedQuadTree<T>::Balance(Global_Handle(SubDivide_QuadTreeNode)& Node)
{
	const Standard_Integer Quad = FindQuadrant(Node);

	Global_Handle(SubDivide_QuadTreeNode) UnBalanced = 0;

	while (Node->Father())
	{
		Node = Node->Father();

		if (Quad NOT_EQUAL FindQuadrant(Node))
		{
			UnBalanced = Node->Father();

			break;
		}
	}

	if (UnBalanced)
	{
		if (Quad == SubDivide_QuadTreeQuadrant_SW)
		{
			CreateQuadrant(UnBalanced, SubDivide_QuadTreeQuadrant_SW);
		}

		if (Quad == SubDivide_QuadTreeQuadrant_SE)
		{
			CreateQuadrant(UnBalanced, SubDivide_QuadTreeQuadrant_SE);
		}

		if (Quad == SubDivide_QuadTreeQuadrant_NW)
		{
			CreateQuadrant(UnBalanced, SubDivide_QuadTreeQuadrant_NW);
		}

		if (Quad == SubDivide_QuadTreeQuadrant_NE)
		{
			CreateQuadrant(UnBalanced, SubDivide_QuadTreeQuadrant_NE);
		}
	}
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedQuadTree<T>::CreateQuadrant
(
	Global_Handle(SubDivide_QuadTreeNode)& Node, 
	const Standard_Integer Quadrant
)
{
	const Standard_Integer Level = Node->Level();

	Get_Const_Object(Box) = Node->Box();

	if (Quadrant == SubDivide_QuadTreeQuadrant_SW)
	{
		Node->SwPointer() = new SubDivide_QuadTreeNode(Level + 1, Box.SwQuarter());
		Node->SwPointer()->SetFather(Node);

		theTerminals_.EnQueue(Node->SwPointer());

		//Balance(Node->SwPointer());
	}

	if (Quadrant == SubDivide_QuadTreeQuadrant_SE)
	{
		Node->SePointer() = new SubDivide_QuadTreeNode(Level + 1, Box.SeQuarter());
		Node->SePointer()->SetFather(Node);

		theTerminals_.EnQueue(Node->SePointer());

		//Balance(Node->SePointer());
	}

	if (Quadrant == SubDivide_QuadTreeQuadrant_NE)
	{
		Node->NePointer() = new SubDivide_QuadTreeNode(Level + 1, Box.NeQuarter());
		Node->NePointer()->SetFather(Node);

		theTerminals_.EnQueue(Node->NePointer());

		//Balance(Node->NePointer());
	}

	if (Quadrant == SubDivide_QuadTreeQuadrant_NW)
	{
		Node->NwPointer() = new SubDivide_QuadTreeNode(Level + 1, Box.NwQuarter());
		Node->NwPointer()->SetFather(Node);

		theTerminals_.EnQueue(Node->NwPointer());

		//Balance(Node->NwPointer());
	}
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedQuadTree<T>::RetrieveTo
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
inline void AutLib::GeoLib::SubDivide_BalancedQuadTree<T>::RetrieveTo
(
	Global_Handle(SubDivide_QuadTreeNode) Pointer, 
	TColEntity_HBasicQueueOfBox2d & Boxes
) const
{
	if (Pointer->SwPointer()) RetrieveTo(Pointer->SwPointer(), Boxes);
	if (Pointer->SePointer()) RetrieveTo(Pointer->SePointer(), Boxes);
	if (Pointer->NwPointer()) RetrieveTo(Pointer->NwPointer(), Boxes);
	if (Pointer->NePointer()) RetrieveTo(Pointer->NePointer(), Boxes);

	if (IsNULL(Pointer->SwPointer()))
		Boxes.EnQueue(new Entity_Box2d(Pointer->Box().SwQuarter()));

	if (IsNULL(Pointer->SePointer()))
		Boxes.EnQueue(new Entity_Box2d(Pointer->Box().SeQuarter()));

	if (IsNULL(Pointer->NwPointer()))
		Boxes.EnQueue(new Entity_Box2d(Pointer->Box().NwQuarter()));

	if (IsNULL(Pointer->NePointer()))
		Boxes.EnQueue(new Entity_Box2d(Pointer->Box().NeQuarter()));
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedQuadTree<T>::Clear(Global_Handle(SubDivide_QuadTreeNode)& Pointer)
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