#pragma once
#include <Global_Debug.hxx>
inline
Standard_Boolean AutLib::CadLib::Cad3d_EdgeOnSolid::IsDegenerate() const
{
	return IsNULL(theCurveOnSurface_);
}

inline 
Standard_Integer AutLib::CadLib::Cad3d_EdgeOnSolid::Index() const
{
	return theIndex_;
}

inline 
const Global_Handle(AutLib::CadLib::Cad3d_CurveOnPlane) AutLib::CadLib::Cad3d_EdgeOnSolid::CurveOnPlane() const
{
	return theCurveOnPlane_;
}

inline 
const Global_Handle(AutLib::CadLib::Cad3d_CurveOnSurface) AutLib::CadLib::Cad3d_EdgeOnSolid::CurveOnSurface() const
{
	return theCurveOnSurface_;
}

inline 
const Global_Handle(AutLib::CadLib::Cad3d_SurfaceOnSolid) AutLib::CadLib::Cad3d_EdgeOnSolid::Surface() const
{
	return theSurface_;
}

inline 
const Global_Handle(AutLib::CadLib::Cad3d_EdgeOnSolid) AutLib::CadLib::Cad3d_EdgeOnSolid::Paired() const
{
	return thePaired_;
}

inline 
const Global_Handle(AutLib::CadLib::Cad3d_PairedOnSolid) AutLib::CadLib::Cad3d_EdgeOnSolid::PairedOnSolid() const
{
	return thePairedOnSolid_;
}

inline 
const Global_Handle(AutLib::CadLib::Cad3d_PointOnSolid) AutLib::CadLib::Cad3d_EdgeOnSolid::StartPoint() const
{
	Debug_Null_Pointer(theP0_);

	return theP0_;
}

inline 
const Global_Handle(AutLib::CadLib::Cad3d_PointOnSolid) AutLib::CadLib::Cad3d_EdgeOnSolid::LastPoint() const
{
	Debug_Null_Pointer(theP1_);

	return theP1_;
}