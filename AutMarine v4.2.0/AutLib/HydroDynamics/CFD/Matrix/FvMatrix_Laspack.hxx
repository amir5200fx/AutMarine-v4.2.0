#pragma once
#ifndef _FvMatrix_Laspack_Header
#define _FvMatrix_Laspack_Header

#include <FvMatrix.hxx>
#include <laspack.h>

namespace AutLib
{
	namespace FvLib
	{

		class FvMatrix_Laspack : public FvMatrix
		{

		private:

			QMatrix theMatrix_;

		public:

			FvMatrix_Laspack();

			Label BandSize(const Label theElement) const;

			Label GetPos(const Label theElement, const Label theNeighbor) const;

			Label Dim() const;

			Scalar GetValue(const Label theElement, const Label theNeighbor) const;

			Standard_Boolean IsSameAs(const FvMatrix& theOther) const;

			virtual void SetValue(const Label theElementIndex, const Label theNeighbor, const Label theNeighborIndex, const Scalar theValue);

			virtual void AddValue(const Label theElementIndex, const Label theNeighbor, const Scalar theValue);

			virtual void AllocateDim(const Label theSize, const Standard_Boolean Symmetry);

			virtual void AllocateBandDim(const Label theElement, const Label theSize);

			virtual void ReleaseMemory();
		};
	}
}

#include <FvMatrix_LaspackI.hxx>

#endif // !_FvMatrix_Laspack_Header
