#pragma once
template<typename T>
inline AutLib::GeoLib::Geometry_Heap<T>::Geometry_Heap()
	: theSize_(0)
{
}

template<typename T>
inline AutLib::GeoLib::Geometry_Heap<T>::Geometry_Heap(Standard_Real(*LengthValue)(const T &))
	: theSize_(0)
	, theLengthValue(LengthValue)
{
}

template<typename T>
inline Standard_Integer AutLib::GeoLib::Geometry_Heap<T>::Size() const
{
	return theSize_;
}

template<typename T>
inline const M_AUT ADT_Ary1d<T>& AutLib::GeoLib::Geometry_Heap<T>::Data() const
{
	return theData_;
}

template<typename T>
inline Standard_Boolean AutLib::GeoLib::Geometry_Heap<T>::IsEmpty() const
{
	return theSize_ == 0;
}

template<typename T>
inline Standard_Boolean AutLib::GeoLib::Geometry_Heap<T>::GetItem(T & Item)
{
	if (IsEmpty())
		return Standard_False;
	else
	{
		Item = Remove();

		return Standard_True;
	}
}

template<typename T>
inline void AutLib::GeoLib::Geometry_Heap<T>::Resize(const Standard_Integer NbItems)
{
	theData_.Resize(NbItems);
}

template<typename T>
inline void AutLib::GeoLib::Geometry_Heap<T>::Insert(const T & Item)
{
	Debug_If_Condition_Message(theLengthValue EQUAL NULL, " No Set Comparable Function For Heap");

	if (theSize_ EQUAL theData_.Size())
	{
		THROW_STANDARD_EXCEPTION(" Heap's underlying storage is overflow");
	}
	else
	{
		theSize_++;

		theData_[theSize_ - 1] = Item;

		ShiftUp(theSize_ - 1);
	}
}

template<typename T>
inline void AutLib::GeoLib::Geometry_Heap<T>::Insert(const ADT_Ary1d<T>& Items)
{
	Resize(Items.Size());

	forThose
	(
		Index,
		0, 
		MaxIndexOf(Items)
	)
	{
		Insert(Items[Index]);
	}
}

template<typename T>
inline void AutLib::GeoLib::Geometry_Heap<T>::SetFunction(Standard_Real(*LengthValue)(const T &))
{
	theLengthValue = LengthValue;
}

template<typename T>
inline T AutLib::GeoLib::Geometry_Heap<T>::Remove()
{
	T Item(0);

	if (IsEmpty())
	{
		THROW_STANDARD_EXCEPTION(" Heap is Empty");
	}
	else
	{
		Item = theData_[0];

		theData_[0] = theData_[theSize_ - 1];

		theSize_--;

		if (theSize_ > 0)
			ShiftDown(0);
	}

	MOVE(Item);
}

template<typename T>
inline void AutLib::GeoLib::Geometry_Heap<T>::ShiftUp(const Standard_Integer Index)
{
	if (Index)
	{
		Standard_Integer ParentIndex = Parent(Index);

		if (theLengthValue(theData_[ParentIndex]) > theLengthValue(theData_[Index]))
		{
			std::swap(theData_[ParentIndex], theData_[Index]);

			ShiftUp(ParentIndex);
		}
	}
}

template<typename T>
inline void AutLib::GeoLib::Geometry_Heap<T>::ShiftDown(const Standard_Integer Index)
{
	Standard_Integer
		LeftChildIndex,
		RightChildIndex,
		MinIndex;

	LeftChildIndex = LeftChild(Index);
	RightChildIndex = RightChild(Index);

	if (RightChildIndex >= theSize_)
	{
		if (LeftChildIndex >= theSize_)
			return;
		else
			MinIndex = LeftChildIndex;
	}
	else
	{
		if (theLengthValue(theData_[LeftChildIndex]) <= theLengthValue(theData_[RightChildIndex]))
			MinIndex = LeftChildIndex;
		else
			MinIndex = RightChildIndex;
	}

	if (theLengthValue(theData_[Index]) > theLengthValue(theData_[MinIndex]))
	{
		std::swap(theData_[MinIndex], theData_[Index]);

		ShiftDown(MinIndex);
	}
}