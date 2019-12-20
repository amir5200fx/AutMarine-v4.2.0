#include <FvSources2d_Pressure.hxx>

#include <FvEntity_Element2d.hxx>
#include <FvVariables2d.hxx>
#include <FvGradient2d.hxx>

AutLib::FvLib::FvSources2d_Pressure::FvSources2d_Pressure(const FvGradient2d_Pressure& theGradient)
	: theGradient_(theGradient)
	, theBoundary_(Standard_True)
{
}

Geom_Pnt2d AutLib::FvLib::FvSources2d_Pressure::Value(const FvEntity_Element2d & theElement) const
{
	return -theGradient_.CalcGradient(theElement, theBoundary_)*theElement.Volume();
}