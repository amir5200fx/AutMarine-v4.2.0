#include <SizeMap2d_FullIntAnIso.hxx>

#include <Geometry_Distance.hxx>
#include <Numeric_AdptIntegral.hxx>
#include <Mesh2d_UnitLineIntegrand.hxx>
#include <Mesh2d_LineIntegrand.hxx>
#include <Mesh2d_QualityMap.hxx>
#include <IO_Tecplot.hxx>

using namespace AutLib;
using namespace GeoLib;

static const Standard_Real DEFAULT_TOLERANCE = 0.01;
static const Standard_Integer DEFAULT_MAXITERS = 50;

AutLib::MeshLib::SizeMap2d_FullIntAnIso::SizeMap2d_FullIntAnIso
(
	const Global_Handle(Mesh2d_SizeMap) theSizeMap,
	const Global_Handle(Mesh2d_MetricMap) theMetricMap
)
	: theSizeMap_(theSizeMap)
	, theMetricMap_(theMetricMap)
	, theTolerance_(DEFAULT_TOLERANCE)
	, theMaxIters_(DEFAULT_MAXITERS)
{
	theBoundingBox_ = theMetricMap_->BoundingBox();
}

void AutLib::MeshLib::SizeMap2d_FullIntAnIso::SetMetric(const Global_Handle(Mesh2d_MetricMap) theMetricMap)
{
	theMetricMap_ = theMetricMap;
}

Standard_Real AutLib::MeshLib::SizeMap2d_FullIntAnIso::CalcUnitDistance
(
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2
) const
{
	Mesh2d_UnitLineIntegrand Integrand(P1, P2, this);

	M_NUMER Numeric_AdptIntegral<Mesh2d_UnitLineIntegrand>
		Integral
		(
			&Integrand,
			&Mesh2d_UnitLineIntegrand::Integrand,
			ZERO,
			ONE,
			theTolerance_
		);

	Integral.SetInitIter(4);
	Integral.Perform();

	Debug_If_Condition_Message(NOT Integral.IsDone(), " Integral NOT Performed");

	if (NOT Integral.IsConverged())
	{
		cout << " Warning in CalcDistance: Integral not converged" << endl;
		//CloseProgram(" Error in CalcDistance: Integral not converged");
	}

	return Integral.Result();
}

Standard_Real AutLib::MeshLib::SizeMap2d_FullIntAnIso::CalcDistance
(
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2
) const
{
	Mesh2d_LineIntegrand Integrand(P1, P2, this);

	M_NUMER Numeric_AdptIntegral<Mesh2d_LineIntegrand>
		Integral
		(
			&Integrand,
			&Mesh2d_LineIntegrand::Integrand,
			ZERO,
			ONE,
			theTolerance_
		);

	Integral.SetInitIter(4);
	Integral.Perform();

	Debug_If_Condition_Message(NOT Integral.IsDone(), " Integral NOT Performed");

	if (NOT Integral.IsConverged())
	{
		cout << " Warning in CalcDistance: Integral not converged" << endl;
		//CloseProgram(" Error in CalcDistance: Integral not converged");
	}

	return Integral.Result();
}

void AutLib::MeshLib::SizeMap2d_FullIntAnIso::ExportSearchingAreaToPlt
(
	const Standard_Real Size,
	const Geom_Pnt2d & Point,
	fstream & File
) const
{
	M_IO IO_TecPlot::ExportBox(SizeMap2d_FullIntAnIso::CalcSearchRegion(Size, Point), File);
}