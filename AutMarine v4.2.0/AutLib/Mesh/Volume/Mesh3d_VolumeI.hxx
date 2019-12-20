#pragma once
inline
Global_Handle(M_MESH Mesh3d_Mesh) AutLib::MeshLib::Mesh3d_Volume::Mesh(const Standard_Integer Index) const
{
	Debug_Bad_Index_Array1(Index, theMeshes_);
	return theMeshes_[Index];
}

inline 
Global_Handle(M_MESH Mesh3d_TMesh) AutLib::MeshLib::Mesh3d_Volume::CurrentMesh() const
{
	Debug_Bad_Index_Array1(theCurrent_, theMeshes_);
	return theMeshes_[theCurrent_];
}

inline 
Global_Handle(M_MESH Mesh3d_TMesh)& AutLib::MeshLib::Mesh3d_Volume::CurrentMesh()
{
	Debug_Bad_Index_Array1(theCurrent_, theMeshes_);
	return theMeshes_[theCurrent_];
}

inline 
Global_Handle(M_MESH Mesh3d_SolidMesher) AutLib::MeshLib::Mesh3d_Volume::Domain(const Standard_Integer Index) const
{
	Debug_Bad_Index_Array1(Index, theDomains_);
	//Debug_Null_Pointer(theDomains_[Index]);
	return theDomains_[Index];
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Volume::NbMeshes() const
{
	return theMeshes_.Size();
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Volume::Current() const
{
	return theCurrent_;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Volume::NbElements() const
{
	return CurrentMesh()->NbElements();
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Volume::NbFacets() const
{
	return CurrentMesh()->NbFacets();
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Volume::NbEdges() const
{
	return CurrentMesh()->NbEdges();
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Volume::NbNodes() const
{
	return CurrentMesh()->NbNodes();
}

inline 
void AutLib::MeshLib::Mesh3d_Volume::SetCurrent(const Standard_Integer Value)
{
	theCurrent_ = Value;
}