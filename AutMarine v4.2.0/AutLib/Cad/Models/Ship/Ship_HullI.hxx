#pragma once

inline 
const M_CAD Ship_Profiles & AutLib::CadLib::Ship_Hull::Profiles() const
{
	return theProfiles_;
}

inline 
M_CAD Ship_Parameters & AutLib::CadLib::Ship_Hull::Parameters()
{
	return theParameters_;
}
