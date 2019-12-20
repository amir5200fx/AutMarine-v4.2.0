#pragma once
inline
const M_FV FvVariables_Primitives2d & AutLib::FvLib::FvVariables2d::CellVariables0() const
{
	return theCellVariables0_;
}

inline
const M_FV FvVariables_Primitives2d & AutLib::FvLib::FvVariables2d::CellVariables() const
{
	return theCellVariables_;
}

inline 
const M_FV FvVariables_Primitives2d & AutLib::FvLib::FvVariables2d::FaceVariables() const
{
	return theFaceVariables_;
}

inline 
const M_FV FvVariables_Sources2d & AutLib::FvLib::FvVariables2d::Sources() const
{
	return theSources_;
}

inline 
const M_FV FvVariables_FluxVelocity & AutLib::FvLib::FvVariables2d::FluxVelocity() const
{
	return theFluxVelocity_;
}

inline 
const M_FV FvVariables_Assembly & AutLib::FvLib::FvVariables2d::Assembly() const
{
	return theAssembly_;
}

inline
M_FV FvVariables_Primitives2d & AutLib::FvLib::FvVariables2d::CellVariables0()
{
	return theCellVariables0_;
}

inline
M_FV FvVariables_Primitives2d & AutLib::FvLib::FvVariables2d::CellVariables()
{
	return theCellVariables_;
}

inline
M_FV FvVariables_Primitives2d & AutLib::FvLib::FvVariables2d::FaceVariables()
{
	return theFaceVariables_;
}

inline
M_FV FvVariables_Sources2d & AutLib::FvLib::FvVariables2d::Sources()
{
	return theSources_;
}

inline
M_FV FvVariables_FluxVelocity & AutLib::FvLib::FvVariables2d::FluxVelocity()
{
	return theFluxVelocity_;
}

inline 
M_FV FvVariables_Assembly & AutLib::FvLib::FvVariables2d::Assembly()
{
	return theAssembly_;
}