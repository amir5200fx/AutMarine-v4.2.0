#pragma once
inline
AutLib::CadLib::Cad3d_WireOnPlaneOrientationInfo AutLib::CadLib::Cad3d_WireOnPlaneOrientationTools::ReverseOf(const Cad3d_WireOnPlaneOrientationInfo & theOrientation)
{
	if (theOrientation == Cad3d_WireOnPlaneOrientation_Unknown) return Cad3d_WireOnPlaneOrientation_Unknown;
	if (theOrientation == Cad3d_WireOnPlaneOrientation_CCW) return Cad3d_WireOnPlaneOrientation_CW;
	if (theOrientation == Cad3d_WireOnPlaneOrientation_CW) return Cad3d_WireOnPlaneOrientation_CCW;

	return Cad3d_WireOnPlaneOrientation_Unknown;  // prevent compiler warning
}