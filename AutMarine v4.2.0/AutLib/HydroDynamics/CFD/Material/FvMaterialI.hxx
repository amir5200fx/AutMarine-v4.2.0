#pragma once
inline
AutLib::FvLib::FvMaterial_Density & AutLib::FvLib::FvMaterial::Density()
{
	return theDensity_;
}

inline 
AutLib::FvLib::FvMaterial_Viscosity & AutLib::FvLib::FvMaterial::Viscosity()
{
	return theViscosity_;
}

inline
const AutLib::FvLib::FvMaterial_Density & AutLib::FvLib::FvMaterial::Density() const
{
	return theDensity_;
}

inline 
const AutLib::FvLib::FvMaterial_Viscosity & AutLib::FvLib::FvMaterial::Viscosity() const
{
	return theViscosity_;
}