#include <Entity_Metric1Tools.hxx>

#include <Armadillo.hxx>
#include <Entity_Eigen2d.hxx>

using namespace AutLib;
using namespace GeoLib;

Entity_Metric1 AutLib::GeoLib::Entity_Metric1Tools::CalcMetric
(
	const Standard_Real Lamda1,
	const Standard_Real Lamda2,
	const Geom_Pnt2d & E1, 
	const Geom_Pnt2d & E2
)
{
	mat22 H;
	H(0, 0) = Lamda1;
	H(1, 0) = H(0, 1) = 0;
	H(1, 1) = Lamda2;

	mat22 S;
	S(0, 0) = E1.X();
	S(1, 0) = E1.Y();
	S(0, 1) = E2.X();
	S(1, 1) = E2.Y();

	mat22 M = trans(S)*H*S;

	return Entity_Metric1(M(0, 0), M(0, 1), M(1, 1));
}

Entity_Metric1 AutLib::GeoLib::Entity_Metric1Tools::Avg(const Entity_Metric1 & M1, const Entity_Metric1 & M2)
{
	return Entity_Metric1(0.5*(M1.A() + M2.A()), 0.5*(M1.B() + M2.B()), 0.5*(M1.C() + M2.C()));
}

Entity_Metric1 AutLib::GeoLib::Entity_Metric1Tools::IntersectionSR
(
	const Entity_Metric1 & M1,
	const Entity_Metric1 & M2
)
{
	mat22 m1 = M1.GetArma();
	mat22 m2 = M2.GetArma();

	mat22 N1 = inv(m1)*m2;

	Entity_Metric1 N(N1(0, 0), N1(0, 1), N1(1, 1));

	Entity_Eigen2d Eigen;
	Eigen.CalcEigen(N);

	vec2 E1, E2;
	E1(0) = Eigen.E1().X();
	E1(1) = Eigen.E1().Y();
	E2(0) = Eigen.E2().X();
	E2(1) = Eigen.E2().Y();

	mat Lamda1 = trans(E1)*m1*E1;
	mat Lamda2 = trans(E2)*m1*E2;
	mat Mu1 = trans(E1)*m2*E1;
	mat Mu2 = trans(E2)*m2*E2;

	mat22 S;
	S(0, 0) = Eigen.E1().X();
	S(1, 0) = Eigen.E1().Y();
	S(0, 1) = Eigen.E2().X();
	S(1, 1) = Eigen.E2().Y();

	Entity_Eigen2d Eigen1, Eigen2;
	Eigen1.CalcEigen(M1);
	Eigen2.CalcEigen(M2);

	mat22 H;
	/*H(0, 0) = MAX(Eigen1.Lamda1(), Eigen2.Lamda1());
	H(1, 0) = H(0, 1) = 0;
	H(1, 1) = MAX(Eigen1.Lamda2(), Eigen2.Lamda2());*/
	H(0, 0) = MAX(Lamda1(0, 0), Mu1(0, 0));
	H(1, 0) = H(0, 1) = 0;
	H(1, 1) = MAX(Lamda2(0, 0), Mu2(0, 0));

	/*S = inv(S);
	S = trans(S)*H*S;*/

	S = inv(trans(S))*H*inv(S);

	return Entity_Metric1(S(0, 0), S(1, 0), S(1, 1));
}

Entity_Metric1 AutLib::GeoLib::Entity_Metric1Tools::IntersectionPD
(
	const Entity_Metric1 & M1,
	const Entity_Metric1 & M2
)
{
	Entity_Eigen2d Eigen1, Eigen2;
	Eigen1.CalcEigen(M1);
	Eigen2.CalcEigen(M2);

	Standard_Real Omega = MAX(1, MAX(Eigen2.Lamda1() / Eigen1.Lamda1(), Eigen2.Lamda2() / Eigen1.Lamda2()));

	return Entity_Metric1(M1*Omega);
}

//Entity_Metric1 AutLib::GeoLib::Entity_Metric1Tools::InterpolationSMR
//(
//	const Standard_Real t,
//	const Entity_Metric1 & M1, 
//	const Entity_Metric1 & M2
//)
//{
//	mat22 N1 = inv(M1.GetArma())*M2.GetArma();
//
//	Entity_Metric1 N(N1(0, 0), N1(0, 1), N1(1, 1));
//
//	Entity_Eigen2d Eigen;
//	Eigen.CalcEigen(N);
//
//	mat22 S;
//	S(0, 0) = Eigen.E1().X();
//	S(1, 0) = Eigen.E1().Y();
//	S(0, 1) = Eigen.E2().X();
//	S(1, 1) = Eigen.E2().Y();
//
//	Entity_Eigen2d Eigen1, Eigen2;
//	Eigen1.CalcEigen(M1);
//	Eigen2.CalcEigen(M2);
//
//	Standard_Real h1 = Eigen1.H1() + t*(Eigen2.H1() - Eigen1.H1());
//	Standard_Real h2 = Eigen1.H2() + t*(Eigen2.H2() - Eigen1.H2());
//
//	mat22 H;
//	H(0, 0) = 1.0 / (h1*h1);
//	H(1, 0) = H(0, 1) = 0;
//	H(1, 1) = 1.0 / (h2*h2);
//
//	S = inv(S);
//	S = trans(S)*H*S;
//
//	return Entity_Metric1(S(0, 0), S(1, 0), S(1, 1));
//}

Entity_Metric1 AutLib::GeoLib::Entity_Metric1Tools::InterpolationIM
(
	const Standard_Real t, 
	const Entity_Metric1 & M1,
	const Entity_Metric1 & M2
)
{
	mat22 m1 = inv(M1.GetArma());
	mat22 m2 = inv(M2.GetArma());

	mat22 M = inv((1.0 - t)*m1 + t*m2);

	return Entity_Metric1(M(0, 0), M(1, 0), M(1, 1));
}

Entity_Metric1 AutLib::GeoLib::Entity_Metric1Tools::InterpolationIM
(
	const Standard_Real c1, 
	const Standard_Real c2, 
	const Standard_Real c3, 
	const Entity_Metric1 & M1,
	const Entity_Metric1 & M2,
	const Entity_Metric1 & M3
)
{
	mat22 m1, m2, m3;
	Standard_Real C1, C2, C3;

	if (M1.Determinant() < EPS6)
	{
		m1.fill(0);
		C1 = 0;
	}
	else
	{
		m1 = inv(M1.GetArma());
		C1 = c1;
	}

	if (M2.Determinant() < EPS6)
	{
		m2.fill(0);
		C2 = 0;
	}
	else
	{
		m2 = inv(M2.GetArma());
		C2 = c2;
	}

	if (M3.Determinant() < EPS6)
	{
		m3.fill(0);
		C3 = 0;
	}
	else
	{
		m3 = inv(M3.GetArma());
		C3 = c3;
	}

	mat22 m = C1*m1 + C2*m2 + C3*m3;

	if (C1 == 0 AND C2 == 0 AND C3 == 0)
	{
		return Entity_Metric1(0, 0, 0);
	}

	mat22 M = inv(m);

	return Entity_Metric1(M(0, 0), M(1, 0), M(1, 1));
}