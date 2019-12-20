#pragma once
#include <Global_Macros.hxx>
inline
const M_CAD Prop_ParameterProfile & AutLib::CadLib::Prop_BladeProfiles::PitchProfile() const
{
	return thePitch_;
}

inline 
const M_CAD Prop_ParameterProfile & AutLib::CadLib::Prop_BladeProfiles::ChordProfile() const
{
	return theChord_;
}

inline 
const M_CAD Prop_ParameterProfile & AutLib::CadLib::Prop_BladeProfiles::CamberProfile() const
{
	return theCamber_;
}

inline 
const M_CAD Prop_ParameterProfile & AutLib::CadLib::Prop_BladeProfiles::SkewProfile() const
{
	return theSkew_;
}

inline 
const M_CAD Prop_ParameterProfile & AutLib::CadLib::Prop_BladeProfiles::RakeProfile() const
{
	return theRake_;
}

inline 
const M_CAD Prop_ParameterProfile & AutLib::CadLib::Prop_BladeProfiles::ThicknessProfile() const
{
	return theThickness_;
}