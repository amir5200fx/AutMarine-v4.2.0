#pragma once
inline
AutLib::CadLib::Cad2d_WireOnPlaneOrientationInfo AutLib::CadLib::Cad2d_WireOnPlaneOrientationTools::ReverseOf(const Cad2d_WireOnPlaneOrientationInfo & theOrientation)
{
	if (theOrientation == Cad2d_WireOnPlaneOrientation_Unknown) return Cad2d_WireOnPlaneOrientation_Unknown;
	if (theOrientation == Cad2d_WireOnPlaneOrientation_CCW) return Cad2d_WireOnPlaneOrientation_CW;
	if (theOrientation == Cad2d_WireOnPlaneOrientation_CW) return Cad2d_WireOnPlaneOrientation_CCW;

	return Cad2d_WireOnPlaneOrientation_Unknown;  // prevent compiler warning
}