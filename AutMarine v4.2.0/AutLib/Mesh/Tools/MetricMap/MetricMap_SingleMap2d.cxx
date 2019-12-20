#include <MetricMap_SingleMap2d.hxx>

#include <Armadillo.hxx>
#include <Mesh2d_QualityMap.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace MeshLib;

AutLib::MeshLib::MetricMap_SingleMap2d::MetricMap_SingleMap2d()
	: theM2_(1.0, 1.0, Geom_Pnt2d(1, 0), Geom_Pnt2d(0, 1))
{
	CalcMetric();
}

AutLib::MeshLib::MetricMap_SingleMap2d::MetricMap_SingleMap2d
(
	const Standard_Real theH1,
	const Standard_Real theH2,
	const gp_Dir2d & theE1,
	const gp_Dir2d & theE2
)
	: theM2_(theH1, theH2, theE1.XY(), theE2.XY())
{
	CalcMetric();
}

AutLib::MeshLib::MetricMap_SingleMap2d::MetricMap_SingleMap2d
(
	const Standard_Real theH1,
	const Standard_Real theH2,
	const gp_Dir2d & theE1,
	const gp_Dir2d & theE2, 
	const M_GEO Entity_Box2d & theBox
)
	: theM2_(theH1, theH2, theE1.XY(), theE2.XY())
{
	SetBoundingBox(theBox);

	CalcMetric();
}

void AutLib::MeshLib::MetricMap_SingleMap2d::Init
(
	const Standard_Real theH1,
	const Standard_Real theH2,
	const gp_Dir2d & theE1,
	const gp_Dir2d & theE2
)
{
	theM2_ = Entity_Metric2(theH1, theH1, theE1.XY(), theE2.XY());

	CalcMetric();
}

void AutLib::MeshLib::MetricMap_SingleMap2d::Init
(
	const Standard_Real theH1,
	const Standard_Real theH2, 
	const gp_Dir2d & theE1,
	const gp_Dir2d & theE2,
	const M_GEO Entity_Box2d & theBox
)
{
	theM2_ = Entity_Metric2(theH1, theH1, theE1.XY(), theE2.XY());

	SetBoundingBox(theBox);

	CalcMetric();
}

Standard_Real AutLib::MeshLib::MetricMap_SingleMap2d::ElementQuality
(
	const GeoLib::Geom_Pnt2d & theP0, 
	const GeoLib::Geom_Pnt2d & theP1,
	const GeoLib::Geom_Pnt2d & theP2,
	const Mesh2d_QualityMap & theQualityMap
) const
{
	Geom_Pnt2d Pm = (theP0 + theP1 + theP2) / (Standard_Real)3.0;

	Entity_Metric1 M = MetricAt(Pm).SQRT();

	Geom_Pnt2d U1 = theP1 - theP0;
	Geom_Pnt2d U2 = theP2 - theP0;

	U1 = M.Multiplied(U1);
	U2 = M.Multiplied(U2);

	Geom_Pnt2d P1 = theP0 + U1;
	Geom_Pnt2d P2 = theP0 + U2;

	return theQualityMap.CalcQuality(theP0, P1, P2);
}

void AutLib::MeshLib::MetricMap_SingleMap2d::SetH1(const Standard_Real theH1)
{
	theM2_.SetH1(theH1);

	CalcMetric();
}

void AutLib::MeshLib::MetricMap_SingleMap2d::SetH2(const Standard_Real theH2)
{
	theM2_.SetH2(theH2);

	CalcMetric();
}

void AutLib::MeshLib::MetricMap_SingleMap2d::SetE1(const gp_Dir2d & theE1)
{
	theM2_.SetE1(theE1.XY());

	CalcMetric();
}

void AutLib::MeshLib::MetricMap_SingleMap2d::SetE2(const gp_Dir2d & theE2)
{
	theM2_.SetE2(theE2.XY());

	CalcMetric();
}

void AutLib::MeshLib::MetricMap_SingleMap2d::CalcMetric()
{
	mat22 E;

	E(0, 0) = theM2_.E1().X();
	E(1, 0) = theM2_.E1().Y();
	E(0, 1) = theM2_.E2().X();
	E(1, 1) = theM2_.E2().Y();

	mat22 M;

	M(0, 1) = M(1, 0) = 0;
	M(0, 0) = 1.0 / (theM2_.H1()*theM2_.H1());
	M(1, 1) = 1.0 / (theM2_.H2()*theM2_.H2());

	M = (E*M)*trans(E);

	theM_ = Entity_Metric1(M(0, 0), M(0, 1), M(1, 1));
}