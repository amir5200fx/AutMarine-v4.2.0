#pragma once
#include <Geometry_Distance.hxx>

inline
Geom_Pnt2d AutLib::MeshLib::SizeMap2d_FullIntAnIsoRefineSearch::CalcOptimumPoint
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
	Geom_Pnt2d Pn(Centre.X() + U(0), Centre.Y() + U(1));

	Get_Const_Object(P0) = Edge.Node(0)->Coord();
	Get_Const_Object(P1) = Edge.Node(1)->Coord();

	if (NOT M_GEO Geometry_Tools::IsPointInsideOnBox(P, theBoundingBox_.Xmin(), theBoundingBox_.Xmax(), theBoundingBox_.Ymin(), theBoundingBox_.Ymax()))
	{
		P = CorrectPoint(Centre, P);
	}

	if (NOT M_GEO Geometry_Tools::IsPointInsideOnBox(Pn, theBoundingBox_.Xmin(), theBoundingBox_.Xmax(), theBoundingBox_.Ymin(), theBoundingBox_.Ymax()))
	{
		Pn = CorrectPoint(Centre, Pn);
	}

	Standard_Real D0 = M_GEO Geometry_Distance::Distance(Centre, Pn, theCurrentMetric_);
	Standard_Real Omega = 0.95;
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
		//P = 0.5*(Pa + Pb);

		if (NOT M_GEO Geometry_Tools::IsPointInsideOnBox(P, theBoundingBox_.Xmin(), theBoundingBox_.Xmax(), theBoundingBox_.Ymin(), theBoundingBox_.Ymax()))
		{
			P = CorrectPoint(Centre, P);
		}

		if (ABS(1.0 - D1) < 0.01 AND ABS(1.0 - D2) < 0.01) break;
	}

	//Standard_Real Dis;
	
	/*forThose
	(
		Iter,
		1,
		theMaxIters_
	)
	{
		Try_Exception_Handle_Exit(Dis = 1.155*CalcUnitDistance(Centre, P));
		cout << Dis << endl;
		P = Centre + Omega*(P - Centre) / Dis;

		if (NOT M_GEO Geometry_Tools::IsPointInsideOnBox(P, theBoundingBox_.Xmin(), theBoundingBox_.Xmax(), theBoundingBox_.Ymin(), theBoundingBox_.Ymax()))
		{
			P = CorrectPoint(Centre, P);
		}

		if (ABS(1.0 - Dis) < 0.01) break;
	}
	PAUSE;*/
	Standard_Real D1 = M_GEO Geometry_Distance::Distance(Centre, P, theMetricMap_->MetricAt(P));

	theCorrectionFactor_ = MIN(MAX(1.0, D1 / D0), 5.0);

	MOVE(P);
}

inline 
M_GEO Entity_Box2d AutLib::MeshLib::SizeMap2d_FullIntAnIsoRefineSearch::CalcSearchRegion
(
	const Standard_Real Radius,
	const Geom_Pnt2d & Centre, 
	const Mesh2d_Edge & Edge
) const
{
	M_GEO Entity_Eigen2d Eigen;
	Eigen.CalcEigen(theCurrentMetric_);

	Standard_Real radius = Radius*theCorrectionFactor_;

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