#include <SizeMap2d_FullIntBackSize.hxx>

#include <Numeric_AdptIntegral.hxx>
#include <Mesh2d_UnitLineIntegrand.hxx>
#include <Mesh2d_LineIntegrand.hxx>

using namespace AutLib;
using namespace NumLib;

static const Standard_Real DEFAULT_TOLERANCE = 0.1;
static const Standard_Integer DEFAULT_MAXITERS = 15;

#define GET_MAXITERS Integral.MaxNbIterations()
#define GET_CURRENT_TOLERANCE 0

AutLib::MeshLib::SizeMap2d_FullIntBackSize::SizeMap2d_FullIntBackSize
(
	const Standard_Real theBaseSize,
	const M_GEO GeoMesh_BackGroundMesh2d & BackGround
)
	: SizeMap2d_StdBackSize(theBaseSize, BackGround)
	, theTolerance_(DEFAULT_TOLERANCE)
	, theMaxIters_(DEFAULT_MAXITERS)
{
}

Standard_Real AutLib::MeshLib::SizeMap2d_FullIntBackSize::CalcUnitDistance
(
	const Geom_Pnt2d & P1,
	const Geom_Pnt2d & P2
) const
{
	Mesh2d_UnitLineIntegrand Integrand(P1, P2, this);

	Numeric_AdptIntegral<Mesh2d_UnitLineIntegrand>
		Integral
		(
			&Integrand,
			&Mesh2d_UnitLineIntegrand::Integrand,
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

void AutLib::MeshLib::SizeMap2d_FullIntBackSize::SetInnerIteration(const Standard_Integer NbIterations)
{
	theMaxIters_ = NbIterations;
}