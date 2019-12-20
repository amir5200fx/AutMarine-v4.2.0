#pragma once
inline
Standard_Real AutLib::MeshLib::SizeMap2d_FullIntBackSize::ElementSize(const Mesh2d_Edge & Edge) const
{
	Get_Const_Object(Centre) = Edge.Centre();

	theOptPoint_ = SizeMap2d_UniSize::CalcOptimumPoint(SizeMap2d_StdBackSize::ElementSize(Centre), Edge);

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
Geom_Pnt2d AutLib::MeshLib::SizeMap2d_FullIntBackSize::CalcOptimumPoint(const Standard_Real Size, const Mesh2d_Edge & Edge) const
{
	return theOptPoint_;
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_FullIntBackSize::MetricIntegrand(const Geom_Pnt2d & Point, const Geom_Pnt2d & Vector) const
{
	return (ONE / SizeMap2d_StdBackSize::ElementSize(Point))*sqrt(M_GEO DotProduct(Vector, Vector));
}