#pragma once
#include <Geometry_Intersect.hxx>
#include <IO_Tecplot.hxx>
template<typename T>
inline AutLib::GeoLib::SubDivide_BalancedOctree<T>::SubDivide_BalancedOctree()
	: theRoot_(0)
	, theMaxUnBalancing_(4)
	, IsBalancing_(Standard_False)
{
}

template<typename T>
inline AutLib::GeoLib::SubDivide_BalancedOctree<T>::SubDivide_BalancedOctree
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
	, theMaxUnBalancing_(4)
	, IsBalancing_(Standard_False)
{
}

template<typename T>
inline AutLib::GeoLib::SubDivide_BalancedOctree<T>::~SubDivide_BalancedOctree()
{
	Clear(theRoot_);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::SetDomain(const Entity_Box3d & Domain)
{
	theDomain_ = Domain;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::SetObject(const Global_Handle(T) Object)
{
	theObject_ = Object;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::SetSubDivider(Standard_Boolean(*Subdivider)(const Entity_Box3d &, const Global_Handle(T)))
{
	theSubdivider = Subdivider;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::SetMaxLevel(const Standard_Integer Value)
{
	theMax_Level_ = Value;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::SetMinLevel(const Standard_Integer Value)
{
	theMin_Level_ = Value;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::SetMaxUnBalancingLevel(const Standard_Integer Value)
{
	if (Value < 1) Value = 1;
	theMaxUnBalancing_ = 4 * Value;
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::Init()
{
	theRoot_ = CreateLeaf(0, theDomain_);

	ForceDivide(theRoot_);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::Perform(const TColSubDivide_HAray1OfBalancedOctreeNode & Nodes)
{
	Debug_If_Condition(NOT theSubdivider);

	forThose(Index, 0, MaxIndexOf(Nodes))
	{
		SubDivide(Nodes[Index]);
	}
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::Perform()
{
	TColSubDivide_HAray1OfBalancedOctreeNode Nodes;
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
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::PostBalancing()
{
	while (Standard_True)
	{
		IsBalancing_ = Standard_False;

		Balancing(theRoot_);

		if (NOT IsBalancing_) break;
	}
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::RetrieveTo(TColEntity_HAry1dOfBox3d & Boxes) const
{
	TColEntity_HBasicQueueOfBox3d Q;
	RetrieveTo(theRoot_, Q);
	Q.RetrieveTo(Boxes);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::RetrieveTo(TColSubDivide_HAray1OfBalancedOctreeNode & Nodes) const
{
	TColSubDivide_HBasicQueueOfBalancedOctreeNode QNodes;

	RetrieveTo(theRoot_, QNodes);

	QNodes.RetrieveTo(Nodes);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::ExportToPlt(fstream & File) const
{
	TColEntity_HAry1dOfBox3d Boxes;

	RetrieveTo(Boxes);

	M_IO IO_TecPlot::ExportBox(Boxes, File);
}

template<typename T>
inline Standard_Boolean AutLib::GeoLib::SubDivide_BalancedOctree<T>::DoSubdivide(SubDivide_BalancedOctreeLeaf * Leaf) const
{
	if (Leaf->theSNeighbors_.Size() > theMaxUnBalancing_) return Standard_True;
	if (Leaf->theENeighbors_.Size() > theMaxUnBalancing_) return Standard_True;
	if (Leaf->theNNeighbors_.Size() > theMaxUnBalancing_) return Standard_True;
	if (Leaf->theWNeighbors_.Size() > theMaxUnBalancing_) return Standard_True;
	if (Leaf->theFNeighbors_.Size() > theMaxUnBalancing_) return Standard_True;
	if (Leaf->theBNeighbors_.Size() > theMaxUnBalancing_) return Standard_True;

	return Standard_False;
}

template<typename T>
inline M_GEO SubDivide_OctreeOctant AutLib::GeoLib::SubDivide_BalancedOctree<T>::CalcOctant
(
	const Geom_Pnt3d & P, 
	const Geom_Pnt3d & Centre
) const
{
	if (P.X() <= Centre.X())
	{
		if (P.Y() <= Centre.Y())
		{
			if (P.Z() <= Centre.Z()) { return SubDivide_OctreeOctant_Bwd_SW; }
			else { return SubDivide_OctreeOctant_Fwd_SW; }
		}
		else
		{
			if (P.Z() <= Centre.Z()) { return SubDivide_OctreeOctant_Bwd_NW; }
			else { return SubDivide_OctreeOctant_Fwd_NW; }
		}
	}
	else
	{
		if (P.Y() <= Centre.Y())
		{
			if (P.Z() <= Centre.Z()) { return SubDivide_OctreeOctant_Bwd_SE; }
			else { return SubDivide_OctreeOctant_Fwd_SE; }
		}
		else
		{
			if (P.Z() <= Centre.Z()) { return SubDivide_OctreeOctant_Bwd_NE; }
			else { return SubDivide_OctreeOctant_Fwd_NE; }
		}
	}
}

template<typename T>
inline M_GEO SubDivide_BalancedOctreeLeaf * AutLib::GeoLib::SubDivide_BalancedOctree<T>::CreateLeaf(const Standard_Integer Level, const Entity_Box3d & Box) const
{
	return new SubDivide_BalancedOctreeLeaf(Level, Box);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::SubDivide(SubDivide_BalancedOctreeNode* & t)
{
	SubDivide_BalancedOctreeLeaf* Leaf = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(t);

	Debug_Null_Pointer(Leaf);

	if (Leaf->theLevel_ > theMax_Level_) return;

	if (theSubdivider(Leaf->theBox_, theObject_))
	{
		Standard_Integer Level = Leaf->theLevel_;
		const Entity_Box3d& Box = Leaf->theBox_;

		SubDivide_BalancedOctreeInternal* Internal = new SubDivide_BalancedOctreeInternal(Level);

		// Subdivide the Leaf
		SubDivide_BalancedOctreeLeaf* Fwd_SwPtr = CreateLeaf(Level + 1, Box.Fwd_SwOctant());
		SubDivide_BalancedOctreeLeaf* Fwd_SePtr = CreateLeaf(Level + 1, Box.Fwd_SeOctant());
		SubDivide_BalancedOctreeLeaf* Fwd_NePtr = CreateLeaf(Level + 1, Box.Fwd_NeOctant());
		SubDivide_BalancedOctreeLeaf* Fwd_NwPtr = CreateLeaf(Level + 1, Box.Fwd_NwOctant());
		SubDivide_BalancedOctreeLeaf* Bwd_SwPtr = CreateLeaf(Level + 1, Box.Bwd_SwOctant());
		SubDivide_BalancedOctreeLeaf* Bwd_SePtr = CreateLeaf(Level + 1, Box.Bwd_SeOctant());
		SubDivide_BalancedOctreeLeaf* Bwd_NePtr = CreateLeaf(Level + 1, Box.Bwd_NeOctant());
		SubDivide_BalancedOctreeLeaf* Bwd_NwPtr = CreateLeaf(Level + 1, Box.Bwd_NwOctant());

		Debug_Null_Pointer(Fwd_SwPtr);
		Debug_Null_Pointer(Fwd_SePtr);
		Debug_Null_Pointer(Fwd_NePtr);
		Debug_Null_Pointer(Fwd_NwPtr);
		Debug_Null_Pointer(Bwd_SwPtr);
		Debug_Null_Pointer(Bwd_SePtr);
		Debug_Null_Pointer(Bwd_NePtr);
		Debug_Null_Pointer(Bwd_NwPtr);

		Fwd_SwPtr->theFather_ = Internal;
		Fwd_SePtr->theFather_ = Internal;
		Fwd_NePtr->theFather_ = Internal;
		Fwd_NwPtr->theFather_ = Internal;
		Bwd_SwPtr->theFather_ = Internal;
		Bwd_SePtr->theFather_ = Internal;
		Bwd_NePtr->theFather_ = Internal;
		Bwd_NwPtr->theFather_ = Internal;

		Internal->theFwd_SwPtr_ = Fwd_SwPtr;
		Internal->theFwd_SePtr_ = Fwd_SePtr;
		Internal->theFwd_NePtr_ = Fwd_NePtr;
		Internal->theFwd_NwPtr_ = Fwd_NwPtr;
		Internal->theBwd_SwPtr_ = Bwd_SwPtr;
		Internal->theBwd_SePtr_ = Bwd_SePtr;
		Internal->theBwd_NePtr_ = Bwd_NePtr;
		Internal->theBwd_NwPtr_ = Bwd_NwPtr;

		InnerLinks(Internal);

		// Remove Old Leaf from Neighbors
		RemoveLeafFromNeighbors(Leaf);

		FillNeighbors(SubDivide_OctreeOctant_Fwd_SW, Leaf, Internal, Fwd_SwPtr);
		FillNeighbors(SubDivide_OctreeOctant_Fwd_SE, Leaf, Internal, Fwd_SePtr);
		FillNeighbors(SubDivide_OctreeOctant_Fwd_NE, Leaf, Internal, Fwd_NePtr);
		FillNeighbors(SubDivide_OctreeOctant_Fwd_NW, Leaf, Internal, Fwd_NwPtr);
		FillNeighbors(SubDivide_OctreeOctant_Bwd_SW, Leaf, Internal, Bwd_SwPtr);
		FillNeighbors(SubDivide_OctreeOctant_Bwd_SE, Leaf, Internal, Bwd_SePtr);
		FillNeighbors(SubDivide_OctreeOctant_Bwd_NE, Leaf, Internal, Bwd_NePtr);
		FillNeighbors(SubDivide_OctreeOctant_Bwd_NW, Leaf, Internal, Bwd_NwPtr);

		UpdateFather(Leaf, Internal);
		
		FreePointer(Leaf);

		t = Internal;

		SubDivide(Internal->theBwd_SwPtr_);
		SubDivide(Internal->theBwd_SePtr_);
		SubDivide(Internal->theBwd_NePtr_);
		SubDivide(Internal->theBwd_NwPtr_);
		SubDivide(Internal->theFwd_SwPtr_);
		SubDivide(Internal->theFwd_SePtr_);
		SubDivide(Internal->theFwd_NePtr_);
		SubDivide(Internal->theFwd_NwPtr_);
	}
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::ForceDivide(SubDivide_BalancedOctreeNode*& t)
{
	SubDivide_BalancedOctreeLeaf* Leaf = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(t);

	Debug_Null_Pointer(Leaf);

	if (Leaf->theLevel_ > theMin_Level_) return;

	Standard_Integer Level = Leaf->theLevel_;
	const Entity_Box3d& Box = Leaf->theBox_;

	SubDivide_BalancedOctreeInternal* Internal = new SubDivide_BalancedOctreeInternal(Level);

	// Subdivide the Leaf
	SubDivide_BalancedOctreeLeaf* Fwd_SwPtr = CreateLeaf(Level + 1, Box.Fwd_SwOctant());
	SubDivide_BalancedOctreeLeaf* Fwd_SePtr = CreateLeaf(Level + 1, Box.Fwd_SeOctant());
	SubDivide_BalancedOctreeLeaf* Fwd_NePtr = CreateLeaf(Level + 1, Box.Fwd_NeOctant());
	SubDivide_BalancedOctreeLeaf* Fwd_NwPtr = CreateLeaf(Level + 1, Box.Fwd_NwOctant());
	SubDivide_BalancedOctreeLeaf* Bwd_SwPtr = CreateLeaf(Level + 1, Box.Bwd_SwOctant());
	SubDivide_BalancedOctreeLeaf* Bwd_SePtr = CreateLeaf(Level + 1, Box.Bwd_SeOctant());
	SubDivide_BalancedOctreeLeaf* Bwd_NePtr = CreateLeaf(Level + 1, Box.Bwd_NeOctant());
	SubDivide_BalancedOctreeLeaf* Bwd_NwPtr = CreateLeaf(Level + 1, Box.Bwd_NwOctant());

	Debug_Null_Pointer(Fwd_SwPtr);
	Debug_Null_Pointer(Fwd_SePtr);
	Debug_Null_Pointer(Fwd_NePtr);
	Debug_Null_Pointer(Fwd_NwPtr);
	Debug_Null_Pointer(Bwd_SwPtr);
	Debug_Null_Pointer(Bwd_SePtr);
	Debug_Null_Pointer(Bwd_NePtr);
	Debug_Null_Pointer(Bwd_NwPtr);

	Fwd_SwPtr->theFather_ = Internal;
	Fwd_SePtr->theFather_ = Internal;
	Fwd_NePtr->theFather_ = Internal;
	Fwd_NwPtr->theFather_ = Internal;
	Bwd_SwPtr->theFather_ = Internal;
	Bwd_SePtr->theFather_ = Internal;
	Bwd_NePtr->theFather_ = Internal;
	Bwd_NwPtr->theFather_ = Internal;

	Internal->theFwd_SwPtr_ = Fwd_SwPtr;
	Internal->theFwd_SePtr_ = Fwd_SePtr;
	Internal->theFwd_NePtr_ = Fwd_NePtr;
	Internal->theFwd_NwPtr_ = Fwd_NwPtr;
	Internal->theBwd_SwPtr_ = Bwd_SwPtr;
	Internal->theBwd_SePtr_ = Bwd_SePtr;
	Internal->theBwd_NePtr_ = Bwd_NePtr;
	Internal->theBwd_NwPtr_ = Bwd_NwPtr;

	InnerLinks(Internal);

	// Remove Old Leaf from Neighbors
	RemoveLeafFromNeighbors(Leaf);

	FillNeighbors(SubDivide_OctreeOctant_Fwd_SW, Leaf, Internal, Fwd_SwPtr);
	FillNeighbors(SubDivide_OctreeOctant_Fwd_SE, Leaf, Internal, Fwd_SePtr);
	FillNeighbors(SubDivide_OctreeOctant_Fwd_NE, Leaf, Internal, Fwd_NePtr);
	FillNeighbors(SubDivide_OctreeOctant_Fwd_NW, Leaf, Internal, Fwd_NwPtr);
	FillNeighbors(SubDivide_OctreeOctant_Bwd_SW, Leaf, Internal, Bwd_SwPtr);
	FillNeighbors(SubDivide_OctreeOctant_Bwd_SE, Leaf, Internal, Bwd_SePtr);
	FillNeighbors(SubDivide_OctreeOctant_Bwd_NE, Leaf, Internal, Bwd_NePtr);
	FillNeighbors(SubDivide_OctreeOctant_Bwd_NW, Leaf, Internal, Bwd_NwPtr);

	UpdateFather(Leaf, Internal);
	
	FreePointer(Leaf);

	t = Internal;

	ForceDivide(Internal->theBwd_SwPtr_);
	ForceDivide(Internal->theBwd_SePtr_);
	ForceDivide(Internal->theBwd_NePtr_);
	ForceDivide(Internal->theBwd_NwPtr_);
	ForceDivide(Internal->theFwd_SwPtr_);
	ForceDivide(Internal->theFwd_SePtr_);
	ForceDivide(Internal->theFwd_NePtr_);
	ForceDivide(Internal->theFwd_NwPtr_);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::UpdateFather
(
	SubDivide_BalancedOctreeLeaf * Node,
	SubDivide_BalancedOctreeNode* Internal
)
{
	if (NOT Node->theFather_) return;
	SubDivide_BalancedOctreeInternal* Father = dynamic_cast<SubDivide_BalancedOctreeInternal*>(Node->theFather_);
	Debug_Null_Pointer(Father);

	if (Father->theBwd_SwPtr_ EQUAL Node) Father->theBwd_SwPtr_ = Internal;
	else if (Father->theBwd_SePtr_ EQUAL Node) Father->theBwd_SePtr_ = Internal;
	else if (Father->theBwd_NePtr_ EQUAL Node) Father->theBwd_NePtr_ = Internal;
	else if (Father->theBwd_NwPtr_ EQUAL Node) Father->theBwd_NwPtr_ = Internal;
	else if (Father->theFwd_SwPtr_ EQUAL Node) Father->theFwd_SwPtr_ = Internal;
	else if (Father->theFwd_SePtr_ EQUAL Node) Father->theFwd_SePtr_ = Internal;
	else if (Father->theFwd_NePtr_ EQUAL Node) Father->theFwd_NePtr_ = Internal;
	else if (Father->theFwd_NwPtr_ EQUAL Node) Father->theFwd_NwPtr_ = Internal;
	else CloseProgram("Contradictory Data");
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::InnerLinks(SubDivide_BalancedOctreeInternal* t)
{
	SubDivide_BalancedOctreeLeaf *Fwd_SwPtr, *Fwd_SePtr, *Fwd_NePtr, *Fwd_NwPtr;
	SubDivide_BalancedOctreeLeaf *Bwd_SwPtr, *Bwd_SePtr, *Bwd_NePtr, *Bwd_NwPtr;

	Fwd_SwPtr = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(t->theFwd_SwPtr_);
	Fwd_SePtr = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(t->theFwd_SePtr_);
	Fwd_NePtr = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(t->theFwd_NePtr_);
	Fwd_NwPtr = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(t->theFwd_NwPtr_);
	Bwd_SwPtr = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(t->theBwd_SwPtr_);
	Bwd_SePtr = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(t->theBwd_SePtr_);
	Bwd_NePtr = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(t->theBwd_NePtr_);
	Bwd_NwPtr = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(t->theBwd_NwPtr_);

	Debug_Null_Pointer(Fwd_SwPtr);
	Debug_Null_Pointer(Fwd_SePtr);
	Debug_Null_Pointer(Fwd_NePtr);
	Debug_Null_Pointer(Fwd_NwPtr);
	Debug_Null_Pointer(Bwd_SwPtr);
	Debug_Null_Pointer(Bwd_SePtr);
	Debug_Null_Pointer(Bwd_NePtr);
	Debug_Null_Pointer(Bwd_NwPtr);
	
	Fwd_SwPtr->theENeighbors_.EnQueue(Fwd_SePtr);
	Fwd_SwPtr->theNNeighbors_.EnQueue(Fwd_NwPtr);
	Fwd_SwPtr->theBNeighbors_.EnQueue(Bwd_SwPtr);

	Fwd_SePtr->theWNeighbors_.EnQueue(Fwd_SwPtr);
	Fwd_SePtr->theNNeighbors_.EnQueue(Fwd_NePtr);
	Fwd_SePtr->theBNeighbors_.EnQueue(Bwd_SePtr);

	Fwd_NePtr->theWNeighbors_.EnQueue(Fwd_NwPtr);
	Fwd_NePtr->theSNeighbors_.EnQueue(Fwd_SePtr);
	Fwd_NePtr->theBNeighbors_.EnQueue(Bwd_NePtr);

	Fwd_NwPtr->theENeighbors_.EnQueue(Fwd_NePtr);
	Fwd_NwPtr->theSNeighbors_.EnQueue(Fwd_SwPtr);
	Fwd_NwPtr->theBNeighbors_.EnQueue(Bwd_NwPtr);

	Bwd_SwPtr->theENeighbors_.EnQueue(Bwd_SePtr);
	Bwd_SwPtr->theNNeighbors_.EnQueue(Bwd_NwPtr);
	Bwd_SwPtr->theFNeighbors_.EnQueue(Fwd_SwPtr);

	Bwd_SePtr->theWNeighbors_.EnQueue(Bwd_SwPtr);
	Bwd_SePtr->theNNeighbors_.EnQueue(Bwd_NePtr);
	Bwd_SePtr->theFNeighbors_.EnQueue(Fwd_SePtr);

	Bwd_NePtr->theWNeighbors_.EnQueue(Bwd_NwPtr);
	Bwd_NePtr->theSNeighbors_.EnQueue(Bwd_SePtr);
	Bwd_NePtr->theFNeighbors_.EnQueue(Fwd_NePtr);

	Bwd_NwPtr->theENeighbors_.EnQueue(Bwd_NePtr);
	Bwd_NwPtr->theSNeighbors_.EnQueue(Bwd_SwPtr);
	Bwd_NwPtr->theFNeighbors_.EnQueue(Fwd_NwPtr);
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::RemoveLeafFromNeighbors(SubDivide_BalancedOctreeLeaf* Old)
{
	ADT_Ary1d<SubDivide_BalancedOctreeLeaf*> SN, EN, NN, WN, FN, BN;
	
	Old->theSNeighbors_.RetrieveTo(SN);
	Old->theENeighbors_.RetrieveTo(EN);
	Old->theNNeighbors_.RetrieveTo(NN);
	Old->theWNeighbors_.RetrieveTo(WN);
	Old->theBNeighbors_.RetrieveTo(BN);
	Old->theFNeighbors_.RetrieveTo(FN);

	forThose(Index, 0, MaxIndexOf(SN))
	{
		SubDivide_BalancedOctreeLeaf* Ptr = SN[Index];
		Ptr->theNNeighbors_.Remove(Old);
	}

	forThose(Index, 0, MaxIndexOf(EN))
	{
		SubDivide_BalancedOctreeLeaf* Ptr = EN[Index];
		Ptr->theWNeighbors_.Remove(Old);
	}

	forThose(Index, 0, MaxIndexOf(NN))
	{
		SubDivide_BalancedOctreeLeaf* Ptr = NN[Index];
		Ptr->theSNeighbors_.Remove(Old);
	}

	forThose(Index, 0, MaxIndexOf(WN))
	{
		SubDivide_BalancedOctreeLeaf* Ptr = WN[Index];
		Ptr->theENeighbors_.Remove(Old);
	}

	forThose(Index, 0, MaxIndexOf(FN))
	{
		SubDivide_BalancedOctreeLeaf* Ptr = FN[Index];
		Ptr->theBNeighbors_.Remove(Old);
	}

	forThose(Index, 0, MaxIndexOf(BN))
	{
		SubDivide_BalancedOctreeLeaf* Ptr = BN[Index];
		Ptr->theFNeighbors_.Remove(Old);
	}
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::FillNeighbors
(
	SubDivide_OctreeOctant Octant, 
	SubDivide_BalancedOctreeLeaf * Old, 
	SubDivide_BalancedOctreeInternal * Father,
	SubDivide_BalancedOctreeLeaf * t
)
{
	ADT_Ary1d<SubDivide_BalancedOctreeLeaf*> SN, EN, NN, WN, FN, BN;

	Old->theSNeighbors_.RetrieveTo(SN);
	Old->theENeighbors_.RetrieveTo(EN);
	Old->theNNeighbors_.RetrieveTo(NN);
	Old->theWNeighbors_.RetrieveTo(WN);
	Old->theBNeighbors_.RetrieveTo(BN);
	Old->theFNeighbors_.RetrieveTo(FN);

	SubDivide_BalancedOctreeLeaf* Fwd_SwPtr, *Fwd_SePtr, *Fwd_NePtr, *Fwd_NwPtr;
	SubDivide_BalancedOctreeLeaf* Bwd_SwPtr, *Bwd_SePtr, *Bwd_NePtr, *Bwd_NwPtr;

	Fwd_SwPtr = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(Father->theFwd_SwPtr_);
	Fwd_SePtr = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(Father->theFwd_SePtr_);
	Fwd_NePtr = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(Father->theFwd_NePtr_);
	Fwd_NwPtr = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(Father->theFwd_NwPtr_);
	Bwd_SwPtr = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(Father->theBwd_SwPtr_);
	Bwd_SePtr = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(Father->theBwd_SePtr_);
	Bwd_NePtr = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(Father->theBwd_NePtr_);
	Bwd_NwPtr = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(Father->theBwd_NwPtr_);

	Debug_Null_Pointer(Fwd_SwPtr);
	Debug_Null_Pointer(Fwd_SePtr);
	Debug_Null_Pointer(Fwd_NePtr);
	Debug_Null_Pointer(Fwd_NwPtr);
	Debug_Null_Pointer(Bwd_SwPtr);
	Debug_Null_Pointer(Bwd_SePtr);
	Debug_Null_Pointer(Bwd_NePtr);
	Debug_Null_Pointer(Bwd_NwPtr);

	Get_Const_Object(tBox) = Old->theBox_;
	Geom_Pnt3d Centre = tBox.CalcCentre();

	ADT_BasicQueue<SubDivide_BalancedOctreeLeaf*> QSN, QEN, QNN, QWN, QFN, QBN;

	if (Octant EQUAL SubDivide_OctreeOctant_Fwd_SW)
	{
		if (WN.Size() <= 1) QWN.EnQueue(WN);
		else
		{
			forThose(Index, 0, MaxIndexOf(WN))
			{
				switch (CalcOctant(WN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Fwd_SW: QWN.EnQueue(WN[Index]); break;
				default: break;
				}
			}
		}

		if (SN.Size() <= 1) QSN.EnQueue(SN);
		else
		{
			forThose(Index, 0, MaxIndexOf(SN))
			{
				switch (CalcOctant(SN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Fwd_SW: QSN.EnQueue(SN[Index]); break;
				default: break;
				}
			}
		}

		if (FN.Size() <= 1) QFN.EnQueue(FN);
		else
		{
			forThose(Index, 0, MaxIndexOf(FN))
			{
				switch (CalcOctant(FN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Fwd_SW: QFN.EnQueue(FN[Index]); break;
				default: break;
				}
			}
		}
	}
	else if (Octant EQUAL SubDivide_OctreeOctant_Fwd_SE)
	{
		if (SN.Size() <= 1) QSN.EnQueue(SN);
		else
		{
			forThose(Index, 0, MaxIndexOf(SN))
			{
				switch (CalcOctant(SN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Fwd_SE: QSN.EnQueue(SN[Index]); break;
				default: break;
				}
			}
		}

		if (EN.Size() <= 1) QEN.EnQueue(EN);
		else
		{
			forThose(Index, 0, MaxIndexOf(EN))
			{
				switch (CalcOctant(EN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Fwd_SE: QEN.EnQueue(EN[Index]); break;
				default: break;
				}
			}
		}

		if (FN.Size() <= 1) QFN.EnQueue(FN);
		else
		{
			forThose(Index, 0, MaxIndexOf(FN))
			{
				switch (CalcOctant(FN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Fwd_SE: QFN.EnQueue(FN[Index]); break;
				default: break;
				}
			}
		}
	}
	else if (Octant EQUAL SubDivide_OctreeOctant_Fwd_NE)
	{
		if (EN.Size() <= 1) QEN.EnQueue(EN);
		else
		{
			forThose(Index, 0, MaxIndexOf(EN))
			{
				switch (CalcOctant(EN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Fwd_NE: QEN.EnQueue(EN[Index]); break;
				default: break;
				}
			}
		}

		if (NN.Size() <= 1) QNN.EnQueue(NN);
		else
		{
			forThose(Index, 0, MaxIndexOf(NN))
			{
				switch (CalcOctant(NN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Fwd_NE: QNN.EnQueue(NN[Index]); break;
				default: break;
				}
			}
		}

		if (FN.Size() <= 1) QFN.EnQueue(FN);
		else
		{
			forThose(Index, 0, MaxIndexOf(FN))
			{
				switch (CalcOctant(FN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Fwd_NE: QFN.EnQueue(FN[Index]); break;
				default: break;
				}
			}
		}
	}
	else if (Octant EQUAL SubDivide_OctreeOctant_Fwd_NW)
	{
		if (NN.Size() <= 1) QNN.EnQueue(NN);
		else
		{
			forThose(Index, 0, MaxIndexOf(NN))
			{
				switch (CalcOctant(NN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Fwd_NW: QNN.EnQueue(NN[Index]); break;
				default: break;
				}
			}
		}

		if (WN.Size() <= 1) QWN.EnQueue(WN);
		else
		{
			forThose(Index, 0, MaxIndexOf(WN))
			{
				switch (CalcOctant(WN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Fwd_NW: QWN.EnQueue(WN[Index]); break;
				default: break;
				}
			}
		}

		if (FN.Size() <= 1) QFN.EnQueue(FN);
		else
		{
			forThose(Index, 0, MaxIndexOf(FN))
			{
				switch (CalcOctant(FN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Fwd_NW: QFN.EnQueue(FN[Index]); break;
				default: break;
				}
			}
		}
	}
	else if (Octant EQUAL SubDivide_OctreeOctant_Bwd_SW)
	{
		if (WN.Size() <= 1) QWN.EnQueue(WN);
		else
		{
			forThose(Index, 0, MaxIndexOf(WN))
			{
				switch (CalcOctant(WN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Bwd_SW: QWN.EnQueue(WN[Index]); break;
				default: break;
				}
			}
		}

		if (SN.Size() <= 1) QSN.EnQueue(SN);
		else
		{
			forThose(Index, 0, MaxIndexOf(SN))
			{
				switch (CalcOctant(SN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Bwd_SW: QSN.EnQueue(SN[Index]); break;
				default: break;
				}
			}
		}

		if (BN.Size() <= 1) QBN.EnQueue(BN);
		else
		{
			forThose(Index, 0, MaxIndexOf(BN))
			{
				switch (CalcOctant(BN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Bwd_SW: QBN.EnQueue(BN[Index]); break;
				default: break;
				}
			}
		}
	}
	else if (Octant EQUAL SubDivide_OctreeOctant_Bwd_SE)
	{
		if (SN.Size() <= 1) QSN.EnQueue(SN);
		else
		{
			forThose(Index, 0, MaxIndexOf(SN))
			{
				switch (CalcOctant(SN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Bwd_SE: QSN.EnQueue(SN[Index]); break;
				default: break;
				}
			}
		}

		if (EN.Size() <= 1) QEN.EnQueue(EN);
		else
		{
			forThose(Index, 0, MaxIndexOf(EN))
			{
				switch (CalcOctant(EN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Bwd_SE: QEN.EnQueue(EN[Index]); break;
				default: break;
				}
			}
		}

		if (BN.Size() <= 1) QBN.EnQueue(BN);
		else
		{
			forThose(Index, 0, MaxIndexOf(BN))
			{
				switch (CalcOctant(BN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Bwd_SE: QBN.EnQueue(BN[Index]); break;
				default: break;
				}
			}
		}
	}
	else if (Octant EQUAL SubDivide_OctreeOctant_Bwd_NE)
	{
		if (EN.Size() <= 1) QEN.EnQueue(EN);
		else
		{
			forThose(Index, 0, MaxIndexOf(EN))
			{
				switch (CalcOctant(EN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Bwd_NE: QEN.EnQueue(EN[Index]); break;
				default: break;
				}
			}
		}

		if (NN.Size() <= 1) QNN.EnQueue(NN);
		else
		{
			forThose(Index, 0, MaxIndexOf(NN))
			{
				switch (CalcOctant(NN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Bwd_NE: QNN.EnQueue(NN[Index]); break;
				default: break;
				}
			}
		}

		if (BN.Size() <= 1) QBN.EnQueue(BN);
		else
		{
			forThose(Index, 0, MaxIndexOf(BN))
			{
				switch (CalcOctant(BN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Bwd_NE: QBN.EnQueue(BN[Index]); break;
				default: break;
				}
			}
		}
	}
	else
	{
		if (NN.Size() <= 1) QNN.EnQueue(NN);
		else
		{
			forThose(Index, 0, MaxIndexOf(NN))
			{
				switch (CalcOctant(NN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Bwd_NW: QNN.EnQueue(NN[Index]); break;
				default: break;
				}
			}
		}

		if (WN.Size() <= 1) QWN.EnQueue(WN);
		else
		{
			forThose(Index, 0, MaxIndexOf(WN))
			{
				switch (CalcOctant(WN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Bwd_NW: QWN.EnQueue(WN[Index]); break;
				default: break;
				}
			}
		}

		if (BN.Size() <= 1) QBN.EnQueue(BN);
		else
		{
			forThose(Index, 0, MaxIndexOf(BN))
			{
				switch (CalcOctant(BN[Index]->theBox_.CalcCentre(), Centre))
				{
				case SubDivide_OctreeOctant_Bwd_NW: QBN.EnQueue(BN[Index]); break;
				default: break;
				}
			}
		}
	}

	ADT_Ary1d<SubDivide_BalancedOctreeLeaf*> nSN, nEN, nNN, nWN, nFN, nBN;
	QSN.RetrieveTo(nSN);
	QEN.RetrieveTo(nEN);
	QNN.RetrieveTo(nNN);
	QWN.RetrieveTo(nWN);
	QFN.RetrieveTo(nFN);
	QBN.RetrieveTo(nBN);

	forThose(Index, 0, MaxIndexOf(nSN))
	{
		//nSN[Index]->theNNeighbors_.Remove(Old);
		nSN[Index]->theNNeighbors_.EnQueue(t);
	}

	forThose(Index, 0, MaxIndexOf(nEN))
	{
		//nEN[Index]->theWNeighbors_.Remove(Old);
		nEN[Index]->theWNeighbors_.EnQueue(t);
	}

	forThose(Index, 0, MaxIndexOf(nNN))
	{
		//nNN[Index]->theWNeighbors_.Remove(Old);
		nNN[Index]->theSNeighbors_.EnQueue(t);
	}

	forThose(Index, 0, MaxIndexOf(nWN))
	{
		//nWN[Index]->theENeighbors_.Remove(Old);
		nWN[Index]->theENeighbors_.EnQueue(t);
	}

	forThose(Index, 0, MaxIndexOf(nBN))
	{
		//nNN[Index]->theWNeighbors_.Remove(Old);
		nBN[Index]->theFNeighbors_.EnQueue(t);
	}

	forThose(Index, 0, MaxIndexOf(nFN))
	{
		//nWN[Index]->theENeighbors_.Remove(Old);
		nFN[Index]->theBNeighbors_.EnQueue(t);
	}

	t->theSNeighbors_.EnQueue(QSN.Retrive());
	t->theENeighbors_.EnQueue(QEN.Retrive());
	t->theNNeighbors_.EnQueue(QNN.Retrive());
	t->theWNeighbors_.EnQueue(QWN.Retrive());
	t->theFNeighbors_.EnQueue(QFN.Retrive());
	t->theBNeighbors_.EnQueue(QBN.Retrive());
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::Balancing(SubDivide_BalancedOctreeNode *& t)
{
	if (NOT t) return;

	SubDivide_BalancedOctreeLeaf* Leaf = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(t);

	if (Leaf)
	{
		if (NOT DoSubdivide(Leaf)) return;

		if (NOT IsBalancing_) IsBalancing_ = Standard_True;

		Standard_Integer Level = Leaf->theLevel_;
		const Entity_Box3d& Box = Leaf->theBox_;

		SubDivide_BalancedOctreeInternal* Internal = new SubDivide_BalancedOctreeInternal(Level);

		// Subdivide the Leaf
		SubDivide_BalancedOctreeLeaf* Bwd_SwPtr = CreateLeaf(Level + 1, Box.Bwd_SwOctant());
		SubDivide_BalancedOctreeLeaf* Bwd_SePtr = CreateLeaf(Level + 1, Box.Bwd_SeOctant());
		SubDivide_BalancedOctreeLeaf* Bwd_NePtr = CreateLeaf(Level + 1, Box.Bwd_NeOctant());
		SubDivide_BalancedOctreeLeaf* Bwd_NwPtr = CreateLeaf(Level + 1, Box.Bwd_NwOctant());
		SubDivide_BalancedOctreeLeaf* Fwd_SwPtr = CreateLeaf(Level + 1, Box.Fwd_SwOctant());
		SubDivide_BalancedOctreeLeaf* Fwd_SePtr = CreateLeaf(Level + 1, Box.Fwd_SeOctant());
		SubDivide_BalancedOctreeLeaf* Fwd_NePtr = CreateLeaf(Level + 1, Box.Fwd_NeOctant());
		SubDivide_BalancedOctreeLeaf* Fwd_NwPtr = CreateLeaf(Level + 1, Box.Fwd_NwOctant());

		Debug_Null_Pointer(Fwd_SwPtr);
		Debug_Null_Pointer(Fwd_SePtr);
		Debug_Null_Pointer(Fwd_NePtr);
		Debug_Null_Pointer(Fwd_NwPtr);
		Debug_Null_Pointer(Bwd_SwPtr);
		Debug_Null_Pointer(Bwd_SePtr);
		Debug_Null_Pointer(Bwd_NePtr);
		Debug_Null_Pointer(Bwd_NwPtr);

		Internal->theFwd_SwPtr_ = Fwd_SwPtr;
		Internal->theFwd_SePtr_ = Fwd_SePtr;
		Internal->theFwd_NePtr_ = Fwd_NePtr;
		Internal->theFwd_NwPtr_ = Fwd_NwPtr;
		Internal->theBwd_SwPtr_ = Bwd_SwPtr;
		Internal->theBwd_SePtr_ = Bwd_SePtr;
		Internal->theBwd_NePtr_ = Bwd_NePtr;
		Internal->theBwd_NwPtr_ = Bwd_NwPtr;

		InnerLinks(Internal);

		Fwd_SwPtr->theBox_ = Box.Fwd_SwOctant();
		Fwd_SePtr->theBox_ = Box.Fwd_SeOctant();
		Fwd_NePtr->theBox_ = Box.Fwd_NeOctant();
		Fwd_NwPtr->theBox_ = Box.Fwd_NwOctant();
		Bwd_SwPtr->theBox_ = Box.Bwd_SwOctant();
		Bwd_SePtr->theBox_ = Box.Bwd_SeOctant();
		Bwd_NePtr->theBox_ = Box.Bwd_NeOctant();
		Bwd_NwPtr->theBox_ = Box.Bwd_NwOctant();

		// Remove Old Leaf from Neighbors
		RemoveLeafFromNeighbors(Leaf);

		FillNeighbors(SubDivide_OctreeOctant_Fwd_SW, Leaf, Internal, Fwd_SwPtr);
		FillNeighbors(SubDivide_OctreeOctant_Fwd_SE, Leaf, Internal, Fwd_SePtr);
		FillNeighbors(SubDivide_OctreeOctant_Fwd_NE, Leaf, Internal, Fwd_NePtr);
		FillNeighbors(SubDivide_OctreeOctant_Fwd_NW, Leaf, Internal, Fwd_NwPtr);
		FillNeighbors(SubDivide_OctreeOctant_Bwd_SW, Leaf, Internal, Bwd_SwPtr);
		FillNeighbors(SubDivide_OctreeOctant_Bwd_SE, Leaf, Internal, Bwd_SePtr);
		FillNeighbors(SubDivide_OctreeOctant_Bwd_NE, Leaf, Internal, Bwd_NePtr);
		FillNeighbors(SubDivide_OctreeOctant_Bwd_NW, Leaf, Internal, Bwd_NwPtr);

		FreePointer(t);

		t = Internal;

		Balancing(Internal->theFwd_SwPtr_);
		Balancing(Internal->theFwd_SePtr_);
		Balancing(Internal->theFwd_NePtr_);
		Balancing(Internal->theFwd_NwPtr_);
		Balancing(Internal->theBwd_SwPtr_);
		Balancing(Internal->theBwd_SePtr_);
		Balancing(Internal->theBwd_NePtr_);
		Balancing(Internal->theBwd_NwPtr_);
	}
	else
	{
		SubDivide_BalancedOctreeInternal* Internal = dynamic_cast<SubDivide_BalancedOctreeInternal*>(t);
		Debug_Null_Pointer(Internal);

		Balancing(Internal->theFwd_SwPtr_);
		Balancing(Internal->theFwd_SePtr_);
		Balancing(Internal->theFwd_NePtr_);
		Balancing(Internal->theFwd_NwPtr_);
		Balancing(Internal->theBwd_SwPtr_);
		Balancing(Internal->theBwd_SePtr_);
		Balancing(Internal->theBwd_NePtr_);
		Balancing(Internal->theBwd_NwPtr_);
	}
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::RetrieveTo
(
	Global_Handle(SubDivide_BalancedOctreeNode) Pointer,
	TColSubDivide_HBasicQueueOfBalancedOctreeNode & Nodes
) const
{
	if (NOT Pointer) return;

	SubDivide_BalancedOctreeLeaf* Leaf = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(Pointer);

	if (Leaf)
	{
		Nodes.EnQueue(Pointer);
	}
	else
	{
		SubDivide_BalancedOctreeInternal* Internal = dynamic_cast<SubDivide_BalancedOctreeInternal*>(Pointer);
		Debug_Null_Pointer(Internal);

		RetrieveTo(Internal->theBwd_SwPtr_, Nodes);
		RetrieveTo(Internal->theBwd_SePtr_, Nodes);
		RetrieveTo(Internal->theBwd_NePtr_, Nodes);
		RetrieveTo(Internal->theBwd_NwPtr_, Nodes);

		RetrieveTo(Internal->theFwd_SwPtr_, Nodes);
		RetrieveTo(Internal->theFwd_SePtr_, Nodes);
		RetrieveTo(Internal->theFwd_NePtr_, Nodes);
		RetrieveTo(Internal->theFwd_NwPtr_, Nodes);
	}
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::RetrieveTo
(
	SubDivide_BalancedOctreeNode * t,
	TColEntity_HBasicQueueOfBox3d & Boxes
) const
{
	if (NOT t) return;

	SubDivide_BalancedOctreeLeaf* Leaf = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(t);

	if (Leaf)
	{
		Boxes.EnQueue(new Entity_Box3d(Leaf->theBox_));
	}
	else
	{
		SubDivide_BalancedOctreeInternal* Internal = dynamic_cast<SubDivide_BalancedOctreeInternal*>(t);
		/*if (NOT Internal)
		{
			cout << t << endl;
			cout << dynamic_cast<SubDivide_BalancedOctreeLeaf*>(t) << endl;
			cout << dynamic_cast<SubDivide_BalancedOctreeInternal*>(t) << endl;
		}*/
		Debug_Null_Pointer(Internal);

		RetrieveTo(Internal->theBwd_SwPtr_, Boxes);
		RetrieveTo(Internal->theBwd_SePtr_, Boxes);
		RetrieveTo(Internal->theBwd_NePtr_, Boxes);
		RetrieveTo(Internal->theBwd_NwPtr_, Boxes);

		RetrieveTo(Internal->theFwd_SwPtr_, Boxes);
		RetrieveTo(Internal->theFwd_SePtr_, Boxes);
		RetrieveTo(Internal->theFwd_NePtr_, Boxes);
		RetrieveTo(Internal->theFwd_NwPtr_, Boxes);
	}
}

template<typename T>
inline void AutLib::GeoLib::SubDivide_BalancedOctree<T>::Clear(SubDivide_BalancedOctreeNode *& t)
{
	SubDivide_BalancedOctreeLeaf* Leaf = dynamic_cast<SubDivide_BalancedOctreeLeaf*>(t);

	if (Leaf)
	{
		Delete_Pointer(t);
	}
	else
	{
		SubDivide_BalancedOctreeInternal* Internal = dynamic_cast<SubDivide_BalancedOctreeInternal*>(t);

		Debug_Null_Pointer(Internal);

		if (Internal->theFwd_SwPtr_) Clear(Internal->theFwd_SwPtr_);
		if (Internal->theFwd_SePtr_) Clear(Internal->theFwd_SePtr_);
		if (Internal->theFwd_NePtr_) Clear(Internal->theFwd_NePtr_);
		if (Internal->theFwd_NwPtr_) Clear(Internal->theFwd_NwPtr_);

		if (Internal->theBwd_SwPtr_) Clear(Internal->theBwd_SwPtr_);
		if (Internal->theBwd_SePtr_) Clear(Internal->theBwd_SePtr_);
		if (Internal->theBwd_NePtr_) Clear(Internal->theBwd_NePtr_);
		if (Internal->theBwd_NwPtr_) Clear(Internal->theBwd_NwPtr_);

		Delete_Pointer(t);
	}
}