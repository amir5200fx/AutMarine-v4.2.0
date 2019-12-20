#pragma once
inline
Standard_Integer AutLib::MeshLib::Mesh2d_Front::LevelNumber() const
{
	return theLevelNb_;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh2d_Front::LevelMaxIndex() const
{
	return theLevelMaxIndex_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_Front::GetItemFromFront(Global_Handle(Mesh2d_Edge)& Edge)
{
	return theSortedEdges_.GetItem(Edge);
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_Front::IsFrontEmpty() const
{
	return theSortedEdges_.IsEmpty();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_Front::IsOnLevel(const Mesh2d_Edge & theEdge) const
{
	Debug_Null_Pointer(theEdge.Node0());
	Debug_Null_Pointer(theEdge.Node1());

	if (theEdge.Node0()->Index() <= theLevelMaxIndex_) { return Standard_True; }
	if (theEdge.Node1()->Index() <= theLevelMaxIndex_) { return Standard_True; }

	return Standard_False;
}

inline 
void AutLib::MeshLib::Mesh2d_Front::InsertToFronts(const TColMesh2d_HAry1dOfEdge & Edges)
{
	theSortedEdges_.Insert(Edges);
}

inline
void AutLib::MeshLib::Mesh2d_Front::SetLevelNumber(const Standard_Integer Value)
{
	Debug_If_Condition_Message(Value < 0, " Invalid Level number");

	theLevelNb_ = Value;
}

inline
void AutLib::MeshLib::Mesh2d_Front::SetLevelMaxIndex(const Standard_Integer Value)
{
	Debug_If_Condition_Message(Value < 0, " Invalid Max Level number");

	theLevelMaxIndex_ = Value;
}