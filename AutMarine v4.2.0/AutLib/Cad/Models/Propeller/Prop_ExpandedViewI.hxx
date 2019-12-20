#pragma once
inline
Standard_Real AutLib::CadLib::Prop_ExpandedView::X(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theX_);
	return theX_.Value(theIndex);
}

inline 
Standard_Real AutLib::CadLib::Prop_ExpandedView::XS(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theXS_);
	return theXS_.Value(theIndex);
}

inline 
Standard_Real AutLib::CadLib::Prop_ExpandedView::TF(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theTF_);
	return theTF_.Value(theIndex);
}

inline 
Standard_Real AutLib::CadLib::Prop_ExpandedView::TB(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theTB_);
	return theTB_.Value(theIndex);
}

inline 
Standard_Real AutLib::CadLib::Prop_ExpandedView::YF(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theYF_);
	return theYF_.Value(theIndex);
}

inline 
Standard_Real AutLib::CadLib::Prop_ExpandedView::YB(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theYB_);
	return theYB_.Value(theIndex);
}

inline
void AutLib::CadLib::Prop_ExpandedView::SetX(const Standard_Integer theIndex, const Standard_Real theValue)
{
	Debug_Bad_Index_Array1(theIndex, theX_);
	theX_.SetValue(theIndex, theValue);
}

inline 
void AutLib::CadLib::Prop_ExpandedView::SetXS(const Standard_Integer theIndex, const Standard_Real theValue)
{
	Debug_Bad_Index_Array1(theIndex, theXS_);
	theXS_.SetValue(theIndex, theValue);
}

inline 
void AutLib::CadLib::Prop_ExpandedView::SetTF(const Standard_Integer theIndex, const Standard_Real theValue)
{
	Debug_Bad_Index_Array1(theIndex, theTF_);
	theTF_.SetValue(theIndex, theValue);
}

inline 
void AutLib::CadLib::Prop_ExpandedView::SetTB(const Standard_Integer theIndex, const Standard_Real theValue)
{
	Debug_Bad_Index_Array1(theIndex, theTB_);
	theTB_.SetValue(theIndex, theValue);
}

inline
void AutLib::CadLib::Prop_ExpandedView::SetYF(const Standard_Integer theIndex, const Standard_Real theValue)
{
	Debug_Bad_Index_Array1(theIndex, theYF_);
	theYF_.SetValue(theIndex, theValue);
}

inline 
void AutLib::CadLib::Prop_ExpandedView::SetYB(const Standard_Integer theIndex, const Standard_Real theValue)
{
	Debug_Bad_Index_Array1(theIndex, theYB_);
	theYB_.SetValue(theIndex, theValue);
}