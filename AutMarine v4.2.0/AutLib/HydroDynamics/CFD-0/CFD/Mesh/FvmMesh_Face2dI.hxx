#pragma once
inline
const Global_Handle(M_FVM FvmMesh_Node2d) AutLib::FvmLib::FvmMesh_Face2d::Node0() const
{
	return theNode0_;
}

inline 
const Global_Handle(M_FVM FvmMesh_Node2d) AutLib::FvmLib::FvmMesh_Face2d::Node1() const
{
	return theNode1_;
}

inline 
const Global_Handle(M_FVM FvmMesh_Element2d) AutLib::FvmLib::FvmMesh_Face2d::Element() const
{
	return theElement_;
}

inline 
const Global_Handle(M_FVM FvmMesh_Face2d) AutLib::FvmLib::FvmMesh_Face2d::Pair() const
{
	return thePair_;
}

inline 
const Geom_Pnt2d & AutLib::FvmLib::FvmMesh_Face2d::Centre() const
{
	return theCentre_;
}

inline 
const gp_Dir2d & AutLib::FvmLib::FvmMesh_Face2d::Vector() const
{
	return theVector_;
}

inline 
const gp_Dir2d & AutLib::FvmLib::FvmMesh_Face2d::Normal() const
{
	return theNormal_;
}

inline 
Standard_Real AutLib::FvmLib::FvmMesh_Face2d::Length() const
{
	return theLength_;
}

inline 
Standard_Integer AutLib::FvmLib::FvmMesh_Face2d::Index() const
{
	return theIndex_;
}