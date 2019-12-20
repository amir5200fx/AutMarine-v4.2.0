#pragma once
template<typename T>
inline AutLib::GeoLib::Merge_Items2d<T>::Merge_Items2d()
	: IsDone_(Standard_False)
{
}

template<typename T>
inline AutLib::GeoLib::Merge_Items2d<T>::Merge_Items2d
(
	const Global_Handle(ADT_Ary1d<T>) Items,
	const Geom_Pnt2d &(*CoordinateFunction)(T)
)
	: theItems_(Items)
	, theCoordinateFunction_(CoordinateFunction)
	, IsDone_(Standard_False)
{
}

template<typename T>
inline void AutLib::GeoLib::Merge_Items2d<T>::Init
(
	const Global_Handle(ADT_Ary1d<T>) Items,
	const Geom_Pnt2d &(*CoordinateFunction)(T)
)
{
	theItems_ = Items;
	theCoordinateFunction_ = CoordinateFunction;
}

template<typename T>
inline void AutLib::GeoLib::Merge_Items2d<T>::SetItems(const Global_Handle(ADT_Ary1d<T>) Items)
{
	theItems_ = Items;
}

template<typename T>
inline void AutLib::GeoLib::Merge_Items2d<T>::SetCoordinateFunction(const Geom_Pnt2d &(*CoordinateFunction)(T))
{
	theCoordinateFunction_ = CoordinateFunction;
}

template<typename T>
inline void AutLib::GeoLib::Merge_Items2d<T>::Perform()
{
	IsDone_ = Standard_True;

	TColGeom_Ary1dOfPnt2d Points = GetCoordinates();

	Merge_Pnt2d Merge;
	Merge.SetCoords(&Points);

	Merge.Perform();

	TColStd_Ary1dOfInteger Indices = Merge.Indices();

	ADT_BasicQueue<T> List;
	const ADT_Ary1d<T>& Items = *theItems_;

	forThose(Index, 1, MaxIndexOf(Indices))
	{
		if (Indices[Index] EQUAL Index)
		{
			List.EnQueue(Items[Index_Of(Indices[Index])]);
		}
	}

	List.RetrieveTo(theMerged_);
}

template<typename T>
inline M_AUT ADT_Ary1d<T> AutLib::GeoLib::Merge_Items2d<T>::CompactItems() const
{
	return theMerged_;
}

template<typename T>
inline Standard_Boolean AutLib::GeoLib::Merge_Items2d<T>::IsDone() const
{
	return IsDone_;
}

template<typename T>
inline M_AUT TColGeom_Ary1dOfPnt2d AutLib::GeoLib::Merge_Items2d<T>::GetCoordinates() const
{
	TColGeom_Ary1dOfPnt2d Points(theItems_->Size());

	Get_Const_Object(Items) = *theItems_;

	forThose(Index, 0, MaxIndexOf(Points))
		Points[Index] = theCoordinateFunction_(Items[Index]);

	MOVE(Points);
}