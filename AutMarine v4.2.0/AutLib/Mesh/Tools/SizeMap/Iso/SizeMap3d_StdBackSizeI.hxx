#pragma once
inline
Standard_Real AutLib::MeshLib::SizeMap3d_StdBackSize::ElementSize(const Geom_Pnt3d & Coord) const
{
	return theMesh_.ElementSize(Coord);
}

inline 
Standard_Real AutLib::MeshLib::SizeMap3d_StdBackSize::ElementSize(const Mesh3d_Facet & Facet) const
{
	return theMesh_.ElementSize(Facet.Centre());
}

inline 
Standard_Real AutLib::MeshLib::SizeMap3d_StdBackSize::CalcUnitDistance(const Geom_Pnt3d & P1, const Geom_Pnt3d & P2) const
{
	const Standard_Real H1 = ElementSize(P1);
	const Standard_Real H2 = ElementSize(P2);

	return M_GEO Distance(P1, P2) / (MEAN(H1, H2));
}

inline 
Standard_Real AutLib::MeshLib::SizeMap3d_StdBackSize::Integrand(const Geom_Pnt3d & Point, const Geom_Pnt3d & Vector) const
{
	return (1.0 / ElementSize(Point))*sqrt(M_GEO DotProduct(Vector, Vector));
}