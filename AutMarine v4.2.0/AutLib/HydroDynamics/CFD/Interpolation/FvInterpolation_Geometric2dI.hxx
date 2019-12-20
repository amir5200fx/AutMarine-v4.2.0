#pragma once
#include <Global_Debug.hxx>
#include <FvVector.hxx>
#include <FvEntity_Element2d.hxx>

inline
Scalar AutLib::FvLib::FvInterpolation_Geometric2d::Apply
(
	const FvEntity_Face2d & theFace, 
	const Standard_Boolean theBoundary
) const
{
	Get_Const_Object(CellVector) = FvInterpolation2d::CellVector();

	if (theFace.IsOnBoundary())
	{
		if (theBoundary)
		{
			Get_Const_Object(FaceVector) = FvInterpolation2d::FaceVector();

			return FaceVector[theFace.Index()];
		}
		else
		{
			Debug_Null_Pointer(theFace.Element());

			Get_Const_Object(Element) = *theFace.Element();

			return CellVector[Element.Index()];
		}
	}
	else
	{
		Debug_Null_Pointer(theFace.Element());
		Debug_Null_Pointer(theFace.Pair());
		Debug_Null_Pointer(theFace.Pair()->Element());

		Get_Const_Object(Neighbor) = *theFace.Pair()->Element();
		Get_Const_Object(Element) = *theFace.Element();

		return CellVector[Neighbor.Index()] * theFace.gcCoeff() + CellVector[Element.Index()] * ((Scalar)1.0 - theFace.gcCoeff());
	}
}