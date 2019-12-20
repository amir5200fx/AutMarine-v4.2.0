#pragma once
#include <Geom_Geometry.hxx>
#include <Geometry_Intersect.hxx>
#include <IO_TecPlot.hxx>

template<typename T>
inline AutLib::GeoLib::Geom_PrQuadTree<T>::Geom_PrQuadTree()
	: theNbItems_(0)
	, theRoot_(NULL)
	, theBUCKET_SIZE_(4)
	, theMAX_INNER_SUBDIVISION_(20)
{
}

template<typename T>
inline AutLib::GeoLib::Geom_PrQuadTree<T>::~Geom_PrQuadTree()
{
	Clear(theRoot_);
}

template<typename T>
inline Standard_Integer AutLib::GeoLib::Geom_PrQuadTree<T>::Size() const
{
	return theNbItems_;
}

template<typename T>
inline Standard_Boolean AutLib::GeoLib::Geom_PrQuadTree<T>::IsEmpty() const
{
	return theRoot_ EQUAL NULL;
}

template<typename T>
inline const M_GEO Entity_Box2d & AutLib::GeoLib::Geom_PrQuadTree<T>::BoundingBox() const
{
	return theDomain_;
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadTree<T>::SetCoordinateFunction(const Geom_Pnt2d &(*Get_Coordinates)(T))
{
	theCoordOf = Get_Coordinates;
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadTree<T>::SetMaxInnerSubdivision(const Standard_Integer Value)
{
	theMAX_INNER_SUBDIVISION_ = Value;
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadTree<T>::SetBucketSize(const Standard_Integer Value)
{
	theBUCKET_SIZE_ = Value;
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadTree<T>::Insert(const T & Item)
{
	Debug_If_Condition_Message(theCoordOf EQUAL NULL, " No coordinate function for Pr-QuadTree");

	theInnerSubdivision_ = 0;

	Insert(Item, theDomain_, theRoot_);
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadTree<T>::Insert(const ADT_Ary1d<T>& Items)
{
	forThose(Index, 0, MaxIndexOf(Items))
	{
		Insert(Items[Index]);
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadTree<T>::Remove(const T & Item)
{
	Debug_If_Condition_Message(theCoordOf EQUAL NULL, " No coordinate function for Pr-QuadTree");

	Remove(Item, theRoot_);
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadTree<T>::RetrieveTo(ADT_Ary1d<T>& Items) const
{
	ADT_BasicQueue<T> Q;

	RetrieveTo(theRoot_, Q);

	Q.RetrieveTo(Items);
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadTree<T>::RetrieveTo(TColGeom_HArray1OfBox2d & Boxes) const
{
	TColEntity_HBasicQueueOfBox2d Q;

	RetrieveTo(theRoot_, Q);

	Q.RetrieveTo(Boxes);
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadTree<T>::SetRegion(const Entity_Box2d & Region)
{
	theDomain_ = Region;
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadTree<T>::Search
(
	const Entity_Box2d & Region,
	ADT_Ary1d<T>& Items
) const
{
	Debug_If_Condition_Message(theCoordOf EQUAL NULL, " No coordinate function for Pr-QuadTree");

	ADT_BasicQueue<T> Q;
	
	Search(Region, theRoot_, Q);
	//system("pause");
	Q.RetrieveTo(Items);
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadTree<T>::ExportToPlt(fstream & File) const
{
	if (IsEmpty())
	{
		M_IO TecPlot::ExportBox(theDomain_, File);
		return;
	}

	TColGeom_HArray1OfBox2d Boxes;
	ADT_Ary1d<T> Items;

	RetrieveTo(Boxes);
	RetrieveTo(Items);

	TColGeom_Array1OfPnt2d Coords(Items.Size());

	forThose(Index, 0, MaxIndexOf(Coords))
		Coords[Index] = theCoordOf(Items[Index]);

	M_IO TecPlot::ExportBox(Boxes, File);
	M_IO TecPlot::ExportPoints(Coords, File);

	FreeMemory(Boxes);
}

template<typename T>
inline M_GEO Geom_PrQuadrant AutLib::GeoLib::Geom_PrQuadTree<T>::CalcQuadrant
(
	const Geom_Pnt2d& Coord,
	const Geom_Pnt2d& Centre
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
inline void AutLib::GeoLib::Geom_PrQuadTree<T>::RetrieveTo
(
	Geom_PrQuadTreeNode<T>* t,
	ADT_BasicQueue<T>& QItems
) const
{
	if (t EQUAL NULL)
		return;
	
	Geom_PrQuadTreeLeaf<T>* Leaf = dynamic_cast<Geom_PrQuadTreeLeaf<T>*>(t);

	if (Leaf)
	{
		ADT_Ary1d<T> Items;

		Leaf->theBucket_.RetrieveTo(Items);

		forThose(Index, 0, MaxIndexOf(Items))
		{
			QItems.EnQueue(Items[Index]);
		}
	}
	else
	{
		Geom_PrQuadTreeInternal<T>* Internal = dynamic_cast<Geom_PrQuadTreeInternal<T>*>(t);

		RetrieveTo(Internal->theSwPtr_, QItems);
		RetrieveTo(Internal->theSePtr_, QItems);
		RetrieveTo(Internal->theNwPtr_, QItems);
		RetrieveTo(Internal->theNePtr_, QItems);
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadTree<T>::RetrieveTo
(
	Geom_PrQuadTreeNode<T>* t,
	TColGeom_HBasicQueueOfBox2d& Boxes
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
		else Boxes.EnQueue(new Entity_Box2d(Internal->theBox_.SwQuarter()));

		if (Internal->theSePtr_) RetrieveTo(Internal->theSePtr_, Boxes);
		else Boxes.EnQueue(new Entity_Box2d(Internal->theBox_.SeQuarter()));

		if (Internal->theNwPtr_) RetrieveTo(Internal->theNwPtr_, Boxes);
		else Boxes.EnQueue(new Entity_Box2d(Internal->theBox_.NwQuarter()));

		if (Internal->theNePtr_) RetrieveTo(Internal->theNePtr_, Boxes);
		else Boxes.EnQueue(new Entity_Box2d(Internal->theBox_.NeQuarter()));
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadTree<T>::Insert
(
	const T & Item,
	const Entity_Box2d & Region,
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

			theNbItems_ -= theBUCKET_SIZE_;

			FreePointer(t);

			t = Internal;

			Get_Const_Object(Box) = Internal->theBox_;

			Geom_Pnt2d Centre = Box.CalcCentre();
			
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
					Insert(pItems[Index], Box.SwQuarter(), Internal->theSwPtr_);
					break;
				case Geom_PrQuadrant_SE:
					Insert(pItems[Index], Box.SeQuarter(), Internal->theSePtr_);
					break;
				case Geom_PrQuadrant_NW:
					Insert(pItems[Index], Box.NwQuarter(), Internal->theNwPtr_);
					break;
				case Geom_PrQuadrant_NE:
					Insert(pItems[Index], Box.NeQuarter(), Internal->theNePtr_);
					break;
				}
			}

			// Insert new Item
			Get_Const_Object(Coord) = theCoordOf(Item);

			switch (CalcQuadrant(Coord, Centre))
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
inline void AutLib::GeoLib::Geom_PrQuadTree<T>::Remove
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
inline void AutLib::GeoLib::Geom_PrQuadTree<T>::Search
(
	const Entity_Box2d & Region,
	Geom_PrQuadTreeNode<T>* t,
	ADT_BasicQueue<T>& QItems
) const
{
	/*if (NOT t)
		return;*/  // Null pointer
	
	/*if (NOT Geom_Intersect::IsIntersect(Region, t->theBox_))
		return;*/
	//cout << "Search" << endl;
	Geom_PrQuadTreeLeaf<T>* Leaf = dynamic_cast<Geom_PrQuadTreeLeaf<T>*>(t);

	if (Leaf)
	{
		ADT_Ary1d<T> Items;

		Leaf->theBucket_.RetrieveTo(Items);

		forThose(Index, 0, MaxIndexOf(Items))
		{
			if (Geom_Geometry::IsPointInsideOnBox(theCoordOf(Items[Index]), Region.Xmin(), Region.Xmax(), Region.Ymin(), Region.Ymax()))
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
			if (Geom_Intersect::IsIntersect(Region, Internal->theSwPtr_->theBox_))
				Search(Region, Internal->theSwPtr_, QItems);
		}
		if (Internal->theSePtr_)
		{
			if (Geom_Intersect::IsIntersect(Region, Internal->theSePtr_->theBox_))
				Search(Region, Internal->theSePtr_, QItems);
		}
		if (Internal->theNwPtr_)
		{
			if (Geom_Intersect::IsIntersect(Region, Internal->theNwPtr_->theBox_))
				Search(Region, Internal->theNwPtr_, QItems);
		}
		if (Internal->theNePtr_)
		{
			if (Geom_Intersect::IsIntersect(Region, Internal->theNePtr_->theBox_))
				Search(Region, Internal->theNePtr_, QItems);
		}
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadTree<T>::Clear(Geom_PrQuadTreeNode<T>*& t)
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