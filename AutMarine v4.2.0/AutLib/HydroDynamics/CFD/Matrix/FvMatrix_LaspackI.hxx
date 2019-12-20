#pragma once
inline
Label AutLib::FvLib::FvMatrix_Laspack::BandSize(const Label theElement) const
{
	return (Label)Q_GetLen((QMatrix*)&theMatrix_, theElement);
}

inline 
Label AutLib::FvLib::FvMatrix_Laspack::GetPos
(
	const Label theElement, 
	const Label theNeighbor
) const
{
	return (Label)Q_GetPos((QMatrix*)&theMatrix_, theElement, theNeighbor);
}

inline 
Label AutLib::FvLib::FvMatrix_Laspack::Dim() const
{
	return (Label)Q_GetDim((QMatrix*)&theMatrix_);
}

inline 
Scalar AutLib::FvLib::FvMatrix_Laspack::GetValue
(
	const Label theElement, 
	const Label theNeighbor
) const
{
	return (Scalar)Q_GetVal((QMatrix*)&theMatrix_, theElement, theNeighbor);
}

inline
void AutLib::FvLib::FvMatrix_Laspack::SetValue
(
	const Label theElementIndex, 
	const Label theNeighbor, 
	const Label theNeighborIndex, 
	const Scalar theValue
)
{
	Q_SetEntry((QMatrix*)&theMatrix_, (size_t)theElementIndex, (size_t)theNeighbor, (size_t)theNeighborIndex, (Real)theValue);
}

inline 
void AutLib::FvLib::FvMatrix_Laspack::AddValue
(
	const Label theElementIndex,
	const Label theNeighbor,
	const Scalar theValue
)
{
	Q_AddVal((QMatrix*)&theMatrix_, (size_t)theElementIndex, (size_t)theNeighbor, (Real)theValue);
}


inline
void AutLib::FvLib::FvMatrix_Laspack::AllocateBandDim
(
	const Label theElement, 
	const Label theSize
)
{
	Q_SetLen((QMatrix*)&theMatrix_, (size_t)theElement, (size_t)theSize);
}