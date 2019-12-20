#include <SizeMap3d_FullIntBackSize.hxx>

#include <Numeric_AdptIntegral.hxx>
#include <Mesh3d_UnitLineIntegrand.hxx>
#include <Mesh3d_LineIntegrand.hxx>

using namespace AutLib;
using namespace NumLib;

static const Standard_Real DEFAULT_TOLERANCE = 0.1;
static const Standard_Integer DEFAULT_MAXITERS = 15;

#define GET_MAXITERS Integral.MaxNbIterations()
#define GET_CURRENT_TOLERANCE 0

AutLib::MeshLib::SizeMap3d_FullIntBackSize::SizeMap3d_FullIntBackSize
(
	const Standard_Real BaseSize,
	const M_GEO GeoMesh_BackGroundMesh3d & BackGround
)
	: SizeMap3d_StdBackSize(BaseSize, BackGround)
	, theTolerance_(DEFAULT_TOLERANCE)
	, theMaxIters_(DEFAULT_MAXITERS)
{
}

Standard_Real AutLib::MeshLib::SizeMap3d_FullIntBackSize::CalcUnitDistance
(
	const Geom_Pnt3d & P1,
	const Geom_Pnt3d & P2
) const
{
	Mesh3d_UnitLineIntegrand Integrand(P1, P2, this);

	Numeric_AdptIntegral<Mesh3d_UnitLineIntegrand>
		Integral
		(
			&Integrand,
			&Mesh3d_UnitLineIntegrand::Integrand,
			ZERO,
			ONE,
			theTolerance_
		);

	Integral.Perform();

	Debug_If_Condition_Message(NOT Integral.IsDone(), " Integral NOT Performed");

	if (NOT Integral.IsConverged())
	{
		THROW_NONCONVERGENCY_ITERATION_EXCEPTION(" Error in CalcDistance: Integral not converged");
	}

	return Integral.Result();
}

void AutLib::MeshLib::SizeMap3d_FullIntBackSize::SetInnerIteration(const Standard_Integer NbIterations)
{
	theMaxIters_ = NbIterations;
}