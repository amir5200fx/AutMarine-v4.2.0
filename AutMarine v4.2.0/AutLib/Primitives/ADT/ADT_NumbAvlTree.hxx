#pragma once
#ifndef _ADT_NumbAvlTree_Header
#define _ADT_NumbAvlTree_Header

#include <ADT_AvlTreeNode.hxx>
#include <ADT_BasicQueue.hxx>
#include <Standard_String.hxx>
#include <Global_Configs.hxx>
#include <Global_Debug.hxx>

namespace AutLib
{
	template<typename Comparable>
	class ADT_NumbAvlTree
	{

	private:

		static const Standard_Integer ALLOWED_IMBALANCE = 1;

		ADT_AvlTreeNode<Comparable>* theRoot_;

		Standard_String theName_;

		Standard_Integer theNbElements_;

		Standard_Boolean(*IsLess)(const Comparable&, const Comparable&);

	public:

		ADT_NumbAvlTree();

		ADT_NumbAvlTree(const ADT_NumbAvlTree & Other);

		~ADT_NumbAvlTree();

		ADT_NumbAvlTree<Comparable>& operator=(const ADT_NumbAvlTree& Other);

		const Comparable& FindMin() const;

		const Comparable& FindMax() const;

		Standard_Boolean IsContains(const Comparable& Element) const;

		Standard_Boolean IsEmpty() const;

		Standard_Integer Size() const;

		ADT_Ary1d<Comparable> Retrieve() const;

		void SetName(const Standard_String& Name);

		void SetComparable(Standard_Boolean(*IS_LESS)(const Comparable &, const Comparable &));

		void Clear();

		void Insert(const ADT_Ary1d<Comparable>& Elements);

		//! Throw an exception
		void Insert(const Comparable& Element);

		void InsertIgnoreDup(const Comparable& Element);

		void InsertIgnoreDup(const ADT_Ary1d<Comparable>& Elements);

		//! Throw an exception
		void Remove(const Comparable & Element);

		void RemoveIgnoreWarning(const Comparable& Element);

		void Root(Comparable& Element);

		void RetrieveTo(ADT_BasicQueue<Comparable>& Queue) const;

		void RetrieveTo(ADT_Ary1d<Comparable>& Array) const;

	private:

		void Insert(const Comparable& x, ADT_AvlTreeNode<Comparable>*& t);

		void InsertIgnoreWarning(const Comparable& x, ADT_AvlTreeNode<Comparable>*& t);

		void Remove(const Comparable& x, ADT_AvlTreeNode<Comparable>*& t);

		void RemoveIgnoreWarning(const Comparable& x, ADT_AvlTreeNode<Comparable>*& t);

		void Balance(ADT_AvlTreeNode<Comparable>*& t);

		void Clear(ADT_AvlTreeNode<Comparable>*& t);

		ADT_AvlTreeNode<Comparable>* Clone(ADT_AvlTreeNode<Comparable>* t) const;

		ADT_AvlTreeNode<Comparable>* FindMin(ADT_AvlTreeNode<Comparable>* t) const;

		ADT_AvlTreeNode<Comparable>* FindMax(ADT_AvlTreeNode<Comparable>* t) const;

		Standard_Boolean IsContains(const Comparable& x, ADT_AvlTreeNode<Comparable>* t) const;

		Standard_Integer Height(ADT_AvlTreeNode<Comparable>* t) const;

		Standard_Integer Maximum(const Standard_Integer lhs, const Standard_Integer rhs) const;

		void RotateWithLeftChild(ADT_AvlTreeNode<Comparable>* &k2);

		void RotateWithRightChild(ADT_AvlTreeNode<Comparable>* &k1);

		void DoubleWithLeftChild(ADT_AvlTreeNode<Comparable>* & k3);

		void DoubleWithRightChild(ADT_AvlTreeNode<Comparable>* & k1);

		void RetrieveTo(ADT_AvlTreeNode<Comparable>* t, ADT_BasicQueue<Comparable>& Queue) const;

		static Standard_String TreeName(const AutLib::Standard_String& theMessage, const AutLib::Standard_String& Name);
	};
}

#include <ADT_NumbAvlTreeI.hxx>

#endif // !_ADT_NumbAvlTree_Header
