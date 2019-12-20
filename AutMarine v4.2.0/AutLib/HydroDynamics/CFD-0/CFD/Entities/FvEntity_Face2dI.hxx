#pragma once
inline
Standard_Integer AutLib::FvLib::FvEntity_Face2d::Index() const
{
	return theIndex_;
}

inline 
const Global_Handle(M_FV FvEntity_Node2d) AutLib::FvLib::FvEntity_Face2d::Node(const Standard_Integer theIndex) const
{
	return (&theNode0_)[theIndex];
}

inline 
const Global_Handle(M_FV FvEntity_Element2d) AutLib::FvLib::FvEntity_Face2d::Element() const
{
	return theElement_;
}

inline 
const Global_Handle(M_FV FvEntity_Face2d) AutLib::FvLib::FvEntity_Face2d::Pair() const
{
	return thePair_;
}

inline
const Geom_Pnt2d & AutLib::FvLib::FvEntity_Face2d::Centre() const
{
	return theCentre_;
}

inline 
const Geom_Pnt2d & AutLib::FvLib::FvEntity_Face2d::N() const
{
	return theN_;
}

inline
const Geom_Pnt2d & AutLib::FvLib::FvEntity_Face2d::A() const
{
	return theA_;
}

inline 
const Geom_Pnt2d & AutLib::FvLib::FvEntity_Face2d::D() const
{
	return theD_;
}

inline 
const Geom_Pnt2d & AutLib::FvLib::FvEntity_Face2d::Rpl() const
{
	return theRpl_;
}

inline 
const Geom_Pnt2d & AutLib::FvLib::FvEntity_Face2d::Rnl() const
{
	return theRnl_;
}

inline 
Standard_Real AutLib::FvLib::FvEntity_Face2d::Volume() const
{
	return theVolume_;
}

inline 
Standard_Real AutLib::FvLib::FvEntity_Face2d::d() const
{
	return thed_;
}

inline 
M_FV FvBC_Physics AutLib::FvLib::FvEntity_Face2d::Physics() const
{
	return thePhysics_;
}