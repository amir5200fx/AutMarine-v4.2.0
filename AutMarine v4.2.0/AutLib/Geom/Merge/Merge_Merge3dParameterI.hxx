#pragma once
inline
Standard_Real AutLib::GeoLib::Merge_Merge3dParameter::Xmin() const
{
	return theXmin_;
}

inline 
Standard_Real AutLib::GeoLib::Merge_Merge3dParameter::Ymin() const
{
	return theYmin_;
}

inline 
Standard_Real AutLib::GeoLib::Merge_Merge3dParameter::Zmin() const
{
	return theZmin_;
}

inline 
Standard_Real AutLib::GeoLib::Merge_Merge3dParameter::Delta() const
{
	return theDelta_;
}

inline 
Standard_Integer AutLib::GeoLib::Merge_Merge3dParameter::MaxIndex() const
{
	return theMaxIndex_;
}

inline
void AutLib::GeoLib::Merge_Merge3dParameter::SetXmin(const Standard_Real Value)
{
	theXmin_ = Value;
}

inline
void AutLib::GeoLib::Merge_Merge3dParameter::SetYmin(const Standard_Real Value)
{
	theYmin_ = Value;
}

inline 
void AutLib::GeoLib::Merge_Merge3dParameter::SetZmin(const Standard_Real Value)
{
	theZmin_ = Value;
}

inline
void AutLib::GeoLib::Merge_Merge3dParameter::SetDelta(const Standard_Real Value)
{
	theDelta_ = Value;
}

inline
void AutLib::GeoLib::Merge_Merge3dParameter::SetMaxIndex(const Standard_Integer Value)
{
	theMaxIndex_ = Value;
}