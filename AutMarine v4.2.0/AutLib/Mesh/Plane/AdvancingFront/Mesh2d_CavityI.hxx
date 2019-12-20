#pragma once
inline
Standard_Boolean AutLib::MeshLib::Mesh2d_Cavity::IsUnCertaintyEmpty() const
{
	return theUnCertainty_.IsEmpty();
}

inline
Standard_Boolean AutLib::MeshLib::Mesh2d_Cavity::IsCertaintyEmpty() const
{
	return theCertainty_.IsEmpty();
}

inline
void AutLib::MeshLib::Mesh2d_Cavity::InsertToUnCertainty(Global_Handle(Mesh2d_Edge) Edge)
{
	theUnCertainty_.Insert(Edge);
}

inline
void AutLib::MeshLib::Mesh2d_Cavity::InsertToCertainty(Global_Handle(Mesh2d_Edge) Edge)
{
	theCertainty_.Insert(Edge);
}

inline
void AutLib::MeshLib::Mesh2d_Cavity::RemoveFromUnCertainty(Global_Handle(Mesh2d_Edge) Edge)
{
	theUnCertainty_.Remove(Edge);
}

inline
void AutLib::MeshLib::Mesh2d_Cavity::RemoveFromCertainty(Global_Handle(Mesh2d_Edge) Edge)
{
	theCertainty_.Remove(Edge);
}

inline
void AutLib::MeshLib::Mesh2d_Cavity::RemoveFromUnCertaintyIgnoreWarning(Global_Handle(Mesh2d_Edge) Edge)
{
	theUnCertainty_.RemoveIgnoreWarning(Edge);
}

inline
void AutLib::MeshLib::Mesh2d_Cavity::RemoveFromCertaintyIgnoreWarning(Global_Handle(Mesh2d_Edge) Edge)
{
	theCertainty_.RemoveIgnoreWarning(Edge);
}

inline
void AutLib::MeshLib::Mesh2d_Cavity::RetrieveUnCertaintyTo(TColMesh2d_HAry1dOfEdge & Edges) const
{
	theUnCertainty_.RetrieveTo(Edges);
}

inline
void AutLib::MeshLib::Mesh2d_Cavity::RetrieveCertaintyTo(TColMesh2d_HAry1dOfEdge & Edges) const
{
	theCertainty_.RetrieveTo(Edges);
}

inline
void AutLib::MeshLib::Mesh2d_Cavity::ClearUnCertainty()
{
	theUnCertainty_.Clear();
}

inline
void AutLib::MeshLib::Mesh2d_Cavity::ClearCertainty()
{
	theCertainty_.Clear();
}