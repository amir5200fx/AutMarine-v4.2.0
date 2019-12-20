#pragma once
inline
Standard_Integer AutLib::GeoLib::GeoMesh_StaticTriangleMesh3d::NbEdges() const
{
	return theEdges_.Size();
}

inline 
const M_AUT TColEntity_Ary1dOfEdgeIndex & AutLib::GeoLib::GeoMesh_StaticTriangleMesh3d::Edges() const
{
	return theEdges_;
}

inline 
const M_GEO Entity_EdgeIndex & AutLib::GeoLib::GeoMesh_StaticTriangleMesh3d::Edge(const Standard_Integer Index) const
{
	Debug_Bad_Index_Array1(Index, theEdges_);
	return theEdges_[Index];
}

inline 
const M_GEO Entity_TriangleIndex & AutLib::GeoLib::GeoMesh_StaticTriangleMesh3d::EdgesInTriangle(const Standard_Integer Index) const
{
	Debug_Bad_Index_Array1(Index, theEdgesOfTriangles_);
	return theEdgesOfTriangles_[Index];
}