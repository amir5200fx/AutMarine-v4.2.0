#pragma once
inline
Standard_Integer AutLib::MeshLib::Mesh2d_Mesh::NbNodes() const
{
	return theNbNodes_;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh2d_Mesh::NbEdges() const
{
	return theNbEdges_;
}

inline 
Standard_Integer AutLib::MeshLib::Mesh2d_Mesh::NbElements() const
{
	return thenbElements_;
}

inline
Standard_Integer& AutLib::MeshLib::Mesh2d_Mesh::NbNodes()
{
	return theNbNodes_;
}

inline
Standard_Integer& AutLib::MeshLib::Mesh2d_Mesh::NbEdges()
{
	return theNbEdges_;
}

inline
Standard_Integer& AutLib::MeshLib::Mesh2d_Mesh::NbElements()
{
	return thenbElements_;
}

inline 
void AutLib::MeshLib::Mesh2d_Mesh::InsertToMesh(Global_Handle(Mesh2d_Node) Node)
{
	theNodes_.Insert(Node);
}

inline 
void AutLib::MeshLib::Mesh2d_Mesh::InsertToMesh(Global_Handle(Mesh2d_Edge) Edge)
{
	theEdges_.Insert(Edge);
}

inline 
void AutLib::MeshLib::Mesh2d_Mesh::InsertToMesh(Global_Handle(Mesh2d_Element) Element)
{
	theElements_.Insert(Element);
}

inline 
void AutLib::MeshLib::Mesh2d_Mesh::InsertToMesh(const TColMesh2d_HAry1dOfNode & Nodes)
{
	theNodes_.Insert(Nodes);
}

inline 
void AutLib::MeshLib::Mesh2d_Mesh::InsertToMesh(const TColMesh2d_HAry1dOfEdge & Edges)
{
	theEdges_.Insert(Edges);
}

inline 
void AutLib::MeshLib::Mesh2d_Mesh::InsertToFronts(Global_Handle(Mesh2d_Node) Node)
{
	theFrontNodes_.Insert(Node);
}

inline 
void AutLib::MeshLib::Mesh2d_Mesh::InsertToFronts(Global_Handle(Mesh2d_Edge) Edge)
{
	theFrontEdges_.Insert(Edge);
}

inline 
void AutLib::MeshLib::Mesh2d_Mesh::InsertToFronts(const TColMesh2d_HAry1dOfNode & Nodes)
{
	theFrontNodes_.Insert(Nodes);
}

inline 
void AutLib::MeshLib::Mesh2d_Mesh::RemoveFromMesh(Global_Handle(Mesh2d_Node) Node)
{
	theNodes_.Remove(Node);
}

inline 
void AutLib::MeshLib::Mesh2d_Mesh::RemoveFromMesh(Global_Handle(Mesh2d_Edge) Edge)
{
	theEdges_.Remove(Edge);
}

inline 
void AutLib::MeshLib::Mesh2d_Mesh::RemoveFromMesh(Global_Handle(Mesh2d_Element) Element)
{
	theElements_.Remove(Element);
}

inline 
void AutLib::MeshLib::Mesh2d_Mesh::RemoveFromFronts(Global_Handle(Mesh2d_Node) Node)
{
	theFrontNodes_.Remove(Node);
}

inline 
void AutLib::MeshLib::Mesh2d_Mesh::RemoveFromFronts(Global_Handle(Mesh2d_Edge) Edge)
{
	theFrontEdges_.Remove(Edge);
}

inline 
void AutLib::MeshLib::Mesh2d_Mesh::RetrieveTo(TColMesh2d_HAry1dOfNode & Nodes) const
{
	theNodes_.RetrieveTo(Nodes);
}

inline 
void AutLib::MeshLib::Mesh2d_Mesh::RetrieveTo(TColMesh2d_HAry1dOfEdge & Edges) const
{
	theEdges_.RetrieveTo(Edges);
}

inline 
void AutLib::MeshLib::Mesh2d_Mesh::RetrieveTo(TColMesh2d_HAry1dOfElement & Elements) const
{
	theElements_.RetrieveTo(Elements);
}

inline 
void AutLib::MeshLib::Mesh2d_Mesh::RetrieveFrontsTo(TColMesh2d_HAry1dOfNode & Nodes) const
{
	theFrontNodes_.RetrieveTo(Nodes);
}

inline 
void AutLib::MeshLib::Mesh2d_Mesh::RetrieveFrontsTo(TColMesh2d_HAry1dOfEdge & Edges) const
{
	theFrontEdges_.RetrieveTo(Edges);
}