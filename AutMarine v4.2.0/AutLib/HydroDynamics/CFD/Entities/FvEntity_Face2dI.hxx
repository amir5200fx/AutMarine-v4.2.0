#pragma once
inline
Label AutLib::FvLib::FvEntity_Face2d::Index() const
{
	return theIndex_;
}

inline 
const Global_Handle(AutLib::FvLib::FvEntity_Node2d) AutLib::FvLib::FvEntity_Face2d::Node(const Label theIndex) const
{
	return (&theNode0_)[theIndex];
}

inline 
const Global_Handle(AutLib::FvLib::FvEntity_Element2d) AutLib::FvLib::FvEntity_Face2d::Element() const
{
	return theElement_;
}

inline 
const Global_Handle(AutLib::FvLib::FvEntity_Face2d) AutLib::FvLib::FvEntity_Face2d::Pair() const
{
	return thePair_;
}

inline 
const Geom_Pnt2d & AutLib::FvLib::FvEntity_Face2d::Centre() const
{
	return theCentre_;
}

inline 
const Vec2 & AutLib::FvLib::FvEntity_Face2d::Normal() const
{
	return theNormal_;
}

inline 
const Vec2 & AutLib::FvLib::FvEntity_Face2d::Sf() const
{
	return theSf_;
}

inline 
Scalar AutLib::FvLib::FvEntity_Face2d::Area() const
{
	return theArea_;
}

inline 
Scalar AutLib::FvLib::FvEntity_Face2d::gcCoeff() const
{
	return thegc_;
}

inline 
AutLib::FvLib::FvBC_Physics AutLib::FvLib::FvEntity_Face2d::Physics() const
{
	return thePhysics_;
}

inline 
Standard_Boolean AutLib::FvLib::FvEntity_Face2d::IsOnBoundary() const
{
	return NOT thePair_;
}