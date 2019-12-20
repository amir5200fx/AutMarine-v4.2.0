#pragma once
#ifndef _ADT_AdressAvlTree_Header
#define _ADT_AdressAvlTree_Header

#include <ADT_AvlTreeNode.hxx>
#include <ADT_BasicQueue.hxx>
#include <Standard_String.hxx>
#include <Global_Configs.hxx>
#include <Global_Debug.hxx>

namespace AutLib
{

	template<typename Comparable>
	class ADT_AdressAvlTree
	{

	private:

		inline AutLib::Standard_String TreeName(const AutLib::Standard_String& theMessage, const AutLib::Standard_String& Name)
		{
			Standard_SStream _SUM;

			_SUM << theMessage << Name;

			return _SUM.str();
		}

		static const Standard_Integer ALLOWED_IMBALANCE = 1;

		ADT_AvlTreeNode<Comparable>* theRoot_;

		Standard_String theName_;

		Standard_Integer theNbElements_;

		Standard_Boolean(*IsLess)(const Comparable&, const Comparable&);

	public:

		ADT_AdressAvlTree();

		ADT_AdressAvlTree(const ADT_AdressAvlTree & Other);

		~ADT_AdressAvlTree();

		ADT_AdressAvlTree<Comparable>& operator=(const ADT_AdressAvlTree& Other);

		const Comparable& FindMin() const;

		const Comparable& FindMax() const;

		Standard_Boolean IsContains(const Comparable& Element) const;

		Standard_Boolean IsEmpty() const;

		Standard_Integer Size() const;

		ADT_Ary1d<Comparable> Retrieve() const;

		void SetName(const Standard_String& Name);

		void SetComparable(bool(*IS_LESS)(const Comparable &, const Comparable &));

		void Clear();

		//! Throw an exception
		void Insert(const Comparable& Element);

		//! Throw an exception
		void Insert(const ADT_Ary1d<Comparable>& Elements);

		void InsertIgnoreDup(const Comparable& Element);

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

	};
}

#include <ADT_AdressAvlTreeI.hxx>

#endif // !_ADT_AdressAvlTree_Header
