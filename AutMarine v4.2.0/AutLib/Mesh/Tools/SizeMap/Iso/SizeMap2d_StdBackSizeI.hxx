#pragma once
inline
Standard_Real AutLib::MeshLib::SizeMap2d_StdBackSize::ElementSize(const Geom_Pnt2d & Coord) const
{
	//return theMesh_.ElementSize(Coord)*SizeMap2d_UniSize::BaseSize();
	return theMesh_.ElementSize(Coord);  // Debug July 14 2018
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_StdBackSize::ElementSize(const Mesh2d_Edge & Edge) const
{
	//return theMesh_.ElementSize(Edge.Centre())*SizeMap2d_UniSize::BaseSize();
	return theMesh_.ElementSize(Edge.Centre());  // Debug July 14 2018
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_StdBackSize::CalcUnitDistance(const Geom_Pnt2d & P1, const Geom_Pnt2d & P2) const
{
	const Standard_Real H1 = ElementSize(P1);
	const Standard_Real H2 = ElementSize(P2);

	return M_GEO Distance(P1, P2) / (MEAN(H1, H2));
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_StdBackSize::Integrand(const Geom_Pnt2d & Point, const Geom_Pnt2d & Vector) const
{
	return (1.0 / ElementSize(Point))*sqrt(M_GEO DotProduct(Vector, Vector));
}