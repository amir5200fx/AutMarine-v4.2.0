#pragma once
#include <Standard_DefineException.hxx>
#include <Global_Debug.hxx>

template<typename T>
inline AutLib::ADT_Ary1d<T>::ADT_Ary1d()
	: myLowerBound_(0)
	, myUpperBound_(-1)
	, myDeletable_(Standard_True)
{
	T* pBegin = new T[Length()];

	vr_ = pBegin - myLowerBound_;
}

template<typename T>
inline AutLib::ADT_Ary1d<T>::ADT_Ary1d(const Standard_Integer Size)
	: myLowerBound_(0)
	, myUpperBound_(Size - 1)
	, myDeletable_(Standard_True)
{
	T* pBegin = new T[Length()];

	vr_ = pBegin - myLowerBound_;
}

template<typename T>
inline AutLib::ADT_Ary1d<T>::ADT_Ary1d
(
	const Standard_Integer theLower, 
	const Standard_Integer theUpper
)
	: myLowerBound_(theLower)
	, myUpperBound_(theUpper)
	, myDeletable_(Standard_True)
{
	T* pBegin = new T[Length()];

	vr_ = pBegin - theLower;
}

template<typename T>
inline AutLib::ADT_Ary1d<T>::ADT_Ary1d(const ADT_Ary1d<T>& Other)
	: myLowerBound_(Other.myLowerBound_)
	, myUpperBound_(Other.myUpperBound_)
	, myDeletable_(Standard_True)
{
	T* pBegin = new T[Length()];

	vr_ = pBegin - myLowerBound_;

	T* pMyItem = &vr_[myLowerBound_];
	T* const pEndItem = &(Other.vr_)[Other.myUpperBound_];
	T* pItem = &(Other.vr_)[Other.myLowerBound_];

	while (pItem <= pEndItem) * pMyItem++ = *pItem++;
}

template<typename T>
inline AutLib::ADT_Ary1d<T>::ADT_Ary1d
(
	const T & theBegin,
	const Standard_Integer theLower,
	const Standard_Integer theUpper
)
	: myLowerBound_(theLower)
	, myUpperBound_(theUpper)
	, myDeletable_(Standard_False)
{
	vr_ = (T*)&theBegin - theLower;
}

template<typename T>
inline AutLib::ADT_Ary1d<T>::~ADT_Ary1d()
{
	Clear();
}

template<typename T>
inline AutLib::ADT_Ary1d<T>& AutLib::ADT_Ary1d<T>::operator=(const ADT_Ary1d<T>& Other)
{
	if (this NOT_EQUAL &Other)
	{
		Clear();

		myLowerBound_ = Other.myLowerBound_;
		myUpperBound_ = Other.myUpperBound_;
		myDeletable_ = Other.myDeletable_;

		T* pBegin = new T[Length()];

		vr_ = pBegin - myLowerBound_;

		T* pMyItem = &vr_[myLowerBound_];
		T* const pEndItem = &(Other.vr_)[Other.myUpperBound_];
		T* pItem = &(Other.vr_)[Other.myLowerBound_];

		while (pItem <= pEndItem) * pMyItem++ = *pItem++;
	}
	return *this;
}

template<typename T>
inline AutLib::ADT_Ary1d<T>& AutLib::ADT_Ary1d<T>::operator+=(const ADT_Ary1d<T>& Other)
{
	if (Length() NOT_EQUAL Other.Length())
	{
		THROW_STANDARD_EXCEPTION(" No match between two array sizes");
	}

	forThose(Index, 0, Length() - 1)
	{
		vr_[Index + Lower()] += Other[Index + Other.Lower()];
	}

	return *this;
}

template<typename T>
inline AutLib::ADT_Ary1d<T>& AutLib::ADT_Ary1d<T>::operator-=(const ADT_Ary1d<T>& Other)
{
	if (Length() NOT_EQUAL Other.Length())
	{
		THROW_STANDARD_EXCEPTION(" No match between two array sizes");
	}

	forThose(Index, 0, Length() - 1)
	{
		vr_[Index + Lower()] -= Other[Index + Other.Lower()];
	}

	return *this;
}

template<typename T>
inline AutLib::ADT_Ary1d<T>& AutLib::ADT_Ary1d<T>::operator*=(const ADT_Ary1d<T>& Other)
{
	if (Length() NOT_EQUAL Other.Length())
	{
		THROW_STANDARD_EXCEPTION(" No match between two array sizes");
	}

	forThose(Index, 0, Length() - 1)
	{
		vr_[Index + Lower()] *= Other[Index + Other.Lower()];
	}

	return *this;
}

template<typename T>
inline AutLib::ADT_Ary1d<T>& AutLib::ADT_Ary1d<T>::operator/=(const ADT_Ary1d<T>& Other)
{
	if (Length() NOT_EQUAL Other.Length())
	{
		THROW_STANDARD_EXCEPTION(" No match between two array sizes");
	}

	forThose(Index, 0, Length() - 1)
	{
		vr_[Index + Lower()] /= Other[Index + Other.Lower()];
	}

	return *this;
}

template<typename T>
inline AutLib::ADT_Ary1d<T>& AutLib::ADT_Ary1d<T>::operator=(const T & Entity)
{
	forThose(Index, 0, Length() - 1)
	{
		vr_[Index + Lower()] = Entity;
	}

	return *this;
}

template<typename T>
inline AutLib::ADT_Ary1d<T>& AutLib::ADT_Ary1d<T>::operator+=(const T & Entity)
{
	forThose(Index, 0, Length() - 1)
	{
		vr_[Index + Lower()] += Entity;
	}

	return *this;
}

template<typename T>
inline AutLib::ADT_Ary1d<T>& AutLib::ADT_Ary1d<T>::operator-=(const T & Entity)
{
	forThose(Index, 0, Length() - 1)
	{
		vr_[Index + Lower()] -= Entity;
	}

	return *this;
}

template<typename T>
inline AutLib::ADT_Ary1d<T>& AutLib::ADT_Ary1d<T>::operator*=(const T & Entity)
{
	forThose(Index, 0, Length() - 1)
	{
		vr_[Index + Lower()] *= Entity;
	}

	return *this;
}

template<typename T>
inline AutLib::ADT_Ary1d<T>& AutLib::ADT_Ary1d<T>::operator/=(const T & Entity)
{
	forThose(Index, 0, Length() - 1)
	{
		vr_[Index + Lower()] /= Entity;
	}

	return *this;
}

template<typename T>
inline AutLib::ADT_Ary1d<T>& AutLib::ADT_Ary1d<T>::operator+()
{
	return *this;
}

template<typename T>
inline AutLib::ADT_Ary1d<T> AutLib::ADT_Ary1d<T>::operator-()
{
	ADT_Ary1d<T> Zero(Lower(), Upper());

	Zero.Init(0);

	ADT_Ary1d<T> Temp = Zero - *this;

	MOVE(Temp);
}

template<typename T>
inline AutLib::ADT_Ary1d<T> AutLib::ADT_Ary1d<T>::operator+(const ADT_Ary1d<T>& Other)
{
	ADT_Ary1d<T> Temp = *this;
	Temp += Other;

	MOVE(Temp);
}

template<typename T>
inline AutLib::ADT_Ary1d<T> AutLib::ADT_Ary1d<T>::operator-(const ADT_Ary1d<T>& Other)
{
	ADT_Ary1d<T> Temp = *this;
	Temp -= Other;

	MOVE(Temp);
}

template<typename T>
inline AutLib::ADT_Ary1d<T> AutLib::ADT_Ary1d<T>::operator*(const ADT_Ary1d<T>& Other)
{
	ADT_Ary1d<T> Temp = *this;
	Temp *= Other;

	MOVE(Temp);
}

template<typename T>
inline AutLib::ADT_Ary1d<T> AutLib::ADT_Ary1d<T>::operator/(const ADT_Ary1d<T>& Other)
{
	ADT_Ary1d<T> Temp = *this;
	Temp /= Other;

	MOVE(Temp);
}

template<typename T>
inline AutLib::ADT_Ary1d<T> AutLib::ADT_Ary1d<T>::operator+(const T & Entity)
{
	ADT_Ary1d<T> Temp = *this;
	Temp += Entity;

	MOVE(Temp);
}

template<typename T>
inline AutLib::ADT_Ary1d<T> AutLib::ADT_Ary1d<T>::operator-(const T & Entity)
{
	ADT_Ary1d<T> Temp = *this;
	Temp -= Entity;

	MOVE(Temp);
}

template<typename T>
inline AutLib::ADT_Ary1d<T> AutLib::ADT_Ary1d<T>::operator*(const T & Entity)
{
	ADT_Ary1d<T> Temp = *this;
	Temp *= Entity;

	MOVE(Temp);
}

template<typename T>
inline AutLib::ADT_Ary1d<T> AutLib::ADT_Ary1d<T>::operator/(const T & Entity)
{
	ADT_Ary1d<T> Temp = *this;
	Temp /= Entity;

	MOVE(Temp);
}

//template<typename T>
//inline AutLib::ADT_Ary1d<T> AutLib::ADT_Ary1d<T>::operator[](const ADT_Ary1d<Standard_Integer>& Ind) const
//{
//	ADT_Ary1d<T> Temp(Ind.Size());
//
//	forThose(Index, 0, MaxIndexOf(Ind))
//	{
//		Temp[Index] = vr_[Ind[Index]];
//	}
//
//	Move(Temp);
//}

template<typename T>
inline const T & AutLib::ADT_Ary1d<T>::operator[](const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, myLowerBound_, myUpperBound_);

	return vr_[Index];
}

template<typename T>
inline const T & AutLib::ADT_Ary1d<T>::operator()(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, myLowerBound_, myUpperBound_);

	return vr_[Index];
}

template<typename T>
inline const T & AutLib::ADT_Ary1d<T>::First() const
{
	return vr_[myLowerBound_];
}

template<typename T>
inline const T & AutLib::ADT_Ary1d<T>::Last() const
{
	return vr_[myUpperBound_];
}

template<typename T>
inline T & AutLib::ADT_Ary1d<T>::First()
{
	return vr_[myLowerBound_];
}

template<typename T>
inline T & AutLib::ADT_Ary1d<T>::Last()
{
	return vr_[myUpperBound_];
}

template<typename T>
inline T & AutLib::ADT_Ary1d<T>::operator[](const Standard_Integer Index)
{
	Debug_Bad_Index(Index, myLowerBound_, myUpperBound_);

	return vr_[Index];
}

template<typename T>
inline T & AutLib::ADT_Ary1d<T>::operator()(const Standard_Integer Index)
{
	Debug_Bad_Index(Index, myLowerBound_, myUpperBound_);

	return vr_[Index];
}

template<typename T>
inline const T & AutLib::ADT_Ary1d<T>::Value(const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, myLowerBound_, myUpperBound_);

	return vr_[Index];
}

template<typename T>
inline T & AutLib::ADT_Ary1d<T>::ChangeValue(const Standard_Integer Index)
{
	Debug_Bad_Index(Index, myLowerBound_, myUpperBound_);

	return vr_[Index];
}

template<typename T>
inline Standard_Integer AutLib::ADT_Ary1d<T>::Size() const
{
	return Length();
}

template<typename T>
inline Standard_Integer AutLib::ADT_Ary1d<T>::Length() const
{
	return (myUpperBound_ - myLowerBound_ + 1);
}

template<typename T>
inline Standard_Integer AutLib::ADT_Ary1d<T>::Lower() const
{
	return myLowerBound_;
}

template<typename T>
inline Standard_Integer AutLib::ADT_Ary1d<T>::Upper() const
{
	return myUpperBound_;
}

template<typename T>
inline Standard_Boolean AutLib::ADT_Ary1d<T>::IsEmpty() const
{
	return NOT Length();
}

template<typename T>
inline void AutLib::ADT_Ary1d<T>::SetValue(const Standard_Integer theIndex, const T & theValue)
{
	Debug_Bad_Index(theIndex, myLowerBound_, myUpperBound_);

	vr_[theIndex] = theValue;
}

template<typename T>
inline void AutLib::ADT_Ary1d<T>::SetFirst(const T & theValue)
{
	First() = theValue;
}

template<typename T>
inline void AutLib::ADT_Ary1d<T>::SetLast(const T & theValue)
{
	Last() = theValue;
}

template<typename T>
inline void AutLib::ADT_Ary1d<T>::Init(const T & theValue)
{
	*this = theValue;
}

template<typename T>
inline void AutLib::ADT_Ary1d<T>::Resize(const Standard_Integer Size)
{
	Clear();

	myLowerBound_ = 0;
	myUpperBound_ = Size - 1;

	T* pBegin = new T[Size];

	vr_ = pBegin - myLowerBound_;
}

template<typename T>
inline void AutLib::ADT_Ary1d<T>::DynResize(const Standard_Integer Size)
{
	ADT_Ary1d<T> Temp = *this;

	Clear();

	myLowerBound_ = 0;
	myUpperBound_ = Size - 1;

	T* pBegin = new T[Length()];

	vr_ = pBegin - myLowerBound_;

	if (Length() <= Temp.Length())
	{
		forThose(Index, 0, Length() - 1)
		{
			vr_[Index + Lower()] = Temp[Index + Temp.Lower()];
		}
	}
	else
	{
		forThose(Index, 0, MaxIndexOf(Temp))
		{
			vr_[Index + Lower()] = Temp[Index + Temp.Lower()];
		}
	}
}

template<typename T>
inline void AutLib::ADT_Ary1d<T>::Clear()
{
	if (myDeletable_) delete[] & (vr_[myLowerBound_]);

	myUpperBound_ = myLowerBound_ = 0;
}

template<typename T>
inline void AutLib::ADT_Ary1d<T>::Reverse()
{
	Standard_Integer size = Size();
	forThose(Index, 0, Size() / 2 - 1)
	{
		std::swap(vr_[Index + Lower()], vr_[size - 1 - Index]);
	}
}

template<typename T>
inline void AutLib::ADT_Ary1d<T>::Print(Standard_OStream & Output) const
{
	forThose(Index, 0, Length() - 1)
	{
		Output << vr_[Index + Lower()] << "  ";

		if (Index%10 EQUAL 9) Output << endl;
	}
}

namespace AutLib
{
	template<typename T>
	ADT_Ary1d<T> operator+(const ADT_Ary1d<T>& V1, const ADT_Ary1d<T>& V2)
	{
		if (V1.Size() NOT_EQUAL V2.Size())
		{
			THROW_STANDARD_EXCEPTION(" No match between two array sizes");
		}

		ADT_Ary1d<T> Temp = V1;
		Temp += V2;

		MOVE(Temp);
	}

	template<typename T>
	ADT_Ary1d<T> operator-(const ADT_Ary1d<T>& V1, const ADT_Ary1d<T>& V2)
	{
		if (V1.Size() NOT_EQUAL V2.Size())
		{
			THROW_STANDARD_EXCEPTION(" No match between two array sizes");
		}

		ADT_Ary1d<T> Temp = V1;
		Temp -= V2;

		MOVE(Temp);
	}

	template<typename T>
	ADT_Ary1d<T> operator*(const ADT_Ary1d<T>& V1, const ADT_Ary1d<T>& V2)
	{
		if (V1.Size() NOT_EQUAL V2.Size())
		{
			THROW_STANDARD_EXCEPTION(" No match between two array sizes");
		}

		ADT_Ary1d<T> Temp = V1;
		Temp *= V2;

		MOVE(Temp);
	}

	template<typename T>
	ADT_Ary1d<T> operator/(const ADT_Ary1d<T>& V1, const ADT_Ary1d<T>& V2)
	{
		if (V1.Size() NOT_EQUAL V2.Size())
		{
			THROW_STANDARD_EXCEPTION(" No match between two array sizes");
		}

		ADT_Ary1d<T> Temp = V1;
		Temp /= V2;

		MOVE(Temp);
	}

	template<typename T>
	ADT_Ary1d<T> operator+(const ADT_Ary1d<T>& V1, const T & Entity)
	{
		ADT_Ary1d<T> Temp = V1;
		Temp += Entity;

		MOVE(Temp);
	}

	template<typename T>
	ADT_Ary1d<T> operator+(const T & Entity, const ADT_Ary1d<T>& V1)
	{
		ADT_Ary1d<T> Temp = V1;
		Temp += Entity;

		MOVE(Temp);
	}

	template<typename T>
	ADT_Ary1d<T> operator-(const ADT_Ary1d<T>& V1, const T & Entity)
	{
		ADT_Ary1d<T> Temp = V1;
		Temp -= Entity;

		MOVE(Temp);
	}

	template<typename T>
	ADT_Ary1d<T> operator-(const T & Entity, const ADT_Ary1d<T>& V1)
	{
		ADT_Ary1d<T> Temp(V1.Size(), Entity);
		Temp -= V1;

		MOVE(Temp);
	}

	template<typename T>
	ADT_Ary1d<T> operator*(const ADT_Ary1d<T>& V1, const T & Entity)
	{
		ADT_Ary1d<T> Temp = V1;
		Temp *= Entity;

		MOVE(Temp);
	}

	template<typename T>
	ADT_Ary1d<T> operator*(const T & Entity, const ADT_Ary1d<T>& V1)
	{
		ADT_Ary1d<T> Temp = V1;
		Temp *= Entity;

		MOVE(Temp);
	}

	template<typename T>
	ADT_Ary1d<T> operator/(const ADT_Ary1d<T>& V1, const T & Entity)
	{
		ADT_Ary1d<T> Temp = V1;
		Temp /= Entity;

		MOVE(Temp);
	}
}