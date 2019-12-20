#pragma once
#include "ADT_BasicList.hxx"

template<typename T>
inline AutLib::ADT_BasicList<T>::ADT_BasicList()
	: theFirst_(0)
	, theLast_(0)
	, theNbItems_(0)
{
}

template<typename T>
inline AutLib::ADT_BasicList<T>::ADT_BasicList(const ADT_BasicList<T>& Other)
{
	ADT_BasicListNode<T>* Current = Other.theFirst_;

	while (Current NOT_EQUAL 0)
	{
		InsertAtBack(Current->Data());
		Current = Current->theNext_;
	}
}

template<typename T>
inline AutLib::ADT_BasicList<T>::~ADT_BasicList()
{
	Clear();
}

template<typename T>
inline AutLib::ADT_BasicList<T>& AutLib::ADT_BasicList<T>::operator=(const ADT_BasicList<T>& Other)
{
	ADT_BasicListNode<T>* Current = Other.theFirst_;

	while (Current NOT_EQUAL 0)
	{
		InsertAtBack(Current->Data());
		Current = Current->theNext_;
	}

	return *this;
}

template<typename T>
inline T AutLib::ADT_BasicList<T>::FirstItem() const
{
	return theFirst_->Data();
}

template<typename T>
inline T AutLib::ADT_BasicList<T>::LastItem() const
{
	return theLast_->Data();
}

template<typename T>
inline AutLib::ADT_BasicListNode<T>* AutLib::ADT_BasicList<T>::NextItem(ADT_BasicListNode<T>* Node) const
{
	return Node->theNext_;
}

template<typename T>
inline Standard_Integer AutLib::ADT_BasicList<T>::Size() const
{
	return theNbItems_;
}

template<typename T>
inline Standard_Boolean AutLib::ADT_BasicList<T>::IsEmpty() const
{
	return IsNULL(theFirst_);
}

template<typename T>
inline Standard_Boolean AutLib::ADT_BasicList<T>::RemoveFromFront(T & Object)
{
	if (IsEmpty())
		return Standard_False;
	else
	{
		ADT_BasicListNode<T> *Temp = theFirst_;

		if (theFirst_ EQUAL theLast_)
			theFirst_ = theLast_ = 0;
		else
			theFirst_ = theFirst_->theNext_;

		Object = Temp->Data();

		delete Temp;
		Temp = NULL;

		theNbItems_--;

		return Standard_True;
	}
}

template<typename T>
inline Standard_Boolean AutLib::ADT_BasicList<T>::RemoveFromBack(T & Object)
{
	if (IsEmpty())
		return Standard_False;
	else
	{
		ADT_BasicListNode<T> *Temp = theFirst_;

		if (theFirst_ EQUAL theLast_)
			theFirst_ = theLast_ = 0;
		else
		{
			ADT_BasicListNode<T> *Current = theFirst_;

			while (Current->theNext_ NOT_EQUAL theLast_)
				Current = Current->theNext_;

			theLast_ = Current;
			Current->theNext_ = 0;
		}

		Object = Temp->Data();

		delete Temp;
		Temp = NULL;

		theNbItems_--;

		return Standard_True;
	}
}

template<typename T>
inline void AutLib::ADT_BasicList<T>::InsertAfter(ADT_BasicListNode<T>* Node, const T & Object)
{
	ADT_BasicListNode<T>* Ptr = NewNode(Object);

	if (IsEmpty())
		theFirst_ = theLast_ = Ptr;
	else
	{
		if (theFirst_ EQUAL theLast_) theLast_ = Ptr;

		Ptr->theNext_ = Node->theNext_;
		Node->theNext_ = Ptr;
	}
}

template<typename T>
inline void AutLib::ADT_BasicList<T>::Remove(const T & Object)
{
	ADT_BasicListNode<T>* Current = theFirst_;

	while (Current NOT_EQUAL 0)
	{
		if (Current->Data() EQUAL Object)
		{
			Remove(Current);

			return;
		}

		Current = Current->Next();
	}
}

template<typename T>
inline void AutLib::ADT_BasicList<T>::Remove(ADT_BasicListNode<T>*& Node)
{
	if (IsEmpty())
		return;
	else
	{
		if (Node EQUAL theFirst_)
		{
			RemoveFromFront();

			Node = NULL;

			return;
		}
		
		if (Node EQUAL theLast_)
		{
			RemoveFromBack();

			Node = NULL;

			return;
		}

		ADT_BasicListNode<T>* Current = theFirst_;

		while (Current->theNext_ NOT_EQUAL Node AND Current NOT_EQUAL theLast_)
			Current = Current->theNext_;

		if (Current EQUAL theLast_)
			return;  // the node is not in list
		else
		{
			Current->theNext_ = Node->theNext_;

			delete Node;
			Node = NULL;

			theNbItems_--;

			return;
		}
	}
}

template<typename T>
inline void AutLib::ADT_BasicList<T>::RemoveFromFront()
{
	if (IsEmpty())
		return;
	else
	{
		ADT_BasicListNode<T>* Temp = theFirst_;

		if (theFirst_ EQUAL theLast_)
			theFirst_ = theLast_ = 0;
		else
			theFirst_ = theFirst_->theNext_;

		delete Temp;
		Temp = NULL;

		theNbItems_--;
	}
}

template<typename T>
inline void AutLib::ADT_BasicList<T>::RemoveFromBack()
{
	if (IsEmpty())
		return;
	else
	{
		ADT_BasicListNode<T>* Temp = theLast_;

		if (theFirst_ EQUAL theLast_)
			theFirst_ = theLast_ = 0;
		else
		{
			ADT_BasicListNode<T>* Current = theFirst_;

			while (Current->theNext_ NOT_EQUAL theLast_)
				Current = Current->theNext_;

			theLast_ = Current;
			Current->theNext_ = 0;
		}

		delete Temp;
		Temp = NULL;

		theNbItems_--;
	}
}

template<typename T>
inline void AutLib::ADT_BasicList<T>::InsertAtFront(const T & Object)
{
	ADT_BasicListNode<T>* Ptr = NewNode(Object);

	if (IsEmpty())
		theFirst_ = theLast_ = Ptr;
	else
	{
		Ptr->theNext_ = theFirst_;
		theFirst_ = Ptr;
	}
}

template<typename T>
inline void AutLib::ADT_BasicList<T>::InsertAtBack(const T & Object)
{
	ADT_BasicListNode<T>* Ptr = NewNode(Object);

	if (IsEmpty())
		theFirst_ = theLast_ = Ptr;
	else
	{
		theLast_->theNext_ = Ptr;
		theLast_ = Ptr;
	}
}

template<typename T>
inline void AutLib::ADT_BasicList<T>::RetrieveTo(ADT_Ary1d<T>& Array) const
{
	Array.Resize(theNbItems_);

	ADT_BasicListNode<T>* Current = theFirst_;

	Standard_Integer Index = 0;

	while (Current NOT_EQUAL 0)
	{
		Array[Index++] = Current->Data();
		Current = Current->theNext_;
	}
}

template<typename T>
inline AutLib::ADT_Ary1d<T> AutLib::ADT_BasicList<T>::Retrive() const
{
	ADT_Ary1d<T> Array;

	RetrieveTo(Array);

	MOVE(Array);
}

template<typename T>
inline void AutLib::ADT_BasicList<T>::Clear()
{
	T Current;

	while(RemoveFromFront(Current))
	{ }
}

template<typename T>
inline void AutLib::ADT_BasicList<T>::Print(Standard_OStream & Ostream) const
{
	ADT_Ary1d<T> Array;

	RetrieveTo(Array);

	Array.Print(Ostream);
}

template<typename T>
inline AutLib::ADT_BasicListNode<T>* AutLib::ADT_BasicList<T>::NewNode(const T & Object)
{
	theNbItems_++;

	return new ADT_BasicListNode<T>(Object);
}