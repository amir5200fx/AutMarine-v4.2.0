#pragma once
inline 
Standard_Boolean AutLib::CadLib::Cad3d_PairedOnSolid::IsPaired() const
{
	return (theEdge0_ && theEdge1_);
}

inline 
const Global_Handle(AutLib::CadLib::Cad3d_EdgeOnSolid) AutLib::CadLib::Cad3d_PairedOnSolid::Edge0() const
{
	return theEdge0_;
}

inline 
const Global_Handle(AutLib::CadLib::Cad3d_EdgeOnSolid) AutLib::CadLib::Cad3d_PairedOnSolid::Edge1() const
{
	return theEdge1_;
}