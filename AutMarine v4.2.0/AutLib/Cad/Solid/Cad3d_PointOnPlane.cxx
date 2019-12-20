#include <Cad3d_PointOnPlane.hxx>

#include <Cad3d_RingOnPlane.hxx>
#include <IO_Tecplot.hxx>
#include <Cad3d_EdgeOnPlaneTools.hxx>
#include <TColCad3d_HBasicQueueOfEdgeOnPlane.hxx>

using namespace AutLib;
using namespace CadLib;

AutLib::CadLib::Cad3d_PointOnPlane::Cad3d_PointOnPlane()
	: theIndex_(0)
{
	theEdges_.SetComparable(&Cad3d_EdgeOnPlaneTools::IsLess);
}

AutLib::CadLib::Cad3d_PointOnPlane::Cad3d_PointOnPlane
(
	const Standard_Integer theIndex, 
	const Geom_Pnt2d & theCoord
)
	: theIndex_(theIndex)
	, theCoord_(theCoord)
{
	theEdges_.SetComparable(&Cad3d_EdgeOnPlaneTools::IsLess);
}

AutLib::CadLib::Cad3d_PointOnPlane::~Cad3d_PointOnPlane()
{
}

Standard_Boolean AutLib::CadLib::Cad3d_PointOnPlane::IsRingPoint() const
{
	if (NbEdges() NOT_EQUAL 1) return Standard_False;
	TColCad3d_HAry1dOfEdgeOnPlane Edges;
	RetrieveEdgesTo(Edges);

	Debug_If_Condition(Edges.Size() NOT_EQUAL 1);
	Debug_Null_Pointer(Edges[0]);

	if (Global_DownCast(Cad3d_RingOnPlane, Edges[0])) return Standard_True;
	return Standard_False;
}

void AutLib::CadLib::Cad3d_PointOnPlane::ImportEdge(const Global_Handle(Cad3d_EdgeOnPlane) theEdge)
{
	theEdges_.Insert((Global_Handle(Cad3d_EdgeOnPlane))theEdge);
}

void AutLib::CadLib::Cad3d_PointOnPlane::SetIndex(const Standard_Integer theIndex)
{
	theIndex_ = theIndex;
}

void AutLib::CadLib::Cad3d_PointOnPlane::SetCoord(const Geom_Pnt2d & theCoord)
{
	theCoord_ = theCoord;
}

void AutLib::CadLib::Cad3d_PointOnPlane::RetrieveEdgesTo(TColCad3d_HAry1dOfEdgeOnPlane & theEdges) const
{
	theEdges_.RetrieveTo(theEdges);
}

void AutLib::CadLib::Cad3d_PointOnPlane::ExportToPlt(fstream & File) const
{
	M_IO IO_TecPlot::ExportPoint(theCoord_, File);
}

Global_Handle(Cad3d_PointOnPlane) AutLib::CadLib::Cad3d_PointOnPlane::Copy() const
{
	return new Cad3d_PointOnPlane(theIndex_, theCoord_);
}