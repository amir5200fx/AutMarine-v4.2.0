#pragma once
#ifndef _ADT_BasicListNode_Header
#define _ADT_BasicListNode_Header

namespace AutLib
{

	template<typename T>
	class ADT_BasicList;

	template<typename T>
	class ADT_BasicListNode 
	{
		friend class ADT_BasicList<T>;

	private:

		T theData_;

		ADT_BasicListNode<T> *theNext_;

	public:

		ADT_BasicListNode(const T&); // constructor

		const T & Data() const;

		ADT_BasicListNode<T>* Next() const;

	};
}

#include "ADT_BasicListNodeI.hxx"

#endif // !_ADT_BasicListNode_Header
