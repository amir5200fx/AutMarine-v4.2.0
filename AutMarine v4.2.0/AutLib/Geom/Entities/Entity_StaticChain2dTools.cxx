#include <Entity_StaticChain2dTools.hxx>

#include <Entity_Node2d.hxx>
#include <Entity_Edge2d.hxx>
#include <Entity_StaticChain2d.hxx>
#include <Entity_Polygon2d.hxx>
#include <Geom_Pnt2d.hxx>
#include <ADT_BasicQueue.hxx>
#include <ADT_AvlTree.hxx>
#include <ADT_AdressAvlTree.hxx>
#include <TColGeom_BasicQueueOfPnt2d.hxx>
#include <TColEntity_HAry1dOfPolygon2d.hxx>
#include <TColEntity_HBasicQueueOfPolygon2d.hxx>

using namespace AutLib;
using namespace GeoLib;

namespace AutLib
{
	namespace GeoLib
	{

		class PairedPts
		{

		private:

			Geom_Pnt2d theP0_;
			Geom_Pnt2d theP1_;

		public:

			PairedPts(const Geom_Pnt2d& P0, const Geom_Pnt2d& P1)
				: theP0_(P0)
				, theP1_(P1)
			{}

			const Geom_Pnt2d& P0() const { return theP0_; }

			const Geom_Pnt2d& P1() const { return theP1_; }
		};

		enum NodeType
		{
			START = 0,
			REGULAR
		};

		class IntEdge;

		typedef ADT_BasicQueue<Global_Handle(IntEdge)> TColGeom_HBasicQueueOfIntEdge;
		typedef ADT_Ary1d<Global_Handle(IntEdge)> TColGeom_HAry1dOfIntEdge;
		typedef ADT_Ary1d<IntEdge> TColGeom_Ary1dOfIntEdge;

		class IntNode
		{

		private:

			Standard_Integer theIndex_;

			Geom_Pnt2d thePoint_;

			TColGeom_HBasicQueueOfIntEdge theEdges_;

			NodeType theNodeType_;

		public:

			IntNode(const Standard_Integer Index, const Geom_Pnt2d& Coord);

			const Geom_Pnt2d& Coord() const;

			Standard_Integer Index() const;

			Standard_Integer NbEdges() const;

			Standard_Boolean IsEdgesEmpty() const;

			NodeType Kind() const;

			void SetKind(NodeType Kind);

			void Insert(Global_Handle(IntEdge) Edge);

			void Remove(Global_Handle(IntEdge) Edge);

			void RetrieveTo(TColGeom_HAry1dOfIntEdge& Edges) const;

		};

		typedef ADT_Ary1d<Global_Handle(IntNode)> TColGeom_HAry1dOfIntNode;

		inline AutLib::GeoLib::IntNode::IntNode(const Standard_Integer Index, const Geom_Pnt2d & Coord)
			: theIndex_(Index)
			, thePoint_(Coord)
		{
		}

		inline const Geom_Pnt2d & AutLib::GeoLib::IntNode::Coord() const
		{
			return thePoint_;
		}

		inline Standard_Integer AutLib::GeoLib::IntNode::Index() const
		{
			return theIndex_;
		}

		inline Standard_Integer AutLib::GeoLib::IntNode::NbEdges() const
		{
			return theEdges_.Size();
		}

		inline Standard_Boolean AutLib::GeoLib::IntNode::IsEdgesEmpty() const
		{
			return theEdges_.IsEmpty();
		}

		inline NodeType AutLib::GeoLib::IntNode::Kind() const
		{
			return theNodeType_;
		}

		inline void AutLib::GeoLib::IntNode::SetKind(NodeType Kind)
		{
			theNodeType_ = Kind;
		}

		inline void AutLib::GeoLib::IntNode::Insert(Global_Handle(IntEdge) Edge)
		{
			theEdges_.EnQueue(Edge);
		}

		inline void AutLib::GeoLib::IntNode::Remove(Global_Handle(IntEdge) Edge)
		{
			theEdges_.Remove(Edge);
		}

		inline void AutLib::GeoLib::IntNode::RetrieveTo(TColGeom_HAry1dOfIntEdge & Edges) const
		{
			theEdges_.RetrieveTo(Edges);
		}

		class IntEdge
		{

		private:

			Standard_Integer theIndex_;

			Global_Handle(IntNode) theNodes_[2];

		public:

			IntEdge(const Standard_Integer Index, Global_Handle(IntNode) Node0, Global_Handle(IntNode) Node1);

			Standard_Integer Index() const;

			Global_Handle(IntNode) Node0() const;

			Global_Handle(IntNode) Node1() const;

			Global_Handle(IntNode) Node(const Standard_Integer Index) const;
		};

		inline AutLib::GeoLib::IntEdge::IntEdge
		(
			const Standard_Integer Index,
			Global_Handle(IntNode) Node0,
			Global_Handle(IntNode) Node1
		)
			: theIndex_(Index)
		{
			theNodes_[0] = Node0;
			theNodes_[1] = Node1;
		}

		inline Standard_Integer AutLib::GeoLib::IntEdge::Index() const
		{
			return theIndex_;
		}

		inline Global_Handle(IntNode) AutLib::GeoLib::IntEdge::Node0() const
		{
			return theNodes_[0];
		}

		inline Global_Handle(IntNode) AutLib::GeoLib::IntEdge::Node1() const
		{
			return theNodes_[1];
		}

		inline Global_Handle(IntNode) AutLib::GeoLib::IntEdge::Node(const Standard_Integer Index) const
		{
			Debug_Bad_Index(Index, 0, 1);
			return theNodes_[Index];
		}

		typedef ADT_AdressAvlTree<Global_Handle(IntNode)> TColGeom_HAvlTreeOfIntNode;
		typedef ADT_AdressAvlTree<Global_Handle(IntEdge)> TColGeom_HAvlTreeOfIntEdge;

		class DynChain
		{

		private:

			TColGeom_HAvlTreeOfIntNode theNodes_;

			TColGeom_HAvlTreeOfIntEdge theEdges_;

			TColEntity_HAry1dOfPolygon2d thePolygons_;

		public:

			DynChain() {}

			~DynChain() { ReleaseMemory(); }

			void Import(const Entity_StaticChain2d& Static);

			void Perform();

			const TColEntity_HAry1dOfPolygon2d& Polygons() const;

		private:

			Global_Handle(IntNode) NextNode(Global_Handle(IntNode) Start);

			Global_Handle(IntNode) FindStart(NodeType Kind) const;

			Global_Handle(Entity_Polygon2d) GetPolygon(Global_Handle(IntNode) Start);

			void SetKinds();

			void ReleaseMemory();
		};

		inline const TColEntity_HAry1dOfPolygon2d & AutLib::GeoLib::DynChain::Polygons() const
		{
			return thePolygons_;
		}
	}
}

void AutLib::GeoLib::DynChain::Import(const Entity_StaticChain2d & Static)
{
	//Get_Const_Object(UnMergedEdges) = Static.Edges();

	Entity_StaticChain2d Merged = Static.Merged();

	Get_Const_Object(Coords) = Merged.Coords();
	Get_Const_Object(Indices) = Merged.Edges();

	TColGeom_HAry1dOfIntNode Nodes(Coords.Size());
	forThose
	(
		Index,
		0,
		MaxIndexOf(Nodes)
	)
	{
		Nodes[Index] = new IntNode(Index + 1, Coords[Index]);

		Try_Exception_Handle_Exit(theNodes_.Insert(Nodes[Index]));
	}

	forThose
	(
		Index,
		0,
		MaxIndexOf(Indices)
	)
	{
		Standard_Integer V0 = Indices[Index].V0();
		Standard_Integer V1 = Indices[Index].V1();

		Global_Handle(IntEdge) Edge = new IntEdge(Index + 1, Nodes[Index_Of(V0)], Nodes[Index_Of(V1)]);

		Try_Exception_Handle_Exit(theEdges_.Insert(Edge));

		Nodes[Index_Of(V0)]->Insert(Edge);
		Nodes[Index_Of(V1)]->Insert(Edge);
	}

	SetKinds();
}

void AutLib::GeoLib::DynChain::Perform()
{
	TColGeom_HAry1dOfIntNode Nodes;
	theNodes_.RetrieveTo(Nodes);

	TColGeom_HAry1dOfIntEdge Edges;
	theEdges_.RetrieveTo(Edges);

	TColEntity_HBasicQueueOfPolygon2d QPolygons;
	Global_Handle(IntNode) Start(0);

	// Create regular chains
	Start = FindStart(START);

	while (Start)
	{
		QPolygons.EnQueue(GetPolygon(Start));

		Start = FindStart(START);
	}

	// Create cycle chain
	if (NOT theEdges_.IsEmpty())
	{
		Start = FindStart(REGULAR);

		while (Start)
		{
			QPolygons.EnQueue(GetPolygon(Start));

			Start = FindStart(REGULAR);
		}
	}

	if (NOT theNodes_.IsEmpty()) CloseProgram(" Fatal Error @ DynChain::Perform(): The Nodes tree is not empty");
	if (NOT theEdges_.IsEmpty()) CloseProgram(" Fatal Error @ DynChain::Perform(): The Edges tree is not empty");

	QPolygons.RetrieveTo(thePolygons_);

	FreeMemory(Nodes);
	FreeMemory(Edges);
}

Global_Handle(IntNode) AutLib::GeoLib::DynChain::NextNode(Global_Handle(IntNode) Start)
{
	if (Start->Kind() NOT_EQUAL REGULAR)
	{
		if (NOT Start->NbEdges()) theNodes_.Remove(Start);
		return NULL;  // End point
	}
	
	TColGeom_HAry1dOfIntEdge Edges;
	Start->RetrieveTo(Edges);

	Global_Handle(IntEdge) Edge = Edges[0];

	Start->Remove(Edge);
	theEdges_.Remove(Edge);

	Global_Handle(IntNode) Left = Edge->Node0();
	Global_Handle(IntNode) Right = Edge->Node1();

	Global_Handle(IntNode) Next(0);

	if (Left EQUAL Start) Next = Right;
	else if (Right EQUAL Start) Next = Left;
	else
	{
		CloseProgram(" Fatal Error @ DynChain::NextNode()");
	}

	if (Edges.Size() EQUAL 1) theNodes_.Remove(Start);
	else
		Start->SetKind(START);

	Next->Remove(Edge);

	return Next;
}

Global_Handle(IntNode) AutLib::GeoLib::DynChain::FindStart(NodeType Kind) const
{
	TColGeom_HAry1dOfIntNode Nodes;
	theNodes_.RetrieveTo(Nodes);

	forThose
	(
		Index,
		0, 
		MaxIndexOf(Nodes)
	)
	{
		if (Nodes[Index]->Kind() EQUAL Kind)
		{
			Nodes[Index]->SetKind(START);
			return Nodes[Index];
		}
	}

	return NULL;
}

Global_Handle(Entity_Polygon2d) AutLib::GeoLib::DynChain::GetPolygon(Global_Handle(IntNode) Start)
{
	Start->SetKind(REGULAR);
	
	Global_Handle(IntNode) Next = NextNode(Start);

	TColGeom_BasicQueueOfPnt2d QPts;
	QPts.EnQueue(Start->Coord());
	
	while (Next)
	{
		QPts.EnQueue(Next->Coord());

		Next = NextNode(Next);
	}

	return new Entity_Polygon2d(QPts.Retrive());
}

void AutLib::GeoLib::DynChain::SetKinds()
{
	TColGeom_HAry1dOfIntNode Nodes;
	theNodes_.RetrieveTo(Nodes);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Nodes)
	)
	{
		if (Nodes[Index]->NbEdges() EQUAL 1)
		{
			// start node
			Nodes[Index]->SetKind(START);
		}
		else
		{
			// regular node
			Nodes[Index]->SetKind(REGULAR);
		}
	}
}

void AutLib::GeoLib::DynChain::ReleaseMemory()
{
	//FreeMemory(thePolygons_);
}

TColEntity_HAry1dOfPolygon2d AutLib::GeoLib::Entity_StaticChain2dTools::GetPolygons(const Entity_StaticChain2d & Chain)
{
	DynChain dynChain;
	dynChain.Import(Chain);

	dynChain.Perform();

	return dynChain.Polygons();
}

void AutLib::GeoLib::Entity_StaticChain2dTools::CreateDynamics
(
	const Entity_StaticChain2d & Chain,
	TColEntity_HAry1dOfNode2d & Nodes,
	TColEntity_HAry1dOfEdge2d & Edges
)
{
	Get_Const_Object(Coords) = Chain.Coords();
	Get_Const_Object(Indices) = Chain.Edges();

	Nodes.Resize(Coords.Size());
	forThose(Index, 0, MaxIndexOf(Nodes))
		Nodes[Index] = new Entity_Node2d(Index + 1, Coords[Index]);

	Edges.Resize(Indices.Size());
	forThose
	(
		Index, 
		0,
		MaxIndexOf(Edges)
	)
	{
		Standard_Integer V0 = Indices[Index].V0();
		Standard_Integer V1 = Indices[Index].V1();

		Global_Handle(Entity_Node2d) Node0 = Nodes[Index_Of(V0)];
		Global_Handle(Entity_Node2d) Node1 = Nodes[Index_Of(V1)];

		Edges[Index] = new Entity_Edge2d(Index + 1, Node0, Node1);

		Node0->InsertToEdges(Edges[Index]);
		Node1->InsertToEdges(Edges[Index]);
	}
}