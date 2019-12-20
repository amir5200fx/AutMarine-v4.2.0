#pragma once

#include <Geometry_Intersect.hxx>
#include <Geometry_Tools.hxx>

template<typename T>
inline AutLib::GeoLib::Geom_ADTree2d<T>::Geom_ADTree2d()
	: NbItems_(0)
{
}

template<typename T>
inline AutLib::GeoLib::Geom_ADTree2d<T>::Geom_ADTree2d
(
	const Entity_Box2d & Region,
	const Geom_Pnt2d &(*Get_Coordinates)(const T &)
)
	: NbItems_(0)
{
	Root_ = NULL;

	Region_ = Region;

	Get_Coordinates_ = Get_Coordinates;
}

template<typename T>
inline AutLib::GeoLib::Geom_ADTree2d<T>::~Geom_ADTree2d()
{
	Clear();
}

template<typename T>
inline Standard_Integer AutLib::GeoLib::Geom_ADTree2d<T>::Size() const
{
	return NbItems_;
}

template<typename T>
inline Standard_Boolean AutLib::GeoLib::Geom_ADTree2d<T>::IsEmpty() const
{
	return Root_ == NULL;
}

template<typename T>
inline const M_GEO Entity_Box2d & AutLib::GeoLib::Geom_ADTree2d<T>::BoundingBox() const
{
	return Region_;
}

template<typename T>
inline void AutLib::GeoLib::Geom_ADTree2d<T>::SetCoordinateFunction(const Geom_Pnt2d &(*Get_Coordinates)(T))
{
	Get_Coordinates_ = Get_Coordinates;
}

template<typename T>
inline void AutLib::GeoLib::Geom_ADTree2d<T>::Insert(const T & Item)
{
	Debug_If_Condition_Message(Get_Coordinates_ EQUAL NULL, " No coordinate function for ADtree");

	Insert
	(
		Item,
		Region_,
		0,
		Root_
	);

	NbItems_++;
}

template<typename T>
inline void AutLib::GeoLib::Geom_ADTree2d<T>::Insert(const ADT_Ary1d<T>& Items)
{
	forThose(Index, 0, MaxIndexOf(Items))
	{
		Insert(Items[Index]);
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_ADTree2d<T>::Remove(const T & Item)
{
	Debug_If_Condition_Message(Get_Coordinates_ EQUAL NULL, " No coordinate function for ADtree");

	Remove(Item, Root_);

	NbItems_--;
}

template<typename T>
inline void AutLib::GeoLib::Geom_ADTree2d<T>::RetrieveTo(ADT_Ary1d<T>& Items) const
{
	ADT_BasicQueue<T> Q;

	RetrieveTo
	(
		Q,
		Root_
	);

	Q.RetrieveTo(Items);
}

template<typename T>
inline void AutLib::GeoLib::Geom_ADTree2d<T>::SetRegion(const Entity_Box2d & Region)
{
	Region_ = Region;
}

template<typename T>
inline void AutLib::GeoLib::Geom_ADTree2d<T>::Search
(
	const Entity_Box2d & Region,
	ADT_Ary1d<T>& Items
) const
{
	Debug_If_Condition_Message(Get_Coordinates_ EQUAL NULL, " No coordinate function for ADtree");

	ADT_BasicQueue<T> Q;

	Search
	(
		Region,
		Root_,
		Q
	);

	Q.RetrieveTo(Items);
}

template<typename T>
inline void AutLib::GeoLib::Geom_ADTree2d<T>::Clear()
{
	Clear(Root_);
}

template<typename T>
inline void AutLib::GeoLib::Geom_ADTree2d<T>::RetrieveTo
(
	ADT_BasicQueue<T>& Items,
	Geom_ADTree2dNode<T>* t
) const
{
	if (t)
	{
		RetrieveTo(Items, t->Left_);

		Items.EnQueue(t->Data_);

		RetrieveTo(Items, t->Right_);
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_ADTree2d<T>::Insert
(
	const T & Item, 
	const Entity_Box2d & Region,
	Standard_Integer Level,
	Geom_ADTree2dNode<T>*& t
)
{
	if (t == NULL)
	{
		t = new Geom_ADTree2dNode<T>(Item, Region, Level, 0, 0);

		return;
	}

	const Geom_Pnt2d Point = Get_Coordinates_(Item);

	Standard_Real
		X,
		Low,
		High;

	Standard_Integer Index = Level % 2;

	if (Index == 0)
	{
		X = Point.X();

		Low = Region.Xmin();
		High = Region.Xmax();
	}
	else
	{
		X = Point.Y();

		Low = Region.Ymin();
		High = Region.Ymax();
	}

	Standard_Real Mid = MEAN(Low, High);

	Standard_Real
		X1,
		X2,
		Y1,
		Y2;

	if (Index == 0)
	{
		Y1 = Region.Ymin();
		Y2 = Region.Ymax();

		if (X >= Low && X < Mid)
		{
			X1 = Low;
			X2 = Mid;
		}
		else
		{
			X1 = Mid;
			X2 = High;
		}
	}
	else
	{
		X1 = Region.Xmin();
		X2 = Region.Xmax();

		if (X >= Low && X < Mid)
		{
			Y1 = Low;
			Y2 = Mid;
		}
		else
		{
			Y1 = Mid;
			Y2 = High;
		}
	}

	if (X >= Low && X < Mid)
	{
		Insert
		(
			Item,
			Entity_Box2d(X1, X2, Y1, Y2),
			t->Level_ + 1,
			t->Left_
		);
	}
	else
	{
		Insert
		(
			Item,
			Entity_Box2d(X1, X2, Y1, Y2),
			t->Level_ + 1,
			t->Right_
		);
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_ADTree2d<T>::Remove
(
	const T & Item,
	Geom_ADTree2dNode<T>*& t
)
{
	if (t == NULL)
	{
		THROW_STANDARD_EXCEPTION(" Item not found");
	}

	if (Item EQUAL t->Data_)
	{
		if (t->Right_)
		{
			Geom_ADTree2dNode<T> *Leaf(0);

			FindLeaf(t->Right_, Leaf);

			t->Data_ = Leaf->Data_;

			Remove(t->Data_, t->Right_);
		}
		else if (t->Left_)
		{
			Geom_ADTree2dNode<T> *Leaf(0);

			FindLeaf(t->Left_, Leaf);

			t->Data_ = Leaf->Data_;

			Remove(t->Data_, t->Left_);
		}
		else
		{
			Geom_ADTree2dNode<T> * Old = t;

			t = (t->Left_) ? t->Left_ : t->Right_;

			delete Old;
		}
	}
	else
	{
		const Geom_Pnt2d & Point = Get_Coordinates_(Item);

		Standard_Integer Index = t->Level_ % 2;

		Standard_Real
			X,
			Low,
			High;

		if (!Index)
		{
			X = Point.X();

			Low = t->Region_.Xmin();
			High = t->Region_.Xmax();
		}
		else
		{
			X = Point.Y();

			Low = t->Region_.Ymin();
			High = t->Region_.Ymax();
		}

		Standard_Real Mid = MEAN(Low, High);

		if (X >= Low && X < Mid)
			Remove(Item, t->Left_);
		else
			Remove(Item, t->Right_);
	}
}

template<typename T>
inline void AutLib::GeoLib::Geom_ADTree2d<T>::Search
(
	const Entity_Box2d & Region,
	Geom_ADTree2dNode<T>* t,
	ADT_BasicQueue<T>& Items
) const
{
	if (NOT t)
	{
		return;
	}

	const Geom_Pnt2d & Point = Get_Coordinates_(t->Data_);

	Standard_Integer Index = t->Level_ % 2;

	Standard_Boolean
		Left,
		Right;

	if (Geometry_Tools::IsPointInsideOnBox(Point, Region.Xmin(), Region.Xmax(), Region.Ymin(), Region.Ymax()))
	{
		Items.EnQueue(t->Data_);
	}

	const Entity_Box2d& Box = t->Region_;

	if (!Index)
	{
		Standard_Real Xm = MEAN(Box.Xmin(), Box.Xmax());

		Left = Geometry_Intersect::IsIntersect
		(
			Region.Xmin(),
			Region.Xmax(),
			Box.Xmin(),
			Xm
		);

		Right = Geometry_Intersect::IsIntersect
		(
			Region.Xmin(),
			Region.Xmax(),
			Xm,
			Box.Xmax()
		);
	}
	else
	{
		Standard_Real Ym = MEAN(Box.Ymin(), Box.Ymax());

		Left = Geometry_Intersect::IsIntersect
		(
			Region.Ymin(),
			Region.Ymax(),
			Box.Ymin(),
			Ym
		);

		Right = Geometry_Intersect::IsIntersect
		(
			Region.Ymin(),
			Region.Ymax(),
			Ym,
			Box.Ymax()
		);
	}

	if (Left)
		Search
		(
			Region,
			t->Left_,
			Items
		);

	if (Right)
		Search
		(
			Region,
			t->Right_,
			Items
		);
}

template<typename T>
inline void AutLib::GeoLib::Geom_ADTree2d<T>::Clear(Geom_ADTree2dNode<T>* t)
{
	if (t NOT_EQUAL nullptr)
	{
		Clear(t->Left_);
		Clear(t->Right_);

		NbItems_--;

		delete t;
	}

	t = NULL;
}