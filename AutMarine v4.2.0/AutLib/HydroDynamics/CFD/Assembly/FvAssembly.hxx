#pragma once
#ifndef _FvAssembly_Header
#define _FvAssembly_Header

#include <Global_Memory.hxx>
#include <FvPrimitives_Scalar.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvMatrix;
		class FvVectorField;

		class FvAssembly
		{

		private:

			Global_Handle(FvMatrix) theMatrix_;

			Global_Handle(FvVectorField) theSources_;

		public:

			FvAssembly();

			Global_Handle(FvMatrix)& Matrix();

			Global_Handle(FvVectorField)& Sources();

			const Global_Handle(FvMatrix) Matrix() const;

			const Global_Handle(FvVectorField) Sources() const;

			Standard_Boolean IsSameAs(const FvAssembly& theOther) const;

			FvAssembly& operator=(const FvAssembly& theOther);

			FvAssembly& operator+=(const FvAssembly& theOther);

			FvAssembly& operator-=(const FvAssembly& theOther);

			FvAssembly& operator+();

			FvAssembly operator-();

			friend FvAssembly operator+(const FvAssembly& theAssembly1, const FvAssembly& theAssembly2);

			friend FvAssembly operator-(const FvAssembly& theAssembly1, const FvAssembly& theAssembly2);
		};
	}
}

#include <FvAssemblyI.hxx>

#endif // !_FvAssembly_Header
