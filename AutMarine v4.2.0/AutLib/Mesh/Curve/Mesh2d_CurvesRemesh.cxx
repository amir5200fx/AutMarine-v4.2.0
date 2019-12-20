#include <Mesh2d_CurvesRemesh.hxx>

#include <Mesh_VariationRate.hxx>
#include <Mesh2d_CurveIntegrand.hxx>
#include <Mesh2d_CurveLength.hxx>
#include <Mesh2d_CurveIterationTools.hxx>
#include <SizeMap2d_UniSize.hxx>
#include <SizeMap2d_ModifyBackSize.hxx>
#include <Entity_EdgeIndexTools.hxx>
#include <Entity_Box2dTools.hxx>
#include <Entity_Triangulation2d.hxx>
#include <Geom2d_Curve.hxx>
#include <Geom2dLProp_CLProps2d.hxx>
#include <Geom_Geometry.hxx>
#include <Geom_Pnt2d.hxx>
#include <Merge_Chain2d.hxx>
#include <Cad2d_CurveOnPlane.hxx>
//#include <Geom_PrQuadSingleObjectTree.hxx>
#include <Geom_BalancedPrQuadTree.hxx>
#include <TColEntity_HAry1dOfBox2d.hxx>
#include <TColEntity_HAry1dOfStaticChain2d.hxx>
#include <TColStd_Ary1dOfAry1dOfReal.hxx>
#include <TColGeom_HAry1dOfPnt2d.hxx>

static const Standard_Real DEFAULT_UnderRelaxationFactor = 0.85;
static const Standard_Real DEFAULT_Tolerance = 1.0E-8;
static const Standard_Real DEFAULT_MIN_SIZE = 0.1;
static const Standard_Real DEFAULT_SPAN_ANGLE = 15;
static const Standard_Real DEFAULT_ITERATION_TOL = 0.05;
static const Standard_Real DEFAULT_SMOOTHING_FACTOR = 0.5;
static const Standard_Real DEFAULT_INIT_TOLERANCE = 0.05;

static const Standard_Integer DEFAULT_MAX_ITERATIONS = 5;
static const Standard_Integer DEFAULT_MAX_NB_SMOOTHING = 3;
static const Standard_Integer DEFAULT_NB_CORRECTION = 5;
static const Standard_Integer DEFAULT_BUCKETSIZE = 2;

using namespace AutLib;
using namespace GeoLib;
using namespace CadLib;

AutLib::MeshLib::Mesh2d_CurvesRemesh::Mesh2d_CurvesRemesh(const M_CAD Cad2d_CurveOnPlane & theCurve)
	: theBaseSize_(0)
	, theMinSize_(DEFAULT_MIN_SIZE)
	, theMaxNbIterations_(DEFAULT_MAX_ITERATIONS)
	, theSpanAngle_(DEFAULT_SPAN_ANGLE)
	, IsDone_(Standard_False)
	, theUnderRelaxation_(DEFAULT_UnderRelaxationFactor)
	, theIterTolerance_(DEFAULT_ITERATION_TOL)
	, IsConverged_(Standard_False)
	, theSmoothingFactor_(DEFAULT_SMOOTHING_FACTOR)
	, theMaxNbSmoothing_(DEFAULT_MAX_NB_SMOOTHING)
	, theVariationRateInfo_(Mesh_VariationRateInfo_FAST)
{
	theCurve_.Resize(1);
	theCurve_.SetValue(0, (Global_Handle(Cad2d_CurveOnPlane))&theCurve);

	theDomain_ = theCurve.BoundingBox(EPS6);
}

AutLib::MeshLib::Mesh2d_CurvesRemesh::Mesh2d_CurvesRemesh
(
	const M_CAD Cad2d_CurveOnPlane & theCurve,
	const M_GEO Entity_Box2d & Domain
)
	: theBaseSize_(0)
	, theMinSize_(DEFAULT_MIN_SIZE)
	, theDomain_(Domain)
	, theMaxNbIterations_(DEFAULT_MAX_ITERATIONS)
	, theSpanAngle_(DEFAULT_SPAN_ANGLE)
	, IsDone_(Standard_False)
	, theUnderRelaxation_(DEFAULT_UnderRelaxationFactor)
	, theIterTolerance_(DEFAULT_ITERATION_TOL)
	, IsConverged_(Standard_False)
	, theSmoothingFactor_(DEFAULT_SMOOTHING_FACTOR)
	, theMaxNbSmoothing_(DEFAULT_MAX_NB_SMOOTHING)
	, theVariationRateInfo_(Mesh_VariationRateInfo_FAST)
{
	theCurve_.Resize(1);
	theCurve_.SetValue(0, (Global_Handle(Cad2d_CurveOnPlane))&theCurve);
}

AutLib::MeshLib::Mesh2d_CurvesRemesh::Mesh2d_CurvesRemesh
(
	const TColCad2d_HAry1dOfCurveOnPlane & Curves,
	const M_GEO Entity_Box2d & Domain
)
	: theBaseSize_(0)
	, theMinSize_(DEFAULT_MIN_SIZE)
	, theCurve_(Curves)
	, theDomain_(Domain)
	, theMaxNbIterations_(DEFAULT_MAX_ITERATIONS)
	, theSpanAngle_(DEFAULT_SPAN_ANGLE)
	, IsDone_(Standard_False)
	, theUnderRelaxation_(DEFAULT_UnderRelaxationFactor)
	, theIterTolerance_(DEFAULT_ITERATION_TOL)
	, IsConverged_(Standard_False)
	, theSmoothingFactor_(DEFAULT_SMOOTHING_FACTOR)
	, theMaxNbSmoothing_(DEFAULT_MAX_NB_SMOOTHING)
	, theVariationRateInfo_(Mesh_VariationRateInfo_FAST)
{
}

AutLib::MeshLib::Mesh2d_CurvesRemesh::Mesh2d_CurvesRemesh
(
	const TColCad2d_HAry1dOfCurveOnPlane & Curves,
	const M_GEO Entity_Box2d & Domain,
	const Standard_Real BaseSize, 
	const Standard_Real MinSize,
	const Standard_Real SpanAngle
)
	: theBaseSize_(BaseSize)
	, theMinSize_(MinSize)
	, theCurve_(Curves)
	, theDomain_(Domain)
	, theMaxNbIterations_(DEFAULT_MAX_ITERATIONS)
	, theSpanAngle_(SpanAngle)
	, IsDone_(Standard_False)
	, theUnderRelaxation_(DEFAULT_UnderRelaxationFactor)
	, theIterTolerance_(DEFAULT_ITERATION_TOL)
	, IsConverged_(Standard_False)
	, theSmoothingFactor_(DEFAULT_SMOOTHING_FACTOR)
	, theMaxNbSmoothing_(DEFAULT_MAX_NB_SMOOTHING)
	, theVariationRateInfo_(Mesh_VariationRateInfo_FAST)
{
}

AutLib::MeshLib::Mesh2d_CurvesRemesh::~Mesh2d_CurvesRemesh()
{
	ReleaseMemory();
}

const M_GEO Entity_StaticChain2d & AutLib::MeshLib::Mesh2d_CurvesRemesh::Chain() const
{
	return theChain_;
}

const M_GEO GeoMesh_BackGroundMesh2d & AutLib::MeshLib::Mesh2d_CurvesRemesh::BackGroundMesh() const
{
	return *theMesh_;
}

Standard_Boolean AutLib::MeshLib::Mesh2d_CurvesRemesh::IsDone() const
{
	return IsDone_;
}

void AutLib::MeshLib::Mesh2d_CurvesRemesh::SetRelaxation(const Standard_Real Factor)
{
	theUnderRelaxation_ = Factor;
}

void AutLib::MeshLib::Mesh2d_CurvesRemesh::SetBaseSize(const Standard_Real BaseSize)
{
	theBaseSize_ = BaseSize;
}

void AutLib::MeshLib::Mesh2d_CurvesRemesh::SetMinSize(const Standard_Real MinSize)
{
	theMinSize_ = MinSize;
}

void AutLib::MeshLib::Mesh2d_CurvesRemesh::SetSpanAngle(const Standard_Real SpanAngle)
{
	theSpanAngle_ = SpanAngle;
}

void AutLib::MeshLib::Mesh2d_CurvesRemesh::SetMaxNbIterations(const Standard_Integer NbIterations)
{
	theMaxNbIterations_ = NbIterations;
}

void AutLib::MeshLib::Mesh2d_CurvesRemesh::Perform()
{
	Debug_If_Condition_Message(theBaseSize_ EQUAL 0, " The base size is zero");

	IsDone_ = Standard_True;

	SizeMap2d_UniSize UniSize(theBaseSize_);

	Standard_Real Length0 = Discrete(&UniSize);

	forThose
	(
		Iteration,
		1,
		theMaxNbIterations_
	)
	{
		SizeMap2d_StdBackSize AdaptiveSize(theBaseSize_, *theMesh_);

		Standard_Real Length = Discrete(&AdaptiveSize);

		if (ABS(Length - Length0) / Length <= theIterTolerance_)
		{ // Convergence criteria
			IsConverged_ = Standard_True;
			break;
		}

		Length0 = Length;
	}
}

void AutLib::MeshLib::Mesh2d_CurvesRemesh::ExportToPlt(fstream & File) const
{
	theChain_.ExportToPlt(File);
}

namespace AutLib
{
	namespace MeshLib
	{

		static Standard_Real CorrectGuess(const Standard_Real U0, const Standard_Real Guess, const Standard_Real Tol, const Mesh2d_CurveIntegrand& Integrand, const Standard_Integer NbLevels)
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
		inline const Geom_Pnt2d& GetCoordinateOf(Global_Handle(Geom_Pnt2d) Coord)
		{
			return *Coord;
		}

		struct DiscreteParameters
		{
			TColStd_Ary1dOfAry1dOfReal theParameters_;
			TColStd_Ary1dOfAry1dOfReal theH_;

			Standard_Integer theIndex_;
		};

		void MakeChain(const Geom2d_Curve& Curve, const TColStd_Ary1dOfReal & Parameters, M_GEO Entity_StaticChain2d& Chain)
		{
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

			Chain.SetCoords(Points);
			Chain.SetEdges(M_GEO Entity_EdgeIndexTools::OrderedList(MaxIndexOf(Points)));
			Chain.SetCycle(Curve.IsClosed());
		}

		Standard_Real DiscreteCurve(const Global_Handle(Cad2d_CurveOnPlane) CurvePtr, const Global_Handle(Mesh2d_SizeMap) Map, M_GEO Entity_StaticChain2d& Chain, DiscreteParameters& DP, const Standard_Real Relaxation)
		{
			Debug_Null_Pointer(CurvePtr);

			Mesh2d_CurveIntegrand Integrand(Map, CurvePtr->Curve().get(), CurvePtr->FirstParameter(), CurvePtr->LastParameter());

			// Determine the Length of the curve under the current space function
			Standard_Real CurveLength = Mesh2d_CurveLength::Length(Integrand, DEFAULT_Tolerance);

			Debug_If_Condition_Message(CurveLength EQUAL 0.0, " The NULL length curve encontred!");

			// uniform nb. of segment under the current space function
			Standard_Integer NbSegments = M_GEO Geometry_Tools::Round(CurveLength);

			// There must be atleast one segment
			if (NbSegments < 1) NbSegments = 1;

			Debug_If_Condition(NbSegments < 1);

			const Standard_Real Ds = CurveLength / (Standard_Real)NbSegments;
			const Standard_Real dt = 1.0 / CurveLength;

			Standard_Real U0, U1, Guess;

			Get_Object(Parameters) = DP.theParameters_[DP.theIndex_];

			Parameters.Resize(NbSegments + 1);

			Get_Const_Object(Curve) = *CurvePtr;

			Parameters.First() = Curve.FirstParameter();
			Parameters.Last() = Curve.LastParameter();

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
					U1 = M_MESH Mesh2d_CurveIterationTools::Iteration
					(
						U0,
						Guess,
						Ds,
						Integrand
					)
				);

				Parameters.SetValue(Index, U1);

				Guess = U1 + MIN(dt, Relaxation*(Parameters[Index] - Parameters[Index - 1]));

				Debug_If_Condition(Guess <= U1);

				U0 = U1;
			}

			MakeChain(*Curve.Curve(), Parameters, Chain);

			return CurveLength;
		}

		Standard_Real DiscreteCurves(const TColCad2d_HAry1dOfCurveOnPlane& Curves, const Global_Handle(Mesh2d_SizeMap) Map, TColEntity_HAry1dOfStaticChain2d& Chains, DiscreteParameters& DP, const Standard_Real UnderRelaxation)
		{
			Chains.Resize(Curves.Size());

			DP.theParameters_.Resize(Curves.Size());
			DP.theH_.Resize(Curves.Size());
			Standard_Real CurveLength = 0;

			forThose
			(
				Index,
				0,
				MaxIndexOf(Curves)
			)
			{
				Chains[Index] = new M_GEO Entity_StaticChain2d;

				DP.theIndex_ = Index;

				CurveLength += DiscreteCurve
				(
					Curves[Index],
					Map,
					*Chains[Index],
					DP,
					UnderRelaxation
				);
			}

			return CurveLength;
		}
	}
}

Standard_Real AutLib::MeshLib::Mesh2d_CurvesRemesh::Discrete(const Global_Handle(Mesh2d_SizeMap) Map)
{
	TColEntity_HAry1dOfStaticChain2d Chains;
	DiscreteParameters DP;

	Standard_Real Length = DiscreteCurves
	(
		theCurve_,
		Map,
		Chains, 
		DP,
		theUnderRelaxation_
	);

	// Merging the chains
	M_GEO Merge_Chain2d Merge;
	Merge.Import(Chains);  // need to be optimized

	FreeMemory(Chains);

	Merge.Perform();

	theChain_ = *Merge.Merged();  // need to be optimized
	Get_Const_Object(Chain) = *Merge.Merged();
	Get_Const_Object(Coords) = Chain.Coords();

	TColGeom_HAry1dOfPnt2d Points(Coords.Size());
	Points.Init(0);
	forThose(Index, 0, MaxIndexOf(Coords))
		Points[Index] = (Global_Handle(Geom_Pnt2d))&Coords[Index];

	forThose
	(
		Index,
		0, 
		MaxIndexOf(theCurve_)
	)
	{
		Debug_Null_Pointer(theCurve_[Index]);
		Debug_Null_Pointer(theCurve_[Index]->Curve());

		UpdateGeoSize
		(
			*theCurve_[Index],
			DP.theParameters_[Index],
			DP.theH_[Index]
		);
	}
	
	Geom_BalancedPrQuadTree<Global_Handle(Geom_Pnt2d)> Tree;
	Tree.SetCoordinateFunction(&GetCoordinateOf);
	Tree.SetRegion(theDomain_.OffsetBox(0.15*theDomain_.Diameter()));
	Tree.SetBucketSize(DEFAULT_BUCKETSIZE);
	Tree.Insert(Points);
	Tree.PostBalancing();

	TColEntity_HAry1dOfBox2d Boxes;
	Tree.RetrieveTo(Boxes);

	Entity_Triangulation2d Triangulation;
	Entity_Box2dTools::Triangulation(Boxes, &Triangulation);

	FreePointer(theMesh_);
	theMesh_ = new GeoMesh_BackGroundMesh2d;
	theMesh_->Mesh().Construct(Triangulation);
	theMesh_->InitiateCurrentElement();
	
	Try_Exception_Handle_Exit(SetSourcesToMesh(DP));

	theMesh_->HvCorrection(Mesh_VariationRate::Rate(theVariationRateInfo_));
	theMesh_->LaplacianSmoothing(1, 0.05);

	FreeMemory(Boxes);

	return Length;
}

namespace AutLib
{
	namespace MeshLib
	{

		static Standard_Real MaxCurvature(const M_CAD Cad2d_CurveOnPlane& theCurve, const Standard_Real theU0, const Standard_Real theU1, const Standard_Integer theNbPts)
		{
			Standard_Integer NbSegments = theNbPts + 1;
			Standard_Real dU = (theU1 - theU0) / (Standard_Real)NbSegments;

			Standard_Real MinC = 0;
			forThose(Index, 1, theNbPts)
			{
				Standard_Real Curvature = theCurve.CalcCurvature(Index*dU + theU0);
				if (Curvature > MinC) MinC = Curvature;
			}
			return MinC;
		}
	}
}

void AutLib::MeshLib::Mesh2d_CurvesRemesh::UpdateGeoSize
(
	const M_CAD Cad2d_CurveOnPlane& theCurve,
	const TColStd_Ary1dOfReal & Parameters,
	TColStd_Ary1dOfReal & H
) const
{
	H.Resize(Parameters.Size());

	Standard_Real SIN = sin(M_GEO Geometry_Tools::DegToRadian(theSpanAngle_) / 2);

	//TColStd_Ary1dOfReal Um(Parameters.Size() - 1);
	TColStd_Ary1dOfReal Hm(Parameters.Size() - 1);
	//forThose(Index, 0, MaxIndexOf(Um)) Um[Index] = MEAN(Parameters[Index], Parameters[Index + 1]);
	forThose(Index, 0, MaxIndexOf(Hm))
	{
		Hm[Index] = MIN(theBaseSize_, MAX(2 * SIN / MaxCurvature(theCurve, Parameters[Index], Parameters[Index + 1], 5), theMinSize_));
	}

	H.First() = Hm.First();	
	forThose(Index, 1, MaxIndexOf(H) - 1)
	{
		H[Index] = MEAN(Hm[Index - 1], Hm[Index]);
	}
	H.Last() = Hm.Last();

	TColStd_Ary1dOfReal nH(H.Size() - 1);

	forThose
	(
		Iter,
		1,
		theMaxNbSmoothing_
	)
	{
		forThose(Index, 0, MaxIndexOf(nH))
			nH[Index] = MEAN(H[Index], H[Index + 1]);

		forThose
		(
			Index,
			1,
			MaxIndexOf(H) - 1
		)
		{
			Standard_Real Hm = MEAN(nH[Index - 1], nH[Index]);
			Standard_Real dH = Hm - H[Index];

			H[Index] += theSmoothingFactor_*dH;
		}
	}
}

void AutLib::MeshLib::Mesh2d_CurvesRemesh::SetSourcesToMesh(const DiscreteParameters & DP)
{
	Get_Object(Mesh) = (*theMesh_).Mesh();

	if (NOT Mesh.NbElements())
	{
		THROW_STANDARD_EXCEPTION(" Not found any background mesh");
		return;
	}

	Get_Object(Sources) = (*theMesh_).Sources();
	Sources.Resize(Mesh.NbNodes());
	Sources.Init(theBaseSize_);

	Get_Const_Object(Elements) = Mesh.ElementsSequence();

	Global_Handle(Entity_Element2d) Start = Elements[0];

	forThose
	(
		Boundary,
		0, 
		MaxIndexOf(theCurve_)
	)
	{
		Get_Const_Object(Parameters) = DP.theParameters_[Boundary];
		Get_Const_Object(Values) = DP.theH_[Boundary];

		Get_Const_Object(Curve) = *theCurve_[Boundary]->Curve();

		forThose
		(
			Index,
			0,
			MaxIndexOf(Parameters)
		)
		{
			Geom_Pnt2d Point = Curve.Value(Parameters[Index]);

			Global_Handle(Entity_Element2d) FoundPtr = Mesh.TriangleLocation(Start, Point);

			if (IsNULL(FoundPtr))
			{
				THROW_STANDARD_EXCEPTION(" the Point is not inside the Mesh");
				return;
			}

			Start = FoundPtr;

			Get_Const_Object(Found) = *FoundPtr;

			Sources[Index_Of(Found.Node0()->Index())] = MIN(Values[Index], Sources[Index_Of(Found.Node0()->Index())]);
			Sources[Index_Of(Found.Node1()->Index())] = MIN(Values[Index], Sources[Index_Of(Found.Node1()->Index())]);
			Sources[Index_Of(Found.Node2()->Index())] = MIN(Values[Index], Sources[Index_Of(Found.Node2()->Index())]);
		}
	}
}

void AutLib::MeshLib::Mesh2d_CurvesRemesh::ReleaseMemory()
{
	FreePointer(theMesh_);
}