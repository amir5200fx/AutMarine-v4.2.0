#include <SizeMap2d_PointsSizeMapTool.hxx>

#include <Merge_Items2d.hxx>
#include <Entity_Box2d.hxx>
#include <Entity_Box2dTools.hxx>
#include <Entity_Triangulation2d.hxx>
#include <GeoMesh_BackGroundMesh2d.hxx>
#include <GeoMesh_BackGroundMesh2dTools.hxx>
#include <Mesh_Values.hxx>
#include <Mesh_VariationRate.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh2d_SourcePoint.hxx>
#include <Mesh2d_SourcePointTools.hxx>
#include <Cad2d_PointOnPlane.hxx>
#include <Cad2d_Plane.hxx>
#include <SubDivide_BalancedQuadTree.hxx>
#include <TColEntity_HAry1dOfBox2d.hxx>
#include <TColMesh2d_HAry1dOfSourcePoint.hxx>
#include <TColCad2d_HAry1dOfPointOnPlane.hxx>

#define TOLERANCE(X1, X2)  ABS(X1 - X2) / MAX(ABS(X1), ABS(X2))

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

static const Standard_Integer DEFAULT_BUCKET_SIZE = 4;
static const Standard_Integer DEFAULT_MIN_SUBDIVISION = 2;
static const Standard_Integer DEFAULT_MAX_SUBDIVISION = 5;
static const Standard_Integer DEFAULT_LAPLACIAN_SMOOTHING = 3;
static const Standard_Real DEFAULT_LAPLACIAN_SMOOTHING_FACTOR = 0.1;

AutLib::MeshLib::SizeMap2d_PointsSizeMapTool::SizeMap2d_PointsSizeMapTool
(
	const Global_Handle(Mesh_ReferenceValues) theReference, 
	const Global_Handle(M_CAD Cad2d_Plane)thePlane
)
	: SizeMap2d_BoundarySizeMapTool(theReference, thePlane)
	, theBucketSize_(DEFAULT_BUCKET_SIZE)
{
}

AutLib::MeshLib::SizeMap2d_PointsSizeMapTool::~SizeMap2d_PointsSizeMapTool()
{
}

void AutLib::MeshLib::SizeMap2d_PointsSizeMapTool::SetBucketSize(const Standard_Integer BucketSize)
{
	theBucketSize_ = BucketSize;
}

namespace AutLib
{
	namespace CadLib
	{

		static inline Standard_Real CalcRadius(const Standard_Real theGrowthRate, const Standard_Real theTarget, const Standard_Real theBase)
		{
			Standard_Real H = theBase - theTarget;
			if (H < 0) { THROW_STANDARD_EXCEPTION("Invalid Element Size"); }

			Standard_Real Teta = asin(theGrowthRate);
			return H / tan(Teta);
		}

		class LocalMesh_BalancedQuadTreeObject
		{

		public:

			const Global_Handle(TColMesh2d_HAry1dOfSourcePoint) theSources_;

			Standard_Real theTolerance_;

			Standard_Real theTarget_;
			Standard_Real theBaseSize_;
			Standard_Real theRadius2_;

			Standard_Real ElementSize(const Geom_Pnt2d& Coord) const;

			static Standard_Boolean SubDivide(const Entity_Box2d& Box, const Global_Handle(LocalMesh_BalancedQuadTreeObject) Object);
		};

		inline Standard_Real LocalMesh_BalancedQuadTreeObject::ElementSize(const Geom_Pnt2d & Coord) const
		{
			Debug_Null_Pointer(theSources_);
			Get_Const_Object(Sources) = *theSources_;

			Debug_If_Condition(Sources.IsEmpty());

			Standard_Real DH = theBaseSize_ - theTarget_;
			Standard_Real H = RealLast();
			Standard_Real h;
			forThose
			(
				Index, 
				0,
				MaxIndexOf(Sources)
			)
			{
				Debug_Null_Pointer(Sources[Index]);

				Standard_Real Radius2 = DistanceSQ(Coord, Sources[Index]->Coord());

				if (Radius2 > theRadius2_)
					h = theBaseSize_;
				else
				{
					h = sqrt(Radius2 / theRadius2_)*DH + theTarget_;
				}

				if (h < H) H = h;
			}
			return H;
		}

		inline Standard_Boolean LocalMesh_BalancedQuadTreeObject::SubDivide(const Entity_Box2d & Box, const Global_Handle(LocalMesh_BalancedQuadTreeObject) ObjectPtr)
		{
			Get_Const_Object(Object) = *ObjectPtr;

			const Standard_Real Tolerance = Object.theTolerance_;

			const Standard_Real H1 = Object.ElementSize(Box.GetSwPoint());
			const Standard_Real H2 = Object.ElementSize(Box.GetSePoint());
			const Standard_Real H3 = Object.ElementSize(Box.GetNePoint());
			const Standard_Real H4 = Object.ElementSize(Box.GetNwPoint());

			if (TOLERANCE(H1, H2) > Tolerance)
				return Standard_True;

			if (TOLERANCE(H1, H3) > Tolerance)
				return Standard_True;

			if (TOLERANCE(H1, H4) > Tolerance)
				return Standard_True;

			if (TOLERANCE(H2, H3) > Tolerance)
				return Standard_True;

			if (TOLERANCE(H2, H4) > Tolerance)
				return Standard_True;

			if (TOLERANCE(H3, H4) > Tolerance)
				return Standard_True;

			return Standard_False;
		}
	}
}

void AutLib::MeshLib::SizeMap2d_PointsSizeMapTool::CreateSizeMap()
{
	TColCad2d_HAry1dOfPointOnPlane Points;
	SizeMap2d_BoundarySizeMapTool::RetrievePointsTo(Points);

	if (Points.IsEmpty()) { return; }

	//! Retrieve Element size
	Standard_Real ElementSize, MinElementSize;
	Standard_Real SpanAngle;

	Try_Exception_Handle_Exit(SpecifyValues(ElementSize, MinElementSize, SpanAngle));

	Standard_Real Radius;
	if (theConditions_.CustomBoundaryGrowthRate()) Radius = ::CalcRadius(Mesh_VariationRate::Rate(theValues_.BoundaryGrowthRate()), ElementSize, theReference_->BaseSize());
	else Radius = ::CalcRadius(Mesh_VariationRate::Rate(theReference_->DefaultGrowthRate()), ElementSize, theReference_->BaseSize());

	TColMesh2d_HAry1dOfSourcePoint Sources(Points.Size());
	forThose
	(
		Index,
		0,
		MaxIndexOf(Points)
	)
	{
		Debug_Null_Pointer(Points[Index]);

		Sources[Index] = new Mesh2d_SourcePoint(Points[Index]->Coord(), ElementSize);
	}

	Merge_Items2d<Global_Handle(Mesh2d_SourcePoint)> Merge(&Sources, &Mesh2d_SourcePointTools::CoordinateOf);
	Merge.Perform();

	Debug_If_Condition_Message(NOT Merge.IsDone(), " Merging Items is not performed");

	TColMesh2d_HAry1dOfSourcePoint CompactItems = Merge.CompactItems();

	LocalMesh_BalancedQuadTreeObject Object;

	Object.theSources_ = &CompactItems;
	if (theConditions_.CustomBoundaryGrowthRate()) Object.theTolerance_ = Mesh_VariationRate::Rate(theValues_.BoundaryGrowthRate());
	else Object.theTolerance_ = Mesh_VariationRate::Rate(theReference_->DefaultGrowthRate());
	Object.theRadius2_ = Radius*Radius;
	Object.theTarget_ = ElementSize;
	Object.theBaseSize_ = theReference_->BaseSize();

	Entity_Box2d Box = thePlane_->BoundingBox();

	SubDivide_BalancedQuadTree<LocalMesh_BalancedQuadTreeObject> Tree;

	Tree.SetMinLevel(DEFAULT_MIN_SUBDIVISION);
	Tree.SetMaxLevel(DEFAULT_MAX_SUBDIVISION);

	Tree.SetObject(&Object);
	Tree.SetSubDivider(&LocalMesh_BalancedQuadTreeObject::SubDivide);
	Tree.SetDomain(Box.OffsetBox(0.15*Box.Diameter()));
	Tree.Init();
	Tree.Perform();

	TColEntity_HAry1dOfBox2d Boxes;
	Tree.RetrieveTo(Boxes);

	Entity_Triangulation2d Triangulation;
	Entity_Box2dTools::Triangulation(Boxes, &Triangulation);

	theBackMesh_ = new GeoMesh_BackGroundMesh2d;
	theBackMesh_->Mesh().Construct(Triangulation);
	theBackMesh_->InitiateCurrentElement();
	theBackMesh_->SetBoundingBox(Box.OffsetBox(0.15*Box.Diameter()));

	Try_Exception_Handle_Exit(GeoMesh_BackGroundMesh2dTools::SetSourcesToMesh(CompactItems, theReference_->BaseSize(), *theBackMesh_));

	if (theConditions_.CustomBoundaryGrowthRate()) theBackMesh_->HvCorrection(Mesh_VariationRate::Rate(theValues_.BoundaryGrowthRate()));
	else theBackMesh_->HvCorrection(Mesh_VariationRate::Rate(theReference_->DefaultGrowthRate()));

	theBackMesh_->LaplacianSmoothing(DEFAULT_LAPLACIAN_SMOOTHING, DEFAULT_LAPLACIAN_SMOOTHING_FACTOR);

	FreeMemory(Sources);
}