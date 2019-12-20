#include <FvSources2d_BodyForce.hxx>

#include <FvEntity_Element2d.hxx>
#include <FvBodyForce2d.hxx>

AutLib::FvLib::FvSources2d_BodyForce::FvSources2d_BodyForce(const FvBodyForce2d & theBodyForce)
	: theBodyForce_(theBodyForce)
{
}

Geom_Pnt2d AutLib::FvLib::FvSources2d_BodyForce::Value(const FvEntity_Element2d & theElement) const
{
	return theBodyForce_.Value(theElement.Centre())*theElement.Volume();
}