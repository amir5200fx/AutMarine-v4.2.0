#include <Entity_StaticChain3d.hxx>

#include <Merge_Chain3d.hxx>
#include <Entity_EdgeIndexTools.hxx>
#include <IO_Tecplot.hxx>

using namespace AutLib;
using namespace GeoLib;

AutLib::GeoLib::Entity_StaticChain3d::Entity_StaticChain3d()
{
}

void AutLib::GeoLib::Entity_StaticChain3d::Init
(
	const TColGeom_Ary1dOfPnt3d & Points, 
	const TColEntity_Ary1dOfEdgeIndex & Edges,
	const Standard_Boolean Cycle
)
{
	thePts_ = Points;
	theEdges_ = Edges;
	IsCycle_ = Cycle;
}

TColEntity_Ary1dOfTriangleIndex AutLib::GeoLib::Entity_StaticChain3d::GetTriangleIndices() const
{
	TColEntity_Ary1dOfTriangleIndex Triangles(theEdges_.Size());

	forThose(Index, 0, MaxIndexOf(Triangles))
	{
		Triangles[Index].SetValue(theEdges_[Index].V0(), theEdges_[Index].V1(), theEdges_[Index].V0());
	}

	MOVE(Triangles);
}

void AutLib::GeoLib::Entity_StaticChain3d::SetCoords(const TColGeom_Ary1dOfPnt3d & Points)
{
	thePts_ = Points;
}

void AutLib::GeoLib::Entity_StaticChain3d::SetEdges(const TColEntity_Ary1dOfEdgeIndex & Edges)
{
	theEdges_ = Edges;
}

void AutLib::GeoLib::Entity_StaticChain3d::SetCycle(const Standard_Boolean Cycle)
{
	IsCycle_ = Cycle;
}

void AutLib::GeoLib::Entity_StaticChain3d::Merging
(
	const Standard_Real Resolution,
	const Standard_Real Radius,
	const Standard_Boolean HandleDegeneracy
)
{
	Merge_Chain3d Merging(Resolution, Radius);
	Merging.Import(*this);
	Merging.SetDegeneracy(HandleDegeneracy);

	Merging.Perform();

	Debug_If_Condition_Message(NOT Merging.IsDone(), " Merging not performed");

	*this = *Merging.Merged();
}

void AutLib::GeoLib::Entity_StaticChain3d::ExportToPlt(fstream & File) const
{
	M_IO IO_TecPlot::ExportMesh(thePts_, theEdges_, File);
}