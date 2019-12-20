#pragma once
#include <Geometry_Tools.hxx>
#include <Geometry_Intersect.hxx>
#include <IO_TecPlot.hxx>

template<typename T>
inline AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::Geom_PrQuadSingleObjectTree()
	: theNbItems_(0)
	, theRoot_(NULL)
	, theMAX_INNER_SUBDIVISION_(20)
{
}

template<typename T>
inline AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::~Geom_PrQuadSingleObjectTree()
{
	Clear(theRoot_);
}

template<typename T>
inline Standard_Integer AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::Size() const
{
	return theNbItems_;
}

template<typename T>
inline Standard_Boolean AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::IsEmpty() const
{
	return theRoot_ EQUAL NULL;
}

template<typename T>
inline const M_GEO Entity_Box2d & AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::BoundingBox() const
{
	return theDomain_;
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::SetCoordinateFunction(const Geom_Pnt2d &(*Get_Coordinates)(T))
{
	theCoordOf = Get_Coordinates;
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::SetMaxInnerSubdivision(const Standard_Integer Value)
{
	theMAX_INNER_SUBDIVISION_ = Value;
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::Insert(const T & Item)
{
	Debug_If_Condition_Message(theCoordOf EQUAL NULL, " No coordinate function for Pr-QuadTree");

	theInnerSubdivision_ = 0;

	Insert(Item, theDomain_, 0, theRoot_);
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::Insert(const ADT_Ary1d<T>& Items)
{
	forThose(Index, 0, MaxIndexOf(Items))
	{
		Insert(Items[Index]);
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::Remove(const T & Item)
{
	Debug_If_Condition_Message(theCoordOf EQUAL NULL, " No coordinate function for Pr-QuadTree");

	Remove(Item, theRoot_);
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::RetrieveTo(ADT_Ary1d<T>& Items) const
{
	ADT_BasicQueue<T> Q;

	RetrieveTo(theRoot_, Q);

	Q.RetrieveTo(Items);
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::RetrieveTo(TColGeom_HArray1OfBox2d & Boxes) const
{
	TColEntity_HBasicQueueOfBox2d Q;

	RetrieveTo(theRoot_, Q);

	Q.RetrieveTo(Boxes);
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::SetRegion(const Entity_Box2d & Region)
{
	theDomain_ = Region;
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::Search(const Entity_Box2d & Region, ADT_Ary1d<T>& Items) const
{
	Debug_If_Condition_Message(theCoordOf EQUAL NULL, " No coordinate function for Pr-QuadTree");

	ADT_BasicQueue<T> Q;

	Search(Region, theRoot_, Q);
	//system("pause");
	Q.RetrieveTo(Items);
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::ExportToPlt(fstream & File) const
{
	if (IsEmpty())
	{
		M_IO IO_TecPlot::ExportBox(theDomain_, File);
		return;
	}

	TColEntity_HAry1dOfBox2d Boxes;
	ADT_Ary1d<T> Items;

	RetrieveTo(Boxes);
	RetrieveTo(Items);

	TColGeom_Ary1dOfPnt2d Coords(Items.Size());

	forThose(Index, 0, MaxIndexOf(Coords))
		Coords[Index] = theCoordOf(Items[Index]);

	M_IO IO_TecPlot::ExportBox(Boxes, File);
	M_IO IO_TecPlot::ExportPoints(Coords, File);

	FreeMemory(Boxes);
}

//template<typename T>
//inline Standard_Integer AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::FindQuadrant(Geom_PrQuadTreeNode<T>* t) const
//{
//	Geom_PrQuadTreeNode<T>* Father = t->theFather_;
//
//	if (NOT Father) return -1;
//
//	Geom_PrQuadTreeInternal<T>* Internal = dynamic_cast<Geom_PrQuadTreeInternal<T>*>(Father);
//	cout << t << "  " << Internal << endl;
//	Debug_Null_Pointer(Internal);
//
//	if (Internal->theSwPtr_ == t) { return Geom_PrQuadrant_SW; }
//	if (Internal->theSePtr_ == t) { return Geom_PrQuadrant_SE; }
//	if (Internal->theNwPtr_ == t) { return Geom_PrQuadrant_NW; }
//	if (Internal->theNePtr_ == t) { return Geom_PrQuadrant_NE; }
//
//	CloseProgram(" Failed Identify Quadrant");
//
//	return 0;  // Prevent compiler warning
//}

template<typename T>
inline M_GEO Geom_PrQuadrant AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::CalcQuadrant(const Geom_Pnt2d & Coord, const Geom_Pnt2d & Centre) const
{
	if (Coord.X() <= Centre.X())
		if (Coord.Y() <= Centre.Y()) return Geom_PrQuadrant_SW;
		else return Geom_PrQuadrant_NW;
	else
	{
		if (Coord.Y() <= Centre.Y()) return Geom_PrQuadrant_SE;
		else return Geom_PrQuadrant_NE;
	}
}

//template<typename T>
//inline void AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::Balance(Geom_PrQuadTreeNode<T>*& t)
//{
//	const Standard_Integer Quad = FindQuadrant(t);
//
//	Geom_PrQuadTreeNode<T>* UnBalanced = 0;
//	Geom_PrQuadTreeNode<T>* Saved = t;
//
//	while (t->theFather_)
//	{
//		t = t->theFather_;
//		cout << "  Q = "  <<Quad <<"  " <<FindQuadrant(t) << endl;
//		if (Quad NOT_EQUAL FindQuadrant(t))
//		{
//			UnBalanced = t->theFather_;
//
//			break;
//		}
//	}
//	cout << "UnBalanced= " << UnBalanced << endl;
//	PAUSE;
//	if (UnBalanced)
//	{
//		cout << "UnBalanced" << endl;
//		PAUSE;
//		if (Quad == Geom_PrQuadrant_SW) { CreateQuadrant(UnBalanced, Geom_PrQuadrant_SW); }
//		if (Quad == Geom_PrQuadrant_SE) { CreateQuadrant(UnBalanced, Geom_PrQuadrant_SE); }
//		if (Quad == Geom_PrQuadrant_NW) { CreateQuadrant(UnBalanced, Geom_PrQuadrant_NW); }
//		if (Quad == Geom_PrQuadrant_NE) { CreateQuadrant(UnBalanced, Geom_PrQuadrant_NE); }
//	}
//
//	t = Saved;
//}

//template<typename T>
//inline void AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::CreateQuadrant(Geom_PrQuadTreeNode<T>*& t, const Standard_Integer Quadrant)
//{
//	Get_Const_Object(Box) = t->theBox_;
//
//	Geom_PrQuadTreeInternal<T>* Internal = dynamic_cast<Geom_PrQuadTreeInternal<T>*>(t);
//	Debug_Null_Pointer(Internal);
//
//	if (Quadrant == Geom_PrQuadrant_SW)
//	{
//		Internal->theSwPtr_ = new Geom_PrQuadTreeInternal<T>;
//		Internal->theSwPtr_->theBox_ = Box.SwQuarter();
//		Internal->theSwPtr_->theFather_ = t;
//
//		Balance(Internal->theSwPtr_);
//	}
//
//	if (Quadrant == Geom_PrQuadrant_SE)
//	{
//		Internal->theSePtr_ = new Geom_PrQuadTreeInternal<T>;
//		Internal->theSePtr_->theBox_ = Box.SeQuarter();
//		Internal->theSePtr_->theFather_ = t;
//
//		Balance(Internal->theSePtr_);
//	}
//
//	if (Quadrant == Geom_PrQuadrant_NW)
//	{
//		Internal->theNwPtr_ = new Geom_PrQuadTreeInternal<T>;
//		Internal->theNwPtr_->theBox_ = Box.NwQuarter();
//		Internal->theNwPtr_->theFather_ = t;
//
//		Balance(Internal->theNwPtr_);
//	}
//
//	if (Quadrant == Geom_PrQuadrant_NE)
//	{
//		Internal->theNePtr_ = new Geom_PrQuadTreeInternal<T>;
//		Internal->theNePtr_->theBox_ = Box.NeQuarter();
//		Internal->theNePtr_->theFather_ = t;
//
//		Balance(Internal->theNePtr_);
//	}
//}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::RetrieveTo(Geom_PrQuadTreeNode<T>* t, ADT_BasicQueue<T>& QItems) const
{
	if (t EQUAL NULL)
		return;

	Geom_PrQuadTreeSingleObjectLeaf<T>* Leaf = dynamic_cast<Geom_PrQuadTreeSingleObjectLeaf<T>*>(t);

	if (Leaf)
	{
		QItems.EnQueue(Leaf->theObject_);
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
inline void AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::RetrieveTo(Geom_PrQuadTreeNode<T>* t, TColEntity_HBasicQueueOfBox2d & Boxes) const
{
	if (t EQUAL NULL)
		return;

	Geom_PrQuadTreeSingleObjectLeaf<T>* Leaf = dynamic_cast<Geom_PrQuadTreeSingleObjectLeaf<T>*>(t);

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
inline void AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::Insert(const T & Item, const Entity_Box2d & Region, Geom_PrQuadTreeNode<T>* Father, Geom_PrQuadTreeNode<T>*& t)
{
	if (t EQUAL NULL)
	{
		Geom_PrQuadTreeSingleObjectLeaf<T>* Leaf = new Geom_PrQuadTreeSingleObjectLeaf<T>;

		Leaf->theObject_ = Item;
		Leaf->theBox_ = Region;

		t = Leaf;
		//t->theFather_ = Father;

		theNbItems_++;

		//Balance(t);

		return;
	}

	Geom_PrQuadTreeSingleObjectLeaf<T>* Leaf = dynamic_cast<Geom_PrQuadTreeSingleObjectLeaf<T>*>(t);

	if (Leaf)
	{
		theInnerSubdivision_++;

		if (theInnerSubdivision_ >= theMAX_INNER_SUBDIVISION_)
		{
			THROW_STANDARD_EXCEPTION(" Max Inner Subdivision EXCEEDED: Items are close too much!");
			return;
		}

		T pItem = Leaf->theObject_;

		Geom_PrQuadTreeInternal<T>* Internal = new Geom_PrQuadTreeInternal<T>;

		Internal->theBox_ = t->theBox_;
		//Internal->theFather_ = t->theFather_;

		theNbItems_--;

		FreePointer(t);

		t = Internal;

		Get_Const_Object(Box) = Internal->theBox_;

		Geom_Pnt2d Centre = Box.CalcCentre();

		switch (CalcQuadrant(theCoordOf(pItem), Centre))
		{
		case Geom_PrQuadrant_SW:
			Insert(pItem, Box.SwQuarter(), t, Internal->theSwPtr_);
			break;
		case Geom_PrQuadrant_SE:
			Insert(pItem, Box.SeQuarter(), t, Internal->theSePtr_);
			break;
		case Geom_PrQuadrant_NW:
			Insert(pItem, Box.NwQuarter(), t, Internal->theNwPtr_);
			break;
		case Geom_PrQuadrant_NE:
			Insert(pItem, Box.NeQuarter(), t, Internal->theNePtr_);
			break;
		}

		switch (CalcQuadrant(theCoordOf(Item), Centre))
		{
		case Geom_PrQuadrant_SW:
			Insert(Item, Box.SwQuarter(), t, Internal->theSwPtr_);
			break;
		case Geom_PrQuadrant_SE:
			Insert(Item, Box.SeQuarter(), t, Internal->theSePtr_);
			break;
		case Geom_PrQuadrant_NW:
			Insert(Item, Box.NwQuarter(), t, Internal->theNwPtr_);
			break;
		case Geom_PrQuadrant_NE:
			Insert(Item, Box.NeQuarter(), t, Internal->theNePtr_);
			break;
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
			Insert(Item, Box.SwQuarter(), t, Internal->theSwPtr_);
			break;
		case Geom_PrQuadrant_SE:
			Insert(Item, Box.SeQuarter(), t, Internal->theSePtr_);
			break;
		case Geom_PrQuadrant_NW:
			Insert(Item, Box.NwQuarter(), t, Internal->theNwPtr_);
			break;
		case Geom_PrQuadrant_NE:
			Insert(Item, Box.NeQuarter(), t, Internal->theNePtr_);
			break;
		}
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::Remove(const T & Item, Geom_PrQuadTreeNode<T>*& t)
{
	if (t EQUAL NULL)
	{
		THROW_STANDARD_EXCEPTION(" Item is not in tree");
		return;
	}

	Geom_PrQuadTreeSingleObjectLeaf<T>* Leaf = dynamic_cast<Geom_PrQuadTreeSingleObjectLeaf<T>*>(t);

	if (Leaf)
	{
		theNbItems_--;

		FreePointer(t);
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
inline void AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::Search(const Entity_Box2d & Region, Geom_PrQuadTreeNode<T>* t, ADT_BasicQueue<T>& QItems) const
{
	Geom_PrQuadTreeSingleObjectLeaf<T>* Leaf = dynamic_cast<Geom_PrQuadTreeSingleObjectLeaf<T>*>(t);

	if (Leaf)
	{
		if (Geom_Geometry::IsPointInsideOnBox(theCoordOf(Leaf->theObject_), Region.Xmin(), Region.Xmax(), Region.Ymin(), Region.Ymax()))
		{
			QItems.EnQueue(Leaf->theObject_);
		}
		//QItems.EnQueue(Leaf->theObject_);
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
inline void AutLib::GeoLib::Geom_PrQuadSingleObjectTree<T>::Clear(Geom_PrQuadTreeNode<T>* & t)
{
	Geom_PrQuadTreeSingleObjectLeaf<T>* Leaf = dynamic_cast<Geom_PrQuadTreeSingleObjectLeaf<T>*>(t);

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