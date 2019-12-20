#include <Cad2d_PointOnPlane.hxx>

#include <IO_Tecplot.hxx>
#include <Cad2d_CurveOnPlane.hxx>
#include <Cad2d_RingOnPlane.hxx>
#include <Cad2d_EdgeOnPlaneTools.hxx>

using namespace AutLib;
using namespace CadLib;

#include <Geom2d_Curve.hxx>

AutLib::CadLib::Cad2d_PointOnPlane::Cad2d_PointOnPlane()
	: theIndex_(0)
{
	theEdges_.SetComparable(&Cad2d_EdgeOnPlaneTools::IsLess);
}

AutLib::CadLib::Cad2d_PointOnPlane::Cad2d_PointOnPlane
(
	const Standard_Integer theIndex,
	const Geom_Pnt2d & theCoord
)
	: theIndex_(theIndex)
	, theCoord_(theCoord)
{
	theEdges_.SetComparable(&Cad2d_EdgeOnPlaneTools::IsLess);
}

AutLib::CadLib::Cad2d_PointOnPlane::~Cad2d_PointOnPlane()
{
}

Standard_Boolean AutLib::CadLib::Cad2d_PointOnPlane::IsRingPoint() const
{
	if (NbEdges() NOT_EQUAL 1) return Standard_False;
	TColCad2d_HAry1dOfEdgeOnPlane Edges;
	theEdges_.RetrieveTo(Edges);

	Debug_If_Condition(Edges.Size() NOT_EQUAL 1);
	Debug_Null_Pointer(Edges[0]);

	if (Global_DownCast(Cad2d_RingOnPlane, Edges[0])) return Standard_True;
	return Standard_False;
}

Standard_Boolean AutLib::CadLib::Cad2d_PointOnPlane::IsManifold() const
{
	if (IsRingPoint()) return Standard_True;
	else if (theEdges_.Size() EQUAL 2) return Standard_True;
	return Standard_False;
}

Standard_Boolean AutLib::CadLib::Cad2d_PointOnPlane::IsSharp(const Standard_Real theRadianAngle) const
{
	THROW_STANDARD_EXCEPTION_IF(NOT IsManifold(), "It's Not a manifold corner");

	TColCad2d_HAry1dOfEdgeOnPlane Edges;
	RetrieveEdgesTo(Edges);

	Debug_If_Condition(Edges.Size() NOT_EQUAL 2);

	Global_Handle(Cad2d_EdgeOnPlane) Edge0 = Edges[0];
	Global_Handle(Cad2d_EdgeOnPlane) Edge1 = Edges[1];

	if (Edge0->LastPoint() NOT_EQUAL this)
	{
		SWAP(Edge0, Edge1);
	}

	const Handle(Geom2d_Curve) Curve0 = Edge0->Curve()->Curve();
	const Handle(Geom2d_Curve) Curve1 = Edge1->Curve()->Curve();

	gp_Vec2d Vec1 = Curve0->DN(Edge0->Curve()->LastParameter(), 1);
	gp_Vec2d Vec2 = Curve1->DN(Edge1->Curve()->FirstParameter(), 1);
	//return acos(Vec1.Dot(Vec2) / (Vec1.Magnitude()*Vec2.Magnitude())) < theRadianAngle;
	return ABS(Vec2.Angle(Vec1)) < theRadianAngle;
}

void AutLib::CadLib::Cad2d_PointOnPlane::SetIndex(const Standard_Integer theIndex)
{
	theIndex_ = theIndex;
}

void AutLib::CadLib::Cad2d_PointOnPlane::SetCoord(const Geom_Pnt2d & theCoord)
{
	theCoord_ = theCoord;
}

void AutLib::CadLib::Cad2d_PointOnPlane::ExportToPlt(fstream & File) const
{
	M_IO IO_TecPlot::ExportPoint(theCoord_, File);
}

void AutLib::CadLib::Cad2d_PointOnPlane::Mirror(const gp_Pnt2d & P)
{
	theCoord_.Mirror(P);
}

void AutLib::CadLib::Cad2d_PointOnPlane::Mirror(const gp_Ax2d & A)
{
	theCoord_.Mirror(A);
}

void AutLib::CadLib::Cad2d_PointOnPlane::Rotate(const gp_Pnt2d & P, const Standard_Real Ang)
{
	theCoord_.Rotate(P, Ang);
}

void AutLib::CadLib::Cad2d_PointOnPlane::Scale(const gp_Pnt2d & P, const Standard_Real S)
{
	theCoord_.Scale(P, S);
}

void AutLib::CadLib::Cad2d_PointOnPlane::Translate(const gp_Vec2d & V)
{
	theCoord_.Translate(V);
}

void AutLib::CadLib::Cad2d_PointOnPlane::Translate(const gp_Pnt2d & P1, const gp_Pnt2d & P2)
{
	theCoord_.Translate(P1, P2);
}

void AutLib::CadLib::Cad2d_PointOnPlane::Transform(const gp_Trsf2d & T)
{
	theCoord_.Transform(T);
}

Global_Handle(Cad2d_PointOnPlane) AutLib::CadLib::Cad2d_PointOnPlane::Copy() const
{
	return new Cad2d_PointOnPlane(theIndex_, theCoord_);
}