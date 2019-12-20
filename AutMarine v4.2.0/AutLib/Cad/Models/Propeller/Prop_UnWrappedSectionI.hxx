#pragma once
inline
const M_AUT Prop_ListOfOffsetPnt3d & AutLib::CadLib::Prop_UnWrappedSection::FaceOffsets() const
{
	return theFace_;
}

inline 
const M_AUT Prop_ListOfOffsetPnt3d & AutLib::CadLib::Prop_UnWrappedSection::BackOffsets() const
{
	return theBack_;
}

inline 
const Geom_Pnt3d & AutLib::CadLib::Prop_UnWrappedSection::FaceOffset(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theFace_);
	return theFace_.Value(theIndex);
}

inline 
const Geom_Pnt3d & AutLib::CadLib::Prop_UnWrappedSection::BackOffset(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theBack_);
	return theBack_.Value(theIndex);
}

inline 
void AutLib::CadLib::Prop_UnWrappedSection::SetFaceOffset(const Standard_Integer theIndex, const Geom_Pnt3d & theCoord)
{
	Debug_Bad_Index_Array1(theIndex, theFace_);
	theFace_.SetValue(theIndex, theCoord);
}

inline 
void AutLib::CadLib::Prop_UnWrappedSection::SetBackOffset(const Standard_Integer theIndex, const Geom_Pnt3d & theCoord)
{
	Debug_Bad_Index_Array1(theIndex, theBack_);
	theBack_.SetValue(theIndex, theCoord);
}