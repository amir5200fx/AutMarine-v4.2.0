#include <Mesh3d_Curve.hxx>

#include <Mesh3d_SizeMap.hxx>
#include <Mesh3d_CurveIntegrand.hxx>
#include <Mesh3d_CurveLength.hxx>
#include <Mesh3d_CurveIterationTools.hxx>
#include <Cad3d_CurveOnSurface.hxx>
#include <Entity_EdgeIndexTools.hxx>
#include <Geometry_Tools.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>

static const Standard_Real DEFAULT_UnderRelaxationFactor = 0.85;
static const Standard_Real DEFAULT_Tolerance = 1.0E-8;
static const Standard_Real DEFAULT_INIT_TOLERANCE = 0.05;
static const Standard_Integer DEFAULT_MAX_LEVELS = 10;
static const Standard_Integer DEFAULT_NB_CORRECTION = 5;

#include <Geom_Curve.hxx>

AutLib::MeshLib::Mesh3d_Curve::Mesh3d_Curve
(
	const Mesh3d_SizeMap & theSizeMap, 
	const CadLib::Cad3d_CurveOnSurface & theCurve
)
	: theMap_(theSizeMap)
	, theCurve_(theCurve)
	, theUnderRelaxation_(DEFAULT_UnderRelaxationFactor)
	, IsDone_(Standard_False)
{
}

void AutLib::MeshLib::Mesh3d_Curve::SetUnderRelaxation(const Standard_Real Factor)
{
	theUnderRelaxation_ = Factor;
}

namespace AutLib
{
	namespace MeshLib
	{

		static Standard_Real CorrectGuess(const Standard_Real U0, const Standard_Real Guess, const Standard_Real Tol, const Mesh3d_CurveIntegrand& Integrand, const Standard_Integer NbLevels)
		{
			Get_Const_Object(Map) = *Integrand.Map();
			Get_Const_Object(Curve) = *Integrand.Curve();

			Standard_Real Correct = Guess;
			Geom_Pnt3d P0 = Curve.Value(U0);

			forThose
			(
				Index,
				1,
				NbLevels
			)
			{
				Standard_Real Dis = Map.CalcUnitDistance(P0, Curve.Value(Correct));

				Correct = U0 + (Correct - U0) / Dis;
				if (ABS(1.0 - Dis) < Tol) break;
			}
			return Correct;
		}
	}
}

namespace AutLib
{
	namespace MeshLib
	{
		static Standard_Real CalcLength(const Mesh3d_CurveIntegrand& Integrand, const Standard_Real Tolerance, const Standard_Integer Current, const Standard_Integer MaxLevels)
		{
			try { return Mesh3d_CurveLength::Length(Integrand, Tolerance); }
			catch (NonConvergency_Iteration_Failure &x)
			{
				if (Current > MaxLevels) THROW_STANDARD_EXCEPTION("Can not Calculate length of the curve");
				return
					CalcLength
					(
						Mesh3d_CurveIntegrand
						(
							Integrand.Map(),
							Integrand.Curve(),
							Integrand.FirstParameter(),
							MEAN(Integrand.FirstParameter(), Integrand.LastParameter())
						),
						Tolerance,
						Current + 1,
						MaxLevels
					)
					+
					CalcLength
					(
						Mesh3d_CurveIntegrand
						(
							Integrand.Map(),
							Integrand.Curve(),
							MEAN(Integrand.FirstParameter(), Integrand.LastParameter()),
							Integrand.LastParameter()
						),
						Tolerance,
						Current + 1,
						MaxLevels
					);
			}
		}

		static Standard_Real CalcLength(const Mesh3d_CurveIntegrand& Integrand, const Standard_Real Tolerance)
		{
			return CalcLength(Integrand, Tolerance, 0, DEFAULT_MAX_LEVELS);
		}
	}
}

void AutLib::MeshLib::Mesh3d_Curve::Perform()
{
	Mesh3d_CurveIntegrand Integrand(&theMap_, theCurve_.Curve().get(), theCurve_.FirstParameter(), theCurve_.LastParameter());
	Standard_Real CurveLength;

	// Determine the Length of the curve under the current space function
	Try_Exception_Handle_Exit(CurveLength = Mesh3d_CurveLength::Length(Integrand, DEFAULT_Tolerance));

	THROW_STANDARD_EXCEPTION_IF(CurveLength < EPS12, " The NULL length curve encontred!");

	// uniform nb. of segment under the current space function
	Standard_Integer NbSegments = MIN(M_GEO Geometry_Tools::Round(CurveLength*(1.0 + EPS6)), M_GEO Geometry_Tools::Round(CurveLength*(1.0 - EPS6)));

	// There must be atleast one segment
	if (NbSegments < 1) NbSegments = 1;

	Debug_If_Condition(NbSegments < 1);

	const Standard_Real Ds = CurveLength / (Standard_Real)NbSegments;
	const Standard_Real dt = 1.0 / CurveLength;

	Standard_Real U0, U1, Guess;
	TColStd_Ary1dOfReal Parameters(NbSegments + 1);

	Parameters.First() = theCurve_.FirstParameter();
	Parameters.Last() = theCurve_.LastParameter();
	U0 = Parameters.First();
	Guess = U0 + dt;

	forThose
	(
		Index,
		1,
		NbSegments - 1
	)
	{
		Guess = CorrectGuess
		(
			U0,
			Guess,
			DEFAULT_INIT_TOLERANCE,
			Integrand,
			DEFAULT_NB_CORRECTION
		);

		Try_Exception_Handle_Exit
		(
			U1 = M_MESH Mesh3d_CurveIterationTools::Iteration
			(
				U0,
				Guess,
				Ds,
				Integrand
			)
		);

		Parameters.SetValue(Index, U1);

		Guess = U1 + MIN(dt, theUnderRelaxation_*(Parameters[Index] - Parameters[Index - 1]));

		Debug_If_Condition(Guess <= U1);

		U0 = U1;
	}

	MakeChain(Parameters);

	IsDone_ = Standard_True;
}

void AutLib::MeshLib::Mesh3d_Curve::ExportToPlt(fstream & File) const
{
	theChain_.ExportToPlt(File);
}

void AutLib::MeshLib::Mesh3d_Curve::MakeChain(const TColStd_Ary1dOfReal & Parameters)
{
	TColGeom_Ary1dOfPnt3d Points(Parameters.Size());

	Get_Const_Object(Curve) = *theCurve_.Curve().get();
	forThose
	(
		Index,
		0,
		MaxIndexOf(Points)
	)
	{
		Curve.D0(Parameters[Index], Points[Index]);
	}

	theChain_.SetCoords(Points);
	theChain_.SetEdges(M_GEO Entity_EdgeIndexTools::OrderedList(MaxIndexOf(Points)));
	theChain_.SetCycle(Curve.IsClosed());
}