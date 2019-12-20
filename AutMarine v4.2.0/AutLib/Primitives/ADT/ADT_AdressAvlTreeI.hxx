#pragma once
#include <Global_Configs.hxx>
#include "ADT_AvlTree.hxx"

template<typename Comparable>
inline AutLib::ADT_AdressAvlTree<Comparable>::ADT_AdressAvlTree()
	: theRoot_(0)
	, theNbElements_(0)
	, IsLess(NULL)
{
}

template<typename Comparable>
inline AutLib::ADT_AdressAvlTree<Comparable>::ADT_AdressAvlTree(const ADT_AdressAvlTree & Other)
{
	theRoot_ = Clone(Other.theRoot_);

	theName_ = Other.theName_;
	theNbElements_ = Other.theNbElements_;

	IsLess = Other.IsLess;
}

template<typename Comparable>
inline AutLib::ADT_AdressAvlTree<Comparable>::~ADT_AdressAvlTree()
{
	Clear();
}

template<typename Comparable>
inline AutLib::ADT_AdressAvlTree<Comparable> & AutLib::ADT_AdressAvlTree<Comparable>::operator=(const ADT_AdressAvlTree & Other)
{
	Assignment(Other);
}

template<typename Comparable>
inline const Comparable & AutLib::ADT_AdressAvlTree<Comparable>::FindMin() const
{
	if (IsEmpty())
	{
		THROW_STANDARD_EXCEPTION(TreeName(" underflow tree: ", theName_));
	}

	return FindMin(theRoot_)->theElement_;
}

template<typename Comparable>
inline const Comparable & AutLib::ADT_AdressAvlTree<Comparable>::FindMax() const
{
	if (IsEmpty())
	{
		THROW_STANDARD_EXCEPTION(TreeName(" underflow tree: ", theName_));
	}

	return FindMax(theRoot_)->theElement_;
}

template<typename Comparable>
inline Standard_Boolean AutLib::ADT_AdressAvlTree<Comparable>::IsContains(const Comparable & Element) const
{
	return IsContains(Element, theRoot_);
}

template<typename Comparable>
inline Standard_Boolean AutLib::ADT_AdressAvlTree<Comparable>::IsEmpty() const
{
	return theRoot_ EQUAL NULL;
}

template<typename Comparable>
inline Standard_Integer AutLib::ADT_AdressAvlTree<Comparable>::Size() const
{
	return theNbElements_;
}

template<typename Comparable>
inline AutLib::ADT_Ary1d<Comparable> AutLib::ADT_AdressAvlTree<Comparable>::Retrieve() const
{
	ADT_Ary1d<Comparable> Array;

	RetrieveTo(Array);

	MOVE(Array);
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::SetName(const Standard_String & Name)
{
	theName_ = Name;
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::SetComparable(bool(*IS_LESS)(const Comparable &, const Comparable &))
{
	IsLess = IS_LESS;
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::Clear()
{
	Clear(theRoot_);
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::Insert(const Comparable & Element)
{
	Insert(Element, theRoot_);
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::Insert(const ADT_Ary1d<Comparable>& Elements)
{
	forThose(Index, 0, MaxIndexOf(Elements))
	{
		Insert(Elements[Index], theRoot_);
	}
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::InsertIgnoreDup(const Comparable & Element)
{
	InsertIgnoreWarning(Element, theRoot_);
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::Remove(const Comparable & Element)
{
	Remove(Element, theRoot_);
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::RemoveIgnoreWarning(const Comparable & Element)
{
	RemoveIgnoreWarning(Element, theRoot_);
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::Root(Comparable & Element)
{
	if (IsEmpty())
	{
		THROW_STANDARD_EXCEPTION(TreeName(" Under flow tree: ", theName_));
	}

	Element = theRoot_->theElement_;
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::RetrieveTo(ADT_BasicQueue<Comparable>& Queue) const
{
	RetrieveTo(theRoot_, Queue);
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::RetrieveTo(ADT_Ary1d<Comparable>& Array) const
{
	ADT_BasicQueue<Comparable> Queue;

	RetrieveTo(theRoot_, Queue);

	Queue.RetrieveTo(Array);
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::Insert(const Comparable & x, ADT_AvlTreeNode<Comparable>*& t)
{
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

	Balance(t);
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::InsertIgnoreWarning(const Comparable & x, ADT_AvlTreeNode<Comparable>*& t)
{
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

	Balance(t);
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::Remove(const Comparable & x, ADT_AvlTreeNode<Comparable>*& t)
{
	if (t == nullptr)
	{
		THROW_STANDARD_EXCEPTION(" Item not found");

		return;
	}

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

	Balance(t);
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::RemoveIgnoreWarning(const Comparable & x, ADT_AvlTreeNode<Comparable>*& t)
{
	if (t == nullptr)
	{
		return;
	}

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

	Balance(t);
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::Balance(ADT_AvlTreeNode<Comparable>*& t)
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
inline void AutLib::ADT_AdressAvlTree<Comparable>::Clear(ADT_AvlTreeNode<Comparable>*& t)
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
inline AutLib::ADT_AvlTreeNode<Comparable>* AutLib::ADT_AdressAvlTree<Comparable>::Clone(ADT_AvlTreeNode<Comparable>* t) const
{
	if (t EQUAL nullptr)
		return nullptr;
	else
		return new ADT_AvlTreeNode<Comparable>(t->theElement_, Clone(t->theLeft_), Clone(t->theRight_), t->theHeight_);
}

template<typename Comparable>
inline AutLib::ADT_AvlTreeNode<Comparable>* AutLib::ADT_AdressAvlTree<Comparable>::FindMin(ADT_AvlTreeNode<Comparable>* t) const
{
	if (t EQUAL nullptr)
		return nullptr;
	if (t->theLeft_ EQUAL nullptr)
		return t;
	return FindMin(t->theLeft_);
}

template<typename Comparable>
inline AutLib::ADT_AvlTreeNode<Comparable>* AutLib::ADT_AdressAvlTree<Comparable>::FindMax(ADT_AvlTreeNode<Comparable>* t) const
{
	if (t NOT_EQUAL nullptr)
		while (t->theRight_ NOT_EQUAL nullptr)
			t = t->theRight_;
	return t;
}

template<typename Comparable>
inline Standard_Boolean AutLib::ADT_AdressAvlTree<Comparable>::IsContains(const Comparable & x, ADT_AvlTreeNode<Comparable>* t) const
{
	if (t == nullptr)
		return Standard_False;
	else if (x < t->theElement_)
		return IsContains(x, t->theLeft_);
	else if (t->theElement_ < x)
		return IsContains(x, t->theRight_);
	else
		return Standard_True;    // Match

}

template<typename Comparable>
inline Standard_Integer AutLib::ADT_AdressAvlTree<Comparable>::Height(ADT_AvlTreeNode<Comparable>* t) const
{
	return t EQUAL nullptr ? -1 : t->theHeight_;
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::RotateWithLeftChild(ADT_AvlTreeNode<Comparable>*& k2)
{
	ADT_AvlTreeNode<Comparable> *k1 = k2->theLeft_;
	k2->theLeft_ = k1->theRight_;
	k1->theRight_ = k2;
	k2->theHeight_ = MAX(Height(k2->theLeft_), Height(k2->theRight_)) + 1;
	k1->theHeight_ = MAX(Height(k1->theLeft_), k2->theHeight_) + 1;
	k2 = k1;
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::RotateWithRightChild(ADT_AvlTreeNode<Comparable>*& k1)
{
	ADT_AvlTreeNode<Comparable> *k2 = k1->theRight_;
	k1->theRight_ = k2->theLeft_;
	k2->theLeft_ = k1;
	k1->theHeight_ = MAX(Height(k1->theLeft_), Height(k1->theRight_)) + 1;
	k2->theHeight_ = MAX(Height(k2->theRight_), k1->theHeight_) + 1;
	k1 = k2;
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::DoubleWithLeftChild(ADT_AvlTreeNode<Comparable>*& k3)
{
	RotateWithRightChild(k3->theLeft_);
	RotateWithLeftChild(k3);
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::DoubleWithRightChild(ADT_AvlTreeNode<Comparable>*& k1)
{
	RotateWithLeftChild(k1->theRight_);
	RotateWithRightChild(k1);
}

template<typename Comparable>
inline void AutLib::ADT_AdressAvlTree<Comparable>::RetrieveTo(ADT_AvlTreeNode<Comparable>* t, ADT_BasicQueue<Comparable>& Queue) const
{
	if (t NOT_EQUAL nullptr)
	{
		RetrieveTo(t->theLeft_, Queue);

		Queue.EnQueue(t->theElement_);

		RetrieveTo(t->theRight_, Queue);
	}
}