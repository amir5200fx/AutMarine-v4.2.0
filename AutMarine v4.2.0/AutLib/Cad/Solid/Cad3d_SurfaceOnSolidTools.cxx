#include <Cad3d_SurfaceOnSolidTools.hxx>

#include <Entity_Box3d.hxx>
#include <Entity_Box3dTools.hxx>
#include <Entity_IndexedPt3d.hxx>
#include <Entity_IndexedPt3dTools.hxx>
#include <Entity_Triangulation3d.hxx>
#include <Cad3d_RingOnSurface.hxx>
#include <Cad3d_RingCurveOnPlane.hxx>
#include <Cad3d_CurveOnPlane.hxx>
#include <Cad3d_SurfaceOnSolid.hxx>
#include <Cad3d_EdgeOnSolid.hxx>
#include <Cad3d_EdgeOnSolidTools.hxx>
#include <Cad3d_CurveOnSurface.hxx>
#include <Cad3d_EdgeOnPlane.hxx>
#include <Cad3d_WireOnPlaneTools.hxx>
#include <Cad3d_WireOnPlane.hxx>
#include <Cad3d_Plane.hxx>
#include <Merge_Pnt3d.hxx>
#include <Geom_ADTree3d.hxx>
#include <Geom_ADTree2d.hxx>
#include <Geometry_Sort.hxx>
#include <Entity_Box3d.hxx>
#include <TColGeom_BasicQueueOfPnt3d.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <TColCad3d_HBasicQueueOfCurveOnPlane.hxx>
#include <TColCad3d_HBasicQueueOfEdgeOnSolid.hxx>
#include <TColCad3d_HBasicQueueOfEdgeOnPlane.hxx>
#include <TColCad3d_HBasicQueueOfCurveOnSurface.hxx>
#include <TColCad3d_HAry1dOfEdgeOnSolid.hxx>
#include <TColCad3d_HAry1dOfCurveOnSurface.hxx>
#include <TColCad3d_HAry1dOfCurveOnPlane.hxx>
#include <TColGeom_HAry1dOfPnt3d.hxx>
#include <TColGeom_HAry1dOfPnt2d.hxx>
#include <TColStd_BasicQueueOfReal.hxx>
#include <TColStd_Ary1dOfReal.hxx>
#include <TColEntity_HAry1dOfIndexedPt3d.hxx>
#include <TColEntity_Ary1dOfTriangleIndex.hxx>

#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace CadLib;

#include <TopExp_Explorer.hxx>
#include <ShapeExtend_WireData.hxx>
#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>
#include <BRep_Tool.hxx>
#include <BRepTools_WireExplorer.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <ShapeFix_Wire.hxx>
#include <ShapeAnalysis_Wire.hxx>
#include <ShapeAnalysis_WireOrder.hxx>

#define CONTINE_EXPRESSION \
  FreePointer(NewSurface); \
  return NULL;

Entity_Box3d AutLib::CadLib::Cad3d_SurfaceOnSolidTools::BoundingBoxOf
(
	const TColCad3d_HAry1dOfSurfaceOnSolid & Surfaces,
	const Standard_Real Offset
)
{
	if (NOT Surfaces.Size()) THROW_STANDARD_EXCEPTION(" The Surface list is empty");

	Debug_Null_Pointer(Surfaces.First());
	Entity_Box3d Box = Surfaces.First()->BoundingBox();

	forThose
	(
		Index,
		1,
		MaxIndexOf(Surfaces)
	)
	{
		Debug_Null_Pointer(Surfaces[Index]);

		Box = Entity_Box3dTools::Union(Box, Surfaces[Index]->BoundingBox());
	}

	return Box.OffsetBox(Offset);
}

Global_Handle(Entity_Triangulation3d) AutLib::CadLib::Cad3d_SurfaceOnSolidTools::TriangulationOf(const TopoDS_Face & theFace)
{
	TopLoc_Location Loc;
	Handle(Poly_Triangulation) Triangulation = BRep_Tool::Triangulation(theFace, Loc);

	Global_Handle(Entity_Triangulation3d) myTriangulation = new Entity_Triangulation3d;
	if (Triangulation.IsNull()) return myTriangulation;

	const Poly_Array1OfTriangle& Triangles = Triangulation->Triangles();
	const TColgp_Array1OfPnt& Nodes = Triangulation->Nodes();
	
	TColEntity_Ary1dOfTriangleIndex& myTriangles = myTriangulation->Triangles();
	TColGeom_Ary1dOfPnt3d& myPts = myTriangulation->Points();

	myTriangles.Resize(Triangles.Size());
	myPts.Resize(Nodes.Size());

	Standard_Integer K = 0;
	forThose
	(
		Index,
		0,
		MaxIndexOf(myTriangles)
	)
	{
		Poly_Triangle TriangleIndex = Triangles.Value(Index + Triangles.Lower());
		Standard_Integer I1, I2, I3;
		TriangleIndex.Get(I1, I2, I3);
		myTriangles[Index].SetValue(I1, I2, I3);
	}

	K = 0;
	forThose(Index, 0, MaxIndexOf(myPts))
	{
		myPts[Index] = Geom_Pnt3d(Nodes.Value(Index + Nodes.Lower()));
	}
	return myTriangulation;
}

Standard_Boolean AutLib::CadLib::Cad3d_SurfaceOnSolidTools::CheckForConfomity
(
	const Cad3d_SurfaceOnSolid & theSurface, 
	const Standard_Real Tolerance
)
{
	Get_Const_Object(Edges) = theSurface.Edges();

	forThose(Index, 0, MaxIndexOf(Edges))
	{
		Debug_Null_Pointer(Edges[Index]);

		if (Cad3d_EdgeOnSolidTools::CheckForConfomity(*Edges[Index], Tolerance))
			return Standard_True;
	}

	return Standard_False;
}

//Standard_Boolean AutLib::CadLib::Cad3d_SurfaceOnSolidTools::CheckForConfomityWithDirection
//(
//	const Cad3d_SurfaceOnSolid & theSurface, 
//	const Standard_Real Tolerance
//)
//{
//	Get_Const_Object(Edges) = theSurface.Edges();
//
//	forThose(Index, 0, MaxIndexOf(Edges))
//	{
//		Debug_Null_Pointer(Edges[Index]);
//
//		if (Cad3d_EdgeOnSolidTools::CheckForConfomityWithDirection(*Edges[Index], Tolerance))
//			return Standard_True;
//	}
//
//	return Standard_False;
//}

namespace AutLib
{
	namespace CadLib
	{

		class DiscreteParameters
		{

		public:

			DiscreteParameters
			(
				const Global_Handle(Cad3d_EdgeOnSolid) Edge,
				Global_Handle(TColStd_Ary1dOfReal) the3D,
				Global_Handle(TColStd_Ary1dOfReal) the2D
			)
				: theEdge_(Edge)
				, the3D_(the3D)
				, the2D_(the2D)
			{}

			~DiscreteParameters()
			{
				FreePointer(the2D_);
				FreePointer(the3D_);
			}

			const Global_Handle(Cad3d_EdgeOnSolid) theEdge_;

			Global_Handle(TColStd_Ary1dOfReal) the3D_;
			Global_Handle(TColStd_Ary1dOfReal) the2D_;
		};

		static Global_Handle(DiscreteParameters) Calc3DDiscreteParameters(const Cad3d_EdgeOnSolid& theEdge, const Geom_ADTree3d<Global_Handle(Geom_Pnt3d)>& Register, const Standard_Real Tolerance)
		{
			Debug_Null_Pointer(theEdge.CurveOnSurface());

			Get_Const_Object(EdgeOnSurface) = *theEdge.CurveOnSurface();

			Debug_Null_Pointer(EdgeOnSurface.Curve());

			Entity_Box3d Box = theEdge.CurveOnSurface()->BoundingBox();
			Box.Expand(0.01*Box.Diameter());

			TColGeom_HAry1dOfPnt3d Found;
			Register.Search(Box, Found);

			Geom_Pnt3d P0 = theEdge.CurveOnSurface()->StartCoord();
			Geom_Pnt3d P1 = theEdge.CurveOnSurface()->LastCoord();

			GeomAPI_ProjectPointOnCurve Projection;
			Projection.Init(EdgeOnSurface.Curve(), EdgeOnSurface.FirstParameter(), EdgeOnSurface.LastParameter());

			TColStd_BasicQueueOfReal QParams;
			forThose
			(
				Index,
				0, 
				MaxIndexOf(Found)
			)
			{
				Debug_Null_Pointer(Found[Index]);

				Get_Const_Object(Source) = *Found[Index];

				if (Distance(Source, P0) <= Tolerance OR Distance(Source, P1) <= Tolerance) { continue; }

				Projection.Perform(Source);

				if (NOT Projection.NbPoints()) { continue; }

				QParams.EnQueue(Projection.LowerDistanceParameter());
			}

			Global_Handle(TColStd_Ary1dOfReal) Params = new TColStd_Ary1dOfReal;
			QParams.RetrieveTo(*Params);

			if(Params->Size()) Geometry_Sort<Standard_Real>::Sort(*Params);

			return new DiscreteParameters(&theEdge, Params, NULL);
		}
	}

	typedef ADT_Ary1d<Global_Handle(CadLib::DiscreteParameters)> TColCad3d_HAry1dOfDiscreteParameters;
	typedef ADT_BasicQueue<Global_Handle(CadLib::DiscreteParameters)> TColCad3d_HBasicQueueOfDiscreteParameters;


	namespace CadLib
	{
		static TColGeom_Ary1dOfPnt2d CalcParameterCoords(const TColCad3d_HAry1dOfDiscreteParameters& theDisParameters, const Cad3d_SurfaceOnSolid & theSurface)
		{
			TColGeom_BasicQueueOfPnt3d QPts3d;
			forThose
			(
				Index,
				0, 
				MaxIndexOf(theDisParameters)
			)
			{
				Debug_Null_Pointer(theDisParameters[Index]);
				Debug_Null_Pointer(theDisParameters[Index]->theEdge_);
				Debug_Null_Pointer(theDisParameters[Index]->the3D_);
				Debug_Null_Pointer(theDisParameters[Index]->theEdge_->CurveOnSurface());

				Get_Const_Object(DisParameter) = *theDisParameters[Index];
				Get_Const_Object(Parameters) = *DisParameter.the3D_;
				Get_Const_Object(Edge) = *DisParameter.theEdge_->CurveOnSurface();
				
				forThose(I, 0, MaxIndexOf(Parameters))
					QPts3d.EnQueue(Edge.Value(Parameters[I]));

				QPts3d.EnQueue(Edge.StartCoord());
				QPts3d.EnQueue(Edge.LastCoord());
			}

			TColGeom_Ary1dOfPnt3d Pts;
			QPts3d.RetrieveTo(Pts);

			Merge_Pnt3d Merge;
			Merge.SetCoords(&Pts);
			Merge.Perform();

			Pts = Merge.CompactPoints();

			TColGeom_Ary1dOfPnt2d ProjPts(Pts.Size());

			GeomAPI_ProjectPointOnSurf Projection;
			Projection.Init(theSurface.Geometry(), theSurface.Umin(), theSurface.Umax(), theSurface.Vmin(), theSurface.Vmax());

			forThose
			(
				Index, 
				0, 
				MaxIndexOf(Pts)
			)
			{
				Projection.Perform(Pts[Index]);

				Debug_If_Condition(NOT Projection.NbPoints());

				Projection.LowerDistanceParameters(ProjPts[Index].X(), ProjPts[Index].Y());
			}

			MOVE(ProjPts);
		}

		static void Calc2DDiscreteParameters(const Geom_ADTree2d<Global_Handle(Geom_Pnt2d)>& Register, TColCad3d_HAry1dOfDiscreteParameters& theDisParameters, const Standard_Real Tolerance)
		{
			forThose
			(
				Index,
				0,
				MaxIndexOf(theDisParameters)
			)
			{
				Debug_Null_Pointer(theDisParameters[Index]);
				Debug_Null_Pointer(theDisParameters[Index]->theEdge_);
				Debug_Null_Pointer(theDisParameters[Index]->theEdge_->CurveOnPlane());

				Get_Const_Object(Curve) = *theDisParameters[Index]->theEdge_->CurveOnPlane();

				Geom_Pnt2d P0 = Curve.FirstCoord();
				Geom_Pnt2d P1 = Curve.LastCoord();

				Entity_Box2d Box = Curve.BoundingBox();

				TColGeom_HAry1dOfPnt2d Pts;
				Register.Search(Box.OffsetBox(0.1*Box.Diameter()), Pts);

				Geom2dAPI_ProjectPointOnCurve Projection;

				TColStd_BasicQueueOfReal QParams;
				forThose
				(
					I,
					0,
					MaxIndexOf(Pts)
				)
				{
					Debug_Null_Pointer(Pts[I]);

					if (Distance(P0, *Pts[I]) <= Tolerance OR Distance(P1, *Pts[I]) <= Tolerance) { continue; }

					Projection.Init(*Pts[I], Curve.Curve(), Curve.FirstParameter(), Curve.LastParameter());

					if (NOT Projection.NbPoints()) { continue; }

					QParams.EnQueue(Projection.LowerDistanceParameter());
				}

				Global_Handle(TColStd_Ary1dOfReal) Params = new TColStd_Ary1dOfReal;
				QParams.RetrieveTo(*Params);

				if (Params->Size()) Geometry_Sort<Standard_Real>::Sort(*Params);

				theDisParameters[Index]->the2D_ = Params;
			}
		}

		static TColStd_Ary1dOfReal AssembleParameters(const Standard_Real theFirst, const Standard_Real theLast, const TColStd_Ary1dOfReal& theParameters)
		{
			TColStd_Ary1dOfReal Params(theParameters.Size() + 2);
			Params.First() = theFirst;
			
			forThose(Index, 0, MaxIndexOf(theParameters))
				Params[Index + 1] = theParameters.Value(Index);

			Params.Last() = theLast;

			MOVE(Params);
		}

		static TColCad3d_HAry1dOfCurveOnPlane CurvesOnPlane(const Cad3d_CurveOnPlane& theCurve, const TColStd_Ary1dOfReal& theParameters)
		{
			Debug_Null_Pointer(theCurve.Curve());
			TColStd_Ary1dOfReal Parameters = AssembleParameters(theCurve.Curve()->FirstParameter(), theCurve.Curve()->LastParameter(), theParameters);

			TColCad3d_HAry1dOfCurveOnPlane newCurves(Parameters.Size() - 1);
			forThose(Index, 0, MaxIndexOf(newCurves))
			{
				newCurves[Index] = new Cad3d_CurveOnPlane(Parameters[Index], Parameters[Index + 1], theCurve.Curve());
			}
			MOVE(newCurves);
		}

		static TColCad3d_HAry1dOfCurveOnSurface EdgesOnSurface(const Cad3d_CurveOnSurface& theEdge, const TColStd_Ary1dOfReal& theParameters)
		{
			TColStd_Ary1dOfReal Parameters = AssembleParameters(theEdge.FirstParameter(), theEdge.LastParameter(), theParameters);

			TColCad3d_HAry1dOfCurveOnSurface newEdges(Parameters.Size() - 1);
			forThose(Index, 0, MaxIndexOf(newEdges))
			{
				newEdges[Index] = new Cad3d_CurveOnSurface(Parameters[Index], Parameters[Index + 1], theEdge.Curve());
			}
			MOVE(newEdges);
		}

		static void ReMatchCurves(const TColCad3d_HAry1dOfCurveOnPlane& theEdgesOnPlane, TColCad3d_HAry1dOfCurveOnSurface& theEdgesOnSurface, const Cad3d_SurfaceOnSolid & theSurface, const Standard_Real theTolerance)
		{
			Entity_Box3d Box = theSurface.BoundingBox();
			Box.Expand(0.1*Box.Diameter());

			Geom_ADTree3d<Global_Handle(Entity_IndexedPt3d)> Register;
			Register.SetRegion(Box);
			Register.SetCoordinateFunction(&Entity_IndexedPt3dTools::CoordOf);

			forThose
			(
				Index,
				0,
				MaxIndexOf(theEdgesOnPlane)
			)
			{
				Debug_Null_Pointer(theEdgesOnPlane[Index]);

				Register.Insert(new Entity_IndexedPt3d(Index + 1, theSurface.Value(theEdgesOnPlane[Index]->MidCoord())));
			}

			TColCad3d_HAry1dOfCurveOnSurface Copy = theEdgesOnSurface;
			theEdgesOnSurface = NULL;

			forThose
			(
				Index,
				0,
				MaxIndexOf(Copy)
			)
			{
				Debug_Null_Pointer(Copy[Index]);

				Entity_Box3d Region = Copy[Index]->BoundingBox();
				Region.Expand(0.1*Region.Diameter());

				TColEntity_HAry1dOfIndexedPt3d Found;
				Register.Search(Region, Found);

				GeomAPI_ProjectPointOnCurve Projection;
				Projection.Init(Copy[Index]->Curve(), Copy[Index]->FirstParameter(), Copy[Index]->LastParameter());

				Geom_Pnt3d P0 = Copy[Index]->StartCoord();
				Geom_Pnt3d P1 = Copy[Index]->LastCoord();

				Standard_Boolean Exist = Standard_False;

				forThose(I, 0, MaxIndexOf(Found))
				{
					/*if (Distance(Found[I]->Coord(), P0) <= theTolerance OR Distance(Found[I]->Coord(), P1) <= theTolerance)
					{

					}*/

					Projection.Perform(Found[I]->Coord());

					if (NOT Projection.NbPoints()) continue;

					if (Projection.LowerDistance() <= 10.0*theTolerance)
					{
						Standard_Integer ID = Found[I]->Index();

						theEdgesOnSurface[Index_Of(ID)] = Copy[Index];

						Exist = Standard_True;

						break;
					}
				}

				if (NOT Exist) THROW_STANDARD_EXCEPTION("Unexpected Error: not found the matched curve");
			}

			TColEntity_HAry1dOfIndexedPt3d IndexedPts3d;
			Register.RetrieveTo(IndexedPts3d);

			FreeMemory(IndexedPts3d);
		}

		static TColCad3d_HAry1dOfEdgeOnSolid SubDivideCurves(const TColCad3d_HAry1dOfDiscreteParameters& DisParameters, const Cad3d_SurfaceOnSolid & theSurface, const Standard_Real theTolerance)
		{
			TColCad3d_HBasicQueueOfCurveOnSurface QEdgeOnSurface;
			TColCad3d_HBasicQueueOfCurveOnPlane QEdgeOnPlane;

			forThose
			(
				Index,
				0, 
				MaxIndexOf(DisParameters)
			)
			{
				Debug_Null_Pointer(DisParameters[Index]);

				Get_Const_Object(disParam) = *DisParameters[Index];

				Debug_Null_Pointer(disParam.theEdge_);
				Debug_Null_Pointer(disParam.the2D_);
				Debug_Null_Pointer(disParam.the3D_);

				Get_Const_Object(theEdge) = *disParam.theEdge_;
				Get_Const_Object(the2D) = *disParam.the2D_;
				Get_Const_Object(the3D) = *disParam.the3D_;

				Debug_Null_Pointer(theEdge.CurveOnPlane());

				QEdgeOnPlane.EnQueue(CurvesOnPlane(*theEdge.CurveOnPlane(), the2D));

				Debug_Null_Pointer(theEdge.CurveOnSurface());

				QEdgeOnSurface.EnQueue(EdgesOnSurface(*theEdge.CurveOnSurface(), the3D));
			}

			if (QEdgeOnPlane.Size() NOT_EQUAL QEdgeOnSurface.Size()) { THROW_STANDARD_EXCEPTION("UnExpected contradictory data"); }

			TColCad3d_HAry1dOfCurveOnPlane CurveOnPlane;
			QEdgeOnPlane.RetrieveTo(CurveOnPlane);

			TColCad3d_HAry1dOfCurveOnSurface EdgeOnSurface;
			QEdgeOnSurface.RetrieveTo(EdgeOnSurface);

			Try_Exception_Handle_Exit(ReMatchCurves(CurveOnPlane, EdgeOnSurface, theSurface, theTolerance));

			TColCad3d_HAry1dOfEdgeOnSolid EdgeOnSolid(CurveOnPlane.Size());
			forThose(Index, 0, MaxIndexOf(EdgeOnSolid))
			{
				EdgeOnSolid[Index] = new Cad3d_EdgeOnSolid(Index + 1, CurveOnPlane[Index], EdgeOnSurface[Index], NULL);
			}

			MOVE(EdgeOnSolid);
		}
	}
}

static inline const Geom_Pnt3d& GetCoordOf(Global_Handle(Geom_Pnt3d) thePoint)
{
	return *thePoint;
}

static inline const Geom_Pnt2d& GetCoordOf(Global_Handle(Geom_Pnt2d) thePoint)
{
	return *thePoint;
}

Global_Handle(Cad3d_SurfaceOnSolid) AutLib::CadLib::Cad3d_SurfaceOnSolidTools::RepairNonConfomityOfBoundaries
(
	const Cad3d_SurfaceOnSolid & theSurface,
	const Standard_Real Tolerance
)
{
	Debug_Null_Pointer(theSurface.Geometry());

	Get_Const_Object(Edges) = theSurface.Edges();
	Get_Const_Object(Geom) = *theSurface.Geometry();

	TColGeom_BasicQueueOfPnt3d QPts3d;
	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]->CurveOnPlane());

		Get_Const_Object(Curve) = *Edges[Index]->CurveOnPlane();

		QPts3d.EnQueue(theSurface.Value(Curve.FirstCoord()));
		QPts3d.EnQueue(theSurface.Value(Curve.LastCoord()));
	}
	
	TColGeom_Ary1dOfPnt3d UnMergedSources;
	QPts3d.RetrieveTo(UnMergedSources);
	
	Merge_Pnt3d Merge;
	Merge.SetCoords(&UnMergedSources);
	Merge.Perform();

	TColGeom_Ary1dOfPnt3d Sources = Merge.CompactPoints();

	Entity_Box3d Box = theSurface.BoundingBox();
	Box.Expand(0.01*Box.Diameter());

	Geom_ADTree3d<Global_Handle(Geom_Pnt3d)> Engine;
	Engine.SetRegion(Box);
	Engine.SetCoordinateFunction(&GetCoordOf);

	forThose(Index, 0, MaxIndexOf(Sources))
		Engine.Insert(&Sources[Index]);

	TColCad3d_HBasicQueueOfDiscreteParameters QdisParameters;
	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]->CurveOnSurface());

		Get_Const_Object(Edge) = *Edges[Index];

		QdisParameters.EnQueue(Calc3DDiscreteParameters(Edge, Engine, Tolerance));
	}

	TColCad3d_HAry1dOfDiscreteParameters DisParameters;
	QdisParameters.RetrieveTo(DisParameters);

	TColGeom_Ary1dOfPnt2d ParamPts = CalcParameterCoords(DisParameters, theSurface);

	Entity_Box2d Box2d = theSurface.ParametricBoundingBox();
	
	Geom_ADTree2d<Global_Handle(Geom_Pnt2d)> Engine2d;
	Engine2d.SetRegion(Box2d.OffsetBox(1.0E-2*Box2d.Diameter()));
	Engine2d.SetCoordinateFunction(&GetCoordOf);

	forThose(Index, 0, MaxIndexOf(ParamPts))
		Engine2d.Insert(&ParamPts[Index]);

	Calc2DDiscreteParameters(Engine2d, DisParameters, Tolerance);

	TColCad3d_HAry1dOfEdgeOnSolid newEdges;
	Try_Exception_Handle_Exit(newEdges = SubDivideCurves(DisParameters, theSurface, Tolerance));

	Global_Handle(Cad3d_SurfaceOnSolid) NewSurface = new Cad3d_SurfaceOnSolid;
	Try_Exception_Handle_Continue(NewSurface->Init(theSurface.Index(), theSurface.Geometry(), newEdges));
	forThose(Index, 0, MaxIndexOf(newEdges))
		newEdges[Index]->SetSurface(NewSurface);

	FreeMemory(DisParameters);

	return NewSurface;
}

TopoDS_Face AutLib::CadLib::Cad3d_SurfaceOnSolidTools::Make_TopoDS_Face
(
	const Cad3d_SurfaceOnSolid & theSurface,
	const Standard_Real theTolerance
)
{
	Debug_Null_Pointer(theSurface.Plane());
	Debug_Null_Pointer(theSurface.Geometry());

	Get_Const_Object(Plane) = *theSurface.Plane();

	BRepBuilderAPI_MakeFace MakeFace(theSurface.Geometry(), theTolerance);

	Debug_Null_Pointer(Plane.OutterWire());
	MakeFace.Add(Cad3d_WireOnPlaneTools::Make_TopoDS_Wire(Plane.OutterWire()->Edges(), theSurface.Geometry()));

	Get_Const_Object(Inners) = Plane.InnerWires();
	forThose
	(
		Index,
		0,
		MaxIndexOf(Inners)
	)
	{
		Debug_Null_Pointer(Inners[Index]);
		MakeFace.Add(Cad3d_WireOnPlaneTools::Make_TopoDS_Wire(Inners[Index]->Edges(), theSurface.Geometry()));
	}
	THROW_STANDARD_EXCEPTION_IF(NOT MakeFace.IsDone(), "Invalid Data");
	return MakeFace.Face();
}

namespace AutLib
{
	namespace CadLib
	{

		static Geom_Pnt2d MinDistanceFromEndsOfCurve(const Geom_Pnt2d& theCoord0, const Geom_Pnt2d& theCoord1, const Cad3d_CurveOnPlane& theCurve)
		{
			Geom_Pnt2d P0 = theCurve.FirstCoord();
			Geom_Pnt2d P1 = theCurve.LastCoord();

			Standard_Real D0 = MIN(DistanceSQ(theCoord0, P0), DistanceSQ(theCoord0, P1));
			Standard_Real D1 = MIN(DistanceSQ(theCoord1, P0), DistanceSQ(theCoord1, P1));

			if (D0 < D1) return theCoord0;
			else return theCoord1;
		}

		static Standard_Boolean CalcMinDistance(const Geom_Pnt2d& theCoord, const Cad3d_CurveOnPlane& theCurve, Standard_Real& theParameter, Standard_Real& theMinDistance)
		{
			Geom2dAPI_ProjectPointOnCurve Projection(theCoord, theCurve.Curve(), theCurve.FirstParameter(), theCurve.LastParameter());

			if (NOT Projection.NbPoints()) return Standard_False;
			theParameter = Projection.LowerDistanceParameter();
			theMinDistance = Projection.LowerDistance();
			return Standard_True;
		}

		static void EndingReparameterize(const TColCad3d_HAry1dOfCurveOnPlane& theCurves)
		{
			if (theCurves.Size() < 2) return;

			forThose
			(
				Index,
				0,
				MaxIndexOf(theCurves) - 1
			)
			{
				Debug_Null_Pointer(theCurves[Index]);
				Debug_Null_Pointer(theCurves[Index + 1]);

				Get_Object(Curve0) = *theCurves[Index];
				Get_Object(Curve1) = *theCurves[Index + 1];

				Geom_Pnt2d P0 = MinDistanceFromEndsOfCurve(Curve0.FirstCoord(), Curve0.LastCoord(), Curve1);
				Geom_Pnt2d P1 = MinDistanceFromEndsOfCurve(Curve1.FirstCoord(), Curve1.LastCoord(), Curve0);

				Standard_Real p0, d0;
				if (CalcMinDistance(P0, Curve1, p0, d0))
				{
					Standard_Real pm = 0.5*(Curve1.FirstParameter() + Curve1.LastParameter());
					if (p0 < pm)
					{
						Curve1.SetFirst(p0);
					}
					else
					{
						Curve1.SetLast(p0);
					}
				}

				Standard_Real p1, d1;
				if (CalcMinDistance(P1, Curve0, p1, d1))
				{
					Standard_Real pm = 0.5*(Curve0.FirstParameter() + Curve0.LastParameter());
					if (p1 < pm)
					{
						Curve0.SetFirst(p1);
					}
					else
					{
						Curve0.SetLast(p1);
					}
				}
			}

			Get_Object(Curve0) = *theCurves.Last();
			Get_Object(Curve1) = *theCurves.First();

			Geom_Pnt2d P0 = MinDistanceFromEndsOfCurve(Curve0.FirstCoord(), Curve0.LastCoord(), Curve1);
			Geom_Pnt2d P1 = MinDistanceFromEndsOfCurve(Curve1.FirstCoord(), Curve1.LastCoord(), Curve0);

			Standard_Real p0, d0;
			if (CalcMinDistance(P0, Curve1, p0, d0))
			{
				Standard_Real pm = 0.5*(Curve1.FirstParameter() + Curve1.LastParameter());
				if (p0 < pm) 
				{
					Curve1.SetFirst(p0);
				}
				else
				{
					Curve1.SetLast(p0);
				}
			}

			Standard_Real p1, d1;
			if (CalcMinDistance(P1, Curve0, p1, d1))
			{
				Standard_Real pm = 0.5*(Curve0.FirstParameter() + Curve0.LastParameter());
				if (p1 < pm)
				{
					Curve0.SetFirst(p1);
				}
				else
				{
					Curve0.SetLast(p1);
				}
			}
		}
	}
}

Global_Handle(Cad3d_SurfaceOnSolid) AutLib::CadLib::Cad3d_SurfaceOnSolidTools::GetSurfaceOnSolid(const TopoDS_Face & theFace)
{
	TColCad3d_HBasicQueueOfEdgeOnSolid QCurves;
	Standard_Integer CurveIndex = 0;
	Standard_Real Tol = 1.0E-4;

	for (TopExp_Explorer Explorer(theFace, TopAbs_WIRE); Explorer.More(); Explorer.Next())
	{
		TopoDS_Wire Wire = TopoDS::Wire(Explorer.Current());

		if (Wire.IsNull()) continue;

		ShapeFix_Wire SFWF(Wire, theFace, Tol);

		SFWF.SetPrecision(1.0E-3);
		SFWF.SetMaxTolerance(1.0E-2);
		SFWF.SetMinTolerance(1.0E-6);

		SFWF.FixReorder();
		SFWF.ClosedWireMode() = Standard_True;
		SFWF.FixClosed();
		SFWF.FixConnected();

		/*SFWF.FixGaps2dMode() = 1;
		SFWF.FixTailMode() = 1;
		SFWF.ClosedWireMode() = Standard_True;*/
		SFWF.Perform();
		Wire = SFWF.WireAPIMake();

		//ShapeExtend_WireData WireData;
		//ShapeAnalysis_WireOrder WireOrderAnalysis(Standard_False, 1.0E-6);

		TColCad3d_HBasicQueueOfCurveOnPlane QCurvesOnPlane;

		//for (BRepTools_WireExplorer WireExplorer(Wire, theFace); WireExplorer.More(); WireExplorer.Next())
		for (TopExp_Explorer WireExplorer(Wire, TopAbs_EDGE); WireExplorer.More(); WireExplorer.Next())
		{
			TopoDS_Edge Edge = TopoDS::Edge(WireExplorer.Current());

			Standard_Real u0, u1, U0, U1;
			Handle(Geom2d_Curve) PCurve = BRep_Tool::CurveOnSurface(Edge, theFace, u0, u1);
			Handle(Geom_Curve) Curve = BRep_Tool::Curve(Edge, U0, U1);

			if (Edge.Orientation() EQUAL TopAbs_REVERSED)
			{
				PCurve->Reverse();
				Standard_Real Temp = u1;
				u1 = PCurve->ReversedParameter(u0);
				u0 = PCurve->ReversedParameter(Temp);
			}

			Global_Handle(Cad3d_CurveOnSurface) CurveOnSurface;
			Global_Handle(Cad3d_CurveOnPlane) CurveOnPlane;
			CurveOnSurface = NULL;
			CurveOnPlane = NULL;

			if (Curve AND Distance(Curve->Value(U0), Curve->Value(U1)) <= 1.0E-6)
			{
				CurveOnSurface = new Cad3d_RingOnSurface(U0, U1, Curve);
				CurveOnPlane = new Cad3d_RingCurveOnPlane(u0, u1, PCurve);
			}
			else
			{
				if (Curve) CurveOnSurface = new Cad3d_CurveOnSurface(U0, U1, Curve);
				CurveOnPlane = new Cad3d_CurveOnPlane(u0, u1, PCurve);		
			}
			QCurvesOnPlane.EnQueue(CurveOnPlane);
			//WireOrderAnalysis.Add(CurveOnPlane->FirstCoord().XY(), CurveOnPlane->LastCoord().XY());

			Global_Handle(Cad3d_EdgeOnSolid) CurveOnSolid = new Cad3d_EdgeOnSolid(++CurveIndex, CurveOnPlane, CurveOnSurface, NULL);

			QCurves.EnQueue(CurveOnSolid);
		}
		//WireOrderAnalysis.Perform();

		EndingReparameterize(QCurvesOnPlane.Retrive());

		/*forThose(Index, 1, WireOrderAnalysis.NbEdges())
		{
			cout << WireOrderAnalysis.Ordered(Index) << endl;
		}*/
	}

	TColCad3d_HAry1dOfEdgeOnSolid Curves;
	QCurves.RetrieveTo(Curves);

	TopLoc_Location Loc;
	Global_Handle(Cad3d_SurfaceOnSolid) NewSurface = new Cad3d_SurfaceOnSolid;
	forThose(Index, 0, MaxIndexOf(Curves))
		Curves[Index]->SetSurface(NewSurface);

	Try_Exception_Handle_Continue(NewSurface->Init(0, BRep_Tool::Surface(theFace), Curves));

	NewSurface->SetTriangulation(BRep_Tool::Triangulation(TopoDS::Face(theFace), Loc));

	
	return NewSurface;
}