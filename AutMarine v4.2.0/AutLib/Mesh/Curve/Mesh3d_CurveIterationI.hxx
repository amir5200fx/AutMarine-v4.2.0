#pragma once
inline
AutLib::MeshLib::Mesh3d_CurveIteration::Mesh3d_CurveIteration()
{
}

inline 
AutLib::MeshLib::Mesh3d_CurveIteration::Mesh3d_CurveIteration
(
	const Global_Handle(Mesh3d_CurveIntegrand) CurveIntegrand,
	const Standard_Real Start,
	const Standard_Real Step, 
	const Standard_Real Tolerance
)
	: theIntegrand_(CurveIntegrand)
	, theStart_(Start)
	, theStep_(Step)
	, theTolerance_(Tolerance)
{
}

inline 
void AutLib::MeshLib::Mesh3d_CurveIteration::SetIntegrand(const Global_Handle(Mesh3d_CurveIntegrand) CurveIntegrand)
{
	theIntegrand_ = CurveIntegrand;
}

inline 
void AutLib::MeshLib::Mesh3d_CurveIteration::SetStart(const Standard_Real Value)
{
	theStart_ = Value;
}

inline 
void AutLib::MeshLib::Mesh3d_CurveIteration::SetStep(const Standard_Real Value)
{
	theStep_ = Value;
}

inline 
void AutLib::MeshLib::Mesh3d_CurveIteration::SetTolerance(const Standard_Real Value)
{
	theTolerance_ = Value;
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_CurveIteration::Start() const
{
	return theStart_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_CurveIteration::Step() const
{
	return theStep_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_CurveIteration::Tolerance() const
{
	return theTolerance_;
}

inline 
const Global_Handle(M_MESH Mesh3d_CurveIntegrand) AutLib::MeshLib::Mesh3d_CurveIteration::Integrand() const
{
	return theIntegrand_;
}