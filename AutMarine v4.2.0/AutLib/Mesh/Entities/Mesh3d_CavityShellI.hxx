#pragma once
inline
Standard_Integer AutLib::MeshLib::Mesh3d_CavityShell::NbFacets() const
{
	return theFacets_.Size();
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_CavityShell::NbEntities() const
{
	return theEntities_.Size();
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_CavityShell::Index() const
{
	return theIndex_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_CavityShell::IsEmpty() const
{
	return theFacets_.IsEmpty();
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_CavityShell::IsConvex() const
{
	return NOT NbEntities();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_CavityShell::IsOnShell(const Global_Handle(Mesh3d_Facet) theFacet) const
{
	return theFacets_.IsContains((Global_Handle(Mesh3d_Facet))theFacet);
}

inline 
void AutLib::MeshLib::Mesh3d_CavityShell::SetIndex(const Standard_Integer theIndex)
{
	theIndex_ = theIndex;
}

inline 
void AutLib::MeshLib::Mesh3d_CavityShell::ImportToFacets(Global_Handle(Mesh3d_Facet) theFacet)
{
	Debug_Null_Pointer(theFacet);
	theFacets_.Insert(theFacet);
}

inline 
void AutLib::MeshLib::Mesh3d_CavityShell::ImportToEntities(Global_Handle(Mesh3d_CavityEntity) theEntity)
{
	Debug_Null_Pointer(theEntity);
	theEntities_.Insert(theEntity);
}

inline 
void AutLib::MeshLib::Mesh3d_CavityShell::RemoveFromFacets(Global_Handle(Mesh3d_Facet) theFacet)
{
	Debug_Null_Pointer(theFacet);
	theFacets_.Remove(theFacet);
}

inline 
void AutLib::MeshLib::Mesh3d_CavityShell::RemoveFromEntities(Global_Handle(Mesh3d_CavityEntity) theEntity)
{
	Debug_Null_Pointer(theEntity);
	theEntities_.Remove(theEntity);
}

inline 
void AutLib::MeshLib::Mesh3d_CavityShell::RetrieveFacetsTo(TColMesh3d_HAry1dOfFacet & theFacets) const
{
	theFacets_.RetrieveTo(theFacets);
}

inline 
void AutLib::MeshLib::Mesh3d_CavityShell::RetrieveEntitiesTo(TColMesh3d_HAry1dOfCavityEntity & theEntities) const
{
	theEntities_.RetrieveTo(theEntities);
}

inline 
void AutLib::MeshLib::Mesh3d_CavityShell::Clear()
{
	theFacets_.Clear();
	theEntities_.Clear();
}

inline 
void AutLib::MeshLib::Mesh3d_CavityShell::ClearEntities()
{
	theEntities_.Clear();
}