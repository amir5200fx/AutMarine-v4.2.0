#include <Cad3d_SurfaceOnSolid.hxx>

#include <Entity_Box2d.hxx>
#include <Entity_Box3d.hxx>
#include <Entity_StaticChain3d.hxx>
#include <Entity_Triangulation2d.hxx>
#include <Entity_Triangulation2dTools.hxx>
#include <Cad3d_CurveOnSurface.hxx>
#include <Cad3d_EdgeOnSolid.hxx>
#include <Cad3d_EdgeOnPlane.hxx>
#include <Cad3d_EdgeOnPlaneTools.hxx>
#include <BndLib_AddSurface.hxx>
#include <Bnd_Box.hxx>
#include <Geom_Surface.hxx>
#include <GeomAdaptor_Surface.hxx>
#include <Cad2d_CurveOnPlane.hxx>
#include <Cad3d_CurveOnPlane.hxx>
#include <Cad3d_CurveOnPlaneTools.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad3d_Plane.hxx>
#include <Cad3d_SurfaceOrientationTools.hxx>
#include <IO_Tecplot.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <TColCad2d_HAry1dOfCurveOnPlane.hxx>
#include <TColCad3d_HAry1dOfEdgeOnPlane.hxx>

#include <Precision.hxx>
#include <Poly_Triangle.hxx>
#include <Poly_Triangulation.hxx>
#include <gp_Ax2d.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace CadLib;

static const Standard_Real DEFAULT_PARAMETRIC_TOLERANCE = 1.0E-6;

AutLib::CadLib::Cad3d_SurfaceOnSolid::Cad3d_SurfaceOnSolid()
	: theOrientation_(Cad3d_SurfaceOrientation_UNKNOWN)
	, thePlane_(NULL)
	, theParametricTolerance_(DEFAULT_PARAMETRIC_TOLERANCE)
{
}

AutLib::CadLib::Cad3d_SurfaceOnSolid::~Cad3d_SurfaceOnSolid()
{
	ReleaseMemory();
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::Init
(
	const Standard_Integer Index, 
	const Handle(Geom_Surface)& Geometry,
	const TColCad3d_HAry1dOfEdgeOnSolid & Edges
)
{
	Cad3d_EntityOnSolid::SetIndex(Index);

	theGeom_ = Geometry;

	theEdges_ = Edges;

	CreatePlane();

	CalcBoundingParameters();

	UpdateOrientation();
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::SetGeometry(const Handle(Geom_Surface)& Geometry)
{
	theGeom_ = Geometry;
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::SetEdges(const TColCad3d_HAry1dOfEdgeOnSolid & Edges)
{
	theEdges_ = Edges;
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::SetTriangulation(const Handle(Poly_Triangulation)& Triangulation)
{
	theTriangulation_ = Triangulation;
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::SetOrientation(const Cad3d_SurfaceOrientationInfo theOrientation)
{
	theOrientation_ = theOrientation;
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::RetrieveParametricCurvesTo(TColCad3d_HAry1dOfCurveOnPlane & Curves) const
{
	Curves.Resize(theEdges_.Size());

	forThose(Index, 0, MaxIndexOf(theEdges_))
		Curves[Index] = (Global_Handle(Cad3d_CurveOnPlane))theEdges_[Index]->CurveOnPlane();
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::GetParametricPlane(Cad2d_Plane & Plane) const
{
	TColCad2d_HAry1dOfCurveOnPlane CurvesOnPlane(theEdges_.Size());
	forThose
	(
		Index,
		0, 
		MaxIndexOf(CurvesOnPlane)
	)
	{
		Debug_Null_Pointer(theEdges_[Index]);
		Debug_Null_Pointer(theEdges_[Index]->CurveOnPlane());

		Get_Const_Object(Curve) = *theEdges_[Index]->CurveOnPlane();
		
		CurvesOnPlane[Index] =
			new Cad2d_CurveOnPlane
			(
				Curve.FirstParameter(),
				Curve.LastParameter(),
				Curve.Curve()
			);
	}

	Plane.Make(CurvesOnPlane);
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::CalcBoundingParameters()
{
	Debug_Null_Pointer(thePlane_);

	Entity_Box2d Box = thePlane_->BoundingBox();
	Box.Get(theUmin_, theUmax_, theVmin_, theVmax_);
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::GetParametricTriangulation(Entity_Triangulation2d & theTriangulation) const
{
	if (NOT HasTriangulation()) { return; }

	Debug_Null_Pointer(theTriangulation_);

	Get_Const_Object(Triangulation) = *theTriangulation_.get();

	Entity_Triangulation2dTools::GetTriangulation(Triangulation, theTriangulation);
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::UpdateOrientation()
{
	Debug_Null_Pointer(thePlane_);
	if (thePlane_->CheckOrientations(Standard_False))
	{
		theOrientation_ = Cad3d_SurfaceOrientation_OUTWARD;
		return;
	}

	if (thePlane_->CheckOrientations(Standard_True))
	{
		theOrientation_ = Cad3d_SurfaceOrientation_INWARD;
		return;
	}
	theOrientation_ = Cad3d_SurfaceOrientation_UNKNOWN;
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::UReverseOrientation()
{
	if (theOrientation_ EQUAL Cad3d_SurfaceOrientation_UNKNOWN) { THROW_STANDARD_EXCEPTION(" Unknown orientation"); }

	if (theGeom_) theGeom_->UReverse();
	if (theTriangulation_) UReverseTriangulation();

	gp_Ax2d Ax(gp_Pnt2d(0, 0), gp_Dir2d(0, 1));

	forThose
	(
		Index, 
		0, 
		MaxIndexOf(theEdges_)
	)
	{
		Debug_Null_Pointer(theEdges_[Index]);

		Get_Pointer(Curve) = (Global_Handle(Cad3d_CurveOnPlane))theEdges_[Index]->CurveOnPlane();
		Curve->Mirror(Ax);
		//theEdges_[Index]->Reverse();
	}
	//theEdges_.Reverse();

	FreePointer(thePlane_);

	CreatePlane();

	theOrientation_ = Cad3d_SurfaceOrientationTools::ReverseOf(theOrientation_);
}

Standard_Boolean AutLib::CadLib::Cad3d_SurfaceOnSolid::HasFreeEdge() const
{
	forThose(Index, 0, MaxIndexOf(theEdges_))
	{
		Debug_Null_Pointer(theEdges_[Index]);
		if (NOT theEdges_[Index]->Paired()) return Standard_True;
	}
	return Standard_False;
}

Geom_Pnt3d AutLib::CadLib::Cad3d_SurfaceOnSolid::Value(const Geom_Pnt2d & theParameter) const
{
	Debug_Null_Pointer(theGeom_);

	return theGeom_->Value(theParameter.X(), theParameter.Y());
}

Geom_Pnt3d AutLib::CadLib::Cad3d_SurfaceOnSolid::NormalAt(const Geom_Pnt2d & theParameter) const
{
	Debug_Null_Pointer(theGeom_);

	gp_Pnt Pt;
	gp_Vec du, dv;

	theGeom_->D1(theParameter.X(), theParameter.Y(), Pt, du, dv);
	
	gp_Vec N = du.Crossed(dv);

	return Geom_Pnt3d(N.X(), N.Y(), N.Z());
}

Geom_Pnt3d AutLib::CadLib::Cad3d_SurfaceOnSolid::NormalAt
(
	const Geom_Pnt2d & theParameter, 
	Geom_Pnt3d & theCoord
) const
{
	Debug_Null_Pointer(theGeom_);

	gp_Vec du, dv;

	theGeom_->D1(theParameter.X(), theParameter.Y(), theCoord, du, dv);

	gp_Vec N = du.Crossed(dv);

	return Geom_Pnt3d(N.X(), N.Y(), N.Z());
}

Entity_Box3d AutLib::CadLib::Cad3d_SurfaceOnSolid::BoundingBox(const Standard_Real Offset) const
{
	TColCad3d_HAry1dOfCurveOnPlane Curves;
	Cad3d_SurfaceOnSolid::RetrieveParametricCurvesTo(Curves);

	Entity_Box2d ParamBox = Cad3d_CurveOnPlaneTools::BoundingBoxOf(Curves, Offset);

	Bnd_Box BndBox;
	BndLib_AddSurface::Add(GeomAdaptor_Surface(theGeom_), ParamBox.Xmin(), ParamBox.Xmax(), ParamBox.Ymin(), ParamBox.Ymax(), Offset, BndBox);

	Standard_Real Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
	BndBox.Get(Xmin, Ymin, Zmin, Xmax, Ymax, Zmax);

	Entity_Box3d Box(Xmin, Xmax, Ymin, Ymax, Zmin, Zmax);
	return Box.OffsetBox(Offset);
}

GeoLib::Entity_Box2d AutLib::CadLib::Cad3d_SurfaceOnSolid::ParametricBoundingBox(const Standard_Real Offset) const
{
	Entity_Box2d Box(theUmin_, theUmax_, theVmin_, theVmax_);
	return Box.OffsetBox(Offset);
}

Entity_StaticChain3d AutLib::CadLib::Cad3d_SurfaceOnSolid::GetGeometricNormals(const Standard_Real theCoeff) const
{
	Debug_Null_Pointer(theTriangulation_);

	Get_Const_Object(Triangulation) = *theTriangulation_.get();

	Entity_Box3d Box = BoundingBox();
	Standard_Real Coeff = Box.Diameter()*theCoeff;

	if (Coeff < gp::Resolution()) { THROW_STANDARD_EXCEPTION("Invalid Data"); }

	Get_Const_Object(Triangles) = Triangulation.Triangles();
	Get_Const_Object(Points) = Triangulation.UVNodes();

	Entity_StaticChain3d Chain;
	Get_Object(Coords) = Chain.Coords();
	Get_Object(Edges) = Chain.Edges();

	Coords.Resize(2 * Triangles.Size());
	Edges.Resize(Triangles.Size());

	Standard_Integer K = 0;
	Geom_Pnt3d Coord;
	forThose
	(
		Index,
		1,
		Triangles.Size()
	)
	{
		Get_Const_Object(Triangle) = Triangles.Value(Index);

		Standard_Integer V1, V2, V3;
		Triangle.Get(V1, V2, V3);

		gp_Pnt2d P1 = Points.Value(V1);
		gp_Pnt2d P2 = Points.Value(V2);
		gp_Pnt2d P3 = Points.Value(V3);

		gp_Pnt2d Pt((P1.X() + P2.X() + P3.X()) / 3, (P1.Y() + P2.Y() + P3.Y()) / 3);

		Geom_Pnt3d N = NormalAt(Pt, Coord);

		Coords.SetValue(K, Coord);
		K++;

		Standard_Real d = N.TwoNorm();
		if (d > gp::Resolution())
		{
			N /= d;
			N *= Coeff;
		}
		Coords.SetValue(K, Coord + N);
		K++;

		Edges.SetValue(Index - 1, Entity_EdgeIndex(K - 1, K));
	}

	MOVE(Chain);
}

Entity_StaticChain3d AutLib::CadLib::Cad3d_SurfaceOnSolid::GetTriangulationNormals(const Standard_Real theCoeff) const
{
	Debug_Null_Pointer(theTriangulation_);

	Get_Const_Object(Triangulation) = *theTriangulation_.get();

	Entity_Box3d Box = BoundingBox();
	Standard_Real Coeff = Box.Diameter()*theCoeff;

	if (Coeff < gp::Resolution()) { THROW_STANDARD_EXCEPTION("Invalid Data"); }

	Get_Const_Object(Triangles) = Triangulation.Triangles();
	Get_Const_Object(Points) = Triangulation.Nodes();

	Entity_StaticChain3d Chain;
	Get_Object(Coords) = Chain.Coords();
	Get_Object(Edges) = Chain.Edges();

	Coords.Resize(2 * Triangles.Size());
	Edges.Resize(Triangles.Size());

	Standard_Integer K = 0;
	forThose
	(
		Index,
		1,
		Triangles.Size()
	)
	{
		Get_Const_Object(Triangle) = Triangles.Value(Index);

		Standard_Integer V1, V2, V3;
		Triangle.Get(V1, V2, V3);

		Geom_Pnt3d P1 = Points.Value(V1);
		Geom_Pnt3d P2 = Points.Value(V2);
		Geom_Pnt3d P3 = Points.Value(V3);

		Geom_Pnt3d Pt((P1.X() + P2.X() + P3.X()) / 3, (P1.Y() + P2.Y() + P3.Y()) / 3, (P1.Z() + P2.Z() + P3.Z()) / 3);

		Geom_Pnt3d N = CrossProduct(P2 - P1, P3 - P1);

		Coords.SetValue(K, Pt);
		K++;

		Standard_Real d = N.TwoNorm();
		if (d > gp::Resolution())
		{
			N /= d;
			N *= Coeff;
		}

		Coords.SetValue(K, Pt + N);
		K++;

		Edges.SetValue(Index - 1, Entity_EdgeIndex(K - 1, K));
	}

	MOVE(Chain);
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::ExportTriangulationToPlt(fstream & File) const
{
	if (theTriangulation_) M_IO IO_TecPlot::ExportMesh(theTriangulation_, File);
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::ExportParametricCurvesToPlt(fstream & File) const
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(theEdges_)
	)
	{
		Debug_Null_Pointer(theEdges_[Index]);

		theEdges_[Index]->ExportParametricCurvesToPlt(File);
	}
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::ExportCurveToPlt(fstream & File) const
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(theEdges_)
	)
	{
		Debug_Null_Pointer(theEdges_[Index]);

		theEdges_[Index]->ExportToPlt(File);
	}
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::ExportTopologyToPlt(fstream & File) const
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(theEdges_)
	)
	{
		Debug_Null_Pointer(theEdges_[Index]);
		Debug_Null_Pointer(theEdges_[Index]->CurveOnSurface());

		theEdges_[Index]->CurveOnSurface()->ExportTopologyToPlt(File);
	}
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::ExportRopologyFromParametricPlaneToPlt(fstream & File) const
{
	Debug_Null_Pointer(theGeom_);

	Get_Const_Object(Geom) = *theGeom_;

	forThose
	(
		Index,
		0,
		MaxIndexOf(theEdges_)
	)
	{
		Debug_Null_Pointer(theEdges_[Index]);
		Debug_Null_Pointer(theEdges_[Index]->CurveOnPlane());

		Get_Const_Object(Curve) = *theEdges_[Index]->CurveOnPlane();

		Geom_Pnt2d P0 = Curve.FirstCoord();
		Geom_Pnt2d P1 = Curve.LastCoord();

		M_IO IO_TecPlot::ExportCurve(Geom.Value(P0.X(), P0.Y()), Geom.Value(P1.X(), P1.Y()), File);
	}
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::ExportGeometryNormalsToPlt
(
	fstream & File, 
	const Standard_Real theCoeff
) const
{
	Entity_StaticChain3d Chain;
	Try_Exception_Handle_Exit(Chain = GetGeometricNormals(theCoeff));

	Chain.ExportToPlt(File);
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::ExportTriangulationNormalsToPlt(fstream & File) const
{
	Entity_StaticChain3d Chain;
	Try_Exception_Handle_Exit(Chain = GetTriangulationNormals());

	Chain.ExportToPlt(File);
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::ExportToPlt(fstream & File) const
{
	Cad3d_SurfaceOnSolid::ExportTriangulationToPlt(File);
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::ReleaseMemory()
{
	FreeMemory(theEdges_);

	FreePointer(thePlane_);
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::UReverseTriangulation()
{
	gp_Ax2d Ax(gp_Pnt2d(0, 0), gp_Dir2d(0, 1));

	Get_Object(Triangles) = theTriangulation_->ChangeTriangles();
	forThose
	(
		Index,
		1, 
		Triangles.Size()
	)
	{
		Get_Object(Triangle) = Triangles.Value(Index);
		
		Standard_Integer V1, V2, V3;
		Triangle.Get(V1, V2, V3);
		
		Triangles.SetValue(Index, Poly_Triangle(V3, V2, V1));
	}

	Get_Object(Points) = theTriangulation_->ChangeUVNodes();
	Get_Object(Coords) = theTriangulation_->ChangeNodes();
	forThose
	(
		Index,
		1,
		Points.Size()
	)
	{
		Points.ChangeValue(Index).Mirror(Ax);

		Get_Const_Object(Parameter) = Points.Value(Index);
		Coords.SetValue(Index, theGeom_->Value(Parameter.X(), Parameter.Y()));
	}
}

void AutLib::CadLib::Cad3d_SurfaceOnSolid::CreatePlane()
{
	if (theEdges_.IsEmpty()) { THROW_STANDARD_EXCEPTION("Empty List"); }
	thePlane_ = new Cad3d_Plane;
	thePlane_->Make(Cad3d_CurveOnPlaneTools::RetrieveCurvesOnPlane(theEdges_), theParametricTolerance_);
}