#pragma once
#include <Global_Debug.hxx>
inline
Label AutLib::FvLib::FvEntity_TriElement2d::NbNodes() const
{
	return (Label)3;
}

inline 
Label AutLib::FvLib::FvEntity_TriElement2d::NbFaces() const
{
	return (Label)3;
}

inline 
const Global_Handle(M_FV FvEntity_Node2d) AutLib::FvLib::FvEntity_TriElement2d::Node(const Label theIndex) const
{
	return (&theNode0_)[theIndex];
}

inline 
const Global_Handle(M_FV FvEntity_Face2d) AutLib::FvLib::FvEntity_TriElement2d::Face(const Label theIndex) const
{
	return (&theFace0_)[theIndex];
}

inline 
const Global_Handle(M_FV FvEntity_Element2d) AutLib::FvLib::FvEntity_TriElement2d::Neighbor(const Label theIndex) const
{
	const Global_Handle(M_FV FvEntity_Face2d) face = Face(theIndex);
	Debug_Null_Pointer(face);

	const Global_Handle(M_FV FvEntity_Face2d) Pair = face->Pair();
	if (NOT Pair) return NULL;

	return Pair->Element();
}