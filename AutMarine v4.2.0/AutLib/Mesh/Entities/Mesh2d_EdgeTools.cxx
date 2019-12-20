#include <Mesh2d_EdgeTools.hxx>

#include <Geometry_Tools.hxx>
#include <Geometry_Intersect.hxx>
#include <Mesh2d_NodeTools.hxx>
#include <IO_Tecplot.hxx>
#include <ADT_NumbAvlTree.hxx>
#include <Entity_StaticChain2d.hxx>
#include <TColMesh2d_HAvlTreeOfNode.hxx>

using namespace AutLib;
using namespace GeoLib;

Standard_Boolean AutLib::MeshLib::Mesh2d_EdgeTools::IsIntersect
(
	const Mesh2d_Edge & Edge1, 
	const Mesh2d_Edge & Edge2
)
{
	Get_Const_Object(N1) = *Edge1.Node(0);
	Get_Const_Object(N2) = *Edge1.Node(1);
	Get_Const_Object(V1) = *Edge2.Node(0);
	Get_Const_Object(V2) = *Edge2.Node(1);

	if (Geometry_Tools::IsOneCommonPointTwoLineSegment(N1.Index(), N2.Index(), V1.Index(), V2.Index())) { return Standard_False; }

	if (Geometry_Intersect::IsIntersect(N1.Coord(), N2.Coord(), V1.Coord(), V2.Coord())) 
	{ 
		return Standard_True;
	}

	return Standard_False;
}

TColEntity_Ary1dOfEdgeIndex AutLib::MeshLib::Mesh2d_EdgeTools::StaticOf(const TColMesh2d_HAry1dOfEdge & Edges)
{
	TColEntity_Ary1dOfEdgeIndex StaticEdges(Edges.Size());
	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		Get_Const_Object(Edge) = *Edges[Index];

		StaticEdges[Index].SetV12(Edge.Node(0)->Index(), Edge.Node(1)->Index());
	}
	MOVE(StaticEdges);
}

TColMesh2d_HAry1dOfNode AutLib::MeshLib::Mesh2d_EdgeTools::RetrieveNodesFrom(const TColMesh2d_HAry1dOfEdge & Edges)
{
	ADT_NumbAvlTree<Global_Handle(Mesh2d_Node)> TNodes;
	TNodes.SetComparable(Mesh2d_NodeTools::IsLess);
	//Set_Numbering(TNodes, Mesh2d_NodeTools::IsLess);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		Get_Const_Object(Edge) = *Edges[Index];

		Debug_Null_Pointer(Edge.Node(0));
		Debug_Null_Pointer(Edge.Node(1));

		TNodes.InsertIgnoreDup(Edge.Node(0));
		TNodes.InsertIgnoreDup(Edge.Node(1));
	}

	TColMesh2d_HAry1dOfNode Nodes;
	TNodes.RetrieveTo(Nodes);

	MOVE(Nodes);
}

TColMesh2d_HAry1dOfNode AutLib::MeshLib::Mesh2d_EdgeTools::RetrieveSortedNodesFrom(const TColMesh2d_HAry1dOfEdge & Edges)
{
	TColMesh2d_HAvlTreeOfNode TNodes;
	Set_Numbering(TNodes, Mesh2d_NodeTools::IsLess);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		Get_Const_Object(Edge) = *Edges[Index];

		Debug_Null_Pointer(Edge.Node(0));
		Debug_Null_Pointer(Edge.Node(1));

		TNodes.InsertIgnoreDup(Edge.Node(0));
		TNodes.InsertIgnoreDup(Edge.Node(1));
	}

	TColMesh2d_HAry1dOfNode Nodes;
	TNodes.RetrieveTo(Nodes);

	MOVE(Nodes);
}

Entity_StaticChain2d AutLib::MeshLib::Mesh2d_EdgeTools::RetrieveChainFrom(const TColMesh2d_HAry1dOfEdge & theEdges)
{
	return Entity_StaticChain2d(Mesh2d_NodeTools::GetCoordOf(Mesh2d_EdgeTools::RetrieveSortedNodesFrom(theEdges)), StaticOf(theEdges));
}

void AutLib::MeshLib::Mesh2d_EdgeTools::ExportToPlt
(
	const TColMesh2d_HAry1dOfEdge & theEdges,
	fstream & File
)
{
	M_IO IO_TecPlot::ExportMesh(Mesh2d_NodeTools::GetCoordOf(Mesh2d_EdgeTools::RetrieveNodesFrom(theEdges)), Mesh2d_EdgeTools::StaticOf(theEdges), File);
}