#pragma once
#ifndef _ADT_BasicList_Header
#define _ADT_BasicList_Header

#include <ADT_BasicListNode.hxx>
#include <Standard_TypeDef.hxx>
#include <ADT_Ary1d.hxx>

namespace AutLib
{

	template<typename T>
	class ADT_BasicList
	{

	private:

		ADT_BasicListNode<T>* theFirst_;
		ADT_BasicListNode<T>* theLast_;

		Standard_Integer theNbItems_;

	public:

		ADT_BasicList();

		ADT_BasicList(const ADT_BasicList<T>& Other);

		~ADT_BasicList();

		ADT_BasicList<T>& operator=(const ADT_BasicList<T>& Other);

		T FirstItem() const;

		T LastItem() const;

		ADT_BasicListNode<T>* NextItem(ADT_BasicListNode<T>* Node) const;

		Standard_Integer Size() const;

		Standard_Boolean IsEmpty() const;

		Standard_Boolean RemoveFromFront(T& Object);

		Standard_Boolean RemoveFromBack(T& Object);

		void InsertAfter(ADT_BasicListNode<T>* Node, const T& Object);

		void Remove(const T& Object);
		
		void Remove(ADT_BasicListNode<T>*& Node);

		void RemoveFromFront();

		void RemoveFromBack();

		void InsertAtFront(const T& Object);

		void InsertAtBack(const T& Object);

		void RetrieveTo(ADT_Ary1d<T>& Array) const;

		ADT_Ary1d<T> Retrive() const;

		void Clear();

		void Print(Standard_OStream & Output = cout) const;

	private:

		ADT_BasicListNode<T>* NewNode(const T& Object);
	};
}

#include <ADT_BasicListI.hxx>

#endif // !_ADT_BasicList_Header
