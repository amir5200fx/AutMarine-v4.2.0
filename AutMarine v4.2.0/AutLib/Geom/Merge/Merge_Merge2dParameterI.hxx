#pragma once
inline
AutLib::GeoLib::Merge_Merge2dParameter::Merge_Merge2dParameter()
{
}

inline
Standard_Real AutLib::GeoLib::Merge_Merge2dParameter::Xmin() const
{
	return theXmin_;
}

inline
Standard_Real AutLib::GeoLib::Merge_Merge2dParameter::Ymin() const
{
	return theYmin_;
}

inline
Standard_Real AutLib::GeoLib::Merge_Merge2dParameter::Delta() const
{
	return theDelta_;
}

inline
Standard_Integer AutLib::GeoLib::Merge_Merge2dParameter::MaxIndex() const
{
	return theMaxIndex_;
}

inline
void AutLib::GeoLib::Merge_Merge2dParameter::SetXmin(const Standard_Real Value)
{
	theXmin_ = Value;
}

inline
void AutLib::GeoLib::Merge_Merge2dParameter::SetYmin(const Standard_Real Value)
{
	theYmin_ = Value;
}

inline
void AutLib::GeoLib::Merge_Merge2dParameter::SetDelta(const Standard_Real Value)
{
	theDelta_ = Value;
}

inline
void AutLib::GeoLib::Merge_Merge2dParameter::SetMaxIndex(const Standard_Integer Value)
{
	theMaxIndex_ = Value;
}