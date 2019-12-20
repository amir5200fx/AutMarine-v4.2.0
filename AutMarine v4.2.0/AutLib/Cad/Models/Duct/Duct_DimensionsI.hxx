#pragma once
inline
Standard_Integer AutLib::CadLib::Duct_Dimensions::NbSections() const
{
	return theNbSections_;
}

inline 
Standard_Real AutLib::CadLib::Duct_Dimensions::OveralLength() const
{
	return theOveralLength_;
}

inline 
Standard_Real AutLib::CadLib::Duct_Dimensions::BreadthAtInlet() const
{
	return theBreadthAtInlet_;
}

inline 
Standard_Real AutLib::CadLib::Duct_Dimensions::BreadthAtOutlet() const
{
	return theBreadthAtOutlet_;
}

inline 
Standard_Real AutLib::CadLib::Duct_Dimensions::DepthAtInlet() const
{
	return theDepthAtInlet_;
}

inline 
Standard_Real AutLib::CadLib::Duct_Dimensions::DepthAtOutlet() const
{
	return theDepthAtOutlet_;
}

inline 
Standard_Real AutLib::CadLib::Duct_Dimensions::HeightAtOutlet() const
{
	return theHeightAtOutlet_;
}