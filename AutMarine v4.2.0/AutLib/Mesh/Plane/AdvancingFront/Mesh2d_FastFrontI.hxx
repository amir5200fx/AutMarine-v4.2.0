#pragma once
inline
Standard_Boolean AutLib::MeshLib::Mesh2d_FastFront::IsCurrentLevelEmpty() const
{
	return theCurrentLevels_.IsEmpty();
}

inline
Standard_Boolean AutLib::MeshLib::Mesh2d_FastFront::IsNextLevelEmpty() const
{
	return theNextLevels_.IsEmpty();
}

inline
void AutLib::MeshLib::Mesh2d_FastFront::InsertToCurrentLevel(Global_Handle(Mesh2d_Edge) Edge)
{
	theCurrentLevels_.EnQueue(Edge);
}

inline
void AutLib::MeshLib::Mesh2d_FastFront::InsertToNextLevel(Global_Handle(Mesh2d_Edge) Edge)
{
	theNextLevels_.EnQueue(Edge);
}

inline
void AutLib::MeshLib::Mesh2d_FastFront::ClearCurrentLevel()
{
	theCurrentLevels_.Clear();
}

inline
void AutLib::MeshLib::Mesh2d_FastFront::ClearNextLevel()
{
	theNextLevels_.Clear();
}

inline
void AutLib::MeshLib::Mesh2d_FastFront::RetrieveCurrentLevelTo(TColMesh2d_HAry1dOfEdge & Edges) const
{
	theCurrentLevels_.RetrieveTo(Edges);
}

inline
void AutLib::MeshLib::Mesh2d_FastFront::RetrieveNextLevelTo(TColMesh2d_HAry1dOfEdge & Edges) const
{
	theNextLevels_.RetrieveTo(Edges);
}