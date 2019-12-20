#pragma once
inline
AutLib::CadLib::Duct_SectionForm & AutLib::CadLib::Duct_HullForm::InletForm()
{
	return theInletForm_;
}

inline 
AutLib::CadLib::Duct_SectionForm & AutLib::CadLib::Duct_HullForm::MidForm()
{
	return theMidForm_;
}

inline 
AutLib::CadLib::Duct_SectionForm & AutLib::CadLib::Duct_HullForm::OutletForm()
{
	return theOutletForm_;
}

inline
const AutLib::CadLib::Duct_SectionForm & AutLib::CadLib::Duct_HullForm::InletForm() const
{
	return theInletForm_;
}

inline
const AutLib::CadLib::Duct_SectionForm & AutLib::CadLib::Duct_HullForm::MidForm() const
{
	return theMidForm_;
}

inline
const AutLib::CadLib::Duct_SectionForm & AutLib::CadLib::Duct_HullForm::OutletForm() const
{
	return theOutletForm_;
}

inline 
Standard_Real AutLib::CadLib::Duct_HullForm::MidLocation() const
{
	return theMidLocation_;
}