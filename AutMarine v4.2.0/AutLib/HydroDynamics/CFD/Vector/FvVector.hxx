#pragma once
#ifndef _FvVector_Header
#define _FvVector_Header

#include <FvPrimitives_Scalar.hxx>
#include <FvPrimitives_Label.hxx>
#include <Standard_String.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvVector
		{

		private:

			Standard_String theName_;

		public:

			const Standard_String& Name() const;

			void SetName(const Standard_String theName);

			virtual Label Size() const = 0;

			virtual Scalar Value(const Label theIndex) const = 0;

			virtual Scalar operator[](const Label theIndex) const = 0;

			virtual Scalar operator()(const Label theIndex) const = 0;

			virtual void Init(const Scalar theValue) = 0;

			virtual void SetValue(const Label theIndex, const Scalar theValue) = 0;

			virtual void AddValue(const Label theIndex, const Scalar theValue) = 0;

			virtual void Allocate(const Label theSize) = 0;

			virtual void ReleaseMemory() = 0;

		protected:

			FvVector();
		};
	}
}

#include <FvVectorI.hxx>

#endif // !_FvVector_Header
