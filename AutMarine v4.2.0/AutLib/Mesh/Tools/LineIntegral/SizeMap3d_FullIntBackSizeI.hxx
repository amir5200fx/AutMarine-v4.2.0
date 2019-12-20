#pragma once
inline
Standard_Real AutLib::MeshLib::SizeMap3d_FullIntBackSize::ElementSize(const Mesh3d_Facet & Facet) const
{
	Get_Const_Object(Centre) = Facet.Centre();

	theOptPoint_ = SizeMap3d_UniSize::CalcOptimumCoord(SizeMap3d_StdBackSize::ElementSize(Centre), Facet);

	forThose
	(
		Iter,
		1,
		theMaxIters_
	)
	{
		Standard_Real Dis = 1.155*CalcUnitDistance(Centre, theOptPoint_);

		theOptPoint_ = Centre + (theOptPoint_ - Centre) / Dis;
		if (ABS(1.0 - Dis) < 0.01) break;
	}

	return M_GEO Distance(theOptPoint_, Centre);
}

inline
Geom_Pnt3d AutLib::MeshLib::SizeMap3d_FullIntBackSize::CalcOptimumCoord(const Standard_Real Size, const Mesh3d_Facet & Facet) const
{
	return theOptPoint_;
}

inline 
Standard_Real AutLib::MeshLib::SizeMap3d_FullIntBackSize::MetricIntegrand(const Geom_Pnt3d & Point, const Geom_Pnt3d & Vector) const
{
	return (ONE / SizeMap3d_StdBackSize::ElementSize(Point))*sqrt(M_GEO DotProduct(Vector, Vector));
}