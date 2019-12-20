#pragma once
#ifndef _FvVector_Laspack_Header
#define _FvVector_Laspack_Header

#include <FvVector.hxx>
#include <laspack.h>

namespace AutLib
{
	namespace FvLib
	{

		class FvVector_Laspack : public FvVector
		{

		private:

			Vector theVector_;

		public:

			FvVector_Laspack();

			~FvVector_Laspack();

			virtual Label Size() const;

			virtual Scalar Value(const Label theIndex) const;

			virtual Scalar operator[](const Label theIndex) const;

			virtual Scalar operator()(const Label theIndex) const;

			virtual void Init(const Scalar theValue);

			virtual void SetValue(const Label theIndex, const Scalar theValue);

			virtual void AddValue(const Label theIndex, const Scalar theValue);

			virtual void Allocate(const Label theSize);

			virtual void ReleaseMemory();
		};
	}
}

#include <FvVector_LaspackI.hxx>

#endif // !_FvVector_Laspack_Header
