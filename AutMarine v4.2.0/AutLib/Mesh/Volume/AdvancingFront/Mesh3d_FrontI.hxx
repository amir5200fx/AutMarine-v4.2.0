#pragma once
inline
Standard_Integer AutLib::MeshLib::Mesh3d_Front::LevelNumber() const
{
	return theLevelNb_;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh3d_Front::LevelMaxIndex() const
{
	return theLevelMaxIndex_;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Front::GetItemFromFront(Global_Handle(Mesh3d_Facet)& Facet)
{
	return theSortedFacets_.GetItem(Facet);
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Front::IsFrontEmpty() const
{
	return theSortedFacets_.IsEmpty();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Front::IsCurrentLevelEmpty() const
{
	return theCurrentLevels_.IsEmpty();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Front::IsNextLevelEmpty() const
{
	return theNextLevels_.IsEmpty();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_Front::IsOnLevel(const Mesh3d_Facet & theFacet) const
{
	Debug_Null_Pointer(theFacet.Node0());
	Debug_Null_Pointer(theFacet.Node1());
	Debug_Null_Pointer(theFacet.Node2());

	if (theFacet.Node0()->Index() <= theLevelMaxIndex_) { return Standard_True; }
	if (theFacet.Node1()->Index() <= theLevelMaxIndex_) { return Standard_True; }
	if (theFacet.Node2()->Index() <= theLevelMaxIndex_) { return Standard_True; }

	return Standard_False;
}

inline 
void AutLib::MeshLib::Mesh3d_Front::InsertToFronts(const TColMesh3d_HAry1dOfFacet & Facets)
{
	theSortedFacets_.Insert(Facets);
}

inline 
void AutLib::MeshLib::Mesh3d_Front::InsertToCurrentLevel(Global_Handle(Mesh3d_Facet) Facet)
{
	theCurrentLevels_.Insert(Facet);
}

inline 
void AutLib::MeshLib::Mesh3d_Front::InsertToNextLevel(Global_Handle(Mesh3d_Facet) Facet)
{
	theNextLevels_.Insert(Facet);
}

inline 
void AutLib::MeshLib::Mesh3d_Front::ClearCurrentLevel()
{
	theCurrentLevels_.Clear();
}

inline 
void AutLib::MeshLib::Mesh3d_Front::ClearNextLevel()
{
	theNextLevels_.Clear();
}

inline 
void AutLib::MeshLib::Mesh3d_Front::SetLevelNumber(const Standard_Integer Value)
{
	Debug_If_Condition_Message(Value < 0, " Invalid Level number");

	theLevelNb_ = Value;
}

inline 
void AutLib::MeshLib::Mesh3d_Front::SetLevelMaxIndex(const Standard_Integer Value)
{
	Debug_If_Condition_Message(Value < 0, " Invalid Max Level number");

	theLevelMaxIndex_ = Value;
}

inline 
void AutLib::MeshLib::Mesh3d_Front::RetrieveCurrentLevelTo(TColMesh3d_HAry1dOfFacet & Facets) const
{
	theCurrentLevels_.RetrieveTo(Facets);
}

inline 
void AutLib::MeshLib::Mesh3d_Front::RetrieveNextLevelTo(TColMesh3d_HAry1dOfFacet & Facets) const
{
	theNextLevels_.RetrieveTo(Facets);
}