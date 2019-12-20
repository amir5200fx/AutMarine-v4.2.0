#pragma once
#ifndef _ADT_BasicQueue_Header
#define _ADT_BasicQueue_Header

#include <ADT_BasicList.hxx>

namespace AutLib
{

	template<typename T>
	class ADT_BasicQueue : public ADT_BasicList<T>
	{

	public:

		void EnQueue(const T& Object)
		{
			InsertAtBack(Object);
		}

		void EnQueue(const ADT_Ary1d<T>& Objects)
		{
			forThose(Index, 0, MaxIndexOf(Objects))
				EnQueue(Objects[Index]);
		}

		void EnQueue(ADT_BasicQueue<T>& Objects)
		{
			T Item;
			while (Objects.DeQueue(Item))
				EnQueue(Item);
		}

		Standard_Boolean DeQueue(T& Object)
		{
			return RemoveFromFront(Object);
		}
	};
}

#endif // !_ADT_BasicQueue_Header
