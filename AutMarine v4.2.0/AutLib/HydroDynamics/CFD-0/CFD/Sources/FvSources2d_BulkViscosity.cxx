#include <FvSources2d_BulkViscosity.hxx>

#include <Global_Debug.hxx>
#include <FvEntity_Face2d.hxx>
#include <FvEntity_Element2d.hxx>
#include <FvVariables2d.hxx>
#include <FvMaterial_Viscosity.hxx>
#include <FvInterpolation_Mean.hxx>

using namespace AutLib;
using namespace GeoLib;

AutLib::FvLib::FvSources2d_BulkViscosity::FvSources2d_BulkViscosity
(
	const FvVariables2d& theVariables,
	const FvMaterial_Viscosity& theViscosity
)
	: theVariables_(theVariables)
	, theViscosity_(theViscosity)
	, Interpolation_(&FvInterpolation_Mean::Interpolate)
{
}

void AutLib::FvLib::FvSources2d_BulkViscosity::SetInterpolation(Geom_Pnt2d(*Interpolation)(const FvEntity_Face2d &theFace, const TColGeom_Ary1dOfPnt2d &thePhi))
{
	Interpolation_ = Interpolation;
}

Geom_Pnt2d AutLib::FvLib::FvSources2d_BulkViscosity::Value(const FvEntity_Element2d & theElement) const
{
	Get_Const_Object(XuGrad) = theVariables_.GradXu();
	Get_Const_Object(XvGrad) = theVariables_.GradXv();

	Standard_Real Visc = theViscosity_.Value();

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

		Sum += Visc*(DotProduct(Interpolation_(Face, XuGrad), Face.A()), DotProduct(Interpolation_(Face, XvGrad), Face.A()));
	}
	return Sum;
}