#pragma once
inline
const M_CAD Ship_Hull & AutLib::CadLib::Compound_Ship::Hull() const
{
	return theShip_;
}

inline 
const M_CAD Rudder & AutLib::CadLib::Compound_Ship::Rudder() const
{
	return theRudder_;
}

inline 
const M_CAD Prop_Propeller & AutLib::CadLib::Compound_Ship::Propeller() const
{
	return thePropeller_;
}