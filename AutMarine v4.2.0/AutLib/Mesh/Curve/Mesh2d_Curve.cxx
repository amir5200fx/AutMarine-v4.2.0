#include <Mesh2d_Curve.hxx>

#include <Cad3d_CurveOnPlane.hxx>
#include <Cad2d_CurveOnPlane.hxx>
#include <Mesh2d_CurveIntegrand.hxx>
#include <Mesh2d_CurveLength.hxx>
#include <Mesh2d_CurveIterationTools.hxx>
#include <Mesh2d_SizeMap.hxx>
#include <Geometry_Tools.hxx>
#include <Geom2d_Curve.hxx>
#include <Entity_EdgeIndexTools.hxx>
#include <TColGeom_Ary1dOfPnt2d.hxx>

static const Standard_Real UnderRelaxationFactor = 0.85;
static const Standard_Real Tolerance = 1.0E-9;
static const Standard_Real DEFAULT_INIT_TOLERANCE = 0.05;
static const Standard_Real DEFAULT_MAX_TOLERANCE = 1.0E-5;
static const Standard_Integer DEFAULT_NB_CORRECTION = 5;
static const Standard_Integer DEFAULT_MAX_LEVELS = 10;

#define HANDLE_NONCONVERGENCY_ITERATION U1=Guess;/*\
  if(x.resolution_>DEFAULT_MAX_TOLERANCE)  \
    U1 = CorrectGuess(U0, Guess, DEFAULT_MAX_TOLERANCE, Integrand, DEFAULT_NB_CORRECTION);*/

AutLib::MeshLib::Mesh2d_Curve::Mesh2d_Curve
(
	const Mesh2d_SizeMap & SizeMap,
	const Global_Handle(M_CAD Cad2d_CurveOnPlane) theCurve
)
	: theMap_(&SizeMap)
	, theUnderRelaxation_(UnderRelaxationFactor)
	, IsDone_(Standard_False)
{
	theCurve_ = theCurve->Curve();
	theFirst_ = theCurve->FirstParameter();
	theLast_ = theCurve->LastParameter();
}

AutLib::MeshLib::Mesh2d_Curve::Mesh2d_Curve
(
	const Mesh2d_SizeMap & SizeMap,
	const Global_Handle(M_CAD Cad3d_CurveOnPlane) theCurve
)
	: theMap_(&SizeMap)
	, theUnderRelaxation_(UnderRelaxationFactor)
	, IsDone_(Standard_False)
{
	theCurve_ = theCurve->Curve();
	theFirst_ = theCurve->FirstParameter();
	theLast_ = theCurve->LastParameter();
}

AutLib::MeshLib::Mesh2d_Curve::Mesh2d_Curve
(
	const Mesh2d_SizeMap & SizeMap,
	const Global_Handle(Geom2d_Curve) Curve,
	const Standard_Real First,
	const Standard_Real Last
)
	: theMap_(&SizeMap)
	, theCurve_(Curve)
	, theFirst_(First)
	, theLast_(Last)
	, theUnderRelaxation_(UnderRelaxationFactor)
	, IsDone_(Standard_False)
{
}

AutLib::MeshLib::Mesh2d_Curve::~Mesh2d_Curve()
{
}

const M_GEO Entity_StaticChain2d & AutLib::MeshLib::Mesh2d_Curve::Chain() const
{
	return theChain_;
}

Standard_Boolean AutLib::MeshLib::Mesh2d_Curve::IsDone() const
{
	return IsDone_;
}

void AutLib::MeshLib::Mesh2d_Curve::SetRelaxation(const Standard_Real Factor)
{
	theUnderRelaxation_ = Factor;
}

namespace AutLib
{
	namespace MeshLib
	{

		static Standard_Real CorrectGuess(const Standard_Real U0, const Standard_Real Guess, const Standard_Real theUmin, const Standard_Real theUmax, const Standard_Real Tol, const Mesh2d_CurveIntegrand& Integrand, const Standard_Integer NbLevels)
		{
			Get_Const_Object(Map) = *Integrand.Map();
			Get_Const_Object(Curve) = *Integrand.Curve();

			Standard_Real Correct = Guess;
			Geom_Pnt2d P0 = Curve.Value(U0);

			forThose
			(
				Index,
				1,
				NbLevels
			)
			{
				Standard_Real Dis = Map.CalcUnitDistance(P0, Curve.Value(Correct));
				Correct = U0 + (Correct - U0) / Dis;
				
				if (Correct < theUmin) Correct = theUmin;
				if (Correct > theUmax) Correct = theUmax;

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
		static Standard_Real CalcLength(const Mesh2d_CurveIntegrand& Integrand, const Standard_Real Tolerance, const Standard_Integer Current, const Standard_Integer MaxLevels)
		{
			try { return Mesh2d_CurveLength::Length(Integrand, Tolerance); }
			catch (NonConvergency_Iteration_Failure &x)
			{
				if (Current > MaxLevels) THROW_STANDARD_EXCEPTION("Can not Calculate length of the curve");
				return 
					CalcLength
					(
						Mesh2d_CurveIntegrand
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
						Mesh2d_CurveIntegrand
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

		static Standard_Real CalcLength(const Mesh2d_CurveIntegrand& Integrand, const Standard_Real Tolerance)
		{
			return CalcLength(Integrand, Tolerance, 0, DEFAULT_MAX_LEVELS);
		}
	}
}

void AutLib::MeshLib::Mesh2d_Curve::Perform()
{
	Debug_Null_Pointer(theCurve_);
	Debug_Null_Pointer(theMap_);
	Get_Const_Object(Curve) = *theCurve_;

	Mesh2d_CurveIntegrand Integrand(theMap_, theCurve_.get(), theFirst_, theLast_);
	Standard_Real CurveLength;

	// Determine the Length of the curve under the current space function
	Try_Exception_Handle_Exit(CurveLength = CalcLength(Integrand, Tolerance));

	// uniform nb. of segment under the current space function
	Standard_Integer NbSegments = MAX(M_GEO Geometry_Tools::Round(CurveLength*(1.0 + EPS6)), M_GEO Geometry_Tools::Round(CurveLength*(1.0 - EPS6)));

	// There must be atleast one segment
	if (NbSegments < 1) NbSegments = 1;

	Debug_If_Condition(NbSegments < 1);

	const Standard_Real Ds = CurveLength / (Standard_Real)NbSegments;
	const Standard_Real dt = 1.0 / CurveLength;
	Standard_Real U0, U1, Guess;
	TColStd_Ary1dOfReal Parameters(NbSegments + 1);

	Parameters.First() = theFirst_;
	Parameters.Last() = theLast_;
	
	U0 = Parameters.First();
	Guess = U0 + dt;  // Debug: 4/14/2018

	if (Guess < theFirst_) Guess = theFirst_;
	if (Guess > theLast_) Guess = theLast_;

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
			theFirst_,
			theLast_,
			DEFAULT_INIT_TOLERANCE,
			Integrand,
			DEFAULT_NB_CORRECTION
		);

		Try_Exception_Handle_Non_Convergency_Iteration
		(
			U1 = M_MESH Mesh2d_CurveIterationTools::Iteration
			(
				U0,
				Guess, 
				Ds,
				Integrand
			)
		);

		if (NOT INSIDE(U1, theFirst_, theLast_))
		{
			CloseProgram("Invalid Parameter");
		}

		Parameters.SetValue(Index, U1);
		Guess = U1 + MIN(dt, theUnderRelaxation_*(Parameters[Index] - Parameters[Index - 1]));

		Debug_If_Condition(Guess <= U1);

		U0 = U1;
	}

	MakeChain(Parameters);	
	IsDone_ = Standard_True;
}

void AutLib::MeshLib::Mesh2d_Curve::ExportToPlt(fstream & File) const
{
	theChain_.ExportToPlt(File);
}

void AutLib::MeshLib::Mesh2d_Curve::MakeChain(const TColStd_Ary1dOfReal & Parameters)
{
	Debug_Null_Pointer(theCurve_);

	Get_Const_Object(Curve) = *theCurve_;

	TColGeom_Ary1dOfPnt2d Points(Parameters.Size());

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