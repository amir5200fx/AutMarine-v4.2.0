#include <Mesh3d_FaceDiscrete.hxx>

#include <Entity_Box2d.hxx>
#include <Entity_Polygon2d.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_CurveOnPlane.hxx>
#include <Cad3d_SurfaceOnSolidTools.hxx>
#include <SizeMap2d_FullIntAnIso.hxx>
#include <SizeMap2d_FullIntAnIsoTools.hxx>
#include <SizeMap3d_UniSize.hxx>
#include <SizeMap3d_SurfaceSizeMap.hxx>
#include <MetricMap_ApproxSurfaceMetric.hxx>
#include <MetricMap_ExactSurfaceMetric.hxx>
#include <Mesh2d_DegenBoundaryNode.hxx>
#include <Mesh2d_NodeTools.hxx>
#include <Mesh2d_Domain.hxx>
#include <Mesh2d_BasicAft.hxx>
#include <QualityMap2d_Vlrms2Ratio.hxx>
#include <Mesh2d_Optimization.hxx>
#include <TColStd_Ary1dOfInteger.hxx>
#include <TColCad2d_HAry1dOfCurveOnPlane.hxx>
#include <TColCad2d_HBasicQueueOfCurveOnPlane.hxx>
#include <TColMesh2d_ADTree2dOfNode.hxx>

#include <TopoDS.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopExp_Explorer.hxx>
#include <BRep_Tool.hxx>
#include <BRepTools.hxx>
#include <ShapeAnalysis.hxx>
#include <ShapeAnalysis_Edge.hxx>
#include <ShapeAnalysis_Wire.hxx>
#include <ShapeAnalysis_WireOrder.hxx>
#include <ShapeFix_Wire.hxx>
#include <ShapeFix_Shape.hxx>
#include <ShapeBuild_ReShape.hxx>
#include <Geom_Surface.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;
using namespace MeshLib;

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
#define GET_DOMAIN_NAME theSurfaceName_

static const Standard_Real DEFAULT_DEGENERACY = 1.0E-5;

AutLib::MeshLib::Mesh3d_FaceDiscrete::Mesh3d_FaceDiscrete
(
	const Standard_Real theSize,
	const TopoDS_Face & theFace
)
	: theFace_(theFace)
	, ApplySmoothing_(Standard_True)
	, UseExactMetric_(Standard_False)
	, IsDone_(Standard_False)
	, theSurfaceName_("Unknown")
	, theVerbose_(0)
	, theDegeneracy_(DEFAULT_DEGENERACY)
	, theSize_(theSize)
	, CreateAnIsoSizeMap(&SizeMap2d_FullIntAnIsoTools::CreateModifiedSearchAnIsoSizeMap)
{
}

void AutLib::MeshLib::Mesh3d_FaceDiscrete::ApplySmoothing(const Standard_Boolean ApplySmoothing)
{
	ApplySmoothing_ = ApplySmoothing;
}

void AutLib::MeshLib::Mesh3d_FaceDiscrete::ApplyOptimization(const Standard_Boolean ApplyOptimization)
{
	ApplyOptimization_ = ApplyOptimization;
}

void AutLib::MeshLib::Mesh3d_FaceDiscrete::SetToUseExactMetric()
{
	UseExactMetric_ = Standard_True;
}

void AutLib::MeshLib::Mesh3d_FaceDiscrete::SetSurfaceName(const Standard_String Name)
{
	theSurfaceName_ = Name;
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

void AutLib::MeshLib::Mesh3d_FaceDiscrete::Perform()
{
	SizeMap3d_UniSize UniSize(theSize_);
	SizeMap3d_SurfaceSizeMap SurfaceSizeMap(UniSize, BRep_Tool::Surface(theFace_));

	Global_Handle(Cad3d_SurfaceOnSolid) SurfaceOnSolid = Cad3d_SurfaceOnSolidTools::GetSurfaceOnSolid(theFace_);
	
	if (NOT SurfaceOnSolid)
	{
		THROW_BAD_BOUNDARY_EXCEPTION(" Null Surface");
	}

	Global_Handle(MetricMap_ApproxSurfaceMetric) AppxSurfaceMetric = new MetricMap_ApproxSurfaceMetric(*SurfaceOnSolid);
	AppxSurfaceMetric->SetSurfaceName(theSurfaceName_);

	Entity_Box2d BoundingBox = AppxSurfaceMetric->CalcBoundingBox();
	AppxSurfaceMetric->SetBoundingBox(BoundingBox);
	AppxSurfaceMetric->SetDegeneracy(theDegeneracy_);

	AppxSurfaceMetric->Perform();

	MetricMap_ExactSurfaceMetric ExactSurfaceMetric(*SurfaceOnSolid);
	ExactSurfaceMetric.SetBoundingBox(BoundingBox);

	Global_Handle(SizeMap2d_FullIntAnIso) FullAppxAnIso = CreateAnIsoSizeMap(&SurfaceSizeMap, AppxSurfaceMetric);
	Global_Handle(SizeMap2d_FullIntAnIso) FullExactAnIso = CreateAnIsoSizeMap(&SurfaceSizeMap, &ExactSurfaceMetric);

	TColMesh2d_ADTree2dOfNode SearchEngine;
	SearchEngine.SetRegion(AppxSurfaceMetric->BoundingBox());
	SearchEngine.SetCoordinateFunction(&Mesh2d_NodeTools::GetCoordOf);

	Global_Handle(Cad2d_Plane) Plane = GetPlane();

	Mesh2d_Domain Domain(*FullExactAnIso, Plane, 1.0E-6);

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

	Aft.Perform(RemoveDegeneracy2(*AppxSurfaceMetric, ExactSurfaceMetric, *DomainMap, *FullExactAnIso, 1.0E-6));

	if (ApplyOptimization_)
	{
		QualityMap2d_Vlrms2Ratio QualityMap;

		Mesh2d_Optimization Optimization(QualityMap, SurfaceSizeMap, &ExactSurfaceMetric, Aft);
		Optimization.SetVerbosity(theVerbose_ - 1);
		Optimization.Perform();
	}

	// Move degeneracy nodes to original location
	TColMesh2d_HAry1dOfNode BoundaryNodes = Mesh2d_EdgeTools::RetrieveNodesFrom(Aft.Boundary());
	forThose(Index, 0, MaxIndexOf(BoundaryNodes))
		if (Global_DownCast(Mesh2d_DegenBoundaryNode, BoundaryNodes[Index]))
			Global_DownCast(Mesh2d_DegenBoundaryNode, BoundaryNodes[Index])->TranslateToOrigin();

	::RetrieveCoords(BRep_Tool::Surface(theFace_), *Aft.Mesh(0), theParaMesh_, theSurfaceMesh_);

	IsDone_ = Standard_True;

	FreePointer(Plane);
	FreePointer(AppxSurfaceMetric);
	FreePointer(SurfaceOnSolid);
}

void AutLib::MeshLib::Mesh3d_FaceDiscrete::ExportTriangulationToPlt(fstream & File) const
{
	if (NOT IsDone_) return;
	theSurfaceMesh_.ExportToPlt(File);
}

void AutLib::MeshLib::Mesh3d_FaceDiscrete::ExportParametricMeshToPlt(fstream & File) const
{
	if (NOT IsDone_) return;
	theParaMesh_.ExportToPlt(File);
}

void AutLib::MeshLib::Mesh3d_FaceDiscrete::ExportParametricBoundaryToPlt(fstream & File) const
{
	theBoundary_.ExportToPlt(File);
}

namespace AutLib
{
	namespace MeshLib
	{

		static TColCad2d_HAry1dOfCurveOnPlane GetCurvesFrom(const TopoDS_Face& theFace)
		{
			TColCad2d_HBasicQueueOfCurveOnPlane QCurves;

			for (TopExp_Explorer Explorer(theFace, TopAbs_WIRE); Explorer.More(); Explorer.Next())
			{
				TopoDS_Wire Wire = TopoDS::Wire(Explorer.Current());

				ShapeFix_Wire SFWF(Wire, theFace, 1.0E-6);

				ShapeAnalysis_WireOrder WireOrder;
				ShapeAnalysis_Wire Analysis(Wire, theFace, 1.0E-6);
				Analysis.Perform();

				if (Analysis.CheckOrder())
				{
					cout << " The Wire Need ReOrder" << endl;
				}

				if (Analysis.CheckClosed(1.0E-6))
				{
					cout << " The Wire is not CLOSED: Need to be repaired" << endl;
				}

				if (Analysis.CheckSmall(1.0E-6))
				{
					cout << "Small Edge detected" << endl;
					if (SFWF.FixSmall(Standard_False, 1.0E-6))
					{
						cout << "Small Edge Removed" << endl;
					}
				}

				Wire = SFWF.Wire();

				Standard_Integer MaxIndex = 0;
				forThose(Index, 0, Analysis.NbEdges() - 1)
				{
					Standard_Integer Value = WireOrder.Ordered(Index + 1);
					if (ABS(Value) > MaxIndex) MaxIndex = ABS(Value);
				}

				TColStd_Ary1dOfInteger Order(MaxIndex + 1);
				Order.Init(1);

				Analysis.CheckOrder(WireOrder, Standard_True, Standard_False);

				if (Analysis.CheckOrder(WireOrder, Standard_True, Standard_False))
				{
					forThose(Index, 0, Analysis.NbEdges() - 1)
					{
						Standard_Integer Value = WireOrder.Ordered(Index + 1);
						Order[ABS(Value) - 1] = Value;
					}
				}

				Standard_Integer K = 0;

				for (TopExp_Explorer Explorer1(Wire, TopAbs_EDGE); Explorer1.More(); Explorer1.Next())
				{
					TopoDS_Edge Edge = TopoDS::Edge(Explorer1.Current());

					//cout << " Orientation = " << Edge.Orientation() << "  " << TopAbs_REVERSED << endl;


					TopLoc_Location Loc;
					Standard_Real First, Last;
					Handle(Geom2d_Curve) PCurve = BRep_Tool::CurveOnSurface(Edge, theFace, First, Last);
					Handle(Geom2d_Curve) CopyOfPCurve = Handle(Geom2d_Curve)::DownCast(PCurve->Copy());

					Debug_Null_Pointer(CopyOfPCurve);

					if (Order[K] < 0)
					{
						CopyOfPCurve->Reverse();
						Standard_Real Temp = Last;
						Last = CopyOfPCurve->ReversedParameter(First);
						First = CopyOfPCurve->ReversedParameter(Temp);
					}

					K++;

					if (Edge.Orientation() EQUAL TopAbs_REVERSED)
					{
						CopyOfPCurve->Reverse();
						Standard_Real Temp = Last;
						Last = CopyOfPCurve->ReversedParameter(First);
						First = CopyOfPCurve->ReversedParameter(Temp);
					}

					Global_Handle(Cad2d_CurveOnPlane) CurveOnPlane = new Cad2d_CurveOnPlane(First, Last, CopyOfPCurve);
					QCurves.EnQueue(CurveOnPlane);
				}
			}

			TColCad2d_HAry1dOfCurveOnPlane Curves;
			QCurves.RetrieveTo(Curves);

			TColCad2d_HBasicQueueOfCurveOnPlane RemovedZeroLength;
			forThose
			(
				Index,
				0,
				MaxIndexOf(Curves)
			)
			{
				Standard_Real U1 = Curves[Index]->FirstParameter();
				Standard_Real U2 = Curves[Index]->LastParameter();

				Geom_Pnt2d P1 = Curves[Index]->Curve()->Value(U1);
				Geom_Pnt2d P2 = Curves[Index]->Curve()->Value(U2);
				Geom_Pnt2d P3 = Curves[Index]->Curve()->Value(0.5*(U1 + U2));

				if (Distance(P1, P2) > EPS12 OR Distance(P1, P3) > EPS12)
				{
					RemovedZeroLength.EnQueue(Curves[Index]);
					continue;
				}
			}
			RemovedZeroLength.RetrieveTo(Curves);
			MOVE(Curves);
		}
	}
}

Global_Handle(Cad2d_Plane) AutLib::MeshLib::Mesh3d_FaceDiscrete::GetPlane() const
{
	Global_Handle(Cad2d_Plane) Plane = new Cad2d_Plane;
	Try_Exception_Handle_Exit(Plane->Make(GetCurvesFrom(theFace_)));
	return Plane;
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

TColMesh2d_HAry1dOfEdge AutLib::MeshLib::Mesh3d_FaceDiscrete::RemoveDegeneracy2
(
	const MetricMap_ApproxSurfaceMetric & theApproxMetric, 
	const MetricMap_ExactSurfaceMetric theExactMetric,
	const Mesh2d_SizeMap & theSizeMap, 
	const Mesh2d_SizeMap & theBoundarySizeMap, 
	const Standard_Real theDegeneracy
)
{
	const Standard_Real Dmax = theApproxMetric.MaxMetricDeterminant();

	Handle(Geom_Surface) PatchPtr = BRep_Tool::Surface(theFace_);

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