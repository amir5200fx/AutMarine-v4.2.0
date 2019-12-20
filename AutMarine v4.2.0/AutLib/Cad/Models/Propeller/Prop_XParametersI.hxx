#pragma once
inline
const M_AUT TColStd_Ary1dOfReal & AutLib::CadLib::Prop_XParameters::X() const
{
	return theX_;
}

inline 
const M_AUT TColStd_Ary1dOfReal & AutLib::CadLib::Prop_XParameters::xPitchAngle() const
{
	return thePitchAngle_;
}

inline 
const M_AUT TColStd_Ary1dOfReal & AutLib::CadLib::Prop_XParameters::xChord() const
{
	return theChord_;
}

inline 
const M_AUT TColStd_Ary1dOfReal & AutLib::CadLib::Prop_XParameters::xMaxCamber() const
{
	return theMaxCamber_;
}

inline 
const M_AUT TColStd_Ary1dOfReal & AutLib::CadLib::Prop_XParameters::xMaxCamberPosition() const
{
	return theMaxCamberPosition_;
}

inline 
const M_AUT TColStd_Ary1dOfReal & AutLib::CadLib::Prop_XParameters::xSkew() const
{
	return theSkew_;
}

inline 
const M_AUT TColStd_Ary1dOfReal & AutLib::CadLib::Prop_XParameters::xRake() const
{
	return theRake_;
}

inline 
const M_AUT TColStd_Ary1dOfReal & AutLib::CadLib::Prop_XParameters::xThickness() const
{
	return theThickness_;
}

inline
Standard_Real AutLib::CadLib::Prop_XParameters::X(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theX_);
	return theX_.Value(theIndex);
}

inline 
Standard_Real AutLib::CadLib::Prop_XParameters::xPitchAngle(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, thePitchAngle_);
	return thePitchAngle_.Value(theIndex);
}

inline
Standard_Real AutLib::CadLib::Prop_XParameters::xChord(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theChord_);
	return theChord_.Value(theIndex);
}

inline 
Standard_Real AutLib::CadLib::Prop_XParameters::xMaxCamber(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theMaxCamber_);
	return theMaxCamber_.Value(theIndex);
}

inline 
Standard_Real AutLib::CadLib::Prop_XParameters::xMaxCamberPosition(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theMaxCamberPosition_);
	return theMaxCamberPosition_.Value(theIndex);
}

inline 
Standard_Real AutLib::CadLib::Prop_XParameters::xSkew(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theSkew_);
	return theSkew_.Value(theIndex);
}

inline 
Standard_Real AutLib::CadLib::Prop_XParameters::xRake(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theRake_);
	return theRake_.Value(theIndex);
}

inline 
Standard_Real AutLib::CadLib::Prop_XParameters::xThickness(const Standard_Integer theIndex) const
{
	Debug_Bad_Index_Array1(theIndex, theThickness_);
	return theThickness_.Value(theIndex);
}

inline 
void AutLib::CadLib::Prop_XParameters::SetX(const Standard_Integer theIndex, const Standard_Real theValue)
{
	Debug_Bad_Index_Array1(theIndex, theX_);
	theX_.SetValue(theIndex, theValue);
}

inline 
void AutLib::CadLib::Prop_XParameters::SetPitchAngle(const Standard_Integer theIndex, const Standard_Real theValue)
{
	Debug_Bad_Index_Array1(theIndex, thePitchAngle_);
	thePitchAngle_.SetValue(theIndex, theValue);
}

inline 
void AutLib::CadLib::Prop_XParameters::SetChord(const Standard_Integer theIndex, const Standard_Real theValue)
{
	Debug_Bad_Index_Array1(theIndex, theChord_);
	theChord_.SetValue(theIndex, theValue);
}

inline
void AutLib::CadLib::Prop_XParameters::SetMaxCamber(const Standard_Integer theIndex, const Standard_Real theValue)
{
	Debug_Bad_Index_Array1(theIndex, theMaxCamber_);
	theMaxCamber_.SetValue(theIndex, theValue);
}

inline 
void AutLib::CadLib::Prop_XParameters::SetMaxCamberPosition(const Standard_Integer theIndex, const Standard_Real theValue)
{
	Debug_Bad_Index_Array1(theIndex, theMaxCamberPosition_);
	theMaxCamberPosition_.SetValue(theIndex, theValue);
}

inline 
void AutLib::CadLib::Prop_XParameters::SetSkew(const Standard_Integer theIndex, const Standard_Real theValue)
{
	Debug_Bad_Index_Array1(theIndex, theSkew_);
	theSkew_.SetValue(theIndex, theValue);
}

inline 
void AutLib::CadLib::Prop_XParameters::SetRake(const Standard_Integer theIndex, const Standard_Real theValue)
{
	Debug_Bad_Index_Array1(theIndex, theRake_);
	theRake_.SetValue(theIndex, theValue);
}

inline 
void AutLib::CadLib::Prop_XParameters::SetThickness(const Standard_Integer theIndex, const Standard_Real theValue)
{
	Debug_Bad_Index_Array1(theIndex, theThickness_);
	theThickness_.SetValue(theIndex, theValue);
}