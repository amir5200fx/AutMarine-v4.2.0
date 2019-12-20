#pragma once
inline
Standard_Integer AutLib::MeshLib::Mesh2d_Domain::NbCurves() const
{
	return theMeshCurves_.Size();
}

inline
const M_MESH Mesh2d_Curve & AutLib::MeshLib::Mesh2d_Domain::CurveMesh(const Standard_Integer Index) const
{
	Debug_Bad_Index_Array1(Index, theMeshCurves_);

	return *theMeshCurves_[Index];
}

inline
const M_GEO Entity_StaticChain2d & AutLib::MeshLib::Mesh2d_Domain::Merged() const
{
	return theChain_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh2d_Domain::IsDone() const
{
	return IsDone_;
}