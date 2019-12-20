#include <Compound_ShipSystems.hxx>

#include <Geometry_Tools.hxx>

using namespace AutLib;
using namespace GeoLib;

#include <gp_Trsf.hxx>

AutLib::CadLib::Compound_ShipSystems::Compound_ShipSystems()
{
}

void AutLib::CadLib::Compound_ShipSystems::Init
(
	const gp_Ax2 & theHullSys,
	const gp_Ax2 & theRudderSys,
	const gp_Ax2 & thePropSys
)
{
	theHull_ = theHullSys;
	theRudder_ = theRudderSys;
	theProp_ = thePropSys;
}

void AutLib::CadLib::Compound_ShipSystems::SetRudderSystem(const Compound_ShipRudderSystemParameters & theParameters)
{
	//theRudder_ = theHull_;

	gp_Trsf Translation;
	Translation.SetTranslation(theRudder_.Location(), gp_Pnt(theParameters.X(), theParameters.Y(), theParameters.Z()));

	theRudder_.Transform(Translation);

	gp_Trsf Rotate1;
	Rotate1.SetRotation(gp_Ax1(theRudder_.Location(), theRudder_.Direction()), M_PI);

	theRudder_.Transform(Rotate1);

	gp_Trsf Rotate2;
	Rotate2.SetRotation(gp_Ax1(theRudder_.Location(), theRudder_.Direction()), Geometry_Tools::DegToRadian(theParameters.ShaftInclination()));

	theRudder_.Transform(Rotate2);
}

void AutLib::CadLib::Compound_ShipSystems::SetPropellerSystem(const Compound_ShipPropellerSystemParameters & theParameters)
{
	gp_Trsf Translation;
	Translation.SetTranslation(theProp_.Location(), gp_Pnt(theParameters.X(), theParameters.Y(), theParameters.Z()));

	theProp_.Transform(Translation);

	gp_Trsf Rotate;
	Rotate.SetRotation(gp_Ax1(theRudder_.Location(), theRudder_.YDirection()), Geometry_Tools::DegToRadian(theParameters.ShaftInclination()));

	theProp_.Transform(Rotate);
}