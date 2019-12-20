#pragma once
#ifndef _ADT_Ary2d_Header
#define _ADT_Ary2d_Header

#include <Standard_TypeDef.hxx>
#include <Standard_OStream.hxx>
#include <Global_Macros.hxx>

namespace AutLib
{

	template<typename T>
	class ADT_Ary2d
	{

	private:

		Standard_Integer theNbRows_;
		Standard_Integer theNbCols_;

		T** theEts_;

	public:

		ADT_Ary2d(const Standard_Integer NbRows = 0, const Standard_Integer nbCols = 0);

		ADT_Ary2d(const Standard_Integer NbRows, const Standard_Integer nbCols, const T& Value);

		ADT_Ary2d(const ADT_Ary2d<T>& Other);

		~ADT_Ary2d();

		ADT_Ary2d<T>& operator=(const ADT_Ary2d<T>& Other);

		//! Throw an exception
		ADT_Ary2d<T>& operator+=(const ADT_Ary2d<T>& Other);

		//! Throw an exception
		ADT_Ary2d<T>& operator-=(const ADT_Ary2d<T>& Other);

		ADT_Ary2d<T>& operator=(const T& Object);

		ADT_Ary2d<T>& operator+=(const T& Object);

		ADT_Ary2d<T>& operator-=(const T& Object);

		ADT_Ary2d<T>& operator*=(const T& Object);

		ADT_Ary2d<T>& operator/=(const T& Object);

		ADT_Ary2d<T>& operator+();

		ADT_Ary2d<T> operator-();

		//! Throw an exception
		ADT_Ary2d<T> operator+(const ADT_Ary2d<T>& Other);

		//! Throw an exception
		ADT_Ary2d<T> operator-(const ADT_Ary2d<T>& Other);

		ADT_Ary2d<T> operator+(const T& Object);

		ADT_Ary2d<T> operator-(const T& Object);

		ADT_Ary2d<T> operator*(const T& Object);

		ADT_Ary2d<T> operator/(const T& Object);

		T* operator[](const Standard_Integer Index) const;

		T*& operator[](const Standard_Integer Index);

		const T& operator()(const Standard_Integer Index1, const Standard_Integer Index2) const;

		T& operator()(const Standard_Integer Index1, const Standard_Integer Index2);

		Standard_Integer Size(const Standard_Integer Index) const;

		Standard_Integer NbRows() const;

		Standard_Integer NbCols() const;

		Standard_Integer LowerRow() const;

		Standard_Integer UpperRow() const;

		Standard_Integer LowerCol() const;

		Standard_Integer UpperCol() const;

		Standard_Boolean MatchSizeWith(const ADT_Ary2d<T>& Other) const;

		void Init(const T& Value);

		void Clear();

		void Resize(const Standard_Integer NbRows, const Standard_Integer NbCols);

		void DynResize(const Standard_Integer NbRows, const Standard_Integer NbCols);

		void Print(Standard_OStream& Stream = cout) const;

		template<typename T>
		friend ADT_Ary2d<T> operator+(const ADT_Ary2d<T>& A1, const ADT_Ary2d<T>& A2);

		template<typename T>
		friend ADT_Ary2d<T> operator-(const ADT_Ary2d<T>& A1, const ADT_Ary2d<T>& A2);

		template<typename T>
		friend ADT_Ary2d<T> operator+(const ADT_Ary2d<T>& A1, const T& Object);

		template<typename T>
		friend ADT_Ary2d<T> operator+(const T& Object, const ADT_Ary2d<T>& A1);

		template<typename T>
		friend ADT_Ary2d<T> operator-(const ADT_Ary2d<T>& A1, const T& Object);

		template<typename T>
		friend ADT_Ary2d<T> operator*(const ADT_Ary2d<T>& A1, const T& Object);

		template<typename T>
		friend ADT_Ary2d<T> operator*(const T& Object, const ADT_Ary2d<T>& A1);

		template<typename T>
		friend ADT_Ary2d<T> operator/(const ADT_Ary2d<T>& A1, const T& Object);
	};
}

#include <ADT_Ary2dI.hxx>

#endif // !_ADT_Ary2d_Header
