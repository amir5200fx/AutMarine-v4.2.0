#include <Entity_StaticChain2d.hxx>

#include <Merge_Chain2d.hxx>
#include <Entity_Box2d.hxx>
#include <Entity_EdgeIndexTools.hxx>
#include <IO_Tecplot.hxx>

using namespace AutLib;
using namespace GeoLib;

AutLib::GeoLib::Entity_StaticChain2d::Entity_StaticChain2d()
{
}

AutLib::GeoLib::Entity_StaticChain2d::Entity_StaticChain2d
(
	const TColGeom_Ary1dOfPnt2d & Points, 
	const TColEntity_Ary1dOfEdgeIndex & Edges, 
	const Standard_Boolean Cycle
)
	: thePts_(Points)
	, theEdges_(Edges)
	, IsCycle_(Cycle)
{
}

void AutLib::GeoLib::Entity_StaticChain2d::Init
(
	const TColGeom_Ary1dOfPnt2d & Points, 
	const TColEntity_Ary1dOfEdgeIndex & Edges,
	const Standard_Boolean Cycle
)
{
	thePts_ = Points;
	theEdges_ = Edges;
	IsCycle_ = Cycle;
}

TColEntity_Ary1dOfTriangleIndex AutLib::GeoLib::Entity_StaticChain2d::GetTriangleIndices() const
{
	TColEntity_Ary1dOfTriangleIndex Triangles(theEdges_.Size());

	forThose(Index, 0, MaxIndexOf(Triangles))
	{
		Triangles[Index].SetValue(theEdges_[Index].V0(), theEdges_[Index].V1(), theEdges_[Index].V0());
	}

	MOVE(Triangles);
}

Entity_Box2d AutLib::GeoLib::Entity_StaticChain2d::BoundingBox() const
{
	Entity_Box2d Box;

	Standard_Real
		Xp,
		Yp;

	Get_Const_Object(Coords) = thePts_;

	Try_Exception_Handle_Exit(Box.Xmax() = Box.Xmin() = Coords[0].X());
	Try_Exception_Handle_Exit(Box.Ymax() = Box.Ymin() = Coords[0].Y());

	forThose
	(
		Index,
		1,
		MaxIndexOf(Coords)
	)
	{
		Xp = Coords[Index].X();
		Yp = Coords[Index].Y();

		if (Xp < Box.Xmin()) Box.Xmin() = Xp;
		if (Xp > Box.Xmax()) Box.Xmax() = Xp;
		if (Yp < Box.Ymin()) Box.Ymin() = Yp;
		if (Yp > Box.Ymax()) Box.Ymax() = Yp;
	}

	MOVE(Box);
}

void AutLib::GeoLib::Entity_StaticChain2d::Reverse()
{
	forThose(Index, 0, MaxIndexOf(theEdges_))
	{
		theEdges_[Index].Reverse();
	}
	theEdges_.Reverse();
}

void AutLib::GeoLib::Entity_StaticChain2d::SetCoords(const TColGeom_Ary1dOfPnt2d & Points)
{
	thePts_ = Points;
}

void AutLib::GeoLib::Entity_StaticChain2d::SetEdges(const TColEntity_Ary1dOfEdgeIndex & Edges)
{
	theEdges_ = Edges;
}

void AutLib::GeoLib::Entity_StaticChain2d::SetCycle(const Standard_Boolean Cycle)
{
	IsCycle_ = Cycle;
}

void AutLib::GeoLib::Entity_StaticChain2d::Merging
(
	const Standard_Boolean HandleDegeneracy,
	const Standard_Real Resolution,
	const Standard_Real Radius
)
{
	Merge_Chain2d Merging(Resolution, Radius);
	Merging.Import(*this);

	Merging.SetDegeneracy(HandleDegeneracy);

	Merging.Perform();

	Debug_If_Condition_Message(NOT Merging.IsDone(), " Merging not performed");

	*this = *Merging.Merged();
}

void AutLib::GeoLib::Entity_StaticChain2d::ExportToPlt(fstream & File) const
{
	M_IO IO_TecPlot::ExportMesh(thePts_, theEdges_, File);
}