#pragma once
#include <Global_Debug.hxx>
inline
Standard_Integer AutLib::FvLib::FvEntity_TriElement2d::NbNodes() const
{
	return (Standard_Integer)3;
}

inline 
Standard_Integer AutLib::FvLib::FvEntity_TriElement2d::NbFaces() const
{
	return (Standard_Integer)3;
}

inline 
const Global_Handle(M_FV FvEntity_Node2d) AutLib::FvLib::FvEntity_TriElement2d::Node(const Standard_Integer theIndex) const
{
	return (&theNode0_)[theIndex];
}

inline 
const Global_Handle(M_FV FvEntity_Face2d) AutLib::FvLib::FvEntity_TriElement2d::Face(const Standard_Integer theIndex) const
{
	return (&theFace0_)[theIndex];
}

inline 
const Global_Handle(M_FV FvEntity_Element2d) AutLib::FvLib::FvEntity_TriElement2d::Neighbor(const Standard_Integer theIndex) const
{
	const Global_Handle(M_FV FvEntity_Face2d) face = Face(theIndex);
	Debug_Null_Pointer(face);

	const Global_Handle(M_FV FvEntity_Face2d) Pair = face->Pair();
	if (NOT Pair) return NULL;

	return Pair->Element();
}