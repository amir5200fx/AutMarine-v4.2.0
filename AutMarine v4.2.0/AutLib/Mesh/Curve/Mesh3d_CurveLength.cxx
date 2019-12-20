#include <Mesh3d_CurveLength.hxx>

#include <Mesh3d_CurveIntegrand.hxx>
#include <Mesh3d_CurveIntegrandTools.hxx>
#include <Numeric_AdptIntegral.hxx>

Standard_Real AutLib::MeshLib::Mesh3d_CurveLength::Length
(
	const Mesh3d_CurveIntegrand & Integrand,
	const Standard_Real Tolerance
)
{
	Debug_Null_Pointer(Integrand.Curve());

	Get_Const_Object(Curve) = *Integrand.Curve();

	Standard_Real CurveLength;

	CurveLength = Mesh3d_CurveLength::Length
	(
		Integrand,
		Integrand.FirstParameter(),
		Integrand.LastParameter(),
		Tolerance
	);

	return CurveLength;
}

Standard_Real AutLib::MeshLib::Mesh3d_CurveLength::Length
(
	const Mesh3d_CurveIntegrand & Integrand,
	const Standard_Real Lower,
	const Standard_Real Upper, 
	const Standard_Real Tolerance
)
{
	M_NUMER Numeric_AdptIntegral<Mesh3d_CurveIntegrand>
		Integral
		(
			&Integrand,
			&Mesh3d_CurveIntegrandTools::Integrand,
			Lower,
			Upper,
			Tolerance
		);

	Integral.Perform();

	Debug_If_Condition_Message(NOT Integral.IsDone(), " Integral not performed");

	if (NOT Integral.IsConverged())
	{
		THROW_STANDARD_EXCEPTION(" Integral not converged");
	}

	return Integral.Result();
}