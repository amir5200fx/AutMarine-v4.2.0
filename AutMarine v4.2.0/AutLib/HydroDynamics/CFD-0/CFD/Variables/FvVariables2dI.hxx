#pragma once
inline
const M_FV FvVariables_Faces2d & AutLib::FvLib::FvVariables2d::Uf() const
{
	return theUf_;
}

inline 
const M_FV FvVariables_Faces2d & AutLib::FvLib::FvVariables2d::Xuf() const
{
	return theXuf_;
}

inline 
const M_FV FvVariables_Faces2d & AutLib::FvLib::FvVariables2d::Xvf() const
{
	return theXvf_;
}

inline 
const M_FV FvVariables_Faces2d & AutLib::FvLib::FvVariables2d::Xpf() const
{
	return theXpf_;
}

inline 
const M_FV FvVariables_Elements2d & AutLib::FvLib::FvVariables2d::Xu0() const
{
	return theXu0_;
}

inline 
const M_FV FvVariables_Elements2d & AutLib::FvLib::FvVariables2d::Xv0() const
{
	return theXv0_;
}

inline
const M_FV FvVariables_Elements2d & AutLib::FvLib::FvVariables2d::Xp0() const
{
	return theXp0_;
}

inline 
const M_FV FvVariables_Elements2d & AutLib::FvLib::FvVariables2d::Xu() const
{
	return theXu_;
}

inline 
const M_FV FvVariables_Elements2d & AutLib::FvLib::FvVariables2d::Xv() const
{
	return theXv_;
}

inline 
const M_FV FvVariables_Elements2d & AutLib::FvLib::FvVariables2d::Xp() const
{
	return theXp_;
}

inline 
const M_FV FvVariables_Elements2d & AutLib::FvLib::FvVariables2d::Xpp() const
{
	return theXpp_;
}

inline 
const M_FV FvVariables_Elements2d & AutLib::FvLib::FvVariables2d::Bu() const
{
	return theBu_;
}

inline 
const M_FV FvVariables_Elements2d & AutLib::FvLib::FvVariables2d::Bv() const
{
	return theBv_;
}

inline 
const M_FV FvVariables_Elements2d & AutLib::FvLib::FvVariables2d::Bp() const
{
	return theBp_;
}

inline 
const M_AUT TColGeom_Ary1dOfPnt2d & AutLib::FvLib::FvVariables2d::GradXu() const
{
	return theGradXu_;
}

inline
const M_AUT TColGeom_Ary1dOfPnt2d & AutLib::FvLib::FvVariables2d::GradXv() const
{
	return theGradXv_;
}

inline
Standard_Real AutLib::FvLib::FvVariables2d::Uf(const Standard_Integer theIndex) const
{
	return (Standard_Real)V_GetCmp((Vector*)&theUf_, theIndex);
}

inline 
Standard_Real AutLib::FvLib::FvVariables2d::Xuf(const Standard_Integer theIndex) const
{
	return (Standard_Real)V_GetCmp((Vector*)&theXuf_, theIndex);
}

inline 
Standard_Real AutLib::FvLib::FvVariables2d::Xvf(const Standard_Integer theIndex) const
{
	return (Standard_Real)V_GetCmp((Vector*)&theXvf_, theIndex);
}

inline 
Standard_Real AutLib::FvLib::FvVariables2d::Xpf(const Standard_Integer theIndex) const
{
	return (Standard_Real)V_GetCmp((Vector*)&theXpf_, theIndex);
}

inline 
Standard_Real AutLib::FvLib::FvVariables2d::Xu0(const Standard_Integer theIndex) const
{
	return (Standard_Real)V_GetCmp((Vector*)&theXu0_, theIndex);
}

inline 
Standard_Real AutLib::FvLib::FvVariables2d::Xv0(const Standard_Integer theIndex) const
{
	return (Standard_Real)V_GetCmp((Vector*)&theXv0_, theIndex);
}

inline 
Standard_Real AutLib::FvLib::FvVariables2d::Xp0(const Standard_Integer theIndex) const
{
	return (Standard_Real)V_GetCmp((Vector*)&theXp0_, theIndex);
}

inline 
Standard_Real AutLib::FvLib::FvVariables2d::Xu(const Standard_Integer theIndex) const
{
	return (Standard_Real)V_GetCmp((Vector*)&theXu_, theIndex);
}

inline
Standard_Real AutLib::FvLib::FvVariables2d::Xv(const Standard_Integer theIndex) const
{
	return (Standard_Real)V_GetCmp((Vector*)&theXv_, theIndex);
}

inline
Standard_Real AutLib::FvLib::FvVariables2d::Xp(const Standard_Integer theIndex) const
{
	return (Standard_Real)V_GetCmp((Vector*)&theXp_, theIndex);
}

inline 
Standard_Real AutLib::FvLib::FvVariables2d::Xpp(const Standard_Integer theIndex) const
{
	return (Standard_Real)V_GetCmp((Vector*)&theXpp_, theIndex);
}

inline 
Standard_Real AutLib::FvLib::FvVariables2d::Bu(const Standard_Integer theIndex) const
{
	return (Standard_Real)V_GetCmp((Vector*)&theBu_, theIndex);
}

inline
Standard_Real AutLib::FvLib::FvVariables2d::Bv(const Standard_Integer theIndex) const
{
	return (Standard_Real)V_GetCmp((Vector*)&theBv_, theIndex);
}

inline
Standard_Real AutLib::FvLib::FvVariables2d::Bp(const Standard_Integer theIndex) const
{
	return (Standard_Real)V_GetCmp((Vector*)&theBp_, theIndex);
}

inline 
const Geom_Pnt2d& AutLib::FvLib::FvVariables2d::GradXu(const Standard_Integer theIndex) const
{
	return theGradXu_.Value(theIndex);
}

inline
const Geom_Pnt2d& AutLib::FvLib::FvVariables2d::GradXv(const Standard_Integer theIndex) const
{
	return theGradXv_(theIndex);
}

inline 
void AutLib::FvLib::FvVariables2d::SetUf(const Standard_Integer theIndex, const Standard_Real theValue) const
{
	V_SetCmp((Vector*)&theUf_, theIndex, (Real)theValue);
}

inline 
void AutLib::FvLib::FvVariables2d::SetXuf(const Standard_Integer theIndex, const Standard_Real theValue) const
{
	V_SetCmp((Vector*)&theXuf_, theIndex, (Real)theValue);
}

inline
void AutLib::FvLib::FvVariables2d::SetXvf(const Standard_Integer theIndex, const Standard_Real theValue) const
{
	V_SetCmp((Vector*)&theXvf_, theIndex, (Real)theValue);
}

inline
void AutLib::FvLib::FvVariables2d::SetXpf(const Standard_Integer theIndex, const Standard_Real theValue) const
{
	V_SetCmp((Vector*)&theXpf_, theIndex, (Real)theValue);
}

inline 
void AutLib::FvLib::FvVariables2d::SetXu0(const Standard_Integer theIndex, const Standard_Real theValue) const
{
	V_SetCmp((Vector*)&theXu0_, theIndex, (Real)theValue);
}

inline
void AutLib::FvLib::FvVariables2d::SetXv0(const Standard_Integer theIndex, const Standard_Real theValue) const
{
	V_SetCmp((Vector*)&theXv0_, theIndex, (Real)theValue);
}

inline
void AutLib::FvLib::FvVariables2d::SetXp0(const Standard_Integer theIndex, const Standard_Real theValue) const
{
	V_SetCmp((Vector*)&theXp0_, theIndex, (Real)theValue);
}

inline 
void AutLib::FvLib::FvVariables2d::SetXu(const Standard_Integer theIndex, const Standard_Real theValue) const
{
	V_SetCmp((Vector*)&theXu_, theIndex, (Real)theValue);
}

inline
void AutLib::FvLib::FvVariables2d::SetXv(const Standard_Integer theIndex, const Standard_Real theValue) const
{
	V_SetCmp((Vector*)&theXv_, theIndex, (Real)theValue);
}

inline
void AutLib::FvLib::FvVariables2d::SetXp(const Standard_Integer theIndex, const Standard_Real theValue) const
{
	V_SetCmp((Vector*)&theXp_, theIndex, (Real)theValue);
}

inline 
void AutLib::FvLib::FvVariables2d::SetXpp(const Standard_Integer theIndex, const Standard_Real theValue) const
{
	V_SetCmp((Vector*)&theXpp_, theIndex, (Real)theValue);
}

inline 
void AutLib::FvLib::FvVariables2d::SetBu(const Standard_Integer theIndex, const Standard_Real theValue) const
{
	V_SetCmp((Vector*)&theBu_, theIndex, (Real)theValue);
}

inline
void AutLib::FvLib::FvVariables2d::SetBv(const Standard_Integer theIndex, const Standard_Real theValue) const
{
	V_SetCmp((Vector*)&theBv_, theIndex, (Real)theValue);
}

inline
void AutLib::FvLib::FvVariables2d::SetBp(const Standard_Integer theIndex, const Standard_Real theValue) const
{
	V_SetCmp((Vector*)&theBp_, theIndex, (Real)theValue);
}

inline 
void AutLib::FvLib::FvVariables2d::SetGradXu(const Standard_Integer theIndex, const Geom_Pnt2d& theValue) const
{
	theGradXu_.SetValue(theIndex, theValue);
}

inline
void AutLib::FvLib::FvVariables2d::SetGradXv(const Standard_Integer theIndex, const Geom_Pnt2d& theValue) const
{
	theGradXv_.SetValue(theIndex, theValue);
}