#pragma once
inline
const M_CAD Prop_BladeProfiles & AutLib::CadLib::Prop_Propeller::Profiles() const
{
	return theProfiles_;
}

inline 
const M_CAD Prop_PropellerParameters & AutLib::CadLib::Prop_Propeller::Parameters() const
{
	return theParameters_;
}

inline 
M_CAD Prop_PropellerParameters & AutLib::CadLib::Prop_Propeller::Parameters()
{
	return theParameters_;
}