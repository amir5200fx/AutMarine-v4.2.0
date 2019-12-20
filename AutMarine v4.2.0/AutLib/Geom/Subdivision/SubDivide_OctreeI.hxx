#pragma once
#include <Geometry_Intersect.hxx>
#include <IO_Tecplot.hxx>


template<typename T>
inline AutLib::GeoLib::SubDivide_Octree<T>::SubDivide_Octree()
	: theRoot_(0)
{
}

template<typename T>
inline AutLib::GeoLib::SubDivide_Octree<T>::SubDivide_Octree
(
	const Entity_Box3d & Domain, 
	const Global_Handle(T) Object, 
	Standard_Boolean(*Subdivider)(const Entity_Box3d &, const Global_Handle(T))
)
	: theDomain_(Domain)
	, theObject_(Object)
	, theSubdivider(Subdivider)
	, theRoot_(0)
	, theMin_Level_(2)
	, theMax_Level_(5)
{
}

template<typename T>
inline AutLib::GeoLib::SubDivide_Octree<T>::~SubDivide_Octree()
{
	Clear(theRoot_);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_Octree<T>::SetDomain(const Entity_Box3d & Domain)
{
	theDomain_ = Domain;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_Octree<T>::SetObject(const Global_Handle(T) Object)
{
	theObject_ = Object;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_Octree<T>::SetSubDivider(Standard_Boolean(*Subdivider)(const Entity_Box3d &, const Global_Handle(T)))
{
	theSubdivider = Subdivider;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_Octree<T>::SetMaxLevel(const Standard_Integer Value)
{
	theMax_Level_ = Value;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_Octree<T>::SetMinLevel(const Standard_Integer Value)
{
	theMin_Level_ = Value;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_Octree<T>::Init()
{
	theRoot_ = CreateNode(0, theDomain_);

	ForceDivide(theRoot_);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_Octree<T>::Perform(const TColSubDivide_HAray1OfOctreeNode & Nodes)
{
	Debug_If_Condition(NOT theSubdivider);

	forThose(Index, 0, MaxIndexOf(Nodes))
	{
		SubDivide(Nodes[Index]);
	}
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_Octree<T>::Perform()
{
	TColSubDivide_HAray1OfOctreeNode Nodes;

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
inline void AutLib::GeoLib::SubDivide_Octree<T>::RetrieveTo(TColEntity_HAry1dOfBox3d & Boxes) const
{
	TColSubDivide_HBasicQueueOfOctreeNode QNodes;

	RetrieveTo(theRoot_, QNodes);

	Global_Handle(SubDivide_OctreeNode) NodePtr(0);

	Boxes.Resize(QNodes.Size());

	Standard_Integer K = 0;

	while (QNodes.DeQueue(NodePtr))
	{
		Boxes[K++] = const_cast<Global_Handle(Entity_Box3d)>(&NodePtr->Box());
	}
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_Octree<T>::RetrieveTo(TColSubDivide_HAray1OfOctreeNode & Nodes) const
{
	TColSubDivide_HBasicQueueOfOctreeNode QNodes;

	RetrieveTo(theRoot_, QNodes);

	QNodes.RetrieveTo(Nodes);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_Octree<T>::Search(const Entity_Box3d & Box, TColSubDivide_HAray1OfOctreeNode & Nodes) const
{
	TColSubDivide_HBasicQueueOfOctreeNode QNodes;

	Search(Box, theRoot_, QNodes);

	QNodes.RetrieveTo(Nodes);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_Octree<T>::ExportToPlt(fstream & File) const
{
	TColEntity_HAry1dOfBox3d Boxes;

	RetrieveTo(Boxes);

	M_IO IO_TecPlot::ExportBox(Boxes, File);
}

template<typename T>
inline Global_Handle(M_GEO SubDivide_OctreeNode) AutLib::GeoLib::SubDivide_Octree<T>::CreateNode(const Standard_Integer Level, const Entity_Box3d & Box) const
{
	return new SubDivide_OctreeNode(Level, Box);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_Octree<T>::SubDivide(Global_Handle(SubDivide_OctreeNode)& Node)
{
	if (Node->Level() > theMax_Level_)
		return;

	if (theSubdivider(Node->Box(), theObject_))
	{
		Standard_Integer Level = Node->Level();

		Get_Const_Object(Box) = Node->Box();

		Node->SetBwd_SwPointer(CreateNode(Level + 1, Box.Bwd_SwOctant()));

		SubDivide(Node->Bwd_SwPointer());

		Node->SetBwd_SePointer(CreateNode(Level + 1, Box.Bwd_SeOctant()));

		SubDivide(Node->Bwd_SePointer());

		Node->SetBwd_NePointer(CreateNode(Level + 1, Box.Bwd_NeOctant()));

		SubDivide(Node->Bwd_NePointer());

		Node->SetBwd_NwPointer(CreateNode(Level + 1, Box.Bwd_NwOctant()));

		SubDivide(Node->Bwd_NwPointer());

		Node->SetFwd_SwPointer(CreateNode(Level + 1, Box.Fwd_SwOctant()));

		SubDivide(Node->Fwd_SwPointer());

		Node->SetFwd_SePointer(CreateNode(Level + 1, Box.Fwd_SeOctant()));

		SubDivide(Node->Fwd_SePointer());

		Node->SetFwd_NePointer(CreateNode(Level + 1, Box.Fwd_NeOctant()));

		SubDivide(Node->Fwd_NePointer());

		Node->SetFwd_NwPointer(CreateNode(Level + 1, Box.Fwd_NwOctant()));

		SubDivide(Node->Fwd_NwPointer());
	}
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_Octree<T>::ForceDivide(Global_Handle(SubDivide_OctreeNode)& Node)
{
	if (Node->Level() > theMin_Level_)
		return;

	const Standard_Integer Level = Node->Level();

	Get_Const_Object(Box) = Node->Box();

	Node->SetBwd_SwPointer(CreateNode(Level + 1, Box.Bwd_SwOctant()));
	ForceDivide(Node->Bwd_SwPointer());

	Node->SetBwd_SePointer(CreateNode(Level + 1, Box.Bwd_SeOctant()));
	ForceDivide(Node->Bwd_SePointer());

	Node->SetBwd_NePointer(CreateNode(Level + 1, Box.Bwd_NeOctant()));
	ForceDivide(Node->Bwd_NePointer());

	Node->SetBwd_NwPointer(CreateNode(Level + 1, Box.Bwd_NwOctant()));
	ForceDivide(Node->Bwd_NwPointer());

	Node->SetFwd_SwPointer(CreateNode(Level + 1, Box.Fwd_SwOctant()));
	ForceDivide(Node->Fwd_SwPointer());

	Node->SetFwd_SePointer(CreateNode(Level + 1, Box.Fwd_SeOctant()));
	ForceDivide(Node->Fwd_SePointer());

	Node->SetFwd_NePointer(CreateNode(Level + 1, Box.Fwd_NeOctant()));
	ForceDivide(Node->Fwd_NePointer());

	Node->SetFwd_NwPointer(CreateNode(Level + 1, Box.Fwd_NwOctant()));
	ForceDivide(Node->Fwd_NwPointer());
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_Octree<T>::RetrieveTo
(
	Global_Handle(SubDivide_OctreeNode) Pointer,
	TColSubDivide_HBasicQueueOfOctreeNode & Nodes
) const
{
	if (Pointer->Bwd_SwPointer()) RetrieveTo(Pointer->Bwd_SwPointer(), Nodes);
	if (Pointer->Bwd_SePointer()) RetrieveTo(Pointer->Bwd_SePointer(), Nodes);
	if (Pointer->Bwd_NePointer()) RetrieveTo(Pointer->Bwd_NePointer(), Nodes);
	if (Pointer->Bwd_NwPointer()) RetrieveTo(Pointer->Bwd_NwPointer(), Nodes);
	if (Pointer->Fwd_SwPointer()) RetrieveTo(Pointer->Fwd_SwPointer(), Nodes);
	if (Pointer->Fwd_SePointer()) RetrieveTo(Pointer->Fwd_SePointer(), Nodes);
	if (Pointer->Fwd_NePointer()) RetrieveTo(Pointer->Fwd_NePointer(), Nodes);
	if (Pointer->Fwd_NwPointer()) RetrieveTo(Pointer->Fwd_NwPointer(), Nodes);

	if (IsNULL(Pointer->Bwd_SwPointer()) AND IsNULL(Pointer->Bwd_SePointer()) AND IsNULL(Pointer->Bwd_NePointer()) AND IsNULL(Pointer->Bwd_NwPointer()) AND IsNULL(Pointer->Fwd_SwPointer()) AND IsNULL(Pointer->Fwd_SePointer()) AND IsNULL(Pointer->Fwd_NePointer()) AND IsNULL(Pointer->Fwd_NwPointer()))
		Nodes.EnQueue(Pointer);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_Octree<T>::RetrieveTo
(
	Global_Handle(SubDivide_OctreeNode) Pointer,
	TColEntity_HBasicQueueOfBox3d & Boxes
) const
{
	if (Pointer->Bwd_SwPointer()) RetrieveTo(Pointer->Bwd_SwPointer(), Boxes);
	if (Pointer->Bwd_SePointer()) RetrieveTo(Pointer->Bwd_SePointer(), Boxes);
	if (Pointer->Bwd_NePointer()) RetrieveTo(Pointer->Bwd_NePointer(), Boxes);
	if (Pointer->Bwd_NwPointer()) RetrieveTo(Pointer->Bwd_NwPointer(), Boxes);
	if (Pointer->Fwd_SwPointer()) RetrieveTo(Pointer->Fwd_SwPointer(), Boxes);
	if (Pointer->Fwd_SePointer()) RetrieveTo(Pointer->Fwd_SePointer(), Boxes);
	if (Pointer->Fwd_NePointer()) RetrieveTo(Pointer->Fwd_NePointer(), Boxes);
	if (Pointer->Fwd_NwPointer()) RetrieveTo(Pointer->Fwd_NwPointer(), Boxes);

	if (IsNULL(Pointer->Bwd_SwPointer()))
		Boxes.EnQueue(new Entity_Box3d(Pointer->Box().Bwd_SwOctant()));

	if (IsNULL(Pointer->Bwd_SePointer()))
		Boxes.EnQueue(new Entity_Box3d(Pointer->Box().Bwd_SeOctant()));

	if (IsNULL(Pointer->Bwd_NePointer()))
		Boxes.EnQueue(new Entity_Box3d(Pointer->Box().Bwd_NeOctant()));

	if (IsNULL(Pointer->Bwd_NwPointer()))
		Boxes.EnQueue(new Entity_Box3d(Pointer->Box().Bwd_NwOctant()));

	if (IsNULL(Pointer->Fwd_SwPointer()))
		Boxes.EnQueue(new Entity_Box3d(Pointer->Box().Fwd_SwOctant()));

	if (IsNULL(Pointer->Fwd_SePointer()))
		Boxes.EnQueue(new Entity_Box3d(Pointer->Box().Fwd_SeOctant()));

	if (IsNULL(Pointer->Fwd_NePointer()))
		Boxes.EnQueue(new Entity_Box3d(Pointer->Box().Fwd_NeOctant()));

	if (IsNULL(Pointer->Fwd_NwPointer()))
		Boxes.EnQueue(new Entity_Box3d(Pointer->Box().Fwd_NwOctant()));
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_Octree<T>::Clear(Global_Handle(SubDivide_OctreeNode)& Pointer)
{
	if (Pointer)
	{
		Clear(Pointer->Bwd_SwPointer());
		Clear(Pointer->Bwd_SePointer());
		Clear(Pointer->Bwd_NePointer());
		Clear(Pointer->Bwd_NwPointer());
		Clear(Pointer->Fwd_SwPointer());
		Clear(Pointer->Fwd_SePointer());
		Clear(Pointer->Fwd_NePointer());
		Clear(Pointer->Fwd_NwPointer());

		Delete_Pointer(Pointer);
	}
}