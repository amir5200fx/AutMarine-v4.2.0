#pragma once
#ifndef _ADT_BasicStack_Header
#define _ADT_BasicStack_Header

#include <ADT_BasicList.hxx>

namespace AutLib
{

	template<typename T>
	class ADT_BasicStack : public ADT_BasicList<T>
	{

	public:

		void Push(const T& Object)
		{
			InsertAtFront(Object);
		}

		Standard_Boolean Pop(T& Object)
		{
			return RemoveFromFront(Object);
		}
	};
}

#endif // !_ADT_BasicStack_Header
