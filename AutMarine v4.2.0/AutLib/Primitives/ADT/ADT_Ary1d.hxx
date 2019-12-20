#pragma once
#ifndef _ADT_Ary1d_Header
#define _ADT_Ary1d_Header

#include <Standard_DefineException.hxx>
#include <Standard_TypeDef.hxx>
#include <Standard_OStream.hxx>
#include <Global_Macros.hxx>

#define RESIZE_ARRAY1(Array, SIZE) \
  if(Array.Length() NOT_EQUAL SIZE) Array.Resize(SIZE);

#define SizeOf(List) \
  List.Size()

namespace AutLib
{

	template<typename T>
	class ADT_Ary1d
	{

	private:

		Standard_Integer myLowerBound_;
		Standard_Integer myUpperBound_;
		Standard_Boolean myDeletable_;

		T* vr_;

	public:

		ADT_Ary1d();

		ADT_Ary1d(const Standard_Integer Size);

		ADT_Ary1d(const Standard_Integer theLower, const Standard_Integer theUpper);

		ADT_Ary1d(const T& theBegin, const Standard_Integer theLower, const Standard_Integer theUpper);

		ADT_Ary1d(const ADT_Ary1d<T>& Other);

		~ADT_Ary1d();

		ADT_Ary1d<T>& operator=(const ADT_Ary1d<T>& Other);

		ADT_Ary1d<T>& operator+=(const ADT_Ary1d<T>& Other);

		ADT_Ary1d<T>& operator-=(const ADT_Ary1d<T>& Other);

		ADT_Ary1d<T>& operator*=(const ADT_Ary1d<T>& Other);

		ADT_Ary1d<T>& operator/=(const ADT_Ary1d<T>& Other);

		ADT_Ary1d<T>& operator=(const T& Entity);

		ADT_Ary1d<T>& operator+=(const T& Entity);

		ADT_Ary1d<T>& operator-=(const T& Entity);

		ADT_Ary1d<T>& operator*=(const T& Entity);

		ADT_Ary1d<T>& operator/=(const T& Entity);

		ADT_Ary1d<T>& operator+();

		ADT_Ary1d<T> operator-();

		ADT_Ary1d<T> operator+(const ADT_Ary1d<T>& Other);

		ADT_Ary1d<T> operator-(const ADT_Ary1d<T>& Other);

		ADT_Ary1d<T> operator*(const ADT_Ary1d<T>& Other);

		ADT_Ary1d<T> operator/(const ADT_Ary1d<T>& Other);

		ADT_Ary1d<T> operator+(const T& Entity);

		ADT_Ary1d<T> operator-(const T& Entity);

		ADT_Ary1d<T> operator*(const T& Entity);

		ADT_Ary1d<T> operator/(const T& Entity);

		//! Throw Exception
		ADT_Ary1d<T> operator[](const ADT_Ary1d<Standard_Integer>& Ind) const;

		const T& operator[](const Standard_Integer Index) const;

		const T& operator()(const Standard_Integer Index) const;

		const T& First() const;

		const T& Last() const;

		T& First();

		T& Last();

		T& operator[](const Standard_Integer Index);

		T& operator()(const Standard_Integer Index);

		const T& Value(const Standard_Integer Index) const;

		T& ChangeValue(const Standard_Integer Index);

		Standard_Integer Size() const;

		Standard_Integer Length() const;

		Standard_Integer Lower() const;

		Standard_Integer Upper() const;

		Standard_Boolean IsEmpty() const;

		void SetValue(const Standard_Integer theIndex, const T& theValue);

		void SetFirst(const T& theValue);

		void SetLast(const T& theValue);

		void Init(const T& theValue);

		void Resize(const Standard_Integer Size);

		void DynResize(const Standard_Integer Size);

		void Clear();

		void Reverse();

		void Print(Standard_OStream & Output = cout) const;

		template<typename T>
		friend ADT_Ary1d<T> operator+(const ADT_Ary1d<T>& V1, const ADT_Ary1d<T>& V2);

		template<typename T>
		friend ADT_Ary1d<T> operator-(const ADT_Ary1d<T>& V1, const ADT_Ary1d<T>& V2);

		template<typename T>
		friend ADT_Ary1d<T> operator*(const ADT_Ary1d<T>& V1, const ADT_Ary1d<T>& V2);

		template<typename T>
		friend ADT_Ary1d<T> operator/(const ADT_Ary1d<T>& V1, const ADT_Ary1d<T>& V2);

		template<typename T>
		friend ADT_Ary1d<T> operator+(const ADT_Ary1d<T>& V1, const T& Entity);

		template<typename T>
		friend ADT_Ary1d<T> operator+(const T& Entity, const ADT_Ary1d<T>& V1);

		template<typename T>
		friend ADT_Ary1d<T> operator-(const ADT_Ary1d<T>& V1, const T& Entity);

		template<typename T>
		friend ADT_Ary1d<T> operator-(const T& Entity, const ADT_Ary1d<T>& V1);

		template<typename T>
		friend ADT_Ary1d<T> operator*(const ADT_Ary1d<T>& V1, const T& Entity);

		template<typename T>
		friend ADT_Ary1d<T> operator*(const T& Entity, const ADT_Ary1d<T>& V1);

		template<typename T>
		friend ADT_Ary1d<T> operator/(const ADT_Ary1d<T>& V1, const T& Entity);
	};

	inline ADT_Ary1d<Standard_Integer> IndexAray(const Standard_Integer n)
	{
		ADT_Ary1d<Standard_Integer> a(n);

		for (Standard_Integer i = 0; i < n; i++)
			a[i] = i;

		MOVE(a);
	}
}

#include "ADT_Ary1dI.hxx"

#endif // !_ADT_Ary1d_Header
