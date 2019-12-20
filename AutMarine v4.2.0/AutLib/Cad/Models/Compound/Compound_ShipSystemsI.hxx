#pragma once
inline
const gp_Ax2 & AutLib::CadLib::Compound_ShipSystems::RudderSystem() const
{
	return theRudder_;
}

inline
const gp_Ax2 & AutLib::CadLib::Compound_ShipSystems::PropellerSystem() const
{
	return theProp_;
}

inline 
const gp_Ax2 & AutLib::CadLib::Compound_ShipSystems::HullSystem() const
{
	return theHull_;
}