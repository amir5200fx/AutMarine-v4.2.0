#include <SizeMap2d_CorrectSizeMapTool.hxx>

#include <Entity_Box2dTools.hxx>
#include <Entity_Triangulation2d.hxx>
#include <GeoMesh_BackGroundMesh2d.hxx>
#include <GeoMesh_BackGroundMesh2dTools.hxx>
#include <Geom_BalancedPrQuadTree.hxx>
#include <Cad2d_Plane.hxx>
#include <Mesh2d_Curve.hxx>
#include <Mesh2d_Domain.hxx>
#include <Mesh2d_SourcePoint.hxx>
#include <Mesh2d_SourcePointTools.hxx>
#include <Mesh_VariationRate.hxx>
#include <Mesh_Values.hxx>
#include <SizeMap2d_StdBackSize.hxx>
#include <SizeMap2d_UnionSizeMaps.hxx>
#include <TColMesh2d_HBasicQueueOfSourcePoint.hxx>
#include <TColMesh2d_HAry1dOfSourcePoint.hxx>

static const Standard_Integer DEFAULT_BUCKET_SIZE = 4;
static const Standard_Integer DEFAULT_MAX_LEVELS = 5;
static const Standard_Integer DEFAULT_LAPLACIAN_SMOOTHING = 3;
static const Standard_Real DEFAULT_LAPLACIAN_SMOOTHING_FACTOR = 0.1;
static const Standard_Real DEFAULT_MAX_DEVIATION = 0.5;

using namespace AutLib;
using namespace MeshLib;
using namespace CadLib;
using namespace GeoLib;

#define TOLERANCE(X1, X2)  ABS(X1 - X2) / ABS(X2)

AutLib::MeshLib::SizeMap2d_CorrectSizeMapTool::SizeMap2d_CorrectSizeMapTool()
	: theBucketSize_(DEFAULT_BUCKET_SIZE)
	, theMaxLevels_(DEFAULT_MAX_LEVELS)
	, theMaxDeviation_(DEFAULT_MAX_DEVIATION)
	, thePlane_(NULL)
	, theBack_(NULL)
{
}

AutLib::MeshLib::SizeMap2d_CorrectSizeMapTool::SizeMap2d_CorrectSizeMapTool
(
	const Global_Handle(M_CAD Cad2d_Plane) thePlane,
	const Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) theBack
)
	: theBucketSize_(DEFAULT_BUCKET_SIZE)
	, theMaxLevels_(DEFAULT_MAX_LEVELS)
	, theMaxDeviation_(DEFAULT_MAX_DEVIATION)
	, thePlane_(thePlane)
	, theBack_(theBack)
{
}

AutLib::MeshLib::SizeMap2d_CorrectSizeMapTool::~SizeMap2d_CorrectSizeMapTool()
{
	FreePointer(theModified_);
}

void AutLib::MeshLib::SizeMap2d_CorrectSizeMapTool::Init
(
	const Global_Handle(M_CAD Cad2d_Plane) thePlane,
	const Global_Handle(Mesh_Values) theValues,
	const Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) theBack
)
{
	thePlane_ = thePlane;
	theBack_ = theBack;
}

void AutLib::MeshLib::SizeMap2d_CorrectSizeMapTool::SetPlane(const Global_Handle(M_CAD Cad2d_Plane) thePlane)
{
	thePlane_ = thePlane;
}

void AutLib::MeshLib::SizeMap2d_CorrectSizeMapTool::SetBackMesh(const Global_Handle(M_GEO GeoMesh_BackGroundMesh2d) theBack)
{
	theBack_ = theBack;
}


void AutLib::MeshLib::SizeMap2d_CorrectSizeMapTool::SetBucketSize(const Standard_Integer theBucketSize)
{
	theBucketSize_ = theBucketSize;
}

void AutLib::MeshLib::SizeMap2d_CorrectSizeMapTool::SetMaxLevelCorrection(const Standard_Integer theMaxLevel)
{
	theMaxLevels_ = theMaxLevel;
}

namespace AutLib
{
	namespace CadLib
	{
		static Standard_Boolean DoCorrection(const Mesh2d_Domain& theDomain, const GeoMesh_BackGroundMesh2d& theSizeMap, const Standard_Real theDeviation)
		{
			forThose
			(
				Index,
				1,
				theDomain.NbCurves()
			)
			{
				Get_Const_Object(Curve) = theDomain.CurveMesh(Index_Of(Index));
				Get_Const_Object(Chain) = Curve.Chain();

				Get_Const_Object(Coords) = Chain.Coords();
				Get_Const_Object(Edges) = Chain.Edges();

				forThose
				(
					Inner,
					0,
					MaxIndexOf(Edges)
				)
				{
					Standard_Integer V0 = Edges[Inner].V0() - 1;
					Standard_Integer V1 = Edges[Inner].V1() - 1;

					Geom_Pnt2d Centre = MEAN(Coords[V0], Coords[V1]);

					if (TOLERANCE(theSizeMap.ElementSize(Centre), Distance(Coords[V0], Coords[V1])) > theDeviation) { return Standard_True; }
				}
			}
			return Standard_False;
		}
	}
}

void AutLib::MeshLib::SizeMap2d_CorrectSizeMapTool::Perform()
{
	SizeMap2d_StdBackSize Map(1.0, *theBack_);

	Global_Handle(Mesh2d_Domain) Domain = new Mesh2d_Domain(Map, thePlane_, 1.0E-6);

	Domain->Perform(Standard_False);

	if (NOT::DoCorrection(*Domain, *theBack_, theMaxDeviation_))
	{
		theModified_ = new GeoMesh_BackGroundMesh2d;
		theModified_->Mesh().Construct(theBack_->Mesh().Static());
		theModified_->Sources() = theBack_->Sources();
		return;
	}

	forThose
	(
		Iter, 
		1, 
		theMaxLevels_
	)
	{
		Debug_Null_Pointer(theModified_);

		if (OneLevelModify(*Domain))
		{
			FreePointer(Domain);
			Domain = new Mesh2d_Domain(SizeMap2d_StdBackSize(1.0, *theModified_), thePlane_, 1.0E-6);
			Domain->Perform(Standard_False);

			continue;
		}

		break;
	}

	FreePointer(Domain);
}

void AutLib::MeshLib::SizeMap2d_CorrectSizeMapTool::ExportToPlt(fstream & File) const
{
	if (theModified_) theModified_->ExportMeshToPlt(File);
}

Standard_Boolean AutLib::MeshLib::SizeMap2d_CorrectSizeMapTool::OneLevelModify(const Mesh2d_Domain& theDomain)
{
	const Global_Handle(GeoMesh_BackGroundMesh2d) Back;

	if (NOT theModified_) Back = theBack_;
	else Back = theModified_;

	TColMesh2d_HBasicQueueOfSourcePoint QSources;
	forThose
	(
		Index,
		1, 
		theDomain.NbCurves()
	)
	{
		Get_Const_Object(Curve) = theDomain.CurveMesh(Index_Of(Index));
		Get_Const_Object(Chain) = Curve.Chain();

		Get_Const_Object(Coords) = Chain.Coords();
		Get_Const_Object(Edges) = Chain.Edges();

		forThose
		(
			Inner,
			0,
			MaxIndexOf(Edges)
		)
		{
			Standard_Integer V0 = Edges[Inner].V0() - 1;
			Standard_Integer V1 = Edges[Inner].V1() - 1;

			Geom_Pnt2d Centre = MEAN(Coords[V0], Coords[V1]);

			Standard_Real BackSize = Back->ElementSize(Centre);
			Standard_Real H = Distance(Coords[V0], Coords[V1]);

			Standard_Real Coeff = MIN(1.0, H / BackSize);

			QSources.EnQueue(new Mesh2d_SourcePoint(Centre, Coeff));
		}
	}

	TColMesh2d_HAry1dOfSourcePoint Sources;
	QSources.RetrieveTo(Sources);

	Entity_Box2d Box = thePlane_->BoundingBox();

	Geom_BalancedPrQuadTree<Global_Handle(Mesh2d_SourcePoint)> Tree;
	Tree.SetCoordinateFunction(&Mesh2d_SourcePointTools::CoordinateOf);
	Tree.SetRegion(Box.OffsetBox(0.15*Box.Diameter()));
	Tree.SetBucketSize(theBucketSize_);
	Tree.Insert(Sources);
	Tree.PostBalancing();

	TColEntity_HAry1dOfBox2d Boxes;
	Tree.RetrieveTo(Boxes);

	Entity_Triangulation2d Triangulation;
	Entity_Box2dTools::Triangulation(Boxes, &Triangulation);

	GeoMesh_BackGroundMesh2d NewBack;
	NewBack.Mesh().Construct(Triangulation);
	NewBack.InitiateCurrentElement();
	NewBack.SetBoundingBox(Tree.BoundingBox());

	Try_Exception_Handle_Exit(GeoMesh_BackGroundMesh2dTools::SetSourcesToMesh(Sources, 1.0, NewBack));
	
	NewBack.HvCorrection(0.95, 3);

	Get_Object(NewSources) = NewBack.Sources();
	Get_Const_Object(Nodes) = NewBack.Mesh().NodesSequence();
	forThose
	(
		Index,
		0,
		MaxIndexOf(NewSources)
	)
	{
		Standard_Real ElementSize = theBack_->ElementSize(Nodes[Index]->Coord());
		NewSources[Index] *= ElementSize;
	}
	
	//NewBack.LaplacianSmoothing(DEFAULT_LAPLACIAN_SMOOTHING, DEFAULT_LAPLACIAN_SMOOTHING_FACTOR);

	SizeMap2d_UnionSizeMaps Union;
	Union.ImportSizeMap(Back);
	Union.ImportSizeMap(&NewBack);

	Union.Perform();

	Standard_Boolean Correction = ::DoCorrection(theDomain, *Back, theMaxDeviation_);

	FreePointer(theModified_);
	theModified_ = Union.BackGroundMesh();
	theModified_->HvCorrection(0.8, 3);

	FreeMemory(Sources);

	if (Correction) { return Standard_True; }
	return Standard_False;
}