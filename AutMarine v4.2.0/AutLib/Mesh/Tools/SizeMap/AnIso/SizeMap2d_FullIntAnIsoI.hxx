#pragma once
#include <Geometry_Tools.hxx>
#include <Entity_Eigen2d.hxx>

inline
const Global_Handle(M_MESH Mesh2d_SizeMap) AutLib::MeshLib::SizeMap2d_FullIntAnIso::SizeMap() const
{
	return theSizeMap_;
}

inline 
const Global_Handle(M_MESH Mesh2d_MetricMap) AutLib::MeshLib::SizeMap2d_FullIntAnIso::MetricMap() const
{
	return theMetricMap_;
}

inline
Standard_Real AutLib::MeshLib::SizeMap2d_FullIntAnIso::BaseSize() const
{
	return theSizeMap_->BaseSize();
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_FullIntAnIso::ElementSize(const Geom_Pnt2d & Coord) const
{
	return theSizeMap_->ElementSize(Coord);
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_FullIntAnIso::ElementSize(const Mesh2d_Edge & Edge) const
{
	return theSizeMap_->ElementSize(Edge);
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_FullIntAnIso::Oriented(const Geom_Pnt2d & P0, const Geom_Pnt2d & P1, const Geom_Pnt2d & P2) const
{
	return M_GEO Geometry_Tools::Oriented(P0, P1, P2);
}

inline
Standard_Real AutLib::MeshLib::SizeMap2d_FullIntAnIso::CalcDistanceSQ(const Geom_Pnt2d & P1, const Geom_Pnt2d & P2) const
{
	Standard_Real Distance = CalcDistance(P1, P2);
	return Distance*Distance;
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_FullIntAnIso::CalcDistancePointFromLSeg
(
	const Geom_Pnt2d & thePoint, 
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2
) const
{
	Standard_Real bot = DistanceSQ(P1, P2);

	Geom_Pnt2d Pn;
	if (bot == 0.0) Pn = P1;
	else
	{
		Geom_Pnt2d V1 = P2 - P1;
		Geom_Pnt2d V2 = thePoint - P1;

		Standard_Real t = M_GEO DotProduct(V1, V2) / bot;
		if (t > 1) t = 1;
		if (t < 0) t = 0;

		Pn = P1 + t*V1;
	}

	return CalcDistance(thePoint, Pn);
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_FullIntAnIso::CalcDistancePointFromLSegSQ
(
	const Geom_Pnt2d & thePoint,
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2
) const
{
	Standard_Real bot = DistanceSQ(P1, P2);

	Geom_Pnt2d Pn;
	if (bot == 0.0) Pn = P1;
	else
	{
		Geom_Pnt2d V1 = P2 - P1;
		Geom_Pnt2d V2 = thePoint - P1;

		Standard_Real t = M_GEO DotProduct(V1, V2) / bot;
		if (t > 1) t = 1;
		if (t < 0) t = 0;

		Pn = P1 + t*V1;
	}

	return CalcDistanceSQ(thePoint, Pn);
}

inline 
Geom_Pnt2d AutLib::MeshLib::SizeMap2d_FullIntAnIso::CalcOptimumPoint
(
	const Standard_Real Size,
	const Mesh2d_Edge & Edge
) const
{
	const Standard_Real InvH2 = 1.0 / (Size*Size);
	static const Standard_Real C3 = 1.7320508075688773;

	Get_Const_Object(Centre) = Edge.Centre();

	theCurrentMetric_ = theMetricMap_->MetricAt(Centre);

	//Mp.RemoveDegeneracy(EPS6);
	M_GEO Entity_Metric1 M(InvH2*theCurrentMetric_.A(), InvH2*theCurrentMetric_.B(), InvH2*theCurrentMetric_.C());

	const Standard_Real D = sqrt(M.Determinant());
	const Standard_Real Cte = C3 / (2.0*D*CalcDistance(Centre, Edge.Node(1)->Coord()));

	Geom_Pnt2d DU = Edge.Node(1)->Coord() - Centre;

	vec2 U;
	U(0) = DU.X();
	U(1) = DU.Y();

	mat22 orthM;
	orthM(0, 0) = -M.B();
	orthM(0, 1) = -M.C();
	orthM(1, 0) = M.A();
	orthM(1, 1) = M.B();

	U = Cte*(orthM*U);

	Geom_Pnt2d P(Centre.X() + 0.8*U(0), Centre.Y() + 0.8*U(1));

	Get_Const_Object(P0) = Edge.Node(0)->Coord();
	Get_Const_Object(P1) = Edge.Node(1)->Coord();

	if (NOT M_GEO Geometry_Tools::IsPointInsideOnBox(P, theBoundingBox_.Xmin(), theBoundingBox_.Xmax(), theBoundingBox_.Ymin(), theBoundingBox_.Ymax()))
	{
		P = CorrectPoint(Centre, P);
	}

	Standard_Real Omega = 0.85;
	forThose
	(
		Iter,
		1,
		theMaxIters_
	)
	{
		Standard_Real D1 = CalcUnitDistance(P0, P);
		Standard_Real D2 = CalcUnitDistance(P1, P);

		Geom_Pnt2d Pa = P0 + (P - P0) / D1;
		Geom_Pnt2d Pb = P1 + (P - P1) / D2;

		Geom_Pnt2d Pn = 0.5*(Pa + Pb);
		Geom_Pnt2d dP = Pn - P;

		P += Omega*dP;

		if (NOT M_GEO Geometry_Tools::IsPointInsideOnBox(P, theBoundingBox_.Xmin(), theBoundingBox_.Xmax(), theBoundingBox_.Ymin(), theBoundingBox_.Ymax()))
		{
			P = CorrectPoint(Centre, P);
		}

		if (ABS(1.0 - D1) < 0.01 AND ABS(1.0 - D2) < 0.01) break;
	}

	/*Standard_Real Dis;
	forThose
	(
		Iter,
		1,
		theMaxIters_
	)
	{
		Try_Exception_Handle_Exit(Dis = 1.155*CalcUnitDistance(Centre, P));

		P = Centre + (P - Centre) / Dis;

		if (NOT M_GEO Geometry_Tools::IsPointInsideOnBox(P, theBoundingBox_.Xmin(), theBoundingBox_.Xmax(), theBoundingBox_.Ymin(), theBoundingBox_.Ymax()))
		{
			P = CorrectPoint(Centre, P);
		}

		if (ABS(1.0 - Dis) < 0.01) break;
	}*/

	MOVE(P);
}

inline 
Geom_Pnt2d AutLib::MeshLib::SizeMap2d_FullIntAnIso::CalcCentreOf(const Geom_Pnt2d & P1, const Geom_Pnt2d & P2) const
{
	Geom_Pnt2d P = MEAN(P1, P2);
	MOVE(P);
	if (theMetricMap_->MetricAt(P).Determinant() < 1.0E-6)
	{
		MOVE(P);
	}

	forThose
	(
		Iter,
		1,
		theMaxIters_
	)
	{
		Standard_Real Dis = CalcUnitDistance(P1, P);

		P = P1 + 0.5*(P - P1) / Dis;
		if (ABS(1.0 - 2 * Dis) < theTolerance_) break;
	}
	MOVE(P);
}

inline 
M_GEO Entity_Box2d AutLib::MeshLib::SizeMap2d_FullIntAnIso::CalcSearchRegion
(
	const Standard_Real Radius, 
	const Geom_Pnt2d & Centre
) const
{
	M_GEO Entity_Eigen2d Eigen;
	Eigen.CalcEigen(theMetricMap_->MetricAt(Centre));

	Standard_Real radius = Radius;

	const Standard_Real Dx = MAX
	(
		ABS(GeoLib::DotProduct(Geom_Pnt2d(1, 0), radius*Eigen.H1()*Eigen.E1())),
		ABS(GeoLib::DotProduct(Geom_Pnt2d(1, 0), radius*Eigen.H2()*Eigen.E2()))
	);

	const Standard_Real Dy = MAX
	(
		ABS(GeoLib::DotProduct(Geom_Pnt2d(0, 1), radius*Eigen.H1()*Eigen.E1())),
		ABS(GeoLib::DotProduct(Geom_Pnt2d(0, 1), radius*Eigen.H2()*Eigen.E2()))
	);

	return M_GEO Entity_Box2d
	(
		Centre.X() - Dx,
		Centre.X() + Dx,
		Centre.Y() - Dy,
		Centre.Y() + Dy
	);
}

inline 
M_GEO Entity_Box2d AutLib::MeshLib::SizeMap2d_FullIntAnIso::CalcSearchRegion(const Standard_Real Radius, const Geom_Pnt2d & Centre, const Mesh2d_Edge & Edge) const
{
	M_GEO Entity_Eigen2d Eigen;
	Eigen.CalcEigen(theCurrentMetric_);

	Standard_Real radius = Radius;

	const Standard_Real Dx = MAX
	(
		ABS(GeoLib::DotProduct(Geom_Pnt2d(1, 0), radius*Eigen.H1()*Eigen.E1())),
		ABS(GeoLib::DotProduct(Geom_Pnt2d(1, 0), radius*Eigen.H2()*Eigen.E2()))
	);

	const Standard_Real Dy = MAX
	(
		ABS(GeoLib::DotProduct(Geom_Pnt2d(0, 1), radius*Eigen.H1()*Eigen.E1())),
		ABS(GeoLib::DotProduct(Geom_Pnt2d(0, 1), radius*Eigen.H2()*Eigen.E2()))
	);

	return M_GEO Entity_Box2d
	(
		Centre.X() - Dx,
		Centre.X() + Dx,
		Centre.Y() - Dy,
		Centre.Y() + Dy
	);
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_FullIntAnIso::Integrand(const Geom_Pnt2d & Point, const Geom_Pnt2d & Vector) const
{
	return (1.0 / ElementSize(Point))*
		sqrt
		(
			M_GEO DotProduct(Vector, M_GEO Geometry_Tools::Mul(theMetricMap_->MetricAt(Point), Vector))
		);
}

inline 
Standard_Real AutLib::MeshLib::SizeMap2d_FullIntAnIso::MetricIntegrand(const Geom_Pnt2d & Point, const Geom_Pnt2d & Vector) const
{
	return
		sqrt
		(
			M_GEO DotProduct(Vector, M_GEO Geometry_Tools::Mul(theMetricMap_->MetricAt(Point), Vector))
		);
}

inline
Standard_Real AutLib::MeshLib::SizeMap2d_FullIntAnIso::ElementQuality
(
	const Geom_Pnt2d & theP0,
	const Geom_Pnt2d & theP1,
	const Geom_Pnt2d & theP2,
	const Mesh2d_QualityMap & theQualityMap
) const
{
	return theMetricMap_->ElementQuality(theP0, theP1, theP2, theQualityMap);
}

inline 
Geom_Pnt2d AutLib::MeshLib::SizeMap2d_FullIntAnIso::CorrectPoint
(
	const Geom_Pnt2d & theCentre,
	const Geom_Pnt2d & P
) const
{
	const Standard_Real Xmin = theBoundingBox_.Xmin();
	const Standard_Real Xmax = theBoundingBox_.Xmax();
	const Standard_Real Ymin = theBoundingBox_.Ymin();
	const Standard_Real Ymax = theBoundingBox_.Ymax();

	Geom_Pnt2d DU = P - theCentre;

	Standard_Real tx = 1;
	Standard_Real ty = 1;

	if (P.X() > Xmax) tx = (Xmax - theCentre.X()) / (P.X() - theCentre.X());
	else if (P.X() < Xmin) tx = (Xmin - theCentre.X()) / (P.X() - theCentre.X());

	if (P.Y() > Ymax) ty = (Ymax - theCentre.Y()) / (P.Y() - theCentre.Y());
	else if (P.Y() < Ymin) ty = (Ymin - theCentre.Y()) / (P.Y() - theCentre.Y());

	Standard_Real t = MIN(tx, ty);
	DU *= (1.0 - EPS6)*t;

	Geom_Pnt2d N = theCentre + DU;
	if (NOT INSIDE(N.X(), Xmin, Xmax)) N.X() = MAX(Xmin, MIN(N.X(), Xmax));
	if (NOT INSIDE(N.Y(), Ymin, Ymax)) N.Y() = MAX(Ymin, MIN(N.Y(), Ymax));

	MOVE(N);
}