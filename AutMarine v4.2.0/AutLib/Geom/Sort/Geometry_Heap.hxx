#pragma once
#ifndef _Geom_Heap_Header
#define _Geom_Heap_Header

#include <ADT_Ary1d.hxx>

namespace AutLib
{
	namespace GeoLib
	{

		template<typename T>
		class Geometry_Heap
		{

		private:

			ADT_Ary1d<T> theData_;

			Standard_Integer theSize_;

			Standard_Real(*theLengthValue)(const T&);

		public:

			Geometry_Heap();

			Geometry_Heap(Standard_Real(*LengthValue)(const T&));

			Standard_Integer Size() const;

			const ADT_Ary1d<T>& Data() const;

			Standard_Boolean IsEmpty() const;

			Standard_Boolean GetItem(T& Item);

			void Resize(const Standard_Integer NbItems);

			// Throw an Exception
			void Insert(const T& Item);

			// Throw an Exception
			void Insert(const ADT_Ary1d<T>& Item);

			void SetFunction(Standard_Real(*LengthValue)(const T&));

		private:

			// Throw an Exception
			T Remove();

			void ShiftUp(const Standard_Integer);

			void ShiftDown(const Standard_Integer);

			inline Standard_Integer LeftChild(const Standard_Integer Index) { return 2 * Index + 1; }

			inline Standard_Integer RightChild(const Standard_Integer Index) { return 2 * Index + 2; }

			inline Standard_Integer Parent(const Standard_Integer Index) { return (Index - 1) / 2; }
		};
	}
}

#include <Geometry_HeapI.hxx>

#endif // !_Geom_Heap_Header
