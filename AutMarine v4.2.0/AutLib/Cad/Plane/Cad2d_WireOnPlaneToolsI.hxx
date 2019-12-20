#pragma once
inline
Standard_Boolean AutLib::CadLib::Cad2d_WireOnPlaneTools::IsLess
(
	Global_Handle(Cad2d_WireOnPlane) const & theWire1,
	Global_Handle(Cad2d_WireOnPlane) const & theWire2
)
{
	Debug_Null_Pointer(theWire1);
	Debug_Null_Pointer(theWire2);

	return theWire1->Index() < theWire2->Index();
}