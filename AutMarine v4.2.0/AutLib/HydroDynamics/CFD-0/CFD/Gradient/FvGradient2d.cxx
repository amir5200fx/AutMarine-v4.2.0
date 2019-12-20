#include <FvGradient2d.hxx>

#include <Global_Debug.hxx>
#include <FvEntity_Face2d.hxx>
#include <FvEntity_Element2d.hxx>
#include <FvInterpolation.hxx>

AutLib::FvLib::FvGradient2d::FvGradient2d(const FvInterpolation & theInterpolation)
	: theInterpolation_(theInterpolation)
{
}

Geom_Pnt2d AutLib::FvLib::FvGradient2d::CalcGradient
(
	const FvEntity_Element2d & theElement, 
	const Standard_Boolean Boundary
) const
{
	Geom_Pnt2d Sum(0, 0);
	forThose
	(
		Index,
		0,
		theElement.NbFaces() - 1
	)
	{
		Debug_Null_Pointer(theElement.Face(Index));

		Get_Const_Object(Face) = *theElement.Face(Index);

		Sum += theInterpolation_.Interpolate(Face, Boundary)*Face.A();
	}
	return Sum / theElement.Volume();
}