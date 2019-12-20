#pragma once
inline
const M_GEO Entity_Triangulation3d & AutLib::MeshLib::Mesh3d_ShapeMesher::Mesh() const
{
	if (NOT IsDone_) THROW_STANDARD_EXCEPTION(" ShapeMesher is not performed");
	return theMergedMesh_;
}