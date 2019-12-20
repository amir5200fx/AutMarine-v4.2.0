#pragma once
#include <Global_Debug.hxx>
#include <FvEntity_Face2d.hxx>
#include <FvEntity_Element2d.hxx>
#include <FvInterpolation2d.hxx>

inline
Vec2 AutLib::FvLib::FvGradient2d::CalcGradient
(
	const FvEntity_Element2d & theElement,
	const Standard_Boolean Boundary
) const
{
	Vec2 Sum(0, 0);
	forThose
	(
		Index,
		0, 
		theElement.NbFaces() - 1
	)
	{
		Debug_Null_Pointer(theElement.Face(Index));

		Get_Const_Object(Face) = *theElement.Face(Index);

		Sum += theInterpolation_.Apply(Face, Boundary)*Face.Sf();
	}
	return Sum / theElement.Volume();
}