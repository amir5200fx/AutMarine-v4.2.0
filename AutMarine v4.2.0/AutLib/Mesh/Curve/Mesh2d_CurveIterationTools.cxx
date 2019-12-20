#include "Mesh2d_CurveIterationTools.hxx"

#include <Geom2d_Curve.hxx>
#include <Mesh2d_CurveIntegrand.hxx>
#include <Mesh2d_CurveIntegrandTools.hxx>
#include <Mesh2d_CurveLength.hxx>
#include <Numeric_NewtonIter.hxx>
#include <Standard_OStream.hxx>

static const Standard_Real Tolerance = 1.0E-8;
static const Standard_Real UnderRelaxationFactor = 0.85;

#define GET_MAXITERS Newton.NbIterated()
#define GET_CURRENT_TOLERANCE Newton.Residual()

inline 
Standard_Real IterValueAt
(
	const Standard_Real X,
	const M_MESH Mesh2d_CurveIteration& CurveIteration
)
{
	Standard_Real Length;
	Try_Exception_Handle_Exit
	(
		Length = M_MESH Mesh2d_CurveLength::Length
		(
			*CurveIteration.Integrand(),
			CurveIteration.Start(),
			X,
			CurveIteration.Tolerance()
		) - CurveIteration.Step();
	);
	return Length;
}

inline 
Standard_Real IterDeriveAt
(
	const Standard_Real X,
	const M_MESH Mesh2d_CurveIteration& CurveIteration
)
{
	Standard_Real Result;
	Try_Exception_Handle_Exit
	(
		Result = M_MESH Mesh2d_CurveIntegrandTools::Integrand
		(
			X,
			*CurveIteration.Integrand()
		)
	);
	return Result;
}

Standard_Real AutLib::MeshLib::Mesh2d_CurveIterationTools::Iteration
(
	const Standard_Real Start,
	const Standard_Real Guess,
	const Standard_Real Step, 
	const Mesh2d_CurveIntegrand & CurveIntegrand
)
{
	Mesh2d_CurveIteration Iteration
	(
		&CurveIntegrand,
		Start,
		Step, 
		Tolerance
	);

	M_NUMER Numeric_NewtonIter<Mesh2d_CurveIteration>
		Newton
		(
			&Iteration,
			&IterValueAt,
			&IterDeriveAt,
			Tolerance
		);

	Newton.SetUnderRelaxation(UnderRelaxationFactor);
	Newton.Iterate(Guess);

	Debug_If_Condition_Message(NOT Newton.IsDone(), " Newton Algorithm is not performed");

	if (Newton.Condition() EQUAL M_NUMER NewtonIter_ZERODIVIDE)
	{
		THROW_STANDARD_EXCEPTION("Fatal Error: divide zero in Iterative function");
	}

	if (Newton.Condition() EQUAL M_NUMER NewtonIter_LEVEL_EXCEEDED)
	{
		THROW_NONCONVERGENCY_ITERATION_EXCEPTION("LEVEL EXCEEDED encontered in Iterative function");
		cout << "  Warning! LEVEL EXCEEDED encontered in Iterative function\n";
		cout << "  no. of MAX ITERATION = " << Newton.NbIterated() << "\n";
		cout << "  Residual = " << Newton.Residual() << "\n";
	}
	return Newton.Result();
}