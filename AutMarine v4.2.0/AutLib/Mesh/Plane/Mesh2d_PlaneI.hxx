#pragma once
inline
Global_Handle(M_MESH Mesh2d_TMesh) AutLib::MeshLib::Mesh2d_Plane::Mesh(const Standard_Integer Index) const
{
	Debug_Bad_Index_Array1(Index, theMeshes_);

	return theMeshes_[Index];
}

inline 
Global_Handle(M_MESH Mesh2d_TMesh) AutLib::MeshLib::Mesh2d_Plane::CurrentMesh() const
{
	Debug_Bad_Index_Array1(theCurrent_, theMeshes_);

	return theMeshes_[theCurrent_];
}

inline 
Global_Handle(M_MESH Mesh2d_TMesh)& AutLib::MeshLib::Mesh2d_Plane::CurrentMesh()
{
	Debug_Bad_Index_Array1(theCurrent_, theMeshes_);

	return theMeshes_[theCurrent_];
}

inline
AutLib::MeshLib::Mesh_LaplacianSmoothingInfo & AutLib::MeshLib::Mesh2d_Plane::LaplacianSmoothing()
{
	return theSmoothing_;
}

inline
const AutLib::MeshLib::Mesh_LaplacianSmoothingInfo & AutLib::MeshLib::Mesh2d_Plane::LaplacianSmoothing() const
{
	return theSmoothing_;
}

inline 
const M_MESH Mesh2d_Domain & AutLib::MeshLib::Mesh2d_Plane::Domain(const Standard_Integer Index) const
{
	Debug_Bad_Index_Array1(Index, theDomains_);

	return *theDomains_[Index];
}

inline 
M_MESH Mesh2d_Domain & AutLib::MeshLib::Mesh2d_Plane::Domain(const Standard_Integer Index)
{
	Debug_Bad_Index_Array1(Index, theDomains_);

	return *theDomains_[Index];
}

inline 
Standard_Integer AutLib::MeshLib::Mesh2d_Plane::NbMeshes() const
{
	return theMeshes_.Size();
}

inline 
Standard_Integer AutLib::MeshLib::Mesh2d_Plane::Current() const
{
	return theCurrent_;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh2d_Plane::NbElements() const
{
	return CurrentMesh()->NbElements();
}

inline 
Standard_Integer AutLib::MeshLib::Mesh2d_Plane::NbEdges() const
{
	return CurrentMesh()->NbEdges();
}

inline 
Standard_Integer AutLib::MeshLib::Mesh2d_Plane::NbNodes() const
{
	return CurrentMesh()->NbNodes();
}

inline 
void AutLib::MeshLib::Mesh2d_Plane::SetCurrent(const Standard_Integer Value)
{
	theCurrent_ = Value;
}