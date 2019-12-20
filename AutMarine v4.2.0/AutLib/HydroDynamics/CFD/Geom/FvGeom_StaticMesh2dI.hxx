#pragma once
inline
Label AutLib::FvLib::FvGeom_StaticMesh2d::NbNodes() const
{
	return theNodes_.Size();
}

inline
Label AutLib::FvLib::FvGeom_StaticMesh2d::NbElements() const
{
	return theElements_.Size();
}

inline
Label AutLib::FvLib::FvGeom_StaticMesh2d::NbFaces() const
{
	return theFaces_.Size();
}

inline
const M_FV FvGeom_Node2d & AutLib::FvLib::FvGeom_StaticMesh2d::Node(const Label theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theNodes_);
	return theNodes_.Value(theIndex);
}

inline
const M_FV FvGeom_Element2d & AutLib::FvLib::FvGeom_StaticMesh2d::Element(const Label theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theElements_);
	return theElements_.Value(theIndex);
}

inline
const M_FV FvGeom_Face2d & AutLib::FvLib::FvGeom_StaticMesh2d::Face(const Label theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theFaces_);
	return theFaces_.Value(theIndex);
}