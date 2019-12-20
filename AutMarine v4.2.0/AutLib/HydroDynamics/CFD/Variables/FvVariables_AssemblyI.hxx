#pragma once
inline
const M_FV FvMatrix & AutLib::FvLib::FvVariables_Assembly::Continuity() const
{
	return theAc_;
}

inline 
const M_FV FvMatrix & AutLib::FvLib::FvVariables_Assembly::Momentum() const
{
	return theAm_;
}

inline
M_FV FvMatrix & AutLib::FvLib::FvVariables_Assembly::Continuity()
{
	return theAc_;
}

inline
M_FV FvMatrix & AutLib::FvLib::FvVariables_Assembly::Momentum()
{
	return theAm_;
}