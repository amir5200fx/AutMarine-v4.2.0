#pragma once
inline
Standard_Boolean AutLib::MeshLib::Mesh2d_SafeFront::IsCurrentLevelEmpty() const
{
	return theCurrentLevels_.IsEmpty();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_SafeFront::IsNextLevelEmpty() const
{
	return theNextLevels_.IsEmpty();
}

inline
void AutLib::MeshLib::Mesh2d_SafeFront::InsertToCurrentLevel(Global_Handle(Mesh2d_Edge) Edge)
{
	theCurrentLevels_.Insert(Edge);
}

inline 
void AutLib::MeshLib::Mesh2d_SafeFront::InsertToNextLevel(Global_Handle(Mesh2d_Edge) Edge)
{
	theNextLevels_.Insert(Edge);
}

inline 
void AutLib::MeshLib::Mesh2d_SafeFront::ClearCurrentLevel()
{
	theCurrentLevels_.Clear();
}

inline 
void AutLib::MeshLib::Mesh2d_SafeFront::ClearNextLevel()
{
	theNextLevels_.Clear();
}

inline 
void AutLib::MeshLib::Mesh2d_SafeFront::RetrieveCurrentLevelTo(TColMesh2d_HAry1dOfEdge & Edges) const
{
	theCurrentLevels_.RetrieveTo(Edges);
}

inline 
void AutLib::MeshLib::Mesh2d_SafeFront::RetrieveNextLevelTo(TColMesh2d_HAry1dOfEdge & Edges) const
{
	theNextLevels_.RetrieveTo(Edges);
}