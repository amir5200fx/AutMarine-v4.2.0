#include "Mesh2d_CurveLength.hxx"

#include <Global_Debug.hxx>
#include <Mesh2d_CurveIntegrand.hxx>
#include <Mesh2d_CurveIntegrandTools.hxx>
#include <Cad2d_CurveOnPlane.hxx>
#include <Numeric_AdptIntegral.hxx>

#define GET_MAXITERS  Integral.MaxNbIterations()
#define GET_CURRENT_TOLERANCE 0

Standard_Real AutLib::MeshLib::Mesh2d_CurveLength::Length
(
	const Mesh2d_CurveIntegrand & Integrand,
	const Standard_Real Tolerance
)
{
	Debug_Null_Pointer(Integrand.Curve());
	Get_Const_Object(Curve) = *Integrand.Curve();

	Standard_Real CurveLength;
	CurveLength = Mesh2d_CurveLength::Length
	(
		Integrand,
		Integrand.FirstParameter(),
		Integrand.LastParameter(),
		Tolerance
	);
	return CurveLength;
}

Standard_Real AutLib::MeshLib::Mesh2d_CurveLength::Length
(
	const Mesh2d_CurveIntegrand & Integrand, 
	const Standard_Real Lower, 
	const Standard_Real Upper,
	const Standard_Real Tolerance
)
{
	M_NUMER Numeric_AdptIntegral<Mesh2d_CurveIntegrand>
		Integral
		(
			&Integrand,
			&Mesh2d_CurveIntegrandTools::Integrand,
			Lower, 
			Upper,
			Tolerance
		);

	Integral.SetInitIter(4);
	Integral.Perform();
	
	Debug_If_Condition_Message(NOT Integral.IsDone(), " Integral not performed");
	
	if (NOT Integral.IsConverged())
	{
		THROW_NONCONVERGENCY_ITERATION_EXCEPTION("Integral not converged @ Mesh2d_CurveLength::Length()");
	}
	return Integral.Result();
}