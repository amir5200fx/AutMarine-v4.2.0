#pragma once
inline
Global_Handle(AutLib::CadLib::Cad2d_Plane) AutLib::CadLib::Cad2d_PlanePlaneSubdivide::SubDivided1() const
{
	return theSubdivided1_;
}

inline 
Global_Handle(AutLib::CadLib::Cad2d_Plane) AutLib::CadLib::Cad2d_PlanePlaneSubdivide::SubDivided2() const
{
	return theSubdivided2_;
}

inline 
Standard_Boolean AutLib::CadLib::Cad2d_PlanePlaneSubdivide::IsDone() const
{
	return IsDone_;
}

inline 
Standard_Boolean AutLib::CadLib::Cad2d_PlanePlaneSubdivide::AreSubdivided() const
{
	return AreSubdivided_;
}