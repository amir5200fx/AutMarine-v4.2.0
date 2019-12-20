#pragma once
inline
const M_CAD Prop_BladeForm& AutLib::CadLib::Prop_PropellerParameters::BladeParameters() const
{
	return theBlade_;
}

inline 
const M_CAD Prop_HubForm & AutLib::CadLib::Prop_PropellerParameters::HubParameters() const
{
	return theHub_;
}

inline 
M_CAD Prop_BladeForm & AutLib::CadLib::Prop_PropellerParameters::BladeParameters()
{
	return theBlade_;
}

inline 
M_CAD Prop_HubForm & AutLib::CadLib::Prop_PropellerParameters::HubParameters()
{
	return theHub_;
}

inline 
Standard_Boolean AutLib::CadLib::Prop_PropellerParameters::RemoveHubApex() const
{
	return RemoveHubApex_;
}

inline 
Standard_Integer AutLib::CadLib::Prop_PropellerParameters::NbBlades() const
{
	return theNbBlades_;
}

inline 
Standard_Integer AutLib::CadLib::Prop_PropellerParameters::NbSections() const
{
	return theNbSections_;
}

inline 
Standard_Integer AutLib::CadLib::Prop_PropellerParameters::NbSpans() const
{
	return theNbSpans_;
}

inline 
Standard_Real AutLib::CadLib::Prop_PropellerParameters::Diameter() const
{
	return theDiameter_;
}

inline 
Standard_Real AutLib::CadLib::Prop_PropellerParameters::HubRadius() const
{
	return theHubRadius_;
}

inline 
Standard_Real AutLib::CadLib::Prop_PropellerParameters::TipGap() const
{
	return theTipGap_;
}

inline 
Standard_Real AutLib::CadLib::Prop_PropellerParameters::TEGap() const
{
	return theTEGap_;
}