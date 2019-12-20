#include <Entity_Eigen2d.hxx>

#include <Numeric_Eigen.hxx>
#include <Entity_Metric1.hxx>
#include <IO_Tecplot.hxx>
#include <Armadillo.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace NumLib;
using namespace IoLib;

AutLib::GeoLib::Entity_Eigen2d::Entity_Eigen2d()
	: IsDone_(Standard_False)
{
}

void AutLib::GeoLib::Entity_Eigen2d::CalcEigen(const Entity_Metric1 & M)
{
	TColStd_Ary2dOfReal eigvec(2, 2);
	TColStd_Ary1dOfReal eigval(2);

	eigvec.Init(0);
	eigval.Init(0);

	Numeric_Eigen::CalcEigen(M.GetMatrix(), eigval, eigvec, 1.0E-6);

	theE1_.X() = eigvec[0][0];
	theE1_.Y() = eigvec[1][0];

	theE2_.X() = eigvec[0][1];
	theE2_.Y() = eigvec[1][1];

	theLamda1_ = eigval[0];
	theLamda2_ = eigval[1];

	theH1_ = 1.0 / sqrt(theLamda1_);
	theH2_ = 1.0 / sqrt(theLamda2_);

	IsDone_ = Standard_True;

	/*mat22 A = M.GetArma();
	
	cx_vec2 eigval;
	cx_mat22 eigvec;

	eig_gen(eigval, eigvec, A);

	theE1_.X() = eigvec(0, 0).real();
	theE1_.Y() = eigvec(1, 0).real();

	theE2_.X() = eigvec(0, 1).real();
	theE2_.Y() = eigvec(1, 1).real();

	theLamda1_ = eigval[0].real();
	theLamda2_ = eigval[1].real();

	theH1_ = 1.0 / sqrt(theLamda1_);
	theH2_ = 1.0 / sqrt(theLamda2_);*/
}

//void AutLib::GeoLib::Entity_Eigen2d::CalcGenEigen(const Entity_Metric1 & A, const Entity_Metric1 & B)
//{
//	TColStd_Ary2dOfReal eigvec(2, 2);
//	TColStd_Ary1dOfReal eigval(2);
//
//	eigvec.Init(0);
//	eigval.Init(0);
//
//	Numeric_Eigen::CalcGenEigen(A.GetMatrix(), B.GetMatrix(), eigval, eigvec, 1.0E-6);
//
//	theE1_.X() = eigvec[0][0];
//	theE1_.Y() = eigvec[1][0];
//
//	theE2_.X() = eigvec[0][1];
//	theE2_.Y() = eigvec[1][1];
//
//	theLamda1_ = eigval[0];
//	theLamda2_ = eigval[1];
//
//	theH1_ = 1.0 / sqrt(theLamda1_);
//	theH2_ = 1.0 / sqrt(theLamda2_);
//
//	IsDone_ = Standard_True;
//}

void AutLib::GeoLib::Entity_Eigen2d::ExportToPlt(fstream & File) const
{
	IO_TecPlot::ExportMetric(theH1_, theH2_, theE1_, theE2_, Geom_Pnt2d(), File);
}

void AutLib::GeoLib::Entity_Eigen2d::ExportToPlt(const Geom_Pnt2d & Centre, fstream & File) const
{
	IO_TecPlot::ExportMetric(theH1_, theH2_, theE1_, theE2_, Centre, File);
}

void AutLib::GeoLib::Entity_Eigen2d::Print(Standard_OStream & Ostream) const
{
	Ostream << "E1 = " << theE1_ << "\n";
	Ostream << "E2 = " << theE2_ << "\n";

	Ostream << "H1 = " << theH1_ << "\n";
	Ostream << "H2 = " << theH2_ << "\n";
}