#include <Cad3d_SolidTools.hxx>

#include <Geometry_Sort.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_CurveOnPlane.hxx>
#include <Cad3d_RingOnSurface.hxx>
#include <Cad3d_RingCurveOnPlane.hxx>
#include <Cad3d_CurveOnSurface.hxx>
#include <Cad3d_SurfaceOnSolid.hxx>
#include <Cad3d_SurfaceOnSolidTools.hxx>
#include <Cad3d_EdgeOnSolid.hxx>
#include <Cad3d_PairedOnSolid.hxx>
#include <Cad3d_PointOnSolidTools.hxx>
#include <Cad3d_SurfaceOnSolidTools.hxx>
#include <IO_Tecplot.hxx>
#include <IO_IGESRead.hxx>
#include <TColStd_Ary1dOfInteger.hxx>
#include <TColStd_BasicQueueOfReal.hxx>
#include <TColEntity_HBasicQueueOfTriangulation3d.hxx>
#include <TColCad3d_HBasicQueueOfSurfaceOnSolid.hxx>
#include <TColCad3d_HBasicQueueOfEdgeOnSolid.hxx>
#include <TColCad3d_HAry1dOfEdgeOnSolid.hxx>
#include <TColCad3d_HAry1dOfPairedOnSolid.hxx>
#include <TColCad3d_HADTree3dOfPointOnSolid.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;
using namespace IoLib;

#include <BRepTools_ReShape.hxx>
#include <BRep_Tool.hxx>
#include <BRep_Builder.hxx>
#include <BRepOffsetAPI_Sewing.hxx>
#include <BRepBuilderAPI_Sewing.hxx>
#include <BRepBuilderAPI_MakeSolid.hxx>
#include <TopExp.hxx>
#include <TopExp_Explorer.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Solid.hxx>
#include <TopoDS.hxx>
#include <ShapeAnalysis_WireOrder.hxx>
#include <ShapeAnalysis_Wire.hxx>
#include <ShapeFix_Wire.hxx>
#include <ShapeFix_Shell.hxx>
#include <IGESControl_Controller.hxx>
#include <IGESControl_Writer.hxx>

#include <Bnd_Box.hxx>
#include <BRepBndLib.hxx>
#include <TopoDS_Shape.hxx>
#include <BRepMesh_FastDiscret.hxx>

#include <GeomAPI_ProjectPointOnCurve.hxx>
#include <GeomAPI_ProjectPointOnSurf.hxx>
#include <Geom2dAPI_ProjectPointOnCurve.hxx>

Standard_Integer AutLib::CadLib::Cad3d_SolidTools::NbOfSurfaces(const TopoDS_Shape & theShape)
{
	Standard_Integer K = 0;
	for (TopExp_Explorer Explorer(theShape, TopAbs_FACE); Explorer.More(); Explorer.Next())
	{
		++K;
	}
	return K;
}

namespace AutLib
{
	namespace CadLib
	{

		//static TColCad3d_HAry1dOfEdgeOnSolid GetEdgesFromWire(const TopoDS_Wire& Wire, const TopoDS_Face& Face)
		//{
		//	ShapeAnalysis_WireOrder WireOrder;
		//	ShapeAnalysis_Wire Analysis(Wire, Face, 1.0E-6);
		//	Analysis.SetFace(Face);
		//	Analysis.Load(Wire);
		//	Analysis.SetPrecision(1.0E-6);

		//	Analysis.Perform();

		//	TColStd_Ary1dOfInteger Order(Analysis.NbEdges() + 1);
		//	Order.Init(1);

		//	Analysis.CheckOrder(WireOrder, Standard_True, Standard_False);

		//	if (Analysis.CheckOrder(WireOrder, Standard_True, Standard_False))
		//	{
		//		forThose(Index, 1, Analysis.NbEdges())
		//		{
		//			Standard_Integer Value = WireOrder.Ordered(Index);
		//			Order[ABS(Value) - 1] = Value;
		//		}
		//	}

		//	Standard_Integer K = 0;

		//	TColCad3d_HBasicQueueOfEdgeOnSolid QCurves;
		//	for (TopExp_Explorer Inner(Wire, TopAbs_EDGE); Inner.More(); Inner.Next())
		//	{
		//		TopoDS_Edge Edge = TopoDS::Edge(Inner.Current());

		//		//TopLoc_Location Loc;
		//		Standard_Real u0, u1, U0, U1;
		//		Handle(Geom2d_Curve) PCurve = BRep_Tool::CurveOnSurface(Edge, Face, u0, u1);
		//		Handle(Geom_Curve) Curve = BRep_Tool::Curve(Edge, U0, U1);

		//		if (Order[K] < 0)
		//		{
		//			PCurve->Reverse();

		//			Standard_Real Temp = u1;
		//			u1 = PCurve->ReversedParameter(u0);
		//			u0 = PCurve->ReversedParameter(Temp);
		//		}

		//		K++;

		//		if (Edge.Orientation() EQUAL TopAbs_REVERSED)
		//		{
		//			PCurve->Reverse();

		//			Standard_Real Temp = u1;
		//			u1 = PCurve->ReversedParameter(u0);
		//			u0 = PCurve->ReversedParameter(Temp);
		//		}

		//		Global_Handle(Cad3d_CurveOnSurface) CurveOnSurface;
		//		Global_Handle(Cad3d_CurveOnPlane) CurveOnPlane;
		//		CurveOnSurface = NULL;
		//		CurveOnPlane = NULL;

		//		if (Curve AND Distance(Curve->Value(U0), Curve->Value(U1)) <= 1.0E-6)
		//		{
		//			CurveOnSurface = new Cad3d_RingOnSurface(U0, U1, Curve);
		//			CurveOnPlane = new Cad3d_RingCurveOnPlane(u0, u1, PCurve);
		//		}
		//		else
		//		{
		//			CurveOnSurface = new Cad3d_CurveOnSurface(U0, U1, Curve);
		//			CurveOnPlane = new Cad3d_CurveOnPlane(u0, u1, PCurve);
		//		}

		//		Global_Handle(Cad3d_EdgeOnSolid) CurveOnSolid = new Cad3d_EdgeOnSolid(0, CurveOnPlane, CurveOnSurface, NULL);
		//		QCurves.EnQueue(CurveOnSolid);
		//	}
		//}
	}
}

namespace AutLib
{
	namespace CadLib
	{

		static Global_Handle(Cad3d_SurfaceOnSolid) GetSurfaceOnSolid(const Standard_Integer SurfIndex, const TopoDS_Face& Face)
		{
			TColCad3d_HBasicQueueOfEdgeOnSolid QCurves;
			Standard_Integer CurveIndex = 0;

			Handle(Geom_Surface) GSurface = BRep_Tool::Surface(Face);
			Bnd_B2d box;

			for (TopExp_Explorer Explorer(Face, TopAbs_WIRE); Explorer.More(); Explorer.Next())
			{
				TopoDS_Wire Wire = TopoDS::Wire(Explorer.Current());

				/*ShapeFix_Wire FixWire;
				FixWire.SetFace(Face);
				FixWire.SetPrecision(1.0E-6);
				FixWire.Load(Wire);

				cout << "Fix wire is ready ? " << FixWire.IsReady() << endl;

				FixWire.FixReorderMode() = 1;
				FixWire.FixShiftedMode() = 1;
				FixWire.FixEdgeCurvesMode() = 1;
				FixWire.ClosedWireMode() = 1;
				FixWire.FixEdgeCurvesMode() = 1;
				FixWire.FixGaps2dMode() = 1;

				FixWire.Perform();

				cout << "fix shifted = " << FixWire.FixShifted() << endl;

				Wire = FixWire.Wire();*/

				if (Wire.IsNull()) continue;
				
				ShapeAnalysis_WireOrder WireOrder;
				ShapeAnalysis_Wire Analysis(Wire, Face, 1.0E-6);
				Analysis.SetFace(Face);
				Analysis.Load(Wire);
				Analysis.SetPrecision(1.0E-6);

				Analysis.Perform();

				TColStd_Ary1dOfInteger Order(Analysis.NbEdges() + 1);
				Order.Init(1);

				Analysis.CheckOrder(WireOrder, Standard_True, Standard_False);

				if (Analysis.CheckOrder(WireOrder, Standard_True, Standard_False))
				{
					forThose(Index, 1, Analysis.NbEdges())
					{
						Standard_Integer Value = WireOrder.Ordered(Index);
						Order[ABS(Value) - 1] = Value;
					}
				}

				Standard_Integer K = 0;

				for (TopExp_Explorer Inner(Wire, TopAbs_EDGE); Inner.More(); Inner.Next())
				{
					TopoDS_Edge Edge = TopoDS::Edge(Inner.Current());

					//TopLoc_Location Loc;
					Standard_Real u0, u1, U0, U1;
					Handle(Geom2d_Curve) PCurve = BRep_Tool::CurveOnSurface(Edge, Face, u0, u1);
					Handle(Geom_Curve) Curve = BRep_Tool::Curve(Edge, U0, U1);
					cout << Curve.IsNull() << endl;
					//if (Curve)
					//{
					//	gp_Pnt2d pt0 = PCurve->Value(u0);
					//	gp_Pnt2d pt1 = PCurve->Value(u1);

					//	gp_Pnt PtFromParameter0 = GSurface->Value(pt0.X(), pt0.Y());
					//	gp_Pnt PtFromParameter1 = GSurface->Value(pt1.X(), pt1.Y());

					//	gp_Pnt Pt0 = Curve->Value(U0);
					//	gp_Pnt Pt1 = Curve->Value(U1);
					//	cout << u0 << "   " << u1 << endl;
					//	cout << pt0 << "   ----   " << pt1 << endl;

					//	/*cout << PtFromParameter0 << "------ " << PtFromParameter1 << endl;
					//	cout << Pt0 << "------ " << Pt1 << endl;*/
					//	cout << endl;
					//}

					Standard_Boolean Reversed = Standard_False;

					if (Order[K] < 0)
					{
						PCurve->Reverse();

						Standard_Real Temp = u1;
						u1 = PCurve->ReversedParameter(u0);
						u0 = PCurve->ReversedParameter(Temp);

						Reversed = Standard_True;
					}

					K++;

					if (Edge.Orientation() EQUAL TopAbs_REVERSED)
					{
						PCurve->Reverse();

						Standard_Real Temp = u1;
						u1 = PCurve->ReversedParameter(u0);
						u0 = PCurve->ReversedParameter(Temp);

						Reversed = Standard_True;
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

					Global_Handle(Cad3d_EdgeOnSolid) CurveOnSolid = new Cad3d_EdgeOnSolid(++CurveIndex, CurveOnPlane, CurveOnSurface, NULL);

					//CurveOnPlane->SetReverse(Reversed);

					QCurves.EnQueue(CurveOnSolid);
				}
			}

			TColCad3d_HAry1dOfEdgeOnSolid Curves;
			QCurves.RetrieveTo(Curves);

			TopLoc_Location Loc;
			Global_Handle(Cad3d_SurfaceOnSolid) NewSurface = new Cad3d_SurfaceOnSolid;
			NewSurface->Init(SurfIndex, GSurface, Curves);
			NewSurface->SetTriangulation(BRep_Tool::Triangulation(TopoDS::Face(Face), Loc));

			forThose(Index, 0, MaxIndexOf(Curves))
				Curves[Index]->SetSurface(NewSurface);

			return NewSurface;
		}
	}
}

TColCad3d_HAry1dOfSurfaceOnSolid AutLib::CadLib::Cad3d_SolidTools::GetSurfaces(const TopoDS_Shape & theShape)
{
	TColCad3d_HBasicQueueOfSurfaceOnSolid QSurfaces;
	Standard_Integer Index = 0;

	for (TopExp_Explorer Explorer(theShape, TopAbs_FACE); Explorer.More(); Explorer.Next())
	{
		TopoDS_Face Face = TopoDS::Face(Explorer.Current());
		
		//Get_Pointer(Surface) = GetSurfaceOnSolid(++Index, Face);
		Global_Handle(Cad3d_SurfaceOnSolid) Surface = Cad3d_SurfaceOnSolidTools::GetSurfaceOnSolid(Face);

		if (NOT Surface) continue;

		Surface->SetOrientation(Cad3d_SurfaceOrientation_OUTWARD);
		if (Face.Orientation() EQUAL TopAbs_REVERSED)
		{
			Surface->SetOrientation(Cad3d_SurfaceOrientation_INWARD);
		}

		Surface->SetIndex(++Index);

		QSurfaces.EnQueue(Surface);
	}

	TColCad3d_HAry1dOfSurfaceOnSolid Surfaces;
	QSurfaces.RetrieveTo(Surfaces);

	/*Open_OutputFile_TecPlot(Plot, "test");
	forThose(Index, 0, MaxIndexOf(Surfaces))
		Surfaces[Index]->ExportParametricCurvesToPlt(Plot);
	exit(1);*/

	MOVE(Surfaces);
}

TColEntity_HAry1dOfTriangulation3d AutLib::CadLib::Cad3d_SolidTools::GetTriangulations(const TopoDS_Shape & theShape)
{
	TColEntity_HBasicQueueOfTriangulation3d QTriangulations;
	for (TopExp_Explorer Explorer(theShape, TopAbs_FACE); Explorer.More(); Explorer.Next())
	{
		QTriangulations.EnQueue(Cad3d_SurfaceOnSolidTools::TriangulationOf(TopoDS::Face(Explorer.Current())));
	}
	TColEntity_HAry1dOfTriangulation3d Triangulations;
	QTriangulations.RetrieveTo(Triangulations);
	MOVE(Triangulations);
}

TopoDS_Shape AutLib::CadLib::Cad3d_SolidTools::Make_TopoDS_Shape(const Cad3d_Solid & theSolid, const Standard_Real theTolerance)
{
	//Open_OutputFile_TecPlot(Plot, "test");

	TColCad3d_HAry1dOfEntityOnSolid Surfaces;
	theSolid.RetrieveSurfacesTo(Surfaces);

	BRep_Builder shellMaker;
	TopoDS_Shell shellShape;
	shellMaker.MakeShell(shellShape);
	forThose
	(
		Index,
		0,
		MaxIndexOf(Surfaces)
	)
	{
		Debug_Null_Pointer(Surfaces[Index]);

		Get_Const_Pointer(Surface) = Global_DownCast(Cad3d_SurfaceOnSolid, Surfaces[Index]);
		Debug_Null_Pointer(Surface);

		TopoDS_Face Face = Cad3d_SurfaceOnSolidTools::Make_TopoDS_Face(*Surface, theTolerance);

		/*BRepMesh_FastDiscret::Parameters Params;
		Params.Deflection = 0.1;
		Params.Angle = 1.0;

		Bnd_Box BoundingBox;
		BRepBndLib::Add(Face, BoundingBox);

		BRepMesh_FastDiscret Mesh(BoundingBox, Params);
		Mesh.Perform(Face);*/

		//M_IO IO_TecPlot::ExportSurface(Face, Plot);
		shellMaker.Add(shellShape, Face);
	}
	// The resulting shape may consist of multiple shells!
	// Use TopExp_Explorer to iterate through shells
	BRepBuilderAPI_MakeSolid solidmaker;
	TopTools_IndexedMapOfShape shellMap;
	TopExp::MapShapes(shellShape, TopAbs_SHELL, shellMap);
	for (Standard_Integer ishell = 1; ishell <= shellMap.Extent(); ++ishell) 
	{
		const TopoDS_Shell& shell = TopoDS::Shell(shellMap(ishell));
		solidmaker.Add(shell);
	}
	TopoDS_Shape Solid = solidmaker.Solid();

	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = 0.1;
	Params.Angle = 1.0;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(Solid, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(Solid);

	return Solid;
}

TopoDS_Shape AutLib::CadLib::Cad3d_SolidTools::GetSolid
(
	const TopoDS_Shape & theShape, 
	const TopAbs_Orientation theOrientation
)
{
	BRepOffsetAPI_Sewing Sewing;
	Sewing.Add(theShape);
	Sewing.Perform();

	TopoDS_Shape Sewed = Sewing.SewedShape();
	TopoDS_CompSolid Compound;
	TopoDS_Builder Builder;
	Builder.MakeCompSolid(Compound);

	for (TopExp_Explorer Explorer(Sewed, TopAbs_SHELL); Explorer.More(); Explorer.Next())
	{
		TopoDS_Shell Shell = TopoDS::Shell(Explorer.Current());

		ShapeFix_Shell Fix;
		Fix.Init(Shell);

		Fix.FixFaceMode() = 1;
		Fix.FixFaceOrientation(Shell, Standard_False);
		Fix.Perform();
		Shell = Fix.Shell();

		BRepBuilderAPI_MakeSolid brep_solid(Shell);
		TopoDS_Solid Solid = brep_solid.Solid();
		//Solid.Compose(theOrientation);
		Builder.Add(Compound, Solid);
	}
	return Compound.Complemented();
}

TopoDS_Shape AutLib::CadLib::Cad3d_SolidTools::ReplaceFace(const TopoDS_Shape & Shape, const TopoDS_Face & Face)
{
	Handle(BRepTools_ReShape) rebuild = new BRepTools_ReShape();

	TopoDS_Shape newface = Face.Complemented();
	rebuild->Replace(Face, newface);
	TopoDS_Shape newshape = rebuild->Apply(Shape, TopAbs_FACE);
	return newshape;
}

TopoDS_Shape AutLib::CadLib::Cad3d_SolidTools::CheckOrientation(const TopoDS_Shape & theShape)
{
	for (TopExp_Explorer Explorer(theShape, TopAbs_FACE); Explorer.More(); Explorer.Next())
	{
		TopoDS_Face Face = TopoDS::Face(Explorer.Current());
		if (Face.Orientation() EQUAL TopAbs_REVERSED)
		{
			Face.Reverse();
			//cout << "Reversing" << endl;
			//PAUSE;
			TopoDS_Shape newShape = ReplaceFace(theShape, Face);

			return CheckOrientation(newShape);
		}
	}
	return theShape;
}

TopoDS_Shape AutLib::CadLib::Cad3d_SolidTools::RepairWithIGES(const TopoDS_Shape & theShape)
{
	IGESControl_Controller::Init();

	IGESControl_Writer Writer("MM", 0);
	Writer.AddShape(theShape);
	Writer.ComputeModel();

	Standard_Boolean OK = Writer.Write("~GetSolid_RepairWithIGES.tmp");

	TopoDS_Shape Shape;
	IO_IGESRead::ReadFileNonDiscretized("~GetSolid_RepairWithIGES.tmp", Shape);

	std::remove("~GetSolid_AutMarine.tmp");

	return Shape;
}

void AutLib::CadLib::Cad3d_SolidTools::MakeSolid
(
	const TopoDS_Shape & theShape,
	Cad3d_Solid & theSolid
)
{
	TColCad3d_HAry1dOfSurfaceOnSolid Surfaces = Cad3d_SolidTools::GetSurfaces(theShape);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Surfaces)
	)
	{
		Debug_Null_Pointer(Surfaces[Index]);

		if (Cad3d_SurfaceOnSolidTools::CheckForConfomity(*Surfaces[Index], 1.0E-4))
		{
			Global_Handle(Cad3d_SurfaceOnSolid) newSurface = Cad3d_SurfaceOnSolidTools::RepairNonConfomityOfBoundaries(*Surfaces[Index], 1.0E-4);

			FreePointer(Surfaces[Index]);

			Surfaces[Index] = newSurface;
		}
	}

	theSolid.Make(Surfaces);
}

namespace AutLib
{
	namespace CadLib
	{

		static void SplitParameters(const Cad3d_EdgeOnSolid& theEdge, const TColCad3d_HADTree3dOfPointOnSolid& theRegister, const Standard_Real Tolerance, TColStd_Ary1dOfReal& Params)
		{
			Debug_Null_Pointer(theEdge.CurveOnSurface());
			Get_Const_Object(CurveOnSurface) = *theEdge.CurveOnSurface();

			Entity_Box3d Region = CurveOnSurface.BoundingBox();
			Region.Expand(0.01*Region.Diameter());

			TColCad3d_HAry1dOfPointOnSolid Found;
			theRegister.Search(Region, Found);

			const Handle(Geom_Curve) Curve = CurveOnSurface.Curve();

			GeomAPI_ProjectPointOnCurve Projection;
			Projection.Init(Curve, CurveOnSurface.FirstParameter(), CurveOnSurface.LastParameter());

			Geom_Pnt3d P0 = CurveOnSurface.StartCoord();
			Geom_Pnt3d P1 = CurveOnSurface.LastCoord();

			TColStd_BasicQueueOfReal QParams;
			forThose
			(
				Index,
				0,
				MaxIndexOf(Found)
			)
			{
				if (Distance(Found[Index]->Coord(), P0) <= Tolerance OR Distance(Found[Index]->Coord(), P1) <= Tolerance) { continue; }

				Projection.Perform(Found[Index]->Coord());

				/*if (NOT Projection.NbPoints())
				{
				fstream Plot;
				Plot.open("ProjectionFailed.plt", ios::app);

				theEdge.ExportToPlt(Plot);
				IO_TecPlot::ExportPoint(Found[Index]->Coord(), Plot);
				}*/

				if (NOT Projection.NbPoints()) continue;

				if (Projection.LowerDistance() < 10.0*Tolerance)
				{
					Standard_Real Parameter = Projection.LowerDistanceParameter();

					QParams.EnQueue(Parameter);
				}
			}

			QParams.RetrieveTo(Params);

			Geometry_Sort<Standard_Real>::Sort(Params);
		}

		static void CalcPrametersOfCurveonPlane(const Cad3d_EdgeOnSolid& theEdge, const TColStd_Ary1dOfReal& SortedParams, TColStd_Ary1dOfReal& tm)
		{
			Debug_Null_Pointer(theEdge.CurveOnSurface());
			Debug_Null_Pointer(theEdge.CurveOnPlane());
			Debug_Null_Pointer(theEdge.Surface());

			Get_Const_Object(CurveOnSurface) = *theEdge.CurveOnSurface();
			Get_Const_Object(CurveOnPlane) = *theEdge.CurveOnPlane();
			Get_Const_Object(SurfaceOnSolid) = *theEdge.Surface();

			const Handle(Geom_Curve) Curve = CurveOnSurface.Curve();
			const Handle(Geom2d_Curve) Curve2d = CurveOnPlane.Curve();

			const Handle(Geom_Surface) Surface = SurfaceOnSolid.Geometry();

			TColGeom_Ary1dOfPnt2d pPts(SortedParams.Size());
			TColGeom_Ary1dOfPnt3d Pts(SortedParams.Size());
			forThose(Index, 0, MaxIndexOf(SortedParams))
			{
				Pts[Index] = Curve->Value(SortedParams[Index]);
			}
			GeomAPI_ProjectPointOnSurf SurfProjection;
			SurfProjection.Init(Surface, SurfaceOnSolid.Umin(), SurfaceOnSolid.Umax(), SurfaceOnSolid.Vmin(), SurfaceOnSolid.Vmax());
			forThose
			(
				Index,
				0,
				MaxIndexOf(Pts)
			)
			{
				SurfProjection.Perform(Pts[Index]);
				SurfProjection.LowerDistanceParameters(pPts[Index].X(), pPts[Index].Y());
			}

			Geom2dAPI_ProjectPointOnCurve CurveProjection;

			tm.Resize(pPts.Size());
			forThose(Index, 0, MaxIndexOf(pPts))
			{
				CurveProjection.Init(pPts[Index], Curve2d, CurveOnPlane.FirstParameter(), CurveOnPlane.LastParameter());
				if (NOT CurveProjection.NbPoints()) continue;
				tm[Index] = CurveProjection.LowerDistanceParameter();
			}

			Geometry_Sort<Standard_Real>::Sort(tm);
		}

		static TColCad3d_HAry1dOfEdgeOnSolid CreateNewEdges(const Cad3d_EdgeOnSolid& theOldEdge, const TColStd_Ary1dOfReal& params2d, const TColStd_Ary1dOfReal& params3d)
		{
			Debug_If_Condition(params2d.Size() NOT_EQUAL params3d.Size());

			Debug_Null_Pointer(theOldEdge.CurveOnPlane());
			Debug_Null_Pointer(theOldEdge.Surface());

			Get_Const_Object(CurveOnPlane) = *theOldEdge.CurveOnPlane();
			Get_Const_Object(CurveOnSurface) = *theOldEdge.CurveOnSurface();

			TColStd_Ary1dOfReal Params2d(params2d.Size() + 2);
			TColStd_Ary1dOfReal Params3d(params3d.Size() + 2);

			Params2d.First() = CurveOnPlane.FirstParameter();
			Params2d.Last() = CurveOnPlane.LastParameter();

			Params3d.First() = CurveOnSurface.FirstParameter();
			Params3d.Last() = CurveOnSurface.LastParameter();

			forThose(Index, 0, MaxIndexOf(params2d))
				Params2d[Index + 1] = params2d[Index];

			forThose(Index, 0, MaxIndexOf(params3d))
				Params3d[Index + 1] = params3d[Index];

			TColCad3d_HAry1dOfEdgeOnSolid Edges(params2d.Size() + 1);
			forThose
			(
				Index,
				0,
				MaxIndexOf(Edges)
			)
			{
				Global_Handle(Cad3d_CurveOnPlane) newCurveOnPlane = new Cad3d_CurveOnPlane(Params2d[Index], Params2d[Index + 1], CurveOnPlane.Curve());
				Global_Handle(Cad3d_CurveOnSurface) newCurveOnSurface = new Cad3d_CurveOnSurface(Params3d[Index], Params3d[Index + 1], CurveOnSurface.Curve());

				Edges[Index] = new Cad3d_EdgeOnSolid(0, newCurveOnPlane, newCurveOnSurface, NULL);
			}
			MOVE(Edges);
		}

		static Global_Handle(Cad3d_EdgeOnSolid) CopyOfOldEdge(const Cad3d_EdgeOnSolid& theOldEdge)
		{
			Debug_Null_Pointer(theOldEdge.CurveOnPlane());
			Debug_Null_Pointer(theOldEdge.CurveOnSurface());

			Get_Const_Object(CurveOnPlane) = *theOldEdge.CurveOnPlane();
			Get_Const_Object(CurveOnSurface) = *theOldEdge.CurveOnSurface();

			Global_Handle(Cad3d_CurveOnPlane) newCurveOnPlane = new Cad3d_CurveOnPlane(CurveOnPlane.FirstParameter(), CurveOnPlane.LastParameter(), CurveOnPlane.Curve());

			return new Cad3d_EdgeOnSolid(0, newCurveOnPlane, CurveOnSurface.Copy(), NULL);
		}

		static Global_Handle(Cad3d_SurfaceOnSolid) CopyOfOldSurface(const Cad3d_SurfaceOnSolid& OldSurface)
		{
			const TColCad3d_HAry1dOfEdgeOnSolid& OldEdges = OldSurface.Edges();

			TColCad3d_HAry1dOfEdgeOnSolid newEdges(OldEdges.Size());
			forThose(Index, 0, MaxIndexOf(newEdges))
			{
				newEdges[Index] = CopyOfOldEdge(*OldEdges[Index]);
				newEdges[Index]->SetIndex(Index + 1);
			}

			Global_Handle(Cad3d_SurfaceOnSolid) newSurface = new Cad3d_SurfaceOnSolid;
			newSurface->Init(OldSurface.Index(), OldSurface.Geometry(), newEdges);
			forThose(Index, 0, MaxIndexOf(newEdges))
				newEdges[Index]->SetSurface(newSurface);

			newSurface->SetTriangulation(OldSurface.Triangulation());

			return newSurface;
		}

		static Global_Handle(Cad3d_SurfaceOnSolid) RefineSurface(const Cad3d_SurfaceOnSolid& Surface, const TColCad3d_HADTree3dOfPointOnSolid& Register, const Standard_Real Tolerance)
		{
			Get_Const_Object(Edges) = Surface.Edges();

			//Open_OutputFile_TecPlot(Plot, "RefineSurface1");

			TColCad3d_HBasicQueueOfEdgeOnSolid QEdges;
			forThose
			(
				Index,
				0,
				MaxIndexOf(Edges)
			)
			{
				/*if (NOT Edges[Index]->PairedOnSolid())
				{
				QEdges.EnQueue(CopyOfOldEdge(*Edges[Index]));
				continue;
				}*/
				Debug_Null_Pointer(Edges[Index]);
				Get_Const_Object(Edge) = *Edges[Index];

				TColStd_Ary1dOfReal Params3d;
				SplitParameters(Edge, Register, Tolerance, Params3d);

				if (NOT Params3d.Size())
				{
					QEdges.EnQueue(CopyOfOldEdge(*Edges[Index]));
					continue;
				}

				TColStd_Ary1dOfReal Params2d;
				CalcPrametersOfCurveonPlane(Edge, Params3d, Params2d);
	
				//CheckForReverseParameters(Edge, Params2d);

				QEdges.EnQueue(CreateNewEdges(Edge, Params2d, Params3d));

				/*if (NOT Edges[Index]->Paired())
				{
				Get_Const_Object(Edge) = *Edges[Index];

				TColStd_Ary1dOfReal Params3d;
				SplitParameters(Edge, Register, Tolerance, Params3d);

				if (NOT Params3d.Size())
				{
				QEdges.EnQueue(CopyOfOldEdge(*Edges[Index]));
				continue;
				}

				TColStd_Ary1dOfReal Params2d;
				CalcPrametersOfCurveonPlane(Edge, Params3d, Params2d);

				QEdges.EnQueue(CreateNewEdges(Edge, Params2d, Params3d));
				}
				else
				{
				QEdges.EnQueue(CopyOfOldEdge(*Edges[Index]));
				}*/
			}

			TColCad3d_HAry1dOfEdgeOnSolid newEdges;
			QEdges.RetrieveTo(newEdges);

			forThose(Index, 0, MaxIndexOf(newEdges))
				newEdges[Index]->SetIndex(Index + 1);

			Global_Handle(Cad3d_SurfaceOnSolid) newSurface = new Cad3d_SurfaceOnSolid;
			newSurface->Init(Surface.Index(), Surface.Geometry(), newEdges);
			forThose(Index, 0, MaxIndexOf(newEdges))
				newEdges[Index]->SetSurface(newSurface);

			newSurface->SetTriangulation(Surface.Triangulation());

			return newSurface;
		}

		static void ConformBoundaries(const TColCad3d_HAry1dOfPairedOnSolid& FreeEdges, const TColCad3d_HADTree3dOfPointOnSolid& Register, const TColCad3d_HAry1dOfSurfaceOnSolid& OldSurfaces, const Standard_Real Tolerance, TColCad3d_HAry1dOfSurfaceOnSolid& Surfaces)
		{
			Surfaces.Resize(OldSurfaces.Size());
			forThose(Index, 0, MaxIndexOf(Surfaces))
			{
				Surfaces[Index_Of(OldSurfaces[Index]->Index())] = CopyOfOldSurface(*OldSurfaces[Index]);
				Surfaces[Index_Of(OldSurfaces[Index]->Index())]->SetIndex(OldSurfaces[Index]->Index());
			}

			TColCad3d_HNumbAvlTreeOfSurfaceOnSolid TMerge;
			TMerge.SetComparable(&Cad3d_SurfaceOnSolidTools::IsLess);

			forThose(Index, 0, MaxIndexOf(FreeEdges))
				Try_Exception_Handle_Exit(TMerge.InsertIgnoreDup((Global_Handle(Cad3d_SurfaceOnSolid))FreeEdges[Index]->Edge0()->Surface()));

			TColCad3d_HAry1dOfSurfaceOnSolid RefineSurfaces;
			TMerge.RetrieveTo(RefineSurfaces);

			/*forThose
			(
			Index,
			0,
			MaxIndexOf(OldSurfaces)
			)
			{
			Global_Handle(Cad3d_SurfaceOnSolid) newSurface = RefineSurface(*OldSurfaces[Index], Register, Tolerance);

			Debug_Null_Pointer(newSurface);

			FreePointer(Surfaces[Index_Of(newSurface->Index())]);

			Surfaces[Index_Of(newSurface->Index())] = newSurface;
			}*/

			forThose
			(
				Index,
				0,
				MaxIndexOf(RefineSurfaces)
			)
			{
				Global_Handle(Cad3d_SurfaceOnSolid) newSurface = RefineSurface(*RefineSurfaces[Index], Register, Tolerance);

				Debug_Null_Pointer(newSurface);

				FreePointer(Surfaces[Index_Of(newSurface->Index())]);

				Surfaces[Index_Of(newSurface->Index())] = newSurface;
			}
		}
	}
}

void AutLib::CadLib::Cad3d_SolidTools::ConformBoundaries
(
	const Cad3d_Solid & theUnConformed, 
	Cad3d_Solid & theConformed, 
	const Standard_Real theTolerance
)
{
	TColCad3d_HAry1dOfPairedOnSolid FreeEdges;
	theUnConformed.RetrieveFreeEdgesTo(FreeEdges);

	TColCad3d_HAry1dOfPointOnSolid ThePoints;
	theUnConformed.RetrieveVerticesTo(ThePoints);

	TColCad3d_HADTree3dOfPointOnSolid Register;
	Register.SetRegion(theUnConformed.BoundingBox());
	Register.SetCoordinateFunction(&Cad3d_PointOnSolidTools::CoordOf);

	Register.Insert(ThePoints);

	TColCad3d_HAry1dOfSurfaceOnSolid Surfaces;
	theUnConformed.RetrieveSurfacesTo(Surfaces);

	TColCad3d_HAry1dOfSurfaceOnSolid newSurfaces;
	::ConformBoundaries(FreeEdges, Register, Surfaces, theTolerance, newSurfaces);

	theConformed.Make(newSurfaces, 1.0E-4);
}

void AutLib::CadLib::Cad3d_SolidTools::ExportToPlt
(
	const TopoDS_Shape & theShape, 
	fstream & File
)
{
	for (TopExp_Explorer Explorer(theShape, TopAbs_FACE); Explorer.More(); Explorer.Next())
	{
		TopoDS_Face Face = TopoDS::Face(Explorer.Current());
		
		M_IO IO_TecPlot::ExportSurface(Face, File);
	}
}

void AutLib::CadLib::Cad3d_SolidTools::ExportToIGES
(
	const TopoDS_Shape & theShape,
	const Standard_String FileName
)
{
	IGESControl_Controller::Init();

	IGESControl_Writer Writer("MM", 0);
	Writer.AddShape(theShape);
	Writer.ComputeModel();

	Standard_Boolean OK = Writer.Write(FileName.c_str());
}

void AutLib::CadLib::Cad3d_SolidTools::Triangulation
(
	const TopoDS_Shape & theShape,
	const Standard_Real theDeflection, 
	const Standard_Real theAngle
)
{
	BRepMesh_FastDiscret::Parameters Params;
	Params.Deflection = theDeflection;
	Params.Angle = theAngle;

	Bnd_Box BoundingBox;
	BRepBndLib::Add(theShape, BoundingBox);

	BRepMesh_FastDiscret Mesh(BoundingBox, Params);
	Mesh.Perform(theShape);
}