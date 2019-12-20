#include <Entity_Metric1.hxx>

#include <Entity_Eigen2d.hxx>
#include <Entity_Metric1Tools.hxx>
#include <Geom_Pnt2d.hxx>

using namespace AutLib;
using namespace GeoLib;

void AutLib::GeoLib::Entity_Metric1::ExportToPlt(fstream & File) const
{
	Entity_Eigen2d Eigen;
	Eigen.CalcEigen(*this);

	Eigen.ExportToPlt(File);
}

Geom_Pnt2d AutLib::GeoLib::Entity_Metric1::Multiplied(const Geom_Pnt2d & theU) const
{
	return Geom_Pnt2d(theA_*theU.X() + theB_*theU.Y(), theB_*theU.X() + theC_*theU.Y());
}

Entity_Metric1 AutLib::GeoLib::Entity_Metric1::SQRT() const
{
	Entity_Eigen2d Eigen;
	Eigen.CalcEigen(*this);

	Standard_Real Lamda1 = Eigen.Lamda1();
	Standard_Real Lamda2 = Eigen.Lamda2();

	Standard_Real A = sqrt(Lamda1);
	Standard_Real C = sqrt(Lamda2);

	const Geom_Pnt2d& E1 = Eigen.E1();
	const Geom_Pnt2d& E2 = Eigen.E2();

	return Entity_Metric1Tools::CalcMetric(A, C, E1, E2);
}

void AutLib::GeoLib::Entity_Metric1::ExportToPlt
(
	const Geom_Pnt2d & Centre, 
	fstream & File
) const
{
	Entity_Eigen2d Eigen;
	Eigen.CalcEigen(*this);

	Eigen.ExportToPlt(Centre, File);
}

void AutLib::GeoLib::Entity_Metric1::Print(Standard_OStream & Ostream) const
{
	Ostream << " A = " << theA_ << ", B = " << theB_ << ", C = " << theC_ << endl;
}