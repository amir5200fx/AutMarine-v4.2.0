#pragma once
inline
const M_AUT TColMesh3d_HAry1dOfNode & AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTriangles::Nodes() const
{
	return theNodes_;
}

inline 
const M_AUT TColMesh3d_HAry1dOfEdge & AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTriangles::Edges() const
{
	return theEdges_;
}

inline 
const M_AUT TColEntity_Ary1dOfTriangleIndex & AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTriangles::Triangles() const
{
	return theTriangles_;
}

inline 
Standard_Real AutLib::MeshLib::Mesh3d_EdgeRemovalEquatorialTriangles::WorstQuality() const
{
	return theWorstQuality_;
}