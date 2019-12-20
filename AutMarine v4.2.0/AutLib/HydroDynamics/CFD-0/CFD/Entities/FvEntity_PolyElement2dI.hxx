#pragma once
#include <FvEntity_Face2d.hxx>
inline
Standard_Integer AutLib::FvLib::FvEntity_PolyElement2d::NbNodes() const
{
	return theNodes_.Size();
}

inline 
Standard_Integer AutLib::FvLib::FvEntity_PolyElement2d::NbFaces() const
{
	return theFaces_.Size();
}

inline 
const Global_Handle(M_FV FvEntity_Node2d) AutLib::FvLib::FvEntity_PolyElement2d::Node(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theNodes_);
	return theNodes_.Value(theIndex);
}

inline 
const Global_Handle(M_FV FvEntity_Face2d) AutLib::FvLib::FvEntity_PolyElement2d::Face(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theFaces_);
	return theFaces_.Value(theIndex);
}

inline 
const Global_Handle(M_FV FvEntity_Element2d) AutLib::FvLib::FvEntity_PolyElement2d::Neighbor(const Standard_Integer theIndex) const
{
	const Global_Handle(M_FV FvEntity_Face2d) face = Face(theIndex);
	Debug_Null_Pointer(face);

	const Global_Handle(M_FV FvEntity_Face2d) Pair = face->Pair();
	if (NOT Pair) return NULL;

	return Pair->Element();
}