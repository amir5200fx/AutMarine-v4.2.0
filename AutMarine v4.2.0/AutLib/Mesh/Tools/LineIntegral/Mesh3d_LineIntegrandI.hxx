#pragma once
inline
AutLib::MeshLib::Mesh3d_LineIntegrand::Mesh3d_LineIntegrand
(
	const Geom_Pnt3d & Start_Point, 
	const Geom_Pnt3d & End_Point, 
	const Mesh3d_SizeMap * SizeMap
)
	: theStart_(Start_Point)
	, theEnd_(End_Point)
	, theSize_(SizeMap)
{
	theVector_ = theEnd_ - theStart_;
}

inline
Standard_Real AutLib::MeshLib::Mesh3d_LineIntegrand::Integrand
(
	const Standard_Real Parameter,
	const Mesh3d_LineIntegrand & LineIntegrand
)
{
	return LineIntegrand.theSize_->MetricIntegrand(LineIntegrand.CalcPoint(Parameter), LineIntegrand.theVector_);
}

inline
Geom_Pnt3d AutLib::MeshLib::Mesh3d_LineIntegrand::CalcPoint(const Standard_Real Parameter) const
{
	return theStart_ + (theEnd_ - theStart_)*Parameter;
}