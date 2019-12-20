#pragma once
inline
Label AutLib::FvLib::FvMesh2d::NbNodes() const
{
	return theNodes_.Size();
}

inline 
Label AutLib::FvLib::FvMesh2d::NbFaces() const
{
	return theFaces_.Size();
}

inline 
Label AutLib::FvLib::FvMesh2d::NbElements() const
{
	return theFaces_.Size();
}

inline 
const Global_Handle(AutLib::FvLib::FvEntity_Node2d) AutLib::FvLib::FvMesh2d::Node(const Label theIndex) const
{
	return theNodes_.Value(theIndex);
}

inline 
const Global_Handle(AutLib::FvLib::FvEntity_Face2d) AutLib::FvLib::FvMesh2d::Face(const Label theIndex) const
{
	return theFaces_.Value(theIndex);
}

inline 
const Global_Handle(AutLib::FvLib::FvEntity_Element2d) AutLib::FvLib::FvMesh2d::Element(const Label theIndex) const
{
	return theElements_.Value(theIndex);
}