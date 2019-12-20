#pragma once
inline
AutLib::MeshLib::Mesh2d_CurveIntegrand::Mesh2d_CurveIntegrand()
{
}

inline AutLib::MeshLib::Mesh2d_CurveIntegrand::Mesh2d_CurveIntegrand
(
	const Global_Handle(Mesh2d_SizeMap) Map,
	const Global_Handle(Geom2d_Curve)Curve,
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
const Global_Handle(M_MESH Mesh2d_SizeMap) AutLib::MeshLib::Mesh2d_CurveIntegrand::Map() const
{
	return theMap_;
}

inline 
const Global_Handle(Geom2d_Curve) AutLib::MeshLib::Mesh2d_CurveIntegrand::Curve() const
{
	return theCurve_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh2d_CurveIntegrand::FirstParameter() const
{
	return theFirst_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh2d_CurveIntegrand::LastParameter() const
{
	return theLast_;
}

inline 
void AutLib::MeshLib::Mesh2d_CurveIntegrand::SetFirstParameter(const Standard_Real Value)
{
	theFirst_ = Value;
}

inline 
void AutLib::MeshLib::Mesh2d_CurveIntegrand::SetLastParameter(const Standard_Real Value)
{
	theLast_ = Value;
}

inline 
void AutLib::MeshLib::Mesh2d_CurveIntegrand::SetMap(const Global_Handle(Mesh2d_SizeMap) Map)
{
	theMap_ = Map;
}

inline 
void AutLib::MeshLib::Mesh2d_CurveIntegrand::SetCurve(const Global_Handle(Geom2d_Curve)Curve)
{
	theCurve_ = Curve;
}