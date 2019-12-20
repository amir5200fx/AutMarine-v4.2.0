#pragma once
inline
AutLib::MeshLib::Mesh3d_CurveIntegrand::Mesh3d_CurveIntegrand
(
	const Global_Handle(Mesh3d_SizeMap) Map,
	const Global_Handle(Geom_Curve) Curve,
	const Standard_Real First,
	const Standard_Real Last
)
	: theMap_(Map)
	, theCurve_(Curve)
	, theFirst_(First)
	, theLast_(Last)
{
}

inline 
const Global_Handle(M_MESH Mesh3d_SizeMap) AutLib::MeshLib::Mesh3d_CurveIntegrand::Map() const
{
	return theMap_;
}

inline 
const Global_Handle(Geom_Curve) AutLib::MeshLib::Mesh3d_CurveIntegrand::Curve() const
{
	return theCurve_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_CurveIntegrand::FirstParameter() const
{
	return theFirst_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_CurveIntegrand::LastParameter() const
{
	return theLast_;
}