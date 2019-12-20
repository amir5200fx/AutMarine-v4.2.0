#pragma once

#include <Global_Configs.hxx>
#include "ADT_AvlTree.hxx"

inline AutLib::Standard_String TreeName(const AutLib::Standard_String& theMessage, const AutLib::Standard_String& Name)
{
	Standard_SStream _SUM;

	_SUM << theMessage << Name;

	return _SUM.str();
}

template<typename Comparable>
inline AutLib::ADT_AvlTree<Comparable>::ADT_AvlTree()
	: theRoot_(0)
	, theNbElements_(0)
	, IsLess(NULL)
{
}

template<typename Comparable>
inline AutLib::ADT_AvlTree<Comparable>::ADT_AvlTree(const ADT_AvlTree & Other)
{
	theRoot_ = Clone(Other.theRoot_);

	theName_ = Other.theName_;
	theNbElements_ = Other.theNbElements_;

	IsLess = Other.IsLess;
}

template<typename Comparable>
inline AutLib::ADT_AvlTree<Comparable>::~ADT_AvlTree()
{
	Clear();
}

template<typename Comparable>
inline AutLib::ADT_AvlTree<Comparable> & AutLib::ADT_AvlTree<Comparable>::operator=(const ADT_AvlTree & Other)
{
	Assignment(Other);
}

template<typename Comparable>
inline const Comparable & AutLib::ADT_AvlTree<Comparable>::FindMin() const
{
	if (IsEmpty())
	{
		THROW_STANDARD_EXCEPTION(TreeName(" underflow tree: ", theName_));
	}

	return FindMin(theRoot_)->theElement_;
}

template<typename Comparable>
inline const Comparable & AutLib::ADT_AvlTree<Comparable>::FindMax() const
{
	if (IsEmpty())
	{
		THROW_STANDARD_EXCEPTION(TreeName(" underflow tree: ", theName_));
	}

	return FindMax(theRoot_)->theElement_;
}

template<typename Comparable>
inline Standard_Boolean AutLib::ADT_AvlTree<Comparable>::IsContains(const Comparable & Element) const
{
	return IsContains(Element, theRoot_);
}

template<typename Comparable>
inline Standard_Boolean AutLib::ADT_AvlTree<Comparable>::IsEmpty() const
{
	return theRoot_ EQUAL NULL;
}

template<typename Comparable>
inline Standard_Integer AutLib::ADT_AvlTree<Comparable>::Size() const
{
	return theNbElements_;
}

template<typename Comparable>
inline AutLib::ADT_Ary1d<Comparable> AutLib::ADT_AvlTree<Comparable>::Retrieve() const
{
	ADT_Ary1d<Comparable> Array;

	RetrieveTo(Array);

	MOVE(Array);
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::SetName(const Standard_String & Name)
{
	theName_ = Name;
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::SetComparable(Standard_Boolean(*IS_LESS)(const Comparable &, const Comparable &))
{
	IsLess = IS_LESS;
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::Clear()
{
	Clear(theRoot_);
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::Insert(const Comparable & Element)
{
	Check_Comparable_Function(IsLess);

	Insert(Element, theRoot_);
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::Insert(const ADT_Ary1d<Comparable>& Elements)
{
	Check_Comparable_Function(IsLess);

	forThose(Index, 0, MaxIndexOf(Elements))
	{
		Insert(Elements[Index], theRoot_);
	}
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::InsertIgnoreDup(const Comparable & Element)
{
	Check_Comparable_Function(IsLess);

	InsertIgnoreWarning(Element, theRoot_);
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::InsertIgnoreDup(const ADT_Ary1d<Comparable>& Elements)
{
	Check_Comparable_Function(IsLess);

	forThose(Index, 0, MaxIndexOf(Elements))
	{
		InsertIgnoreWarning(Elements[Index], theRoot_);
	}
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::Remove(const Comparable & Element)
{
	Check_Comparable_Function(IsLess);

	Remove(Element, theRoot_);
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::Remove(const ADT_Ary1d<Comparable>& Elements)
{
	Check_Comparable_Function(IsLess);

	forThose(Index, 0, MaxIndexOf(Elements))
		Remove(Elements[Index], theRoot_);
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::RemoveIgnoreWarning(const Comparable & Element)
{
	Check_Comparable_Function(IsLess);

	RemoveIgnoreWarning(Element, theRoot_);
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::RemoveIgnoreWarning(const ADT_Ary1d<Comparable>& Elements)
{
	Check_Comparable_Function(IsLess);

	forThose(Index, 0, MaxIndexOf(Elements))
		RemoveIgnoreWarning(Elements[Index], theRoot_);
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::Root(Comparable & Element) const
{
	if (IsEmpty())
	{
		THROW_STANDARD_EXCEPTION(TreeName(" Under flow tree: ", theName_));
	}

	Element = theRoot_->theElement_;
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::RetrieveTo(ADT_BasicQueue<Comparable>& Queue) const
{
	RetrieveTo(theRoot_, Queue);
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::RetrieveTo(ADT_Ary1d<Comparable>& Array) const
{
	ADT_BasicQueue<Comparable> Queue;

	RetrieveTo(theRoot_, Queue);

	Queue.RetrieveTo(Array);
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::Insert(const Comparable & x, ADT_AvlTreeNode<Comparable>*& t)
{
#ifdef USE_INDEX_NUMBERING
	if (t == nullptr)
	{
		t = new ADT_AvlTreeNode<Comparable>(x, 0, 0);

		theNbElements_++;
	}
	else if (IsLess(x, t->theElement_))
		Insert(x, t->theLeft_);
	else if (IsLess(t->theElement_, x))
		Insert(x, t->theRight_);
	else
	{
		THROW_STANDARD_EXCEPTION(" Duplicate Data");  // duplicate data
	}
#else
	if (t == nullptr)
	{
		t = new ADT_AvlTreeNode<Comparable>(x, 0, 0);

		theNbElements_++;
	}
	else if (x < t->theElement_)
		Insert(x, t->theLeft_);
	else if (t->theElement_ < x)
		Insert(x, t->theRight_);
	else
	{
		THROW_STANDARD_EXCEPTION(" Duplicate Data");  // duplicate data
	}
#endif // !USE_INDEX_NUMBERING

	Balance(t);
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::InsertIgnoreWarning(const Comparable & x, ADT_AvlTreeNode<Comparable>*& t)
{
#ifdef USE_INDEX_NUMBERING
	if (t == nullptr)
	{
		t = new ADT_AvlTreeNode<Comparable>(x, 0, 0);

		theNbElements_++;
	}
	else if (IsLess(x, t->theElement_))
		InsertIgnoreWarning(x, t->theLeft_);
	else if (IsLess(t->theElement_, x))
		InsertIgnoreWarning(x, t->theRight_);
	else
	{
		return;  // duplicate data
	}
#else
	if (t == nullptr)
	{
		t = new ADT_AvlTreeNode<Comparable>(x, 0, 0);

		theNbElements_++;
	}
	else if (x < t->theElement_)
		InsertIgnoreWarning(x, t->theLeft_);
	else if (t->theElement_ < x)
		InsertIgnoreWarning(x, t->theRight_);
	else
	{
		return;  // duplicate data
	}
#endif // !USE_INDEX_NUMBERING

	Balance(t);
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::Remove(const Comparable & x, ADT_AvlTreeNode<Comparable>*& t)
{
	if (t == nullptr)
	{
		THROW_STANDARD_EXCEPTION(" Item not found");

		return;
	}

#ifdef USE_INDEX_NUMBERING
	if (IsLess(x, t->theElement_))
		Remove(x, t->theLeft_);
	else if (IsLess(t->theElement_, x))
		Remove(x, t->theRight_);
	else if (t->theLeft_ != nullptr && t->theRight_ != nullptr) // Two children
	{
		t->theElement_ = FindMin(t->theRight_)->theElement_;
		Remove(t->theElement_, t->theRight_);
	}
	else
	{
		ADT_AvlTreeNode<Comparable> *oldNode = t;
		t = (t->theLeft_ != nullptr) ? t->theLeft_ : t->theRight_;
		delete oldNode;
		oldNode = NULL;

		theNbElements_--;
	}
#else
	if (x < t->theElement_)
		Remove(x, t->theLeft_);
	else if (t->theElement_ < x)
		Remove(x, t->theRight_);
	else if (t->theLeft_ != nullptr && t->theRight_ != nullptr) // Two children
	{
		t->theElement_ = FindMin(t->theRight_)->theElement_;
		Remove(t->theElement_, t->theRight_);
	}
	else
	{
		ADT_AvlTreeNode<Comparable> *oldNode = t;
		t = (t->theLeft_ != nullptr) ? t->theLeft_ : t->theRight_;
		delete oldNode;
		oldNode = NULL;

		theNbElements_--;
	}
#endif // USE_INDEX_NUMBERING

	Balance(t);
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::RemoveIgnoreWarning(const Comparable & x, ADT_AvlTreeNode<Comparable>*& t)
{
	if (t == nullptr)
	{
		return;
	}

#ifdef USE_INDEX_NUMBERING
	if (IsLess(x, t->theElement_))
		RemoveIgnoreWarning(x, t->theLeft_);
	else if (IsLess(t->theElement_, x))
		RemoveIgnoreWarning(x, t->theRight_);
	else if (t->theLeft_ != nullptr && t->theRight_ != nullptr) // Two children
	{
		t->theElement_ = FindMin(t->theRight_)->theElement_;
		RemoveIgnoreWarning(t->theElement_, t->theRight_);
	}
	else
	{
		ADT_AvlTreeNode<Comparable> *oldNode = t;
		t = (t->theLeft_ != nullptr) ? t->theLeft_ : t->theRight_;
		delete oldNode;
		oldNode = NULL;

		theNbElements_--;
	}
#else
	if (x < t->theElement_)
		RemoveIgnoreWarning(x, t->theLeft_);
	else if (t->theElement_ < x)
		RemoveIgnoreWarning(x, t->theRight_);
	else if (t->theLeft_ != nullptr && t->theRight_ != nullptr) // Two children
	{
		t->theElement_ = FindMin(t->theRight_)->theElement_;
		RemoveIgnoreWarning(t->theElement_, t->theRight_);
	}
	else
	{
		ADT_AvlTreeNode<Comparable> *oldNode = t;
		t = (t->theLeft_ != nullptr) ? t->theLeft_ : t->theRight_;
		delete oldNode;
		oldNode = NULL;

		theNbElements_--;
	}
#endif // USE_INDEX_NUMBERING

	Balance(t);
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::Balance(ADT_AvlTreeNode<Comparable>*& t)
{
	if (t == nullptr)
		return;

	if (Height(t->theLeft_) - Height(t->theRight_) > ALLOWED_IMBALANCE)
		if (Height(t->theLeft_->theLeft_) >= Height(t->theLeft_->theRight_))
			RotateWithLeftChild(t);
		else
			DoubleWithLeftChild(t);
	else
		if (Height(t->theRight_) - Height(t->theLeft_) > ALLOWED_IMBALANCE)
			if (Height(t->theRight_->theRight_) >= Height(t->theRight_->theLeft_))
				RotateWithRightChild(t);
			else
				DoubleWithRightChild(t);

	t->theHeight_ = MAX(Height(t->theLeft_), Height(t->theRight_)) + 1;
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::Clear(ADT_AvlTreeNode<Comparable>*& t)
{
	if (t NOT_EQUAL nullptr)
	{
		Clear(t->theLeft_);
		Clear(t->theRight_);

		theNbElements_--;

		delete t;
	}

	t = NULL;
}

template<typename Comparable>
inline AutLib::ADT_AvlTreeNode<Comparable>* AutLib::ADT_AvlTree<Comparable>::Clone(ADT_AvlTreeNode<Comparable>* t) const
{
	if (t EQUAL nullptr)
		return nullptr;
	else
		return new ADT_AvlTreeNode<Comparable>(t->theElement_, Clone(t->theLeft_), Clone(t->theRight_), t->theHeight_);
}

template<typename Comparable>
inline AutLib::ADT_AvlTreeNode<Comparable>* AutLib::ADT_AvlTree<Comparable>::FindMin(ADT_AvlTreeNode<Comparable>* t) const
{
	if (t EQUAL nullptr)
		return nullptr;
	if (t->theLeft_ EQUAL nullptr)
		return t;
	return FindMin(t->theLeft_);
}

template<typename Comparable>
inline AutLib::ADT_AvlTreeNode<Comparable>* AutLib::ADT_AvlTree<Comparable>::FindMax(ADT_AvlTreeNode<Comparable>* t) const
{
	if (t NOT_EQUAL nullptr)
		while (t->theRight_ NOT_EQUAL nullptr)
			t = t->theRight_;
	return t;
}

template<typename Comparable>
inline Standard_Boolean AutLib::ADT_AvlTree<Comparable>::IsContains(const Comparable & x, ADT_AvlTreeNode<Comparable>* t) const
{
#ifdef USE_INDEX_NUMBERING
	if (t == nullptr)
		return Standard_False;
	else if (IsLess(x, t->theElement_))
		return IsContains(x, t->theLeft_);
	else if (IsLess(t->theElement_, x))
		return IsContains(x, t->theRight_);
	else
		return Standard_True;    // Match
#else
	if (t == nullptr)
		return Standard_False;
	else if (x < t->theElement_)
		return IsContains(x, t->theLeft_);
	else if (t->theElement_ < x)
		return IsContains(x, t->theRight_);
	else
		return Standard_True;    // Match
#endif // USE_INDEX_NUMBERING

}

template<typename Comparable>
inline Standard_Integer AutLib::ADT_AvlTree<Comparable>::Height(ADT_AvlTreeNode<Comparable>* t) const
{
	return t EQUAL nullptr ? -1 : t->theHeight_;
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::RotateWithLeftChild(ADT_AvlTreeNode<Comparable>*& k2)
{
	ADT_AvlTreeNode<Comparable> *k1 = k2->theLeft_;
	k2->theLeft_ = k1->theRight_;
	k1->theRight_ = k2;
	k2->theHeight_ = MAX(Height(k2->theLeft_), Height(k2->theRight_)) + 1;
	k1->theHeight_ = MAX(Height(k1->theLeft_), k2->theHeight_) + 1;
	k2 = k1;
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::RotateWithRightChild(ADT_AvlTreeNode<Comparable>*& k1)
{
	ADT_AvlTreeNode<Comparable> *k2 = k1->theRight_;
	k1->theRight_ = k2->theLeft_;
	k2->theLeft_ = k1;
	k1->theHeight_ = MAX(Height(k1->theLeft_), Height(k1->theRight_)) + 1;
	k2->theHeight_ = MAX(Height(k2->theRight_), k1->theHeight_) + 1;
	k1 = k2;
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::DoubleWithLeftChild(ADT_AvlTreeNode<Comparable>*& k3)
{
	RotateWithRightChild(k3->theLeft_);
	RotateWithLeftChild(k3);
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::DoubleWithRightChild(ADT_AvlTreeNode<Comparable>*& k1)
{
	RotateWithLeftChild(k1->theRight_);
	RotateWithRightChild(k1);
}

template<typename Comparable>
inline void AutLib::ADT_AvlTree<Comparable>::RetrieveTo(ADT_AvlTreeNode<Comparable>* t, ADT_BasicQueue<Comparable>& Queue) const
{
	if (t NOT_EQUAL nullptr)
	{
		RetrieveTo(t->theLeft_, Queue);

		Queue.EnQueue(t->theElement_);

		RetrieveTo(t->theRight_, Queue);
	}
}