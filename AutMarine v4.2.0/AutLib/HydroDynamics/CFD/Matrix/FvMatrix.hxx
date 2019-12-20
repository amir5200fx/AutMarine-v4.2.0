#pragma once
#ifndef _FvMatrix_Header
#define _FvMatrix_Header

#include <Standard_String.hxx>
#include <FvPrimitives_Label.hxx>
#include <FvPrimitives_Scalar.hxx>

namespace AutLib
{
	namespace FvLib
	{

		class FvMatrix
		{

		private:

			Standard_String theName_;
			
		public:

			void SetName(const Standard_String& theName);

			const Standard_String& Name() const;

			virtual Label BandSize(const Label theElement) const = 0;

			virtual Label GetPos(const Label theElement, const Label theNeighbor) const = 0;

			virtual Label Dim() const = 0;

			virtual Scalar GetValue(const Label theElement, const Label theNeighbor) const = 0;

			virtual Standard_Boolean IsSameAs(const FvMatrix& theOther) const = 0;

			virtual void SetValue(const Label theElementIndex, const Label theNeighbor, const Label theNeighborIndex, const Scalar theValue) = 0;

			virtual void AddValue(const Label theElementIndex, const Label theNeighbor, const Scalar theValue) = 0;

			virtual void AllocateDim(const Label theSize, const Standard_Boolean Symmetry) = 0;
			
			virtual void AllocateBandDim(const Label theElement, const Label theSize) = 0;

			virtual void ReleaseMemory() = 0;

		protected:

			FvMatrix();


		};
	}

}

#include <FvMatrixI.hxx>

#endif // !_FvMatrix_Header