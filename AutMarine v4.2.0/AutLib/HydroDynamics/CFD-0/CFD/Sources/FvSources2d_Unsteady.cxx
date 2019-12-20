#include <FvSources2d_Unsteady.hxx>

#include <FvEntity_Element2d.hxx>
#include <FvMaterial_Density.hxx>
#include <FvParameters_TimeConfig.hxx>
#include <FvVariables2d.hxx>

AutLib::FvLib::FvSources2d_Unsteady::FvSources2d_Unsteady
(
	const FvParameters_TimeConfig & theTime,
	const FvMaterial_Density& theDensity,
	const FvVariables2d & theVariables
)
	: theTime_(theTime)
	, theDensity_(theDensity)
	, theVariables_(theVariables)
{
}

Geom_Pnt2d AutLib::FvLib::FvSources2d_Unsteady::Value(const FvEntity_Element2d & theElement) const
{
	return (theDensity_.Value()*theElement.Volume() / theTime_.Step())*Geom_Pnt2d(theVariables_.Xu(theElement.Index()), theVariables_.Xv(theElement.Index()));
}