#pragma once
inline
Standard_Real AutLib::CadLib::Prop_CamberForm::RootCamber() const
{
	return theRootCamber_;
}

inline
Standard_Real AutLib::CadLib::Prop_CamberForm::TipCamber() const
{
	return theTipCamber_;
}

inline
Standard_Real AutLib::CadLib::Prop_CamberForm::MaxCamber() const
{
	return theMaxCamber_;
}

inline
Standard_Real AutLib::CadLib::Prop_CamberForm::MaxCamberLocation() const
{
	return theMaxCamberLocation_;
}

inline
Standard_Real AutLib::CadLib::Prop_CamberForm::RootWeight() const
{
	return theRootWeight_;
}

inline
Standard_Real AutLib::CadLib::Prop_CamberForm::TipWeight() const
{
	return theTipWeight_;
}