#pragma once
inline
Standard_Boolean AutLib::MeshLib::Mesh3d_Cavity::IsUnCertaintyEmpty() const
{
	return theUnCertainty_.IsEmpty();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Cavity::IsCertaintyEmpty() const
{
	return theCertainty_.IsEmpty();
}

inline 
void AutLib::MeshLib::Mesh3d_Cavity::InsertToUnCertainty(Global_Handle(Mesh3d_Facet) Facet)
{
	theUnCertainty_.Insert(Facet);
}

inline 
void AutLib::MeshLib::Mesh3d_Cavity::InsertToCertainty(Global_Handle(Mesh3d_Facet) Facet)
{
	theCertainty_.Insert(Facet);
}

inline 
void AutLib::MeshLib::Mesh3d_Cavity::RemoveFromUnCertainty(Global_Handle(Mesh3d_Facet) Facet)
{
	theUnCertainty_.Remove(Facet);
}

inline 
void AutLib::MeshLib::Mesh3d_Cavity::RemoveFromCertainty(Global_Handle(Mesh3d_Facet) Facet)
{
	theCertainty_.Remove(Facet);
}

inline 
void AutLib::MeshLib::Mesh3d_Cavity::RemoveFromUnCertaintyIgnoreWarning(Global_Handle(Mesh3d_Facet) Facet)
{
	theUnCertainty_.RemoveIgnoreWarning(Facet);
}

inline 
void AutLib::MeshLib::Mesh3d_Cavity::RemoveFromCertaintyIgnoreWarning(Global_Handle(Mesh3d_Facet) Facet)
{
	theCertainty_.RemoveIgnoreWarning(Facet);
}

inline
void AutLib::MeshLib::Mesh3d_Cavity::RetrieveUnCertaintyTo(TColMesh3d_HAry1dOfFacet & Facets) const
{
	theUnCertainty_.RetrieveTo(Facets);
}

inline 
void AutLib::MeshLib::Mesh3d_Cavity::RetrieveCertaintyTo(TColMesh3d_HAry1dOfFacet & Facets) const
{
	theCertainty_.RetrieveTo(Facets);
}

inline 
void AutLib::MeshLib::Mesh3d_Cavity::ClearUnCertainty()
{
	theUnCertainty_.Clear();
}

inline 
void AutLib::MeshLib::Mesh3d_Cavity::ClearCertainty()
{
	theCertainty_.Clear();
}