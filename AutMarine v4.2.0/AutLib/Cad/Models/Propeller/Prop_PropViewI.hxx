#pragma once
inline
const M_AUT TColProp_HAry1dOfExpandedView & AutLib::CadLib::Prop_PropView::ExpandedView() const
{
	return theExpanded_;
}

inline 
const M_AUT TColProp_HAry1dOfWrappedSection & AutLib::CadLib::Prop_PropView::WrappedView() const
{
	return theWrapped_;
}

inline 
const M_AUT TColProp_HAry1dOfUnWrappedSection & AutLib::CadLib::Prop_PropView::UnWrappedView() const
{
	return theUnWrapped_;
}

inline 
const M_CAD Prop_BladeFaces & AutLib::CadLib::Prop_PropView::Surfaces() const
{
	return theSurfaces_;
}

inline 
const Global_Handle(M_CAD Prop_ExpandedView) AutLib::CadLib::Prop_PropView::ExpandedView(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theExpanded_);
	return theExpanded_.Value(theIndex);
}

inline 
const Global_Handle(M_CAD Prop_WrappedSection) AutLib::CadLib::Prop_PropView::WrappedSection(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theWrapped_);
	return theWrapped_.Value(theIndex);
}

inline 
const Global_Handle(M_CAD Prop_UnWrappedSection) AutLib::CadLib::Prop_PropView::UnWrappedSection(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theUnWrapped_);
	return theUnWrapped_.Value(theIndex);
}

inline 
M_CAD Prop_BladeFaces & AutLib::CadLib::Prop_PropView::Surfaces()
{
	return theSurfaces_;
}

inline 
void AutLib::CadLib::Prop_PropView::SetExpandedView(const Standard_Integer theIndex, const Global_Handle(Prop_ExpandedView) theExpandedView)
{
	Debug_Bad_Index_Array1(theIndex, theExpanded_);
	theExpanded_.SetValue(theIndex, (Global_Handle(Prop_ExpandedView))theExpandedView);
}

inline 
void AutLib::CadLib::Prop_PropView::SetWrappedSection(const Standard_Integer theIndex, const Global_Handle(Prop_WrappedSection) theWrappedSection)
{
	Debug_Bad_Index_Array1(theIndex, theWrapped_);
	theWrapped_.SetValue(theIndex, (Global_Handle(Prop_WrappedSection))theWrappedSection);
}

inline 
void AutLib::CadLib::Prop_PropView::SetUnWrappedSection(const Standard_Integer theIndex, const Global_Handle(Prop_UnWrappedSection) theUnWrappedSection)
{
	Debug_Bad_Index_Array1(theIndex, theUnWrapped_);
	theUnWrapped_.SetValue(theIndex, (Global_Handle(Prop_UnWrappedSection))theUnWrappedSection);
}