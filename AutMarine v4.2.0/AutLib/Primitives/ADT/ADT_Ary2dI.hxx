#pragma once
#include <Global_Debug.hxx>

template<typename T>
inline AutLib::ADT_Ary2d<T>::ADT_Ary2d(const Standard_Integer NbRows, const Standard_Integer nbCols)
	: theNbRows_(NbRows)
	, theNbCols_(nbCols)
{
	theEts_ = new T*[theNbRows_];

	forThose(Index, 0, theNbRows_ - 1)
	{
		theEts_[Index] = new T[theNbCols_];
	}
}

template<typename T>
inline AutLib::ADT_Ary2d<T>::ADT_Ary2d(const Standard_Integer NbRows, const Standard_Integer nbCols, const T & Value)
{
	theEts_ = new T*[theNbRows_];

	forThose(Index1, 0, theNbRows_ - 1)
	{
		theEts_[Index1] = new T[theNbCols_];

		forThose(Index2, 0, theNbRows_ - 1)
		{
			theEts_[Index1][Index2] = Value;
		}
	}
}

template<typename T>
inline AutLib::ADT_Ary2d<T>::ADT_Ary2d(const ADT_Ary2d<T>& Other)
	: theNbRows_(Other.theNbRows_)
	, theNbCols_(Other.theNbCols_)
{
	theEts_ = new T*[theNbRows_];

	forThose(Index1, 0, theNbRows_ - 1)
	{
		theEts_[Index1] = new T[theNbCols_];

		forThose(Index2, 0, theNbRows_ - 1)
		{
			theEts_[Index1][Index2] = Other[Index1][Index2];
		}
	}
}

template<typename T>
inline AutLib::ADT_Ary2d<T>::~ADT_Ary2d()
{
	Clear();
}

template<typename T>
inline AutLib::ADT_Ary2d<T>& AutLib::ADT_Ary2d<T>::operator=(const ADT_Ary2d<T>& Other)
{
	theEts_ = new T*[theNbRows_];

	forThose(Index1, 0, theNbRows_ - 1)
	{
		theEts_[Index1] = new T[theNbCols_];

		forThose(Index2, 0, theNbRows_ - 1)
		{
			theEts_[Index1][Index2] = Other[Index1][Index2];
		}
	}

	return *this;
}

template<typename T>
inline AutLib::ADT_Ary2d<T>& AutLib::ADT_Ary2d<T>::operator+=(const ADT_Ary2d<T>& Other)
{
	if (NOT MatchSizeWith(Other))
	{
		THROW_STANDARD_EXCEPTION(" No match between two Arrays");
	}

	forThose(Index1,0,theNbRows_-1)
		forThose(Index2, 0, theNbCols_ - 1)
	{
		theEts_[Index1][Index2] += Other[Index1][Index2];
	}

	return *this;
}

template<typename T>
inline AutLib::ADT_Ary2d<T>& AutLib::ADT_Ary2d<T>::operator-=(const ADT_Ary2d<T>& Other)
{
	if (NOT MatchSizeWith(Other))
	{
		THROW_STANDARD_EXCEPTION(" No match between two Arrays");
	}

	forThose(Index1, 0, theNbRows_ - 1)
		forThose(Index2, 0, theNbCols_ - 1)
	{
		theEts_[Index1][Index2] -= Other[Index1][Index2];
	}

	return *this;
}

template<typename T>
inline AutLib::ADT_Ary2d<T>& AutLib::ADT_Ary2d<T>::operator=(const T & Object)
{
	forThose(Index1, 0, theNbRows_ - 1)
		forThose(Index2, 0, theNbCols_ - 1)
	{
		theEts_[Index1][Index2] = Object;
	}

	return *this;
}

template<typename T>
inline AutLib::ADT_Ary2d<T>& AutLib::ADT_Ary2d<T>::operator+=(const T & Object)
{
	forThose(Index1, 0, theNbRows_ - 1)
		forThose(Index2, 0, theNbCols_ - 1)
	{
		theEts_[Index1][Index2] += Object;
	}

	return *this;
}

template<typename T>
inline AutLib::ADT_Ary2d<T>& AutLib::ADT_Ary2d<T>::operator-=(const T & Object)
{
	forThose(Index1, 0, theNbRows_ - 1)
		forThose(Index2, 0, theNbCols_ - 1)
	{
		theEts_[Index1][Index2] -= Object;
	}

	return *this;
}

template<typename T>
inline AutLib::ADT_Ary2d<T>& AutLib::ADT_Ary2d<T>::operator*=(const T & Object)
{
	forThose(Index1, 0, theNbRows_ - 1)
		forThose(Index2, 0, theNbCols_ - 1)
	{
		theEts_[Index1][Index2] *= Object;
	}

	return *this;
}

template<typename T>
inline AutLib::ADT_Ary2d<T>& AutLib::ADT_Ary2d<T>::operator/=(const T & Object)
{
	forThose(Index1, 0, theNbRows_ - 1)
		forThose(Index2, 0, theNbCols_ - 1)
	{
		theEts_[Index1][Index2] /= Object;
	}

	return *this;
}

template<typename T>
inline AutLib::ADT_Ary2d<T>& AutLib::ADT_Ary2d<T>::operator+()
{
	return *this;
}

template<typename T>
inline AutLib::ADT_Ary2d<T> AutLib::ADT_Ary2d<T>::operator-()
{
	ADT_Ary2d<T> Zero(theNbRows_, theNbCols_, 0);

	return Zero - *this;
}

template<typename T>
inline AutLib::ADT_Ary2d<T> AutLib::ADT_Ary2d<T>::operator+(const ADT_Ary2d<T>& Other)
{
	ADT_Ary2d<T> Temp = *this;

	Temp += Other;

	MOVE(Temp);
}

template<typename T>
inline AutLib::ADT_Ary2d<T> AutLib::ADT_Ary2d<T>::operator-(const ADT_Ary2d<T>& Other)
{
	ADT_Ary2d<T> Temp = *this;

	Temp -= Other;

	MOVE(Temp);
}

template<typename T>
inline AutLib::ADT_Ary2d<T> AutLib::ADT_Ary2d<T>::operator+(const T & Object)
{
	ADT_Ary2d<T> Temp = *this;

	Temp += Object;

	MOVE(Temp);
}

template<typename T>
inline AutLib::ADT_Ary2d<T> AutLib::ADT_Ary2d<T>::operator-(const T & Object)
{
	ADT_Ary2d<T> Temp = *this;

	Temp -= Object;

	MOVE(Temp);
}

template<typename T>
inline AutLib::ADT_Ary2d<T> AutLib::ADT_Ary2d<T>::operator*(const T & Object)
{
	ADT_Ary2d<T> Temp = *this;

	Temp *= Object;

	MOVE(Temp);
}

template<typename T>
inline AutLib::ADT_Ary2d<T> AutLib::ADT_Ary2d<T>::operator/(const T & Object)
{
	ADT_Ary2d<T> Temp = *this;

	Temp /= Object;

	MOVE(Temp);
}

template<typename T>
inline T * AutLib::ADT_Ary2d<T>::operator[](const Standard_Integer Index) const
{
	Debug_Bad_Index(Index, 0, theNbRows_ - 1);

	return theEts_[Index];
}

template<typename T>
inline T *& AutLib::ADT_Ary2d<T>::operator[](const Standard_Integer Index)
{
	Debug_Bad_Index(Index, 0, theNbRows_ - 1);

	return theEts_[Index];
}

template<typename T>
inline const T & AutLib::ADT_Ary2d<T>::operator()(const Standard_Integer Index1, const Standard_Integer Index2) const
{
	Debug_Bad_Index(Index1, 0, theNbRows_ - 1);
	Debug_Bad_Index(Index2, 0, theNbCols_ - 1);

	return theEts_[Index1][Index2];
}

template<typename T>
inline T & AutLib::ADT_Ary2d<T>::operator()(const Standard_Integer Index1, const Standard_Integer Index2)
{
	Debug_Bad_Index(Index1, 0, theNbRows_ - 1);
	Debug_Bad_Index(Index2, 0, theNbCols_ - 1);

	return theEts_[Index1][Index2];
}

template<typename T>
inline Standard_Integer AutLib::ADT_Ary2d<T>::Size(const Standard_Integer Index) const
{
	if (Index EQUAL 0)
		return theNbRows_;
	else
		return theNbCols_;
}

template<typename T>
inline Standard_Integer AutLib::ADT_Ary2d<T>::NbRows() const
{
	return theNbRows_;
}

template<typename T>
inline Standard_Integer AutLib::ADT_Ary2d<T>::NbCols() const
{
	return theNbCols_;
}

template<typename T>
inline Standard_Integer AutLib::ADT_Ary2d<T>::LowerRow() const
{
	return 0;
}

template<typename T>
inline Standard_Integer AutLib::ADT_Ary2d<T>::UpperRow() const
{
	return theNbRows_ - 1;
}

template<typename T>
inline Standard_Integer AutLib::ADT_Ary2d<T>::LowerCol() const
{
	return 0;
}

template<typename T>
inline Standard_Integer AutLib::ADT_Ary2d<T>::UpperCol() const
{
	return theNbCols_ - 1;
}

template<typename T>
inline Standard_Boolean AutLib::ADT_Ary2d<T>::MatchSizeWith(const ADT_Ary2d<T>& Other) const
{
	if (theNbRows_ NOT_EQUAL Other.theNbRows_)
		return Standard_False;
	else if (theNbCols_ NOT_EQUAL Other.theNbCols_)
		return Standard_False;
	else
		return Standard_True;
}

template<typename T>
inline void AutLib::ADT_Ary2d<T>::Init(const T & Value)
{
	forThose(Index1, 0, theNbRows_ - 1)
		forThose(Index2, 0, theNbCols_ - 1)
	{
		theEts_[Index1][Index2] = Value;
	}
}

template<typename T>
inline void AutLib::ADT_Ary2d<T>::Clear()
{
	forThose(Index, 0, theNbRows_ - 1)
	{
		delete[] theEts_[Index];
	}

	delete[] theEts_;
}

template<typename T>
inline void AutLib::ADT_Ary2d<T>::Resize(const Standard_Integer NbRows, const Standard_Integer NbCols)
{
	Clear();

	theNbRows_ = NbRows;
	theNbCols_ = NbCols;

	theEts_ = new T*[theNbRows_];

	forThose(Index, 0, theNbRows_ - 1)
	{
		theEts_[Index] = new T[theNbCols_];
	}
}

template<typename T>
inline void AutLib::ADT_Ary2d<T>::DynResize(const Standard_Integer NbRows, const Standard_Integer NbCols)
{
	ADT_Ary2d<T> Temp = *this;

	Clear();

	Standard_Integer MinNbRows = MIN(NbRows, theNbRows_);
	Standard_Integer MinNbCols = MIN(NbCols, theNbCols_);

	theNbRows_ = NbRows;
	theNbCols_ = NbCols;

	theEts_ = new T*[theNbRows_];

	forThose(Index, 0, theNbRows_ - 1)
	{
		theEts_[Index] = new T[theNbCols_];
	}

	forThose(Index1,0,MinNbRows-1)
		forThose(Index2, 0, MinNbCols - 1)
	{
		theEts_[Index1][Index2] = Temp[Index1][Index2];
	}
}

template<typename T>
inline void AutLib::ADT_Ary2d<T>::Print(Standard_OStream & Stream) const
{
	forThose(Index1, 0, theNbRows_ - 1)
	{
		forThose(Index2, 0, theNbCols_ - 1)
			Stream << theEts_[Index1][Index2] << "  ";
		Stream << endl;
	}
}

namespace AutLib
{
	template<typename T>
	ADT_Ary2d<T> operator+(const ADT_Ary2d<T>& A1, const ADT_Ary2d<T>& A2)
	{
		ADT_Ary2d<T> Temp = A1;

		Temp += A2;

		MOVE(Temp);
	}

	template<typename T>
	ADT_Ary2d<T> operator-(const ADT_Ary2d<T>& A1, const ADT_Ary2d<T>& A2)
	{
		ADT_Ary2d<T> Temp = A1;

		Temp -= A2;

		MOVE(Temp);
	}

	template<typename T>
	ADT_Ary2d<T> operator+(const ADT_Ary2d<T>& A1, const T & Object)
	{
		ADT_Ary2d<T> Temp = A1;

		Temp += Object;

		MOVE(Temp);
	}

	template<typename T>
	ADT_Ary2d<T> operator+(const T & Object, const ADT_Ary2d<T>& A1)
	{
		ADT_Ary2d<T> Temp = A1;

		Temp += Object;

		MOVE(Temp);
	}

	template<typename T>
	ADT_Ary2d<T> operator-(const ADT_Ary2d<T>& A1, const T & Object)
	{
		ADT_Ary2d<T> Temp = A1;

		Temp -= Object;

		MOVE(Temp);
	}

	template<typename T>
	ADT_Ary2d<T> operator*(const ADT_Ary2d<T>& A1, const T & Object)
	{
		ADT_Ary2d<T> Temp = A1;

		Temp *= Object;

		MOVE(Temp);
	}

	template<typename T>
	ADT_Ary2d<T> operator*(const T & Object, const ADT_Ary2d<T>& A1)
	{
		ADT_Ary2d<T> Temp = A1;

		Temp *= Object;

		MOVE(Temp);
	}

	template<typename T>
	ADT_Ary2d<T> operator/(const ADT_Ary2d<T>& A1, const T & Object)
	{
		ADT_Ary2d<T> Temp = A1;

		Temp /= Object;

		MOVE(Temp);
	}
}