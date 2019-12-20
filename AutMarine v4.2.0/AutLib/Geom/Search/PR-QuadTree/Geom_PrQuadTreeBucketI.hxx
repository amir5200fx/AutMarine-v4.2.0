#pragma once
template<typename T>
inline AutLib::GeoLib::Geom_PrQuadTreeBucket<T>::Geom_PrQuadTreeBucket(const Standard_Integer MaxItems)
	: theMaxItems_(MaxItems)
{
}

template<typename T>
inline Standard_Boolean AutLib::GeoLib::Geom_PrQuadTreeBucket<T>::IsEmpty() const
{
	return theBucket_.IsEmpty();
}

template<typename T>
inline Standard_Boolean AutLib::GeoLib::Geom_PrQuadTreeBucket<T>::IsFull() const
{
	return theBucket_.Size() >= theMaxItems_;
}

template<typename T>
inline Standard_Integer AutLib::GeoLib::Geom_PrQuadTreeBucket<T>::NbItems() const
{
	return theBucket_.Size();
}

template<typename T>
inline Standard_Boolean AutLib::GeoLib::Geom_PrQuadTreeBucket<T>::Insert(T Object)
{
	Debug_If_Condition_Message(theBucket_.Size() >= theMaxItems_, " The Bucket is full");

	/*ADT_Ary1d<T> Items;
	theBucket_.RetrieveTo(Items);

	forThose(Index, 0, MaxIndexOf(Items))
		if (Items[Index] EQUAL Object) return Standard_False;*/

	theBucket_.EnQueue(Object);
	//theBucket_.Insert(Object);

	return Standard_True;
}

template<typename T>
inline Standard_Boolean AutLib::GeoLib::Geom_PrQuadTreeBucket<T>::Remove(T Object)
{
	Debug_If_Condition_Message(theBucket_.IsEmpty(), " the Bucket is empty");

	Standard_Integer N0 = theBucket_.Size();

	theBucket_.Remove(Object);

	Standard_Integer N1 = theBucket_.Size();

	if (N1 < N0)
		return Standard_True;
	else
		return Standard_False;
}

template<typename T>
inline void AutLib::GeoLib::Geom_PrQuadTreeBucket<T>::RetrieveTo(ADT_Ary1d<T>& Items) const
{
	theBucket_.RetrieveTo(Items);
}