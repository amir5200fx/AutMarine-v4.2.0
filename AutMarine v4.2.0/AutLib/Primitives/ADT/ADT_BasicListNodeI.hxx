#pragma once

template<typename T>
inline AutLib::ADT_BasicListNode<T>::ADT_BasicListNode(const T & Info)
	: theData_(Info)
	, theNext_(0)
{
}

template<typename T>
inline const T & AutLib::ADT_BasicListNode<T>::Data() const
{
	return theData_;
}

template<typename T>
inline AutLib::ADT_BasicListNode<T>* AutLib::ADT_BasicListNode<T>::Next() const
{
	return theNext_;
}