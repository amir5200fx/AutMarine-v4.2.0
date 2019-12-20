#pragma once
#include <Geometry_Tools.hxx>
#include <Geometry_Intersect.hxx>
#include <IO_TecPlot.hxx>

template<typename T>
inline AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::Geom_BalancedPrQuadTree()
	: theNbItems_(0)
	, theRoot_(NULL)
	, theBUCKET_SIZE_(4)
	, theMAX_INNER_SUBDIVISION_(20)
{
}

template<typename T>
inline AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::~Geom_BalancedPrQuadTree()
{
	Clear(theRoot_);
}

template<typename T>
inline Standard_Integer AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::Size() const
{
	return theNbItems_;
}

template<typename T>
inline Standard_Boolean AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::IsEmpty() const
{
	return theRoot_ EQUAL NULL;
}

template<typename T>
inline const M_GEO Entity_Box2d & AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::BoundingBox() const
{
	return theDomain_;
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::SetCoordinateFunction(const Geom_Pnt2d &(*Get_Coordinates)(T))
{
	theCoordOf = Get_Coordinates;
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::SetMaxInnerSubdivision(const Standard_Integer Value)
{
	theMAX_INNER_SUBDIVISION_ = Value;
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::SetBucketSize(const Standard_Integer Value)
{
	theBUCKET_SIZE_ = Value;
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::Insert(const T & Item)
{
	Debug_If_Condition_Message(theCoordOf EQUAL NULL, " No coordinate function for Pr-QuadTree");

	theInnerSubdivision_ = 0;

	Insert(Item, theDomain_, theRoot_);
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::Insert(const ADT_Ary1d<T>& Items)
{
	forThose(Index, 0, MaxIndexOf(Items))
	{
		Insert(Items[Index]);
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::Remove(const T & Item)
{
	Debug_If_Condition_Message(theCoordOf EQUAL NULL, " No coordinate function for Pr-QuadTree");

	Remove(Item, theRoot_);
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::PostBalancing()
{
	while (Standard_True)
	{
		IsBalancing_ = Standard_False;

		Balancing(theRoot_);

		if (NOT IsBalancing_) break;
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::RetrieveTo(TColEntity_HAry1dOfBox2d & Boxes) const
{
	TColEntity_HBasicQueueOfBox2d Q;

	RetrieveTo(theRoot_, Q);

	Q.RetrieveTo(Boxes);
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::SetRegion(const Entity_Box2d & Region)
{
	theDomain_ = Region;
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::ExportToPlt(fstream & File) const
{
	if (IsEmpty())
	{
		M_IO IO_TecPlot::ExportBox(theDomain_, File);
		return;
	}

	TColEntity_HAry1dOfBox2d Boxes;
	//ADT_Ary1d<T> Items;

	RetrieveTo(Boxes);
	//RetrieveTo(Items);

	//TColGeom_Array1OfPnt2d Coords(Items.Size());

	/*forThose(Index, 0, MaxIndexOf(Coords))
		Coords[Index] = theCoordOf(Items[Index]);*/

	M_IO IO_TecPlot::ExportBox(Boxes, File);
	//M_IO TecPlot::ExportPoints(Coords, File);

	FreeMemory(Boxes);
}

template<typename T>
inline M_GEO Geom_PrQuadrant AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::CalcQuadrant
(
	const Geom_Pnt2d & Coord,
	const Geom_Pnt2d & Centre
) const
{
	if (Coord.X() <= Centre.X())
		if (Coord.Y() <= Centre.Y())
			return Geom_PrQuadrant_SW;
		else
			return Geom_PrQuadrant_NW;
	else
	{
		if (Coord.Y() <= Centre.Y())
			return Geom_PrQuadrant_SE;
		else
			return Geom_PrQuadrant_NE;
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::Balancing(Geom_PrQuadTreeNode<T>* &t)
{
	if (NOT t) return;

	Geom_PrQuadTreeLeaf<T>* Leaf = dynamic_cast<Geom_PrQuadTreeLeaf<T>*>(t);

	if (Leaf)
	{
		Standard_Boolean doSubdivide = Standard_False;

		if (Leaf->theSNeighbors_.Size() > 2) doSubdivide = Standard_True;
		if (Leaf->theENeighbors_.Size() > 2) doSubdivide = Standard_True;
		if (Leaf->theNNeighbors_.Size() > 2) doSubdivide = Standard_True;
		if (Leaf->theWNeighbors_.Size() > 2) doSubdivide = Standard_True;

		if (NOT doSubdivide) return;

		if (NOT IsBalancing_) IsBalancing_ = Standard_True;

		ADT_Ary1d<T> pItems;
		Leaf->theBucket_.RetrieveTo(pItems);

		Geom_PrQuadTreeInternal<T>* Internal = new Geom_PrQuadTreeInternal<T>;
		Internal->theBox_ = t->theBox_;

		// Subdivide the Leaf
		Geom_PrQuadTreeLeaf<T>* SwPtr = new Geom_PrQuadTreeLeaf<T>(theBUCKET_SIZE_);
		Geom_PrQuadTreeLeaf<T>* SePtr = new Geom_PrQuadTreeLeaf<T>(theBUCKET_SIZE_);
		Geom_PrQuadTreeLeaf<T>* NePtr = new Geom_PrQuadTreeLeaf<T>(theBUCKET_SIZE_);
		Geom_PrQuadTreeLeaf<T>* NwPtr = new Geom_PrQuadTreeLeaf<T>(theBUCKET_SIZE_);

		Internal->theSwPtr_ = SwPtr;
		Internal->theSePtr_ = SePtr;
		Internal->theNePtr_ = NePtr;
		Internal->theNwPtr_ = NwPtr;

		InnerLinks(Internal);

		Get_Const_Object(Box) = Internal->theBox_;

		Geom_Pnt2d Centre = Box.CalcCentre();

		SwPtr->theBox_ = Box.SwQuarter();
		SePtr->theBox_ = Box.SeQuarter();
		NePtr->theBox_ = Box.NeQuarter();
		NwPtr->theBox_ = Box.NwQuarter();

		// Remove Old Leaf from Neighbors
		RemoveLeafFromNeighbors(Leaf);

		FillNeighbors(Geom_PrQuadrant_SW, Leaf, Internal, SwPtr);
		FillNeighbors(Geom_PrQuadrant_SE, Leaf, Internal, SePtr);
		FillNeighbors(Geom_PrQuadrant_NE, Leaf, Internal, NePtr);
		FillNeighbors(Geom_PrQuadrant_NW, Leaf, Internal, NwPtr);

		theNbItems_ -= pItems.Size();

		FreePointer(t);

		t = Internal;

		// Insert prior Items
		forThose
		(
			Index,
			0,
			MaxIndexOf(pItems)
		)
		{
			Get_Const_Object(Coord) = theCoordOf(pItems[Index]);

			switch (CalcQuadrant(Coord, Centre))
			{
			case Geom_PrQuadrant_SW:
				Insert(pItems[Index], SwPtr->theBox_, Internal->theSwPtr_);
				break;
			case Geom_PrQuadrant_SE:
				Insert(pItems[Index], SePtr->theBox_, Internal->theSePtr_);
				break;
			case Geom_PrQuadrant_NW:
				Insert(pItems[Index], NwPtr->theBox_, Internal->theNwPtr_);
				break;
			case Geom_PrQuadrant_NE:
				Insert(pItems[Index], NePtr->theBox_, Internal->theNePtr_);
				break;
			}
		}

		Balancing(Internal->theSwPtr_);
		Balancing(Internal->theSePtr_);
		Balancing(Internal->theNwPtr_);
		Balancing(Internal->theNePtr_);
	}
	else
	{
		Geom_PrQuadTreeInternal<T>* Internal = dynamic_cast<Geom_PrQuadTreeInternal<T>*>(t);
		Debug_Null_Pointer(Internal);

		Balancing(Internal->theSwPtr_);
		Balancing(Internal->theSePtr_);
		Balancing(Internal->theNePtr_);
		Balancing(Internal->theNwPtr_);
	}

}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::RemoveLeafFromNeighbors(Geom_PrQuadTreeLeaf<T>* Old)
{
	ADT_Ary1d<Geom_PrQuadTreeLeaf<T>*> SN, EN, NN, WN;
	Old->theSNeighbors_.RetrieveTo(SN);
	Old->theENeighbors_.RetrieveTo(EN);
	Old->theNNeighbors_.RetrieveTo(NN);
	Old->theWNeighbors_.RetrieveTo(WN);

	forThose(Index, 0, MaxIndexOf(SN))
	{
		Geom_PrQuadTreeLeaf<T>* Ptr = SN[Index];
		Ptr->theNNeighbors_.Remove(Old);
	}

	forThose(Index, 0, MaxIndexOf(EN))
	{
		Geom_PrQuadTreeLeaf<T>* Ptr = EN[Index];
		Ptr->theWNeighbors_.Remove(Old);
	}

	forThose(Index, 0, MaxIndexOf(NN))
	{
		Geom_PrQuadTreeLeaf<T>* Ptr = NN[Index];
		Ptr->theSNeighbors_.Remove(Old);
	}

	forThose(Index, 0, MaxIndexOf(WN))
	{
		Geom_PrQuadTreeLeaf<T>* Ptr = WN[Index];
		Ptr->theENeighbors_.Remove(Old);
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::InnerLinks(Geom_PrQuadTreeInternal<T>* Father)
{
	Geom_PrQuadTreeLeaf<T>* SwPtr, *SePtr, *NePtr, *NwPtr;
	SwPtr = dynamic_cast<Geom_PrQuadTreeLeaf<T>*>(Father->theSwPtr_);
	SePtr = dynamic_cast<Geom_PrQuadTreeLeaf<T>*>(Father->theSePtr_);
	NwPtr = dynamic_cast<Geom_PrQuadTreeLeaf<T>*>(Father->theNwPtr_);
	NePtr = dynamic_cast<Geom_PrQuadTreeLeaf<T>*>(Father->theNePtr_);

	Debug_Null_Pointer(SwPtr);
	Debug_Null_Pointer(SePtr);
	Debug_Null_Pointer(NwPtr);
	Debug_Null_Pointer(NePtr);

	SwPtr->theENeighbors_.EnQueue(SePtr);
	SwPtr->theNNeighbors_.EnQueue(NwPtr);

	SePtr->theWNeighbors_.EnQueue(SwPtr);
	SePtr->theNNeighbors_.EnQueue(NePtr);

	NePtr->theWNeighbors_.EnQueue(NwPtr);
	NePtr->theSNeighbors_.EnQueue(SePtr);

	NwPtr->theENeighbors_.EnQueue(NePtr);
	NwPtr->theSNeighbors_.EnQueue(SwPtr);
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::FillNeighbors
(
	Geom_PrQuadrant Quadrant,
	Geom_PrQuadTreeLeaf<T>* Old,
	Geom_PrQuadTreeInternal<T>* Father,
	Geom_PrQuadTreeLeaf<T>* t
)
{
	ADT_Ary1d<Geom_PrQuadTreeLeaf<T>*> SN, EN, NN, WN;
	Old->theSNeighbors_.RetrieveTo(SN);
	Old->theENeighbors_.RetrieveTo(EN);
	Old->theNNeighbors_.RetrieveTo(NN);
	Old->theWNeighbors_.RetrieveTo(WN);

	Geom_PrQuadTreeLeaf<T>* SwPtr, *SePtr, *NePtr, *NwPtr;
	SwPtr = dynamic_cast<Geom_PrQuadTreeLeaf<T>*>(Father->theSwPtr_);
	SePtr = dynamic_cast<Geom_PrQuadTreeLeaf<T>*>(Father->theSePtr_);
	NwPtr = dynamic_cast<Geom_PrQuadTreeLeaf<T>*>(Father->theNwPtr_);
	NePtr = dynamic_cast<Geom_PrQuadTreeLeaf<T>*>(Father->theNePtr_);

	Debug_Null_Pointer(SwPtr);
	Debug_Null_Pointer(SePtr);
	Debug_Null_Pointer(NwPtr);
	Debug_Null_Pointer(NePtr);
	
	Get_Const_Object(tBox) = Old->theBox_;
	Geom_Pnt2d Centre = tBox.CalcCentre();

	ADT_BasicQueue<Geom_PrQuadTreeLeaf<T>*> QSN, QEN, QNN, QWN;

	if (Quadrant EQUAL Geom_PrQuadrant_SW)
	{
		//QEN.EnQueue(SePtr);
		//QNN.EnQueue(NwPtr);

		if (WN.Size() <= 1) QWN.EnQueue(WN);
		else
		{
			forThose(Index, 0, MaxIndexOf(WN))
			{
				switch (CalcQuadrant(WN[Index]->theBox_.CalcCentre(), Centre))
				{
				case Geom_PrQuadrant_SW: QWN.EnQueue(WN[Index]); break;
				default: break;
				}
			}
		}

		if (SN.Size() <= 1) QSN.EnQueue(SN);
		else
		{
			forThose(Index, 0, MaxIndexOf(SN))
			{
				switch (CalcQuadrant(SN[Index]->theBox_.CalcCentre(), Centre))
				{
				case Geom_PrQuadrant_SW: QSN.EnQueue(SN[Index]); break;
				default: break;
				}
			}
		}
	}
	else if (Quadrant EQUAL Geom_PrQuadrant_SE)
	{
		//QWN.EnQueue(SwPtr);
		//QNN.EnQueue(NePtr);

		if (SN.Size() <= 1) QSN.EnQueue(SN);
		else
		{
			forThose(Index, 0, MaxIndexOf(SN))
			{
				switch (CalcQuadrant(SN[Index]->theBox_.CalcCentre(), Centre))
				{
				case Geom_PrQuadrant_SE: QSN.EnQueue(SN[Index]); break;
				default: break;
				}
			}
		}

		if (EN.Size() <= 1) QEN.EnQueue(EN);
		else
		{
			forThose(Index, 0, MaxIndexOf(EN))
			{
				switch (CalcQuadrant(EN[Index]->theBox_.CalcCentre(), Centre))
				{
				case Geom_PrQuadrant_SE: QEN.EnQueue(EN[Index]); break;
				default: break;
				}
			}
		}
	}
	else if (Quadrant EQUAL Geom_PrQuadrant_NE)
	{
		//QSN.EnQueue(SePtr);
		//QWN.EnQueue(NwPtr);

		if (EN.Size() <= 1) QEN.EnQueue(EN);
		else
		{
			forThose(Index, 0, MaxIndexOf(EN))
			{
				switch (CalcQuadrant(EN[Index]->theBox_.CalcCentre(), Centre))
				{
				case Geom_PrQuadrant_NE: QEN.EnQueue(EN[Index]); break;
				default: break;
				}
			}
		}

		if (NN.Size() <= 1) QNN.EnQueue(NN);
		else
		{
			forThose(Index, 0, MaxIndexOf(NN))
			{
				switch (CalcQuadrant(NN[Index]->theBox_.CalcCentre(), Centre))
				{
				case Geom_PrQuadrant_NE: QNN.EnQueue(NN[Index]); break;
				default: break;
				}
			}
		}
	}
	else
	{
		//QEN.EnQueue(NePtr);
		//QSN.EnQueue(SwPtr);

		if (NN.Size() <= 1) QNN.EnQueue(NN);
		else
		{
			forThose(Index, 0, MaxIndexOf(NN))
			{
				switch (CalcQuadrant(NN[Index]->theBox_.CalcCentre(), Centre))
				{
				case Geom_PrQuadrant_NW: QNN.EnQueue(NN[Index]); break;
				default: break;
				}
			}
		}

		if (WN.Size() <= 1) QWN.EnQueue(WN);
		else
		{
			forThose(Index, 0, MaxIndexOf(WN))
			{
				switch (CalcQuadrant(WN[Index]->theBox_.CalcCentre(), Centre))
				{
				case Geom_PrQuadrant_NW: QWN.EnQueue(WN[Index]); break;
				default: break;
				}
			}
		}
	}

	ADT_Ary1d<Geom_PrQuadTreeLeaf<T>*> nSN, nEN, nNN, nWN;
	QSN.RetrieveTo(nSN);
	QEN.RetrieveTo(nEN);
	QNN.RetrieveTo(nNN);
	QWN.RetrieveTo(nWN);

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

	t->theSNeighbors_.EnQueue(QSN.Retrive());
	t->theENeighbors_.EnQueue(QEN.Retrive());
	t->theNNeighbors_.EnQueue(QNN.Retrive());
	t->theWNeighbors_.EnQueue(QWN.Retrive());
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::RetrieveTo
(
	Geom_PrQuadTreeNode<T>* t,
	TColEntity_HBasicQueueOfBox2d & Boxes
) const
{
	if (NOT t) return;

	Geom_PrQuadTreeLeaf<T>* Leaf = dynamic_cast<Geom_PrQuadTreeLeaf<T>*>(t);

	if (Leaf)
	{
		Boxes.EnQueue(new Entity_Box2d(Leaf->theBox_));
	}
	else
	{
		Geom_PrQuadTreeInternal<T>* Internal = dynamic_cast<Geom_PrQuadTreeInternal<T>*>(t);

		if (Internal->theSwPtr_) RetrieveTo(Internal->theSwPtr_, Boxes);
		if (Internal->theSePtr_) RetrieveTo(Internal->theSePtr_, Boxes);
		if (Internal->theNwPtr_) RetrieveTo(Internal->theNwPtr_, Boxes);
		if (Internal->theNePtr_) RetrieveTo(Internal->theNePtr_, Boxes);
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::Insert
(
	const T & Item, 
	const Entity_Box2d & Region,
	/*ADT_Ary1d<Geom_PrQuadTreeLeaf<T>*>* SNeighbors,
	ADT_Ary1d<Geom_PrQuadTreeLeaf<T>*>* ENeighbors,
	ADT_Ary1d<Geom_PrQuadTreeLeaf<T>*>* NNeighbors,
	ADT_Ary1d<Geom_PrQuadTreeLeaf<T>*>* WNeighbors,*/
	/*Geom_PrQuadTreeNode<T>* Father,*/
	Geom_PrQuadTreeNode<T>*& t
)
{
	if (t EQUAL NULL)
	{
		Geom_PrQuadTreeLeaf<T>* Leaf = new Geom_PrQuadTreeLeaf<T>(theBUCKET_SIZE_);

		Leaf->theBox_ = Region;
		Leaf->theBucket_.Insert(Item);

		t = Leaf;

		theNbItems_++;

		return;
	}

	Geom_PrQuadTreeLeaf<T>* Leaf = dynamic_cast<Geom_PrQuadTreeLeaf<T>*>(t);

	if (Leaf)
	{
		if (NOT Leaf->theBucket_.IsFull())
		{
			if (NOT Leaf->theBucket_.Insert(Item))
			{
				THROW_STANDARD_EXCEPTION(" Duplicate Data");
				return;
			}

			theNbItems_++;
			return;
		}
		else
		{
			theInnerSubdivision_++;

			if (theInnerSubdivision_ >= theMAX_INNER_SUBDIVISION_)
			{
				THROW_STANDARD_EXCEPTION(" Max Inner Subdivision EXCEEDED: Items are close too much!");
				return;
			}

			ADT_Ary1d<T> pItems;
			Leaf->theBucket_.RetrieveTo(pItems);

			Geom_PrQuadTreeInternal<T>* Internal = new Geom_PrQuadTreeInternal<T>;
			Internal->theBox_ = t->theBox_;

			// Subdivide the Leaf
			Geom_PrQuadTreeLeaf<T>* SwPtr = new Geom_PrQuadTreeLeaf<T>(theBUCKET_SIZE_);
			Geom_PrQuadTreeLeaf<T>* SePtr = new Geom_PrQuadTreeLeaf<T>(theBUCKET_SIZE_);
			Geom_PrQuadTreeLeaf<T>* NePtr = new Geom_PrQuadTreeLeaf<T>(theBUCKET_SIZE_);
			Geom_PrQuadTreeLeaf<T>* NwPtr = new Geom_PrQuadTreeLeaf<T>(theBUCKET_SIZE_);

			Internal->theSwPtr_ = SwPtr;
			Internal->theSePtr_ = SePtr;
			Internal->theNePtr_ = NePtr;
			Internal->theNwPtr_ = NwPtr;

			InnerLinks(Internal);

			Get_Const_Object(Box) = Internal->theBox_;

			Geom_Pnt2d Centre = Box.CalcCentre();

			SwPtr->theBox_ = Box.SwQuarter();
			SePtr->theBox_ = Box.SeQuarter();
			NePtr->theBox_ = Box.NeQuarter();
			NwPtr->theBox_ = Box.NwQuarter();

			// Remove Old Leaf from Neighbors
			RemoveLeafFromNeighbors(Leaf);

			FillNeighbors(Geom_PrQuadrant_SW, Leaf, Internal, SwPtr);
			FillNeighbors(Geom_PrQuadrant_SE, Leaf, Internal, SePtr);
			FillNeighbors(Geom_PrQuadrant_NE, Leaf, Internal, NePtr);
			FillNeighbors(Geom_PrQuadrant_NW, Leaf, Internal, NwPtr);
			
			theNbItems_ -= theBUCKET_SIZE_;

			FreePointer(t);

			t = Internal;

			// Insert prior Items
			forThose
			(
				Index,
				0,
				MaxIndexOf(pItems)
			)
			{
				Get_Const_Object(Coord) = theCoordOf(pItems[Index]);

				switch (CalcQuadrant(Coord, Centre))
				{
				case Geom_PrQuadrant_SW:
					Insert(pItems[Index], SwPtr->theBox_, Internal->theSwPtr_);
					break;
				case Geom_PrQuadrant_SE:
					Insert(pItems[Index], SePtr->theBox_, Internal->theSePtr_);
					break;
				case Geom_PrQuadrant_NW:
					Insert(pItems[Index], NwPtr->theBox_, Internal->theNwPtr_);
					break;
				case Geom_PrQuadrant_NE:
					Insert(pItems[Index], NePtr->theBox_, Internal->theNePtr_);
					break;
				}
			}

			// Insert new Item
			Get_Const_Object(Coord) = theCoordOf(Item);

			switch (CalcQuadrant(Coord, Centre))
			{
			case Geom_PrQuadrant_SW:
				Insert(Item, SwPtr->theBox_, Internal->theSwPtr_);
				break;
			case Geom_PrQuadrant_SE:
				Insert(Item, SePtr->theBox_, Internal->theSePtr_);
				break;
			case Geom_PrQuadrant_NW:
				Insert(Item, NwPtr->theBox_, Internal->theNwPtr_);
				break;
			case Geom_PrQuadrant_NE:
				Insert(Item, NePtr->theBox_, Internal->theNePtr_);
				break;
			}
		}
	}
	else
	{
		Geom_PrQuadTreeInternal<T>* Internal = dynamic_cast<Geom_PrQuadTreeInternal<T>*>(t);

		Get_Const_Object(Box) = Internal->theBox_;

		Geom_Pnt2d Centre = Box.CalcCentre();

		switch (CalcQuadrant(theCoordOf(Item), Centre))
		{
		case Geom_PrQuadrant_SW:
			Insert(Item, Box.SwQuarter(), Internal->theSwPtr_);
			break;
		case Geom_PrQuadrant_SE:
			Insert(Item, Box.SeQuarter(), Internal->theSePtr_);
			break;
		case Geom_PrQuadrant_NW:
			Insert(Item, Box.NwQuarter(), Internal->theNwPtr_);
			break;
		case Geom_PrQuadrant_NE:
			Insert(Item, Box.NeQuarter(), Internal->theNePtr_);
			break;
		}
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::Remove
(
	const T & Item,
	Geom_PrQuadTreeNode<T>*& t
)
{
	if (t EQUAL NULL)
	{
		THROW_STANDARD_EXCEPTION(" Item is not in tree");
		return;
	}

	Geom_PrQuadTreeLeaf<T>* Leaf = dynamic_cast<Geom_PrQuadTreeLeaf<T>*>(t);

	if (Leaf)
	{
		if (NOT Leaf->theBucket_.Remove(Item))
		{
			THROW_STANDARD_EXCEPTION(" Item is not in tree");
			return;
		}

		theNbItems_--;

		if (Leaf->theBucket_.IsEmpty())
		{
			FreePointer(t);
		}
	}
	else
	{
		Geom_PrQuadTreeInternal<T>* Internal = dynamic_cast<Geom_PrQuadTreeInternal<T>*>(t);

		switch (CalcQuadrant(theCoordOf(Item), Internal->theBox_.CalcCentre()))
		{
		case Geom_PrQuadrant_SW:
			Remove(Item, Internal->theSwPtr_);
			break;
		case Geom_PrQuadrant_SE:
			Remove(Item, Internal->theSePtr_);
			break;
		case Geom_PrQuadrant_NW:
			Remove(Item, Internal->theNwPtr_);
			break;
		case Geom_PrQuadrant_NE:
			Remove(Item, Internal->theNePtr_);
			break;
		}

		if (Internal->IsEmpty())
		{
			FreePointer(t);
		}
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::Search(const Entity_Box2d & Region, Geom_PrQuadTreeNode<T>* t, ADT_BasicQueue<T>& QItems) const
{
	Geom_PrQuadTreeLeaf<T>* Leaf = dynamic_cast<Geom_PrQuadTreeLeaf<T>*>(t);

	if (Leaf)
	{
		ADT_Ary1d<T> Items;

		Leaf->theBucket_.RetrieveTo(Items);

		forThose(Index, 0, MaxIndexOf(Items))
		{
			if (Geometry_Tools::IsPointInsideOnBox(theCoordOf(Items[Index]), Region.Xmin(), Region.Xmax(), Region.Ymin(), Region.Ymax()))
			{
				QItems.EnQueue(Items[Index]);
			}
		}
	}
	else
	{
		Geom_PrQuadTreeInternal<T>* Internal = dynamic_cast<Geom_PrQuadTreeInternal<T>*>(t);

		if (Internal->theSwPtr_)
		{
			if (Geometry_Intersect::IsIntersect(Region, Internal->theSwPtr_->theBox_))
				Search(Region, Internal->theSwPtr_, QItems);
		}
		if (Internal->theSePtr_)
		{
			if (Geometry_Intersect::IsIntersect(Region, Internal->theSePtr_->theBox_))
				Search(Region, Internal->theSePtr_, QItems);
		}
		if (Internal->theNwPtr_)
		{
			if (Geometry_Intersect::IsIntersect(Region, Internal->theNwPtr_->theBox_))
				Search(Region, Internal->theNwPtr_, QItems);
		}
		if (Internal->theNePtr_)
		{
			if (Geometry_Intersect::IsIntersect(Region, Internal->theNePtr_->theBox_))
				Search(Region, Internal->theNePtr_, QItems);
		}
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_BalancedPrQuadTree<T>::Clear(Geom_PrQuadTreeNode<T>*& t)
{
	Geom_PrQuadTreeLeaf<T>* Leaf = dynamic_cast<Geom_PrQuadTreeLeaf<T>*>(t);

	if (Leaf)
	{
		Delete_Pointer(t);
	}
	else
	{
		Geom_PrQuadTreeInternal<T>* Internal = dynamic_cast<Geom_PrQuadTreeInternal<T>*>(t);

		if (Internal->theSwPtr_) Clear(Internal->theSwPtr_);
		if (Internal->theSePtr_) Clear(Internal->theSePtr_);
		if (Internal->theNePtr_) Clear(Internal->theNePtr_);
		if (Internal->theNwPtr_) Clear(Internal->theNwPtr_);

		Delete_Pointer(t);
	}
}