#include <Mesh3d_SurfaceMesher.hxx>

#include <Primitive_Field.hxx>
#include <Entity_Polygon2d.hxx>
#include <Entity_StaticChain2d.hxx>
#include <Entity_Metric1Tools.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_PlaneTools.hxx>
#include <Cad3d_SurfaceOnSolid.hxx>
#include <Cad3d_SurfaceOnSolidTools.hxx>
#include <Mesh2d_BoundaryNode.hxx>
#include <Mesh2d_DegenBoundaryNode.hxx>
#include <Mesh2d_SurfaceBoundaryNode.hxx>
#include <Mesh2d_BoundaryEdge.hxx>
#include <Mesh2d_NodeTools.hxx>
#include <Mesh2d_SizeMap.hxx>
#include <Mesh2d_QualityMap.hxx>
#include <SizeMap2d_FullIntAnIsoTools.hxx>
#include <SizeMap2d_FullIntAnIsoRefineSearchRefineElementSize.hxx>
#include <SizeMap3d_SurfaceSizeMap.hxx>
#include <MetricMap_ApproxSurfaceMetric.hxx>
#include <MetricMap_ExactSurfaceMetric.hxx>
#include <Mesh2d_Domain.hxx>
#include <Mesh2d_BasicAft.hxx>
#include <Mesh2d_Optimization.hxx>
#include <QualityMap2d_Vlrms2Ratio.hxx>
#include <TColMesh2d_ADTree2dOfNode.hxx>
#include <TColMesh2d_HAry1dOfNode.hxx>

using namespace AutLib;
using namespace MeshLib;
using namespace CadLib;
using namespace GeoLib;

#include <GeomAPI_Interpolate.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <Geom2dAPI_Interpolate.hxx>
#include <Geom_Surface.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <BRep_Tool.hxx>
#include <TColgp_HArray1OfPnt.hxx>
#include <TColGeom_HArray1OfBSplineCurve.hxx>
#include <TColGeom2d_HArray1OfBSplineCurve.hxx>

#define NORMALIZED(X, X1, X2) (X - X1) / (X2 - X1)

static const Standard_Real DEFAULT_GRADIENTFACTOR = 5.0;
static const Standard_Real DEFAULT_MINGRADATION = 0.5;
static const Standard_Real DEFAULT_SMOOTHING_FACTOR = 1.5;
static const Standard_Real DEFAULT_DEGENERACY = 1.0E-5;
static const Standard_Integer DEFAULT_MAXITERS = 5;


AutLib::MeshLib::Mesh3d_SurfaceMesher::Mesh3d_SurfaceMesher
(
	const Mesh3d_SizeMap & SizeMap,
	const M_CAD Cad3d_SurfaceOnSolid& theSurface
)
	: theSizeMap_(SizeMap)
	, theSurface_(&theSurface)
	, theMaxGradation_(DEFAULT_GRADIENTFACTOR)
	, ApplySmoothing_(Standard_True)
	, UseExactMetric_(Standard_False)
	, IsDone_(Standard_False)
	, theSurfaceName_("Unknown")
	, theVerbose_(0)
	, theSmoothingFactor_(DEFAULT_SMOOTHING_FACTOR)
	, theDegeneracy_(DEFAULT_DEGENERACY)
	, CreateAnIsoSizeMap(&SizeMap2d_FullIntAnIsoTools::CreateModifiedSearchAndElementSizeAnIsoSizeMap)
	, FaceMODE_(Standard_False)
	, theIndex_(theSurface.Index())
	, ApplyOptimization_(Standard_True)
{
}

AutLib::MeshLib::Mesh3d_SurfaceMesher::Mesh3d_SurfaceMesher
(
	const Mesh3d_SizeMap & SizeMap,
	const TopoDS_Face & theSurface
)
	: theSizeMap_(SizeMap)
	, theMaxGradation_(DEFAULT_GRADIENTFACTOR)
	, ApplySmoothing_(Standard_True)
	, UseExactMetric_(Standard_False)
	, IsDone_(Standard_False)
	, theSurfaceName_("Unknown")
	, theVerbose_(0)
	, theSmoothingFactor_(DEFAULT_SMOOTHING_FACTOR)
	, theDegeneracy_(DEFAULT_DEGENERACY)
	, CreateAnIsoSizeMap(&SizeMap2d_FullIntAnIsoTools::CreateModifiedSearchAndElementSizeAnIsoSizeMap)
	, FaceMODE_(Standard_True)
	, ApplyOptimization_(Standard_True)
{
	theSurface_ = Cad3d_SurfaceOnSolidTools::GetSurfaceOnSolid(theSurface);
}

AutLib::MeshLib::Mesh3d_SurfaceMesher::~Mesh3d_SurfaceMesher()
{
	FreePointer(theAppxSurfaceMetric_);

}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::ApplyMetricSmoothing(const Standard_Boolean ApplySmoothing)
{
	ApplySmoothing_ = ApplySmoothing;
}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::ApplyOptimization(const Standard_Boolean ApplyOptimization)
{
	ApplyOptimization_ = ApplyOptimization;
}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::SetMaxMetricGradation(const Standard_Real Gradation)
{
	theMaxGradation_ = MAX(DEFAULT_MINGRADATION, Gradation);
}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::SetIndex(const Standard_Integer theIndex)
{
	theIndex_ = theIndex;
}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::SetSurfaceName(const Standard_String Name)
{
	theSurfaceName_ = Name;
}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::SetVerbosity(const Standard_Integer theVerbose)
{
	theVerbose_ = theVerbose;
}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::SetSmoothingFactor(const Standard_Real theSmoothingFactor)
{
	theSmoothingFactor_ = theSmoothingFactor;
}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::SetAnIsoSizeMap(Global_Handle(SizeMap2d_FullIntAnIso)(*theCreateAnIsoSizeMap)(const Global_Handle(Mesh2d_SizeMap), const Global_Handle(Mesh2d_MetricMap)))
{
	CreateAnIsoSizeMap = theCreateAnIsoSizeMap;
}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::UseExactMetric()
{
	UseExactMetric_ = Standard_True;
}

namespace AutLib
{
	namespace MeshLib
	{
		static void RetrieveCoords(const Handle(Geom_Surface)& theSurface, const Mesh2d_TMesh& theTMesh, M_GEO Entity_Triangulation2d& theParaMesh, M_GEO Entity_Triangulation3d& theSurfaceMesh)
		{
			TColMesh2d_HAry1dOfNode Nodes = theTMesh.SortedNodes();
			TColMesh2d_HAry1dOfElement Elements = theTMesh.SortedElements();

			Get_Object(Points2d) = theParaMesh.Points();
			Get_Object(Points3d) = theSurfaceMesh.Points();

			Get_Object(Tris2d) = theParaMesh.Triangles();
			Get_Object(Tris3d) = theSurfaceMesh.Triangles();

			Points2d.Resize(Nodes.Size());
			Tris2d.Resize(Elements.Size());

			Points3d.Resize(Nodes.Size());
			Tris3d.Resize(Elements.Size());

			forThose
			(
				Index,
				0,
				MaxIndexOf(Nodes)
			)
			{
				Points2d[Index] = Nodes[Index]->Coord();
				Points3d[Index] = theSurface->Value(Points2d[Index].X(), Points2d[Index].Y());
			}

			forThose
			(
				Index,
				0,
				MaxIndexOf(Elements)
			)
			{
				Tris2d[Index].SetValue(Elements[Index]->Node0()->Index(), Elements[Index]->Node1()->Index(), Elements[Index]->Node2()->Index());
				Tris3d[Index].SetValue(Elements[Index]->Node0()->Index(), Elements[Index]->Node1()->Index(), Elements[Index]->Node2()->Index());
			}
		}
	}
}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::Perform()
{
	SizeMap3d_SurfaceSizeMap SurfaceSizeMap(theSizeMap_, theSurface_->Geometry());

	theAppxSurfaceMetric_ = new MetricMap_ApproxSurfaceMetric(*theSurface_);
	Get_Object(AppxSurfaceMetric) = *theAppxSurfaceMetric_;

	AppxSurfaceMetric.SetSurfaceName(theSurfaceName_);

	Entity_Box2d BoundingBox = AppxSurfaceMetric.CalcBoundingBox();
	AppxSurfaceMetric.SetBoundingBox(BoundingBox);
	AppxSurfaceMetric.SetDegeneracy(theDegeneracy_);

	AppxSurfaceMetric.Perform();

	AppxSurfaceMetric.SetIntersection(&Entity_Metric1Tools::IntersectionSR);
	//if (ApplySmoothing_)
	//{
	//	AppxSurfaceMetric.SetIntersection(&Entity_Metric1Tools::IntersectionSR);	
		//AppxSurfaceMetric.HvCorrection(theSmoothingFactor_);
	//}

	MetricMap_ExactSurfaceMetric ExactSurfaceMetric(*theSurface_);
	ExactSurfaceMetric.SetBoundingBox(BoundingBox);

	Global_Handle(SizeMap2d_FullIntAnIso) FullAppxAnIso = CreateAnIsoSizeMap(&SurfaceSizeMap, &AppxSurfaceMetric);
	Global_Handle(SizeMap2d_FullIntAnIso) FullExactAnIso = CreateAnIsoSizeMap(&SurfaceSizeMap, &ExactSurfaceMetric);

	TColMesh2d_ADTree2dOfNode SearchEngine;
	SearchEngine.SetRegion(AppxSurfaceMetric.BoundingBox());
	SearchEngine.SetCoordinateFunction(&Mesh2d_NodeTools::GetCoordOf);

	Cad2d_Plane Plane;
	theSurface_->GetParametricPlane(Plane);

	Mesh2d_Domain Domain(*FullExactAnIso, &Plane, 1.0E-6);

	Try_Exception_Handle_Exit(Domain.Perform());

	if (NOT Domain.IsDone())
	{
		THROW_STANDARD_EXCEPTION(" Boundary Region Is NOT discretized");
	}

	theBoundary_ = Domain.Merged();

	Global_Handle(SizeMap2d_FullIntAnIso) DomainMap;
	if (UseExactMetric_) DomainMap = FullExactAnIso;
	else DomainMap = FullAppxAnIso;

	Mesh2d_BasicAft Aft(*DomainMap, *FullExactAnIso, &SearchEngine);
	if (theVerbose_) Aft.SetVerbosity(theVerbose_);
	if (ApplySmoothing_) Aft.LaplacianSmoothing().SetApply(Standard_True);

	auto edges = RemoveDegeneracy2(AppxSurfaceMetric, ExactSurfaceMetric, *DomainMap, *FullExactAnIso, 1.0E-6);
	Aft.Perform(edges);

	Global_Handle(Mesh2d_MetricMap) MetricMap(0);
	if (UseExactMetric_) MetricMap = &ExactSurfaceMetric;
	else MetricMap = &AppxSurfaceMetric;

	/*if (ApplyOptimization_)
	{
		QualityMap2d_Vlrms2Ratio QualityMap;

		Mesh2d_Optimization Optimization(QualityMap, SurfaceSizeMap, &ExactSurfaceMetric, Aft);
		Optimization.SetVerbosity(theVerbose_ - 1);
		Optimization.Perform();
	}*/

	theModifiedBoundary_ = Mesh2d_EdgeTools::RetrieveChainFrom(Aft.Boundary());

	// Move degeneracy nodes to original location
	TColMesh2d_HAry1dOfNode BoundaryNodes = Mesh2d_EdgeTools::RetrieveNodesFrom(Aft.Boundary());
	forThose(Index, 0, MaxIndexOf(BoundaryNodes))
		if (Global_DownCast(Mesh2d_DegenBoundaryNode, BoundaryNodes[Index])) 
			Global_DownCast(Mesh2d_DegenBoundaryNode, BoundaryNodes[Index])->TranslateToOrigin();

	::RetrieveCoords(theSurface_->Geometry(), *Aft.Mesh(0), theParaMesh_, theSurfaceMesh_);

	if (theSurface_->Orientation() EQUAL Cad3d_SurfaceOrientation_OUTWARD) theSurfaceMesh_.Reverse();

	FreePointer(FullExactAnIso);
	if (FaceMODE_)
	{
		Global_Handle(Cad3d_SurfaceOnSolid) Surface = (Global_Handle(Cad3d_SurfaceOnSolid))(theSurface_);
		FreePointer(Surface);
	}
	IsDone_ = Standard_True;
}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::ExportDomainToPlt(fstream & File) const
{
	theBoundary_.ExportToPlt(File);
}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::ExportQualityMeshToPlt
(
	fstream & File, 
	const Mesh2d_QualityMap& theQualityMap
) const
{
	Get_Const_Object(Coords) = theParaMesh_.Points();
	Get_Const_Object(Triangles) = theParaMesh_.Triangles();

	MetricMap_ExactSurfaceMetric ExactSurfaceMetric(*theSurface_);

	TColStd_Ary1dOfReal Quality(Triangles.Size());
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Triangles)
	)
	{
		Standard_Integer V0 = Triangles[Index].V0();
		Standard_Integer V1 = Triangles[Index].V1();
		Standard_Integer V2 = Triangles[Index].V2();

		Quality[Index] = ExactSurfaceMetric.ElementQuality(Coords[Index_Of(V0)], Coords[Index_Of(V1)], Coords[Index_Of(V2)], theQualityMap);
	}

	Primitive_Field Field(1, Quality.Size());
	forThose(Index, 0, MaxIndexOf(Quality))
	{
		Field.SetValue(Index, 0, Quality[Index]);
	}
	Field.SetVariablesName("Quality[0-1]");

	M_IO IO_TecPlot::ExportCellCenteredField(SurfaceMesh(), Field, File);
}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::ExportModifiedDomainToPlt(fstream & File) const
{
	theModifiedBoundary_.ExportToPlt(File);
}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::ExportSurfaceMetricDeterminant(fstream & File) const
{
	if (theAppxSurfaceMetric_) theAppxSurfaceMetric_->Metric().ExportMetricDeterminantToPlt(File);
}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::ExportSingularityHorizonToPlt(fstream & File) const
{
	if (NOT theAppxSurfaceMetric_) return;
	if (theAppxSurfaceMetric_->NbSingularityHorizons())
	{
		Mesh3d_SurfaceMesher::ExportSurfaceMetricDeterminant(File);

		forThose
		(
			Index,
			0, 
			theAppxSurfaceMetric_->NbSingularityHorizons() - 1
		)
		{
			Get_Const_Object(SingularityHorizon) = *theAppxSurfaceMetric_->SingularityHorizon(Index);

			Primitive_Field Field(1, SingularityHorizon.NbPoints());
			forThose
			(
				I,
				1,
				SingularityHorizon.NbPoints()
			)
			{
				//Standard_Real Determinant = theAppxSurfaceMetric_->MetricAt(SingularityHorizon.Point(Index_Of(I))).Determinant();
				Standard_Real Determinant = theDegeneracy_;
				Field.SetValue(Index_Of(I), 0, Determinant);
			}
			//SingularityHorizon.ExportToPlt(File);
			SingularityHorizon.ExportToPlt(Field, File);
		}
	}
}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::ExportModifiedMetricDomain(fstream & File) const
{
	theAppxSurfaceMetric_->Metric().ExportMeshToPlt(File);
	theModifiedBoundary_.ExportToPlt(File);
}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::ExportSurfaceMeshToPlt(fstream & File) const
{
	theSurfaceMesh_.ExportToPlt(File);
}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::ExportParametricMeshToPlt(fstream & File) const
{
	theParaMesh_.ExportToPlt(File);
}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::ExportParametricBoundaryToPlt(fstream & File) const
{
	theBoundary_.ExportToPlt(File);
}

void AutLib::MeshLib::Mesh3d_SurfaceMesher::RemoveDegeneracy
(
	const MetricMap_ApproxSurfaceMetric & Metric,
	GeoLib::Entity_StaticChain2d & Repaired,
	const Standard_Real Degeneracy
)
{
	Handle(Geom_Surface) PatchPtr = theSurface_->Geometry();

	const Standard_Real Dmax = Metric.MaxMetricDeterminant();

	Repaired = theBoundary_;

	Get_Const_Object(Polygon) = Metric.SingularityHorizon(0)->Points();
	TColGeom_Ary1dOfPnt3d Poly3d(Polygon.Size());

	forThose(Index, 0, MaxIndexOf(Poly3d))
	{
		Poly3d[Index] = PatchPtr->Value(Polygon[Index].X(), Polygon[Index].Y());
	}

	Get_Object(Coords) = Repaired.Coords();

	Handle(TColgp_HArray1OfPnt) Q3d = new TColgp_HArray1OfPnt(1, Poly3d.Size());
	forThose(Index, 1, Poly3d.Size()) { (*Q3d)(Index) = Poly3d[Index - 1]; }

	Handle(TColgp_HArray1OfPnt2d) Q2d = new TColgp_HArray1OfPnt2d(1, Polygon.Size());
	forThose(Index, 1, Polygon.Size()) { (*Q2d)(Index) = Polygon[Index - 1]; }

	GeomAPI_Interpolate IntCurve3d(Q3d, Standard_False, 1.0E-8);
	IntCurve3d.Perform();

	Geom2dAPI_Interpolate IntCurve2d(Q2d, Standard_False, 1.0E-12);
	IntCurve2d.Perform();

	Handle(Geom2d_BSplineCurve) Curve2d = IntCurve2d.Curve();

	GeomAPI_ProjectPointOnCurve Project;
	Project.Init(IntCurve3d.Curve(), IntCurve3d.Curve()->FirstParameter(), IntCurve3d.Curve()->LastParameter());

	Standard_Real First3d = IntCurve3d.Curve()->FirstParameter();
	Standard_Real Last3d = IntCurve3d.Curve()->LastParameter();

	Standard_Real First2d = IntCurve2d.Curve()->FirstParameter();
	Standard_Real Last2d = IntCurve2d.Curve()->LastParameter();

	forThose
	(
		Index,
		0,
		MaxIndexOf(Coords)
	)
	{

		if (Metric.MetricAt(Coords[Index]).Determinant() / Dmax < Degeneracy)
		{

			Project.Perform(PatchPtr->Value(Coords[Index].X(), Coords[Index].Y()));

			if (NOT Project.NbPoints())
			{
				//CloseProgram(" Fatal Error @ Mesh3d_SurfaceMesher::RemoveDegeneracy()");
				Coords[Index] = Curve2d->Value(First2d + 0.5*(Last2d - First2d));

				continue;
			}

			if (Project.NbPoints() == 1)
			{
				Standard_Real t = NORMALIZED(Project.Parameter(1), First3d, Last3d);
				Coords[Index] = Curve2d->Value(First2d + t*(Last2d - First2d));

				continue;
			}

			Standard_Real t = NORMALIZED(Project.LowerDistanceParameter(), First3d, Last3d);
			Coords[Index] = Curve2d->Value(First2d + t*(Last2d - First2d));

		}
	}
}

namespace AutLib
{
	namespace MeshLib
	{
		static Handle(Geom2d_BSplineCurve) InterpolateCurve(const TColGeom_Ary1dOfPnt2d& theCoords)
		{
			Handle(TColgp_HArray1OfPnt2d) QPts = new TColgp_HArray1OfPnt2d(1, theCoords.Size());
			forThose(Index, 1, theCoords.Size()) { (*QPts)(Index) = theCoords[Index - 1]; }

			Geom2dAPI_Interpolate IntCurve(QPts, Standard_False, 1.0E-12);
			IntCurve.Perform();

			return IntCurve.Curve();
		}

		static Handle(Geom_BSplineCurve) InterpolateCurve(const TColGeom_Ary1dOfPnt3d& theCoords)
		{
			Handle(TColgp_HArray1OfPnt) QPts = new TColgp_HArray1OfPnt(1, theCoords.Size());
			forThose(Index, 1, theCoords.Size()) { (*QPts)(Index) = theCoords[Index - 1]; }

			GeomAPI_Interpolate IntCurve(QPts, Standard_False, 1.0E-12);
			IntCurve.Perform();

			return IntCurve.Curve();
		}

		static TColGeom_Ary1dOfPnt3d GetCoords3d(const TColGeom_Ary1dOfPnt2d& theCoords, const Handle(Geom_Surface)& theSurface)
		{
			TColGeom_Ary1dOfPnt3d Pts(theCoords.Size());
			forThose(Index, 0, MaxIndexOf(theCoords))
				Pts.SetValue(Index, theSurface->Value(theCoords[Index].X(), theCoords[Index].Y()));
			return Pts;
		}

		static const Handle(TColGeom2d_HArray1OfBSplineCurve) GetParaCurves(const MetricMap_ApproxSurfaceMetric & theMetric)
		{
			if (NOT theMetric.NbSingularityHorizons()) return 0;
			Handle(TColGeom2d_HArray1OfBSplineCurve) Curves = new TColGeom2d_HArray1OfBSplineCurve(1, theMetric.NbSingularityHorizons());
			forThose(Index, 1, theMetric.NbSingularityHorizons())
			{
				(*Curves).SetValue(Index, ::InterpolateCurve(theMetric.SingularityHorizon(Index_Of(Index))->Points()));
			}
			return Curves;
		}

		static const Handle(TColGeom_HArray1OfBSplineCurve) GetCurves(const MetricMap_ApproxSurfaceMetric & theMetric, const Handle(Geom_Surface)& theSurface)
		{
			if (NOT theMetric.NbSingularityHorizons()) return 0;
			Handle(TColGeom_HArray1OfBSplineCurve) Curves = new TColGeom_HArray1OfBSplineCurve(1, theMetric.NbSingularityHorizons());
			forThose(Index, 1, theMetric.NbSingularityHorizons())
			{
				(*Curves).SetValue(Index, ::InterpolateCurve(::GetCoords3d(theMetric.SingularityHorizon(Index_Of(Index))->Points(), theSurface)));
			}
			return Curves;
		}

		static Geom_Pnt2d GetParameter(const Geom_Pnt3d& theCoord, const Handle(TColGeom2d_HArray1OfBSplineCurve)& theParaCurves, const Handle(TColGeom_HArray1OfBSplineCurve)& theCurves)
		{
			GeomAPI_ProjectPointOnCurve Projection;
			TColGeom_Ary1dOfPnt2d Parameters(theCurves->Size());
			TColGeom_Ary1dOfPnt3d Points(theCurves->Size());
			TColStd_Ary1dOfReal Dis(theCurves->Size());
			forThose
			(
				Index, 
				1,
				theCurves->Size()
			)
			{
				const Handle(Geom_BSplineCurve)& Curve = theCurves->Value(Index);
				const Handle(Geom2d_BSplineCurve)& ParaCurve = theParaCurves->Value(Index);

				Projection.Init(theCoord, Curve);
				Projection.Perform(theCoord);

				Standard_Real First = Curve->FirstParameter();
				Standard_Real Last = Curve->LastParameter();

				Standard_Real ParaFirst = ParaCurve->FirstParameter();
				Standard_Real ParaLast = ParaCurve->LastParameter();

				if (NOT Projection.NbPoints())
				{
					Parameters[Index_Of(Index)] = ParaCurve->Value(MEAN(ParaFirst, ParaLast));
					Points[Index_Of(Index)] = Curve->Value(MEAN(First, Last));

					Dis[Index_Of(Index)] = Distance(theCoord, Points[Index_Of(Index)]);
					continue;
				}

				Standard_Real t = NORMALIZED(Projection.LowerDistanceParameter(), First, Last);
				Parameters[Index_Of(Index)] = ParaCurve->Value(ParaFirst + t * (ParaLast - ParaFirst));
				Points[Index_Of(Index)] = Projection.NearestPoint();

				Dis[Index_Of(Index)] = Distance(theCoord, Points[Index_Of(Index)]);
			}

			Standard_Real Dmin = RealLast();
			Standard_Integer MinIndex = 0;

			forThose
			(
				Index,
				0,
				MaxIndexOf(Dis)
			)
			{
				if (Dis[Index] < Dmin)
				{
					MinIndex = Index;
					Dmin = Dis[Index];
				}
			}
			return Parameters[MinIndex];
		}
	}
}

TColMesh2d_HAry1dOfEdge AutLib::MeshLib::Mesh3d_SurfaceMesher::RemoveDegeneracy2
(
	const MetricMap_ApproxSurfaceMetric & theApproxMetric,
	const MetricMap_ExactSurfaceMetric theExactMetric,
	const Mesh2d_SizeMap& theSizeMap,
	const Mesh2d_SizeMap& theBoundarySizeMap,
	const Standard_Real theDegeneracy
)
{
	const Standard_Real Dmax = theApproxMetric.MaxMetricDeterminant();

	Handle(Geom_Surface) PatchPtr = theSurface_->Geometry();

	Get_Const_Object(Coords) = theBoundary_.Coords();
	TColMesh2d_HAry1dOfNode Nodes(Coords.Size());
	
	Handle(TColGeom2d_HArray1OfBSplineCurve) ParaCurves = ::GetParaCurves(theApproxMetric);
	Handle(TColGeom_HArray1OfBSplineCurve) Curves = ::GetCurves(theApproxMetric, PatchPtr);	
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Coords)
	)
	{
		Global_Handle(Mesh2d_Node) Node;
		if (theExactMetric.MetricAt(Coords[Index]).Determinant() / Dmax < theDegeneracy)
		{		
			Geom_Pnt2d Coord = ::GetParameter(PatchPtr->Value(Coords[Index].X(), Coords[Index].Y()), ParaCurves, Curves);
			Node = new Mesh2d_DegenBoundaryNode(Index + 1, Coord, Coords[Index]);
		}
		else
		{
			Node = new Mesh2d_SurfaceBoundaryNode(Index + 1, Coords[Index]);
		}
		Nodes.SetValue(Index, Node);
	}

	Get_Const_Object(Edges) = theBoundary_.Edges();

	TColMesh2d_HAry1dOfEdge Boundary(Edges.Size());
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Edges)
	)
	{
		Get_Object(Node0) = *Nodes[Index_Of(Edges[Index].V0())];
		Get_Object(Node1) = *Nodes[Index_Of(Edges[Index].V1())];

		Standard_Real Length = theBoundarySizeMap.CalcDistance(Node0.Coord(), Node1.Coord());

		Geom_Pnt2d Centre;
		if (Length <= theDegeneracy)  // Debug: 8/8/2018
		{
			Centre = MEAN(Node0.Coord(), Node1.Coord());
		}
		else
		{
			Centre = theSizeMap.CalcCentreOf(Node0.Coord(), Node1.Coord());  // Debug: 5/18/2018
		}
		
		Boundary[Index] =
			new Mesh2d_BoundaryEdge
			(
				Index + 1,
				Length,
				Centre,  
				&Node0,
				&Node1
			);

		Try_Exception_Handle_Exit(Node0.InsertToEdges(Boundary[Index]));
		Try_Exception_Handle_Exit(Node1.InsertToEdges(Boundary[Index]));
	}
	MOVE(Boundary);
}