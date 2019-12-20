#pragma once
#include <IO_Tecplot.hxx>

template<typename T>
inline AutLib::GeoLib::Geom_BalancedPrOctTree<T>::Geom_BalancedPrOctTree()
	: theNbItems_(0)
	, theRoot_(NULL)
	, theBUCKET_SIZE_(8)
	, theMAX_INNER_SUBDIVISION_(20)
{
}

template<typename T>
inline AutLib::GeoLib::Geom_BalancedPrOctTree<T>::~Geom_BalancedPrOctTree()
{
	Clear(theRoot_);
}

template<typename T>
inline Standard_Integer AutLib::GeoLib::Geom_BalancedPrOctTree<T>::Size() const
{
	return theNbItems_;
}

template<typename T>
inline Standard_Boolean AutLib::GeoLib::Geom_BalancedPrOctTree<T>::IsEmpty() const
{
	return theRoot_ EQUAL NULL;
}

template<typename T>
inline const M_GEO Entity_Box3d & AutLib::GeoLib::Geom_BalancedPrOctTree<T>::BoundingBox() const
{
	return theDomain_;
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrOctTree<T>::SetCoordinateFunction(const Geom_Pnt3d &(*Get_Coordinates)(T))
{
	theCoordOf = Get_Coordinates;
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrOctTree<T>::SetMaxInnerSubdivision(const Standard_Integer Value)
{
	theMAX_INNER_SUBDIVISION_ = Value;
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrOctTree<T>::SetBucketSize(const Standard_Integer Value)
{
	theBUCKET_SIZE_ = Value;
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrOctTree<T>::Insert(const T & Item)
{
	Debug_If_Condition_Message(theCoordOf EQUAL NULL, " No coordinate function for Pr-QuadTree");

	theInnerSubdivision_ = 0;

	Insert(Item, theDomain_, theRoot_);
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrOctTree<T>::Insert(const ADT_Ary1d<T>& Items)
{
	forThose(Index, 0, MaxIndexOf(Items))
	{
		Insert(Items[Index]);
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrOctTree<T>::PostBalancing()
{
	while (Standard_True)
	{
		IsBalancing_ = Standard_False;

		Balancing(theRoot_);

		if (NOT IsBalancing_) break;
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrOctTree<T>::RetrieveTo(TColEntity_HAry1dOfBox3d & Boxes) const
{
	TColEntity_HBasicQueueOfBox3d Q;
	RetrieveTo(theRoot_, Q);
	Q.RetrieveTo(Boxes);
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrOctTree<T>::SetRegion(const Entity_Box3d & Region)
{
	theDomain_ = Region;
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrOctTree<T>::ExportToPlt(fstream & File) const
{
	if (IsEmpty())
	{
		M_IO IO_TecPlot::ExportBox(theDomain_, File);
		return;
	}

	TColEntity_HAry1dOfBox3d Boxes;
	RetrieveTo(Boxes);

	M_IO IO_TecPlot::ExportBox(Boxes, File);

	FreeMemory(Boxes);
}

template<typename T>
inline M_GEO Geom_PrOctantInfo AutLib::GeoLib::Geom_BalancedPrOctTree<T>::CalcOctant
(
	const Geom_Pnt3d & P,
	const Geom_Pnt3d & Centre
) const
{
	if (P.X() <= Centre.X())
	{
		if (P.Y() <= Centre.Y())
		{
			if (P.Z() <= Centre.Z()) { return Geom_PrOctantInfo_Bwd_SW; }
			else { return Geom_PrOctantInfo_Fwd_SW; }
		}
		else
		{
			if (P.Z() <= Centre.Z()) { return Geom_PrOctantInfo_Bwd_NW; }
			else { return Geom_PrOctantInfo_Fwd_NW; }
		}
	}
	else
	{
		if (P.Y() <= Centre.Y())
		{
			if (P.Z() <= Centre.Z()) { return Geom_PrOctantInfo_Bwd_SE; }
			else { return Geom_PrOctantInfo_Fwd_SE; }
		}
		else
		{
			if (P.Z() <= Centre.Z()) { return Geom_PrOctantInfo_Bwd_NE; }
			else { return Geom_PrOctantInfo_Fwd_NE; }
		}
	}
}

template<typename T>
inline Standard_Boolean AutLib::GeoLib::Geom_BalancedPrOctTree<T>::DoSubdivide(Geom_PrOctantTreeLeaf<T>* Leaf) const
{
	/*cout << Leaf->theSNeighbors_.Size() << endl;
	cout << Leaf->theENeighbors_.Size() << endl;
	cout << Leaf->theNNeighbors_.Size() << endl;
	cout << Leaf->theWNeighbors_.Size() << endl;
	cout << Leaf->theFNeighbors_.Size() << endl;
	cout << Leaf->theBNeighbors_.Size() << endl;
	PAUSE;*/
	if (Leaf->theSNeighbors_.Size() > 4) return Standard_True;
	if (Leaf->theENeighbors_.Size() > 4) return Standard_True;
	if (Leaf->theNNeighbors_.Size() > 4) return Standard_True;
	if (Leaf->theWNeighbors_.Size() > 4) return Standard_True;
	if (Leaf->theFNeighbors_.Size() > 4) return Standard_True;
	if (Leaf->theBNeighbors_.Size() > 4) return Standard_True;

	return Standard_False;
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrOctTree<T>::Balancing(Geom_PrOctantTreeNode<T>*& t)
{
	if (NOT t) return;

	Geom_PrOctantTreeLeaf<T>* Leaf = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(t);

	if (Leaf)
	{
		if (NOT DoSubdivide(Leaf)) return;

		if (NOT IsBalancing_) IsBalancing_ = Standard_True;

		ADT_Ary1d<T> pItems;
		Leaf->theBucket_.RetrieveTo(pItems);

		Geom_PrOctantTreeInternal<T>* Internal = new Geom_PrOctantTreeInternal<T>;
		Internal->theBox_ = t->theBox_;

		// Subdivide the Leaf
		Geom_PrOctantTreeLeaf<T>* Fwd_SwPtr = new Geom_PrOctantTreeLeaf<T>(theBUCKET_SIZE_);
		Geom_PrOctantTreeLeaf<T>* Fwd_SePtr = new Geom_PrOctantTreeLeaf<T>(theBUCKET_SIZE_);
		Geom_PrOctantTreeLeaf<T>* Fwd_NePtr = new Geom_PrOctantTreeLeaf<T>(theBUCKET_SIZE_);
		Geom_PrOctantTreeLeaf<T>* Fwd_NwPtr = new Geom_PrOctantTreeLeaf<T>(theBUCKET_SIZE_);
		Geom_PrOctantTreeLeaf<T>* Bwd_SwPtr = new Geom_PrOctantTreeLeaf<T>(theBUCKET_SIZE_);
		Geom_PrOctantTreeLeaf<T>* Bwd_SePtr = new Geom_PrOctantTreeLeaf<T>(theBUCKET_SIZE_);
		Geom_PrOctantTreeLeaf<T>* Bwd_NePtr = new Geom_PrOctantTreeLeaf<T>(theBUCKET_SIZE_);
		Geom_PrOctantTreeLeaf<T>* Bwd_NwPtr = new Geom_PrOctantTreeLeaf<T>(theBUCKET_SIZE_);

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

		Get_Const_Object(Box) = Internal->theBox_;
		
		Geom_Pnt3d Centre = Box.CalcCentre();

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

		FillNeighbors(Geom_PrOctantInfo_Fwd_SW, Leaf, Internal, Fwd_SwPtr);
		FillNeighbors(Geom_PrOctantInfo_Fwd_SE, Leaf, Internal, Fwd_SePtr);
		FillNeighbors(Geom_PrOctantInfo_Fwd_NE, Leaf, Internal, Fwd_NePtr);
		FillNeighbors(Geom_PrOctantInfo_Fwd_NW, Leaf, Internal, Fwd_NwPtr);
		FillNeighbors(Geom_PrOctantInfo_Bwd_SW, Leaf, Internal, Bwd_SwPtr);
		FillNeighbors(Geom_PrOctantInfo_Bwd_SE, Leaf, Internal, Bwd_SePtr);
		FillNeighbors(Geom_PrOctantInfo_Bwd_NE, Leaf, Internal, Bwd_NePtr);
		FillNeighbors(Geom_PrOctantInfo_Bwd_NW, Leaf, Internal, Bwd_NwPtr);

		theNbItems_ -= pItems.Size();

		FreePointer(t);

		t = Internal;

		forThose
		(
			Index,
			0,
			MaxIndexOf(pItems)
		)
		{
			Get_Const_Object(Coord) = theCoordOf(pItems[Index]);

			switch (CalcOctant(Coord, Centre))
			{
			case Geom_PrOctantInfo_Fwd_SW: Insert(pItems[Index], Fwd_SwPtr->theBox_, Internal->theFwd_SwPtr_); break;
			case Geom_PrOctantInfo_Fwd_SE: Insert(pItems[Index], Fwd_SePtr->theBox_, Internal->theFwd_SePtr_); break;
			case Geom_PrOctantInfo_Fwd_NE: Insert(pItems[Index], Fwd_NePtr->theBox_, Internal->theFwd_NePtr_); break;
			case Geom_PrOctantInfo_Fwd_NW: Insert(pItems[Index], Fwd_NwPtr->theBox_, Internal->theFwd_NwPtr_); break;
			case Geom_PrOctantInfo_Bwd_SW: Insert(pItems[Index], Bwd_SwPtr->theBox_, Internal->theBwd_SwPtr_); break;
			case Geom_PrOctantInfo_Bwd_SE: Insert(pItems[Index], Bwd_SePtr->theBox_, Internal->theBwd_SePtr_); break;
			case Geom_PrOctantInfo_Bwd_NE: Insert(pItems[Index], Bwd_NePtr->theBox_, Internal->theBwd_NePtr_); break;
			case Geom_PrOctantInfo_Bwd_NW: Insert(pItems[Index], Bwd_NwPtr->theBox_, Internal->theBwd_NwPtr_); break;
			}
		}

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
		Geom_PrOctantTreeInternal<T>* Internal = dynamic_cast<Geom_PrOctantTreeInternal<T>*>(t);
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
inline void AutLib::GeoLib::Geom_BalancedPrOctTree<T>::InnerLinks(Geom_PrOctantTreeInternal<T>* t)
{
	Geom_PrOctantTreeLeaf<T>* Fwd_SwPtr, *Fwd_SePtr, *Fwd_NePtr, *Fwd_NwPtr;
	Geom_PrOctantTreeLeaf<T>* Bwd_SwPtr, *Bwd_SePtr, *Bwd_NePtr, *Bwd_NwPtr;
	
	Fwd_SwPtr = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(t->theFwd_SwPtr_);
	Fwd_SePtr = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(t->theFwd_SePtr_);
	Fwd_NePtr = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(t->theFwd_NePtr_);
	Fwd_NwPtr = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(t->theFwd_NwPtr_);
	Bwd_SwPtr = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(t->theBwd_SwPtr_);
	Bwd_SePtr = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(t->theBwd_SePtr_);
	Bwd_NePtr = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(t->theBwd_NePtr_);
	Bwd_NwPtr = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(t->theBwd_NwPtr_);

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
inline void AutLib::GeoLib::Geom_BalancedPrOctTree<T>::RemoveLeafFromNeighbors(Geom_PrOctantTreeLeaf<T>* Old)
{
	ADT_Ary1d<Geom_PrOctantTreeLeaf<T>*> SN, EN, NN, WN, FN, BN;

	Old->theSNeighbors_.RetrieveTo(SN);
	Old->theENeighbors_.RetrieveTo(EN);
	Old->theNNeighbors_.RetrieveTo(NN);
	Old->theWNeighbors_.RetrieveTo(WN);
	Old->theBNeighbors_.RetrieveTo(BN);
	Old->theFNeighbors_.RetrieveTo(FN);

	forThose(Index, 0, MaxIndexOf(SN))
	{
		Geom_PrOctantTreeLeaf<T>* Ptr = SN[Index];
		Ptr->theNNeighbors_.Remove(Old);
	}

	forThose(Index, 0, MaxIndexOf(EN))
	{
		Geom_PrOctantTreeLeaf<T>* Ptr = EN[Index];
		Ptr->theWNeighbors_.Remove(Old);
	}

	forThose(Index, 0, MaxIndexOf(NN))
	{
		Geom_PrOctantTreeLeaf<T>* Ptr = NN[Index];
		Ptr->theSNeighbors_.Remove(Old);
	}

	forThose(Index, 0, MaxIndexOf(WN))
	{
		Geom_PrOctantTreeLeaf<T>* Ptr = WN[Index];
		Ptr->theENeighbors_.Remove(Old);
	}

	forThose(Index, 0, MaxIndexOf(FN))
	{
		Geom_PrOctantTreeLeaf<T>* Ptr = FN[Index];
		Ptr->theBNeighbors_.Remove(Old);
	}

	forThose(Index, 0, MaxIndexOf(BN))
	{
		Geom_PrOctantTreeLeaf<T>* Ptr = BN[Index];
		Ptr->theFNeighbors_.Remove(Old);
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrOctTree<T>::FillNeighbors
(
	Geom_PrOctantInfo Octant,
	Geom_PrOctantTreeLeaf<T>* Old,
	Geom_PrOctantTreeInternal<T>* Father,
	Geom_PrOctantTreeLeaf<T>* t
)
{
	ADT_Ary1d<Geom_PrOctantTreeLeaf<T>*> SN, EN, NN, WN, FN, BN;

	Old->theSNeighbors_.RetrieveTo(SN);
	Old->theENeighbors_.RetrieveTo(EN);
	Old->theNNeighbors_.RetrieveTo(NN);
	Old->theWNeighbors_.RetrieveTo(WN);
	Old->theBNeighbors_.RetrieveTo(BN);
	Old->theFNeighbors_.RetrieveTo(FN);

	Geom_PrOctantTreeLeaf<T>* Fwd_SwPtr, *Fwd_SePtr, *Fwd_NePtr, *Fwd_NwPtr;
	Geom_PrOctantTreeLeaf<T>* Bwd_SwPtr, *Bwd_SePtr, *Bwd_NePtr, *Bwd_NwPtr;

	Fwd_SwPtr = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(Father->theFwd_SwPtr_);
	Fwd_SePtr = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(Father->theFwd_SePtr_);
	Fwd_NePtr = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(Father->theFwd_NePtr_);
	Fwd_NwPtr = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(Father->theFwd_NwPtr_);
	Bwd_SwPtr = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(Father->theBwd_SwPtr_);
	Bwd_SePtr = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(Father->theBwd_SePtr_);
	Bwd_NePtr = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(Father->theBwd_NePtr_);
	Bwd_NwPtr = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(Father->theBwd_NwPtr_);

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

	ADT_BasicQueue<Geom_PrOctantTreeLeaf<T>*> QSN, QEN, QNN, QWN, QFN, QBN;

	if (Octant EQUAL Geom_PrOctantInfo_Fwd_SW)
	{
		if (WN.Size() <= 1) QWN.EnQueue(WN);
		else
		{
			forThose(Index, 0, MaxIndexOf(WN))
			{
				switch (CalcOctant(WN[Index]->theBox_.CalcCentre(), Centre))
				{
				case Geom_PrOctantInfo_Fwd_SW: QWN.EnQueue(WN[Index]); break;
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
				case Geom_PrOctantInfo_Fwd_SW: QSN.EnQueue(SN[Index]); break;
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
				case Geom_PrOctantInfo_Fwd_SW: QFN.EnQueue(FN[Index]); break;
				default: break;
				}
			}
		}
	}
	else if (Octant EQUAL Geom_PrOctantInfo_Fwd_SE)
	{
		if (SN.Size() <= 1) QSN.EnQueue(SN);
		else
		{
			forThose(Index, 0, MaxIndexOf(SN))
			{
				switch (CalcOctant(SN[Index]->theBox_.CalcCentre(), Centre))
				{
				case Geom_PrOctantInfo_Fwd_SE: QSN.EnQueue(SN[Index]); break;
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
				case Geom_PrOctantInfo_Fwd_SE: QEN.EnQueue(EN[Index]); break;
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
				case Geom_PrOctantInfo_Fwd_SE: QFN.EnQueue(FN[Index]); break;
				default: break;
				}
			}
		}
	}
	else if (Octant EQUAL Geom_PrOctantInfo_Fwd_NE)
	{
		if (EN.Size() <= 1) QEN.EnQueue(EN);
		else
		{
			forThose(Index, 0, MaxIndexOf(EN))
			{
				switch (CalcOctant(EN[Index]->theBox_.CalcCentre(), Centre))
				{
				case Geom_PrOctantInfo_Fwd_NE: QEN.EnQueue(EN[Index]); break;
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
				case Geom_PrOctantInfo_Fwd_NE: QNN.EnQueue(NN[Index]); break;
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
				case Geom_PrOctantInfo_Fwd_NE: QFN.EnQueue(FN[Index]); break;
				default: break;
				}
			}
		}
	}
	else if (Octant EQUAL Geom_PrOctantInfo_Fwd_NW)
	{
		if (NN.Size() <= 1) QNN.EnQueue(NN);
		else
		{
			forThose(Index, 0, MaxIndexOf(NN))
			{
				switch (CalcOctant(NN[Index]->theBox_.CalcCentre(), Centre))
				{
				case Geom_PrOctantInfo_Fwd_NW: QNN.EnQueue(NN[Index]); break;
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
				case Geom_PrOctantInfo_Fwd_NW: QWN.EnQueue(WN[Index]); break;
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
				case Geom_PrOctantInfo_Fwd_NW: QFN.EnQueue(FN[Index]); break;
				default: break;
				}
			}
		}
	}
	else if (Octant EQUAL Geom_PrOctantInfo_Bwd_SW)
	{
		if (WN.Size() <= 1) QWN.EnQueue(WN);
		else
		{
			forThose(Index, 0, MaxIndexOf(WN))
			{
				switch (CalcOctant(WN[Index]->theBox_.CalcCentre(), Centre))
				{
				case Geom_PrOctantInfo_Bwd_SW: QWN.EnQueue(WN[Index]); break;
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
				case Geom_PrOctantInfo_Bwd_SW: QSN.EnQueue(SN[Index]); break;
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
				case Geom_PrOctantInfo_Bwd_SW: QBN.EnQueue(BN[Index]); break;
				default: break;
				}
			}
		}
	}
	else if (Octant EQUAL Geom_PrOctantInfo_Bwd_SE)
	{
		if (SN.Size() <= 1) QSN.EnQueue(SN);
		else
		{
			forThose(Index, 0, MaxIndexOf(SN))
			{
				switch (CalcOctant(SN[Index]->theBox_.CalcCentre(), Centre))
				{
				case Geom_PrOctantInfo_Bwd_SE: QSN.EnQueue(SN[Index]); break;
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
				case Geom_PrOctantInfo_Bwd_SE: QEN.EnQueue(EN[Index]); break;
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
				case Geom_PrOctantInfo_Bwd_SE: QBN.EnQueue(BN[Index]); break;
				default: break;
				}
			}
		}
	}
	else if (Octant EQUAL Geom_PrOctantInfo_Bwd_NE)
	{
		if (EN.Size() <= 1) QEN.EnQueue(EN);
		else
		{
			forThose(Index, 0, MaxIndexOf(EN))
			{
				switch (CalcOctant(EN[Index]->theBox_.CalcCentre(), Centre))
				{
				case Geom_PrOctantInfo_Bwd_NE: QEN.EnQueue(EN[Index]); break;
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
				case Geom_PrOctantInfo_Bwd_NE: QNN.EnQueue(NN[Index]); break;
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
				case Geom_PrOctantInfo_Bwd_NE: QBN.EnQueue(BN[Index]); break;
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
				case Geom_PrOctantInfo_Bwd_NW: QNN.EnQueue(NN[Index]); break;
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
				case Geom_PrOctantInfo_Bwd_NW: QWN.EnQueue(WN[Index]); break;
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
				case Geom_PrOctantInfo_Bwd_NW: QBN.EnQueue(BN[Index]); break;
				default: break;
				}
			}
		}
	}

	ADT_Ary1d<Geom_PrOctantTreeLeaf<T>*> nSN, nEN, nNN, nWN, nFN, nBN;
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
inline void AutLib::GeoLib::Geom_BalancedPrOctTree<T>::RetrieveTo
(
	Geom_PrOctantTreeNode<T>* t,
	TColEntity_HBasicQueueOfBox3d & Boxes
) const
{
	if (NOT t) return;

	Geom_PrOctantTreeLeaf<T>* Leaf = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(t);

	if (Leaf)
	{
		Boxes.EnQueue(new Entity_Box3d(Leaf->theBox_));
	}
	else
	{
		Geom_PrOctantTreeInternal<T>* Internal = dynamic_cast<Geom_PrOctantTreeInternal<T>*>(t);

		if (Internal->theFwd_SwPtr_) RetrieveTo(Internal->theFwd_SwPtr_, Boxes);
		if (Internal->theFwd_SePtr_) RetrieveTo(Internal->theFwd_SePtr_, Boxes);
		if (Internal->theFwd_NePtr_) RetrieveTo(Internal->theFwd_NePtr_, Boxes);
		if (Internal->theFwd_NwPtr_) RetrieveTo(Internal->theFwd_NwPtr_, Boxes);

		if (Internal->theBwd_SwPtr_) RetrieveTo(Internal->theBwd_SwPtr_, Boxes);
		if (Internal->theBwd_SePtr_) RetrieveTo(Internal->theBwd_SePtr_, Boxes);
		if (Internal->theBwd_NePtr_) RetrieveTo(Internal->theBwd_NePtr_, Boxes);
		if (Internal->theBwd_NwPtr_) RetrieveTo(Internal->theBwd_NwPtr_, Boxes);
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrOctTree<T>::Insert
(
	const T & Item,
	const Entity_Box3d & Region,
	Geom_PrOctantTreeNode<T>*& t
)
{
	if (t EQUAL NULL)
	{
		Geom_PrOctantTreeLeaf<T>* Leaf = new Geom_PrOctantTreeLeaf<T>(theBUCKET_SIZE_);

		Leaf->theBox_ = Region;
		Leaf->theBucket_.Insert(Item);

		t = Leaf;

		theNbItems_++;

		return;
	}

	Geom_PrOctantTreeLeaf<T>* Leaf = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(t);

	if (Leaf)
	{
		if (NOT Leaf->theBucket_.IsFull())
		{
			if (NOT Leaf->theBucket_.Insert(Item)) { THROW_STANDARD_EXCEPTION(" Duplicate Data"); }

			theNbItems_++;
			return;
		}
		else
		{
			theInnerSubdivision_++;

			if (theInnerSubdivision_ >= theMAX_INNER_SUBDIVISION_) { THROW_STANDARD_EXCEPTION(" Max Inner Subdivision EXCEEDED: Items are close too much!"); }

			ADT_Ary1d<T> pItems;
			Leaf->theBucket_.RetrieveTo(pItems);

			Geom_PrOctantTreeInternal<T>* Internal = new Geom_PrOctantTreeInternal<T>;
			Internal->theBox_ = t->theBox_;

			// Subdivide the Leaf
			Geom_PrOctantTreeLeaf<T>* Fwd_SwPtr = new Geom_PrOctantTreeLeaf<T>(theBUCKET_SIZE_);
			Geom_PrOctantTreeLeaf<T>* Fwd_SePtr = new Geom_PrOctantTreeLeaf<T>(theBUCKET_SIZE_);
			Geom_PrOctantTreeLeaf<T>* Fwd_NePtr = new Geom_PrOctantTreeLeaf<T>(theBUCKET_SIZE_);
			Geom_PrOctantTreeLeaf<T>* Fwd_NwPtr = new Geom_PrOctantTreeLeaf<T>(theBUCKET_SIZE_);
			Geom_PrOctantTreeLeaf<T>* Bwd_SwPtr = new Geom_PrOctantTreeLeaf<T>(theBUCKET_SIZE_);
			Geom_PrOctantTreeLeaf<T>* Bwd_SePtr = new Geom_PrOctantTreeLeaf<T>(theBUCKET_SIZE_);
			Geom_PrOctantTreeLeaf<T>* Bwd_NePtr = new Geom_PrOctantTreeLeaf<T>(theBUCKET_SIZE_);
			Geom_PrOctantTreeLeaf<T>* Bwd_NwPtr = new Geom_PrOctantTreeLeaf<T>(theBUCKET_SIZE_);

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

			Get_Const_Object(Box) = Internal->theBox_;

			Geom_Pnt3d Centre = Box.CalcCentre();

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

			FillNeighbors(Geom_PrOctantInfo_Fwd_SW, Leaf, Internal, Fwd_SwPtr);
			FillNeighbors(Geom_PrOctantInfo_Fwd_SE, Leaf, Internal, Fwd_SePtr);
			FillNeighbors(Geom_PrOctantInfo_Fwd_NE, Leaf, Internal, Fwd_NePtr);
			FillNeighbors(Geom_PrOctantInfo_Fwd_NW, Leaf, Internal, Fwd_NwPtr);
			FillNeighbors(Geom_PrOctantInfo_Bwd_SW, Leaf, Internal, Bwd_SwPtr);
			FillNeighbors(Geom_PrOctantInfo_Bwd_SE, Leaf, Internal, Bwd_SePtr);
			FillNeighbors(Geom_PrOctantInfo_Bwd_NE, Leaf, Internal, Bwd_NePtr);
			FillNeighbors(Geom_PrOctantInfo_Bwd_NW, Leaf, Internal, Bwd_NwPtr);

			theNbItems_ -= theBUCKET_SIZE_;

			FreePointer(t);

			t = Internal;

			forThose
			(
				Index,
				0,
				MaxIndexOf(pItems)
			)
			{
				Get_Const_Object(Coord) = theCoordOf(pItems[Index]);

				switch (CalcOctant(Coord, Centre))
				{
				case Geom_PrOctantInfo_Fwd_SW: Insert(pItems[Index], Fwd_SwPtr->theBox_, Internal->theFwd_SwPtr_); break;
				case Geom_PrOctantInfo_Fwd_SE: Insert(pItems[Index], Fwd_SePtr->theBox_, Internal->theFwd_SePtr_); break;
				case Geom_PrOctantInfo_Fwd_NE: Insert(pItems[Index], Fwd_NePtr->theBox_, Internal->theFwd_NePtr_); break;
				case Geom_PrOctantInfo_Fwd_NW: Insert(pItems[Index], Fwd_NwPtr->theBox_, Internal->theFwd_NwPtr_); break;
				case Geom_PrOctantInfo_Bwd_SW: Insert(pItems[Index], Bwd_SwPtr->theBox_, Internal->theBwd_SwPtr_); break;
				case Geom_PrOctantInfo_Bwd_SE: Insert(pItems[Index], Bwd_SePtr->theBox_, Internal->theBwd_SePtr_); break;
				case Geom_PrOctantInfo_Bwd_NE: Insert(pItems[Index], Bwd_NePtr->theBox_, Internal->theBwd_NePtr_); break;
				case Geom_PrOctantInfo_Bwd_NW: Insert(pItems[Index], Bwd_NwPtr->theBox_, Internal->theBwd_NwPtr_); break;
				}
			}

			// Insert new Item
			Get_Const_Object(Coord) = theCoordOf(Item);

			switch (CalcOctant(Coord, Centre))
			{
			case Geom_PrOctantInfo_Fwd_SW: Insert(Item, Fwd_SwPtr->theBox_, Internal->theFwd_SwPtr_); break;
			case Geom_PrOctantInfo_Fwd_SE: Insert(Item, Fwd_SePtr->theBox_, Internal->theFwd_SePtr_); break;
			case Geom_PrOctantInfo_Fwd_NE: Insert(Item, Fwd_NePtr->theBox_, Internal->theFwd_NePtr_); break;
			case Geom_PrOctantInfo_Fwd_NW: Insert(Item, Fwd_NwPtr->theBox_, Internal->theFwd_NwPtr_); break;
			case Geom_PrOctantInfo_Bwd_SW: Insert(Item, Bwd_SwPtr->theBox_, Internal->theBwd_SwPtr_); break;
			case Geom_PrOctantInfo_Bwd_SE: Insert(Item, Bwd_SePtr->theBox_, Internal->theBwd_SePtr_); break;
			case Geom_PrOctantInfo_Bwd_NE: Insert(Item, Bwd_NePtr->theBox_, Internal->theBwd_NePtr_); break;
			case Geom_PrOctantInfo_Bwd_NW: Insert(Item, Bwd_NwPtr->theBox_, Internal->theBwd_NwPtr_); break;
			}
		}
	}
	else
	{
		Geom_PrOctantTreeInternal<T>* Internal = dynamic_cast<Geom_PrOctantTreeInternal<T>*>(t);

		Get_Const_Object(Box) = Internal->theBox_;

		Geom_Pnt3d Centre = Box.CalcCentre();

		switch (CalcOctant(theCoordOf(Item), Centre))
		{
		case Geom_PrOctantInfo_Fwd_SW: Insert(Item, Box.Fwd_SwOctant(), Internal->theFwd_SwPtr_); break;
		case Geom_PrOctantInfo_Fwd_SE: Insert(Item, Box.Fwd_SeOctant(), Internal->theFwd_SePtr_); break;
		case Geom_PrOctantInfo_Fwd_NE: Insert(Item, Box.Fwd_NeOctant(), Internal->theFwd_NePtr_); break;
		case Geom_PrOctantInfo_Fwd_NW: Insert(Item, Box.Fwd_NwOctant(), Internal->theFwd_NwPtr_); break;
		case Geom_PrOctantInfo_Bwd_SW: Insert(Item, Box.Bwd_SwOctant(), Internal->theBwd_SwPtr_); break;
		case Geom_PrOctantInfo_Bwd_SE: Insert(Item, Box.Bwd_SeOctant(), Internal->theBwd_SePtr_); break;
		case Geom_PrOctantInfo_Bwd_NE: Insert(Item, Box.Bwd_NeOctant(), Internal->theBwd_NePtr_); break;
		case Geom_PrOctantInfo_Bwd_NW: Insert(Item, Box.Bwd_NwOctant(), Internal->theBwd_NwPtr_); break;
		}
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrOctTree<T>::Clear(Geom_PrOctantTreeNode<T>*& t)
{
	Geom_PrOctantTreeLeaf<T>* Leaf = dynamic_cast<Geom_PrOctantTreeLeaf<T>*>(t);

	if (Leaf)
	{
		Delete_Pointer(t);
	}
	else
	{
		Geom_PrOctantTreeInternal<T>* Internal = dynamic_cast<Geom_PrOctantTreeInternal<T>*>(t);

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