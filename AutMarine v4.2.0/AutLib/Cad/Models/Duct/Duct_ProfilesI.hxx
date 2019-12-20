#pragma once
inline
const AutLib::Duct_DuctParameterProfile & AutLib::CadLib::Duct_Profiles::Section(const Standard_Integer theIndex)
{
	Debug_Bad_Index_Array1(theIndex, theSections_);
	return theSections_.Value(theIndex);
}

inline 
const AutLib::Duct_DuctParameterProfile & AutLib::CadLib::Duct_Profiles::Breadth() const
{
	return theBreadth_;
}

inline 
const AutLib::Duct_DuctParameterProfile & AutLib::CadLib::Duct_Profiles::Depth() const
{
	return theDepth_;
}