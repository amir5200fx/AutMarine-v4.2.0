#include <Mesh3d_CurveIterationTools.hxx>

#include <Mesh3d_CurveIteration.hxx>
#include <Mesh3d_CurveIntegrand.hxx>
#include <Mesh3d_CurveIntegrandTools.hxx>
#include <Mesh3d_CurveLength.hxx>
#include <Numeric_NewtonIter.hxx>

static const Standard_Real Tolerance = 1.0E-12;
static const Standard_Real UnderRelaxationFactor = 0.8;

namespace AutLib
{
	namespace MeshLib
	{

		inline static Standard_Real IterValueAt
		(
			const Standard_Real X,
			const Mesh3d_CurveIteration& CurveIteration
		)
		{
			Standard_Real Length;

			Try_Exception_Handle_Exit
			(
				Length = Mesh3d_CurveLength::Length
				(
					*CurveIteration.Integrand(),
					CurveIteration.Start(),
					X,
					CurveIteration.Tolerance()
				) - CurveIteration.Step();
			);

			return Length;
		}

		inline static Standard_Real IterDeriveAt
		(
			const Standard_Real X,
			const Mesh3d_CurveIteration& CurveIteration
		)
		{
			Standard_Real Result;

			Try_Exception_Handle_Exit
			(
				Result = Mesh3d_CurveIntegrandTools::Integrand
				(
					X,
					*CurveIteration.Integrand()
				)
			);

			return Result;
		}
	}
}

Standard_Real AutLib::MeshLib::Mesh3d_CurveIterationTools::Iteration
(
	const Standard_Real Start, 
	const Standard_Real Guess,
	const Standard_Real Step,
	const Mesh3d_CurveIntegrand & CurveIntegrand
)
{
	Mesh3d_CurveIteration Iteration
	(
		&CurveIntegrand,
		Start,
		Step,
		Tolerance
	);

	M_NUMER Numeric_NewtonIter<Mesh3d_CurveIteration>
		Newton
		(
			&Iteration,
			&IterValueAt,
			&IterDeriveAt,
			Tolerance
		);

	Newton.SetUnderRelaxation(UnderRelaxationFactor);

	Newton.Iterate(Guess);

	Debug_If_Condition_Message(NOT Newton.IsDone(), " Newton Algorithm not performed");

	if (Newton.Condition() EQUAL M_NUMER NewtonIter_ZERODIVIDE)
	{
		THROW_STANDARD_EXCEPTION("Fatal Error: divide zero in Iterative function");
	}

	if (Newton.Condition() EQUAL M_NUMER NewtonIter_LEVEL_EXCEEDED)
	{
		cout << "  Warning! LEVEL EXCEEDED encontered in Iterative function\n";
		cout << "  no. of MAX ITERATION = " << Newton.NbIterated() << "\n";
		cout << "  Residual = " << Newton.Residual() << "\n";
	}

	return Newton.Result();
}