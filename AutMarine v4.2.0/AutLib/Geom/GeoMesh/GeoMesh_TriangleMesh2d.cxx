#include <GeoMesh_TriangleMesh2d.hxx>

#include <Entity_Polygon2d.hxx>
#include <Entity_Node2dTools.hxx>
#include <Entity_Edge2dTools.hxx>
#include <Entity_Element2dTools.hxx>
#include <Entity_Triangulation2d.hxx>
#include <TColGeom_BasicQueueOfPnt2d.hxx>
#include <TColEntity_HAry1dOfEdge2d.hxx>
#include <IO_Tecplot.hxx>

using namespace AutLib;
using namespace GeoLib;

AutLib::GeoLib::GeoMesh_TriangleMesh2d::GeoMesh_TriangleMesh2d()
	: theNbNodes_(0)
	, theNbEdges_(0)
	, thenbElements_(0)
	, IsDone_(Standard_False)
{
	Set_Numbering(theNodes_, Entity_Node2dTools::IsLess);
	Set_Numbering(theEdges_, Entity_Edge2dTools::IsLess);
	Set_Numbering(theElements_, Entity_Element2dTools::IsLess);

	theNodes_.SetName(" Mesh Nodes Tree");
	theEdges_.SetName(" Mesh Edges Tree");
	theElements_.SetName(" Mesh Elements Tree");
}

namespace AutLib
{
	namespace GeoLib
	{
		Entity_Polygon2d GetPolygon(Global_Handle(Entity_Edge2d) Edge)
		{
			TColGeom_BasicQueueOfPnt2d PointList;

			Global_Handle(Entity_Node2d) Start = Edge->Node(0);
			Global_Handle(Entity_Node2d) End = Edge->Node(1);
			Global_Handle(Entity_Node2d) Mark = Start;

			while (End NOT_EQUAL Start)
			{
				TColEntity_HAry1dOfEdge2d Edges;
				End->Edges(Edges);

				forThose
				(
					Index,
					0,
					MaxIndexOf(Edges)
				)
				{
					if (NOT Edges[Index]->IsOnBoundary()) continue;

					Global_Handle(Entity_Node2d) Node0 = Edges[Index]->Node(0);
					Global_Handle(Entity_Node2d) Node1 = Edges[Index]->Node(1);

					if (Node0 NOT_EQUAL End)
					{
						if (Node1 NOT_EQUAL Mark)
						{
							PointList.EnQueue(Node1->Coord());
							Mark = End;
							End = Node1;
							break;
						}
					}

					if (Node1 NOT_EQUAL End)
					{
						if (Node0 NOT_EQUAL Mark)
						{
							PointList.EnQueue(Node0->Coord());
							Mark = End;
							End = Node0;
							break;
						}
					}
				}
			}

			return Entity_Polygon2d(PointList.Retrive());
		}

		TColEntity_HAry1dOfEdge2d Marching(TColEntity_HAvlTreeOfEdge2d& TEdges)
		{
			if (NOT TEdges.Size()) { THROW_STANDARD_EXCEPTION(" Edges Tree is Empty"); }

			TColEntity_HBasicQueueOfEdge2d QEdges;

			Global_Handle(Entity_Edge2d) Edge;
			TEdges.Root(Edge);

			QEdges.EnQueue(Edge);
			TEdges.Remove(Edge);

			Global_Handle(Entity_Node2d) Start = Edge->Node(0);
			Global_Handle(Entity_Node2d) End = Edge->Node(1);
			Global_Handle(Entity_Node2d) Mark = Start;

			while (End NOT_EQUAL Start)
			{
				TColEntity_HAry1dOfEdge2d Edges;
				End->Edges(Edges);

				forThose
				(
					Index,
					0,
					MaxIndexOf(Edges)
				)
				{
					if (NOT Edges[Index]->IsOnBoundary()) continue;

					Global_Handle(Entity_Node2d) Node0 = Edges[Index]->Node(0);
					Global_Handle(Entity_Node2d) Node1 = Edges[Index]->Node(1);

					if (Node0 NOT_EQUAL End)
					{
						if (Node1 NOT_EQUAL Mark)
						{
							QEdges.EnQueue(Edges[Index]);
							TEdges.Remove(Edges[Index]);
							Mark = End;
							End = Node1;
							break;
						}
					}

					if (Node1 NOT_EQUAL End)
					{
						if (Node0 NOT_EQUAL Mark)
						{
							QEdges.EnQueue(Edges[Index]);
							TEdges.Remove(Edges[Index]);
							Mark = End;
							End = Node0;
							break;
						}
					}
				}
			}

			return QEdges.Retrive();
		}
	}
}

Entity_Polygon2d AutLib::GeoLib::GeoMesh_TriangleMesh2d::GetBoundaryPolygon(const Standard_Integer Index) const
{
	Debug_If_Condition(NOT IsDone_);
	Debug_Bad_Index(Index, 0, NbBoundaries() - 1);
	return GetPolygon(theBoundaries_[Index]->Value(0));
}

Entity_Triangulation2d AutLib::GeoLib::GeoMesh_TriangleMesh2d::Static() const
{
	Debug_If_Condition(NOT IsDone_);
	return Entity_Triangulation2d(Entity_Node2dTools::GetStaticOf(theNodesSequence_), Entity_Element2dTools::GetStaticOf(theElementsSequence_));
}

void AutLib::GeoLib::GeoMesh_TriangleMesh2d::Construct(const Entity_Triangulation2d & Triangulation)
{
	IsDone_ = Standard_True;

	const TColGeom_Ary1dOfPnt2d& Points = Triangulation.Points();
	const TColEntity_Ary1dOfTriangleIndex &Triangles = Triangulation.Triangles();

	theNodesSequence_.Resize(Points.Size());
	theElementsSequence_.Resize(Triangles.Size());

	// Create Nodes
	forThose(Index, 0, MaxIndexOf(Points))
		theNodesSequence_[Index] = new Entity_Node2d(Index + 1, Points[Index]);

	// Create Elements
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Triangles)
	)
	{
		theElementsSequence_[Index] = new Entity_Element2d(Index + 1);

		Standard_Integer V0 = Index_Of(Triangles[Index].V0());
		Standard_Integer V1 = Index_Of(Triangles[Index].V1());
		Standard_Integer V2 = Index_Of(Triangles[Index].V2());

		theElementsSequence_[Index]->SetNode0(theNodesSequence_[V0]);
		theElementsSequence_[Index]->SetNode1(theNodesSequence_[V1]);
		theElementsSequence_[Index]->SetNode2(theNodesSequence_[V2]);
	}
	
	forThose
	(
		Index,
		0,
		MaxIndexOf(theElementsSequence_)
	)
	{
		Debug_Null_Pointer(theElementsSequence_[Index]);

		Get_Object(Element) = *theElementsSequence_[Index];

		Element.Node0()->InsertToElements(&Element);
		Element.Node1()->InsertToElements(&Element);
		Element.Node2()->InsertToElements(&Element);
	}

	Standard_Integer MaxIndex = Points.Size();
	//ADT_Ary1d<TColEntity_HBasicQueueOfEdge2d> EdgesAroundPoints(MaxIndex);
	TColEntity_HBasicQueueOfEdge2d AllEdges;

	MaxIndex = 0;
	TColEntity_HAvlTreeOfEdge2d BoundaryEdges;
	Set_Numbering(BoundaryEdges, Entity_Edge2dTools::IsLess);

	// Create Edges
	forThose
	(
		Index,
		0, 
		MaxIndexOf(theElementsSequence_)
	)
	{
		Get_Object(Element) = theElementsSequence_[Index];

		forThose
		(
			I,
			0,
			2
		)
		{
			Standard_Integer Id1 = (I + 1) % 3;
			Standard_Integer Id2 = (Id1 + 1) % 3;

			Global_Handle(Entity_Node2d) Node1 = Element->Node(Id1);
			Global_Handle(Entity_Node2d) Node2 = Element->Node(Id2);

			Global_Handle(Entity_Edge2d) Edge = NULL;

			Standard_Integer V1 = Node1->Index();
			Standard_Integer V2 = Node2->Index();

			Standard_Boolean Create = Standard_False;

			if ((NOT Node1->NbEdges()) OR (NOT Node2->NbEdges()))
			{
				Create = Standard_True;
			}
			else
			{
				Standard_Integer Size1 = Node1->NbEdges();
				Standard_Integer Size2 = Node2->NbEdges();

				TColEntity_HAry1dOfEdge2d TempEdges;

				Global_Handle(Entity_Node2d) Compare;

				if (Size1 <= Size2)
				{
					Node1->Edges(TempEdges);
					Compare = Node2;
				}
				else
				{
					Node2->Edges(TempEdges);
					Compare = Node1;
				}

				Standard_Boolean Exist = Standard_False;

				forThose
				(
					J,
					0,
					MaxIndexOf(TempEdges)
				)
				{
					if ((TempEdges[J]->Node(0) EQUAL Compare) OR (TempEdges[J]->Node(1) EQUAL Compare))
					{
						Exist = Standard_True;
						Edge = TempEdges[J];

						Edge->SetRightElement(theElementsSequence_[Index]);
						Edge->SetAsNonBoundary();

						Try_Exception_Handle_Exit(BoundaryEdges.Remove(Edge));

						break;
					}
				}

				if (NOT Exist)
					Create = Standard_True;
			}

			if (Create)
			{
				Debug_If_Condition(Edge);

				Edge = new Entity_Edge2d(++MaxIndex, Node1, Node2);

				theEdges_.Insert(Edge);

				AllEdges.EnQueue(Edge);

				Edge->SetLeftElement(theElementsSequence_[Index]);
				Edge->SetAsBoundary();

				Try_Exception_Handle_Exit(BoundaryEdges.Insert(Edge));

				Node1->InsertToEdges(Edge);
				Node2->InsertToEdges(Edge);
			}

			Element->SetEdge(I, Edge);
		}
	}

	// Identify Neighbors
	forThose
	(
		Index,
		0,
		MaxIndexOf(theElementsSequence_)
	)
	{
		Debug_Null_Pointer(theElementsSequence_[Index]->Edge0());
		Get_Const_Object(Edge0) = *theElementsSequence_[Index]->Edge0();

		theElementsSequence_[Index]->SetNeighbor0(Edge0.LeftElement());
		if (Edge0.LeftElement() EQUAL theElementsSequence_[Index]) theElementsSequence_[Index]->SetNeighbor0(Edge0.RightElement());

		Debug_Null_Pointer(theElementsSequence_[Index]->Edge1());
		Get_Const_Object(Edge1) = *theElementsSequence_[Index]->Edge1();

		theElementsSequence_[Index]->SetNeighbor1(Edge1.LeftElement());
		if (Edge1.LeftElement() EQUAL theElementsSequence_[Index]) theElementsSequence_[Index]->SetNeighbor1(Edge1.RightElement());

		Debug_Null_Pointer(theElementsSequence_[Index]->Edge2());
		Get_Const_Object(Edge2) = *theElementsSequence_[Index]->Edge2();

		theElementsSequence_[Index]->SetNeighbor2(Edge2.LeftElement());
		if (Edge2.LeftElement() EQUAL theElementsSequence_[Index]) theElementsSequence_[Index]->SetNeighbor2(Edge2.RightElement());
	}

	AllEdges.RetrieveTo(theEdgesSequence_);

	/*ADT_BasicQueue<Global_Handle(TColEntity_HAry1dOfEdge2d)> BoundaryLoops;

	while (NOT BoundaryEdges.IsEmpty())
	{
		BoundaryLoops.EnQueue(new TColEntity_HAry1dOfEdge2d(Marching(BoundaryEdges)));
	}
	BoundaryLoops.RetrieveTo(theBoundaries_);*/
}

void AutLib::GeoLib::GeoMesh_TriangleMesh2d::ReleaseMemory()
{
	FreeMemory(theNodesSequence_);
	FreeMemory(theEdgesSequence_);
	FreeMemory(theElementsSequence_);

	FreeMemory(theBoundaries_);
}

void AutLib::GeoLib::GeoMesh_TriangleMesh2d::ExportEdgesAround(const Standard_Integer Index, fstream& File) const
{
	Debug_Bad_Index_Array1(Index, theNodesSequence_);

	TColEntity_HAry1dOfEdge2d Edges = theNodesSequence_[Index]->Edges();

	M_IO IO_TecPlot::ExportMesh(Entity_Node2dTools::GetStaticOf(theNodesSequence_), Entity_Edge2dTools::GetStaticOf(Edges), File);
}

void AutLib::GeoLib::GeoMesh_TriangleMesh2d::ExportToPlt(fstream & File) const
{
	M_IO IO_TecPlot::ExportMesh(Entity_Node2dTools::GetStaticOf(theNodesSequence_), Entity_Element2dTools::GetStaticOf(theElementsSequence_), File);
}