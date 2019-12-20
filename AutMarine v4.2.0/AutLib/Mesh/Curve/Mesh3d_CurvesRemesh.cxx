#include <Mesh3d_CurvesRemesh.hxx>

#include <Mesh_VariationRate.hxx>
#include <Mesh3d_UniSize.hxx>
#include <Mesh3d_BackSize.hxx>
#include <Mesh3d_CurveIntegrand.hxx>
#include <Mesh3d_CurveLength.hxx>
#include <Mesh3d_CurveIterationTools.hxx>
#include <Cad3d_EdgeOnSurface.hxx>
#include <Geometry_Tools.hxx>
#include <Geom_BalancedPrOctTree.hxx>
#include <GeoMesh_TetrahedronMesh.hxx>
#include <Merge_Chain3d.hxx>
#include <Entity_Box3dTools.hxx>
#include <Entity_EdgeIndexTools.hxx>
#include <Entity_Tetrahedralization.hxx>
#include <TColGeom_HAry1dOfPnt3d.hxx>
#include <TColStd_Ary1dOfAry1dOfReal.hxx>
#include <TColEntity_HAry1dOfBox3d.hxx>
#include <TColEntity_HAry1dOfStaticChain3d.hxx>

static const Standard_Real DEFAULT_UnderRelaxationFactor = 0.85;
static const Standard_Real DEFAULT_Tolerance = 1.0E-8;
static const Standard_Real DEFAULT_MIN_SIZE = 0.1;
static const Standard_Real DEFAULT_SPAN_ANGLE = 15;
static const Standard_Real DEFAULT_ITERATION_TOL = 0.05;
static const Standard_Real DEFAULT_SMOOTHING_FACTOR = 0.5;

static const Standard_Integer DEFAULT_MAX_ITERATIONS = 5;
static const Standard_Integer DEFAULT_MAX_NB_SMOOTHING = 3;

using namespace AutLib;
using namespace GeoLib;
using namespace CadLib;

#include <GeomLProp_CLProps.hxx>
#include <Geom_Curve.hxx>

static Global_Handle(GeomLProp_CLProps) theProp_;

AutLib::MeshLib::Mesh3d_CurvesRemesh::Mesh3d_CurvesRemesh
(
	const TColCad3d_HAry1dOfEdgeOnSurface & Curves, 
	const M_GEO Entity_Box3d & Domain
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
{
}

AutLib::MeshLib::Mesh3d_CurvesRemesh::Mesh3d_CurvesRemesh
(
	const TColCad3d_HAry1dOfEdgeOnSurface & Curves, 
	const M_GEO Entity_Box3d & Domain,
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
{
}

AutLib::MeshLib::Mesh3d_CurvesRemesh::~Mesh3d_CurvesRemesh()
{
	ReleaseMemory();
}

const M_GEO Entity_StaticChain3d & AutLib::MeshLib::Mesh3d_CurvesRemesh::Chain() const
{
	return theChain_;
}

const M_GEO GeoMesh_BackGroundMesh3d & AutLib::MeshLib::Mesh3d_CurvesRemesh::BackGroundMesh() const
{
	Debug_Null_Pointer(theMesh_);

	return *theMesh_;
}

Standard_Boolean AutLib::MeshLib::Mesh3d_CurvesRemesh::IsDone() const
{
	return IsDone_;
}

void AutLib::MeshLib::Mesh3d_CurvesRemesh::SetRelaxation(const Standard_Real Factor)
{
	theUnderRelaxation_ = Factor;
}

void AutLib::MeshLib::Mesh3d_CurvesRemesh::SetBaseSize(const Standard_Real BaseSize)
{
	theBaseSize_ = BaseSize;
}

void AutLib::MeshLib::Mesh3d_CurvesRemesh::SetMinSize(const Standard_Real MinSize)
{
	theMinSize_ = MinSize;
}

void AutLib::MeshLib::Mesh3d_CurvesRemesh::SetSpanAngle(const Standard_Real SpanAngle)
{
	theSpanAngle_ = SpanAngle;
}

void AutLib::MeshLib::Mesh3d_CurvesRemesh::SetMaxNbIterations(const Standard_Integer NbIterations)
{
	theMaxNbIterations_ = NbIterations;
}

void AutLib::MeshLib::Mesh3d_CurvesRemesh::Perform()
{
	Debug_If_Condition_Message(theBaseSize_ EQUAL 0, " The base size is zero");

	IsDone_ = Standard_True;

	Mesh3d_UniSize UniSize(theBaseSize_);

	Standard_Real Length0 = Discrete(&UniSize);

	theProp_ = new GeomLProp_CLProps(2, 1.0E-6);

	forThose
	(
		Iteration,
		1,
		theMaxNbIterations_
	)
	{
		Mesh3d_BackSize AdaptiveSize(theBaseSize_, *theMesh_);

		Standard_Real Length = Discrete(&AdaptiveSize);

		if (ABS(Length - Length0) / Length <= theIterTolerance_)
		{ // Convergence criteria
			IsConverged_ = Standard_True;
			break;
		}

		Length0 = Length;

	}
}

void AutLib::MeshLib::Mesh3d_CurvesRemesh::ExportToPlt(fstream & File) const
{
	theChain_.ExportToPlt(File);
}

namespace AutLib
{
	namespace MeshLib
	{

		inline const Geom_Pnt3d& GetCoordinateOf(Global_Handle(Geom_Pnt3d) Coord)
		{
			return *Coord;
		}

		struct DiscreteParameters
		{
			TColStd_Ary1dOfAry1dOfReal theParameters_;
			TColStd_Ary1dOfAry1dOfReal theH_;

			Standard_Integer theIndex_;
		};

		void MakeChain(const Geom_Curve& Curve, const TColStd_Ary1dOfReal & Parameters, M_GEO Entity_StaticChain3d& Chain)
		{
			TColGeom_Ary1dOfPnt3d Points(Parameters.Size());

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

		Standard_Real DiscreteCurve(const Global_Handle(Cad3d_EdgeOnSurface) CurvePtr, const Global_Handle(Mesh3d_SizeMap) Map, M_GEO Entity_StaticChain3d& Chain, DiscreteParameters& DP, const Standard_Real Relaxation)
		{
			Debug_Null_Pointer(CurvePtr);

			Mesh3d_CurveIntegrand Integrand(Map, CurvePtr->Curve().get(), CurvePtr->FirstParameter(), CurvePtr->LastParameter());

			// Determine the Length of the curve under the current space function
			Standard_Real CurveLength = Mesh3d_CurveLength::Length(Integrand, DEFAULT_Tolerance);

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

			Guess = dt;
			U0 = Parameters.First();

			forThose
			(
				Index,
				1,
				NbSegments - 1
			)
			{
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

				Guess = U1 + MIN(dt, Relaxation*(Parameters[Index] - Parameters[Index - 1]));

				Debug_If_Condition(Guess <= U1);

				U0 = U1;
			}

			MakeChain(*Curve.Curve(), Parameters, Chain);

			return CurveLength;
		}

		Standard_Real DiscreteCurves(const TColCad3d_HAry1dOfEdgeOnSurface& Curves, const Global_Handle(Mesh3d_SizeMap) Map, TColEntity_HAry1dOfStaticChain3d& Chains, DiscreteParameters& DP, const Standard_Real UnderRelaxation)
		{
			Chains.Resize(Curves.Size());
			Standard_Real CurveLength = 0;

			forThose
			(
				Index,
				0,
				MaxIndexOf(Curves)
			)
			{
				Chains[Index] = new M_GEO Entity_StaticChain3d;

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

Standard_Real AutLib::MeshLib::Mesh3d_CurvesRemesh::Discrete(const Global_Handle(Mesh3d_SizeMap) Map)
{
	FreePointer(theMesh_);

	TColEntity_HAry1dOfStaticChain3d Chains;
	DiscreteParameters DP;

	DP.theParameters_.Resize(theCurve_.Size());
	DP.theH_.Resize(theCurve_.Size());

	Standard_Real Length = DiscreteCurves
	(
		theCurve_,
		Map,
		Chains,
		DP,
		theUnderRelaxation_
	);

	// Merging the chains
	M_GEO Merge_Chain3d Merge;
	Merge.Import(Chains);  // need to be optimized

	FreeMemory(Chains);

	Merge.Perform();

	theChain_ = *Merge.Merged();  // need to be optimized

	Get_Const_Object(Chain) = *Merge.Merged();

	Get_Const_Object(Coords) = Chain.Coords();

	TColGeom_HAry1dOfPnt3d Points(Coords.Size());
	Points.Init(0);

	forThose(Index, 0, MaxIndexOf(Coords))
		Points[Index] = (Global_Handle(Geom_Pnt3d))&Coords[Index];

	forThose
	(
		Index,
		0,
		MaxIndexOf(theCurve_)
	)
	{
		theProp_->SetCurve(&(*theCurve_[Index]->Curve()));

		UpdateGeoSize
		(
			*theCurve_[Index]->Curve(),
			DP.theParameters_[Index],
			DP.theH_[Index]
		);
	}

	Geom_BalancedPrOctTree<Global_Handle(Geom_Pnt3d)> Tree;

	Tree.SetCoordinateFunction(&GetCoordinateOf);
	Tree.SetRegion(theDomain_);

	Tree.Insert(Points);
	Tree.PostBalancing();

	TColEntity_HAry1dOfBox3d Boxes;
	Tree.RetrieveTo(Boxes);

	Entity_Tetrahedralization Triangulation;
	Entity_Box3dTools::Triangulation(Boxes, &Triangulation);

	GeoMesh_TetrahedronMesh TriMesh;
	TriMesh.Construct(Triangulation);

	theMesh_ = new GeoMesh_BackGroundMesh3d(TriMesh);

	Try_Exception_Handle_Exit(SetSourcesToMesh(DP));

	theMesh_->HvCorrection(Mesh_VariationRate::Rate(theVariationRateInfo_));

	theMesh_->LaplacianSmoothing(1, 0.05);

	FreeMemory(Boxes);

	return Length;
}

void AutLib::MeshLib::Mesh3d_CurvesRemesh::UpdateGeoSize
(
	const Geom_Curve & Curve, 
	const TColStd_Ary1dOfReal & Parameters,
	TColStd_Ary1dOfReal & H
) const
{
	H.Resize(Parameters.Size());
	Get_Object(Prop) = *theProp_;

	Standard_Real SIN = sin(M_GEO Geometry_Tools::DegToRadian(theSpanAngle_) / 2);

	TColStd_Ary1dOfReal Um(Parameters.Size() - 1);
	TColStd_Ary1dOfReal Hm(Parameters.Size() - 1);
	forThose(Index, 0, MaxIndexOf(Um)) Um[Index] = MEAN(Parameters[Index], Parameters[Index + 1]);
	forThose(Index, 0, MaxIndexOf(Hm))
	{
		Prop.SetParameter(Um[Index]);
		Hm[Index] = MIN(theBaseSize_, MAX(ABS(2 * SIN / Prop.Curvature()), theMinSize_));
	}

	H.First() = Hm.First();
	forThose(Index, 1, MaxIndexOf(H) - 1)
	{
		//cout << ABS(2 * SIN / Curve.Curvature(Parameters[Index])) << "  " << theMinSize_ << "  " << theBaseSize_ << endl;
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

void AutLib::MeshLib::Mesh3d_CurvesRemesh::SetSourcesToMesh(const DiscreteParameters & DP)
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

	Global_Handle(Entity_Element3d) Start = Elements[0];

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
			Geom_Pnt3d Point = Curve.Value(Parameters[Index]);

			Global_Handle(Entity_Element3d) FoundPtr = Mesh.TetrahedronLocation(Start, Point);

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
			Sources[Index_Of(Found.Node3()->Index())] = MIN(Values[Index], Sources[Index_Of(Found.Node3()->Index())]);
		}
	}
}

void AutLib::MeshLib::Mesh3d_CurvesRemesh::ReleaseMemory()
{
	FreePointer(theMesh_);
}