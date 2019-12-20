#pragma once
inline
Standard_Integer AutLib::Primitive_Field::NbPoints() const
{
	return theNbPoints_;
}

inline 
Standard_Integer AutLib::Primitive_Field::NbVariables() const
{
	return theNbVariables_;
}

inline 
const Standard_String & AutLib::Primitive_Field::VariablesName() const
{
	return theVariablesName_;
}

inline 
const M_AUT TColStd_Ary1dOfReal & AutLib::Primitive_Field::Variables(const Standard_Integer Point) const
{
	Debug_Bad_Index_Array1(Point, theField_);

	return theField_[Point];
}

inline 
const M_AUT TColStd_Ary1dOfAry1dOfReal & AutLib::Primitive_Field::Field() const
{
	return theField_;
}

inline 
void AutLib::Primitive_Field::SetValue
(
	const Standard_Integer Point,
	const Standard_Integer Variable,
	const Standard_Real Value
)
{
	Try_Exception_Handle_Exit(theField_[Point][Variable] = Value);
}

inline 
void AutLib::Primitive_Field::SetVariablesName(const Standard_String & Name)
{
	theVariablesName_ = Name;
}