#include <Mesh2d_Mesh.hxx>

#include <Primitive_Field.hxx>
#include <IO_TecPlot.hxx>
#include <Entity_Triangulation2d.hxx>
#include <Entity_TriangleIndex.hxx>
#include <Entity_EdgeIndex.hxx>
#include <Mesh2d_Node.hxx>
#include <Mesh2d_Edge.hxx>
#include <Mesh2d_Element.hxx>
#include <Mesh2d_BoundaryNode.hxx>
#include <Mesh2d_NodeTools.hxx>
#include <Mesh2d_EdgeTools.hxx>
#include <Mesh2d_ElementTools.hxx>
#include <Mesh2d_SizeMap.hxx>
#include <QualityMap2d_Vlrms2Ratio.hxx>
#include <TColMesh2d_HBasicQueueOfNode.hxx>
#include <TColMesh2d_HBasicQueueOfEdge.hxx>
#include <TColMesh2d_HBasicQueueOfElement.hxx>

using namespace AutLib;
using namespace GeoLib;

AutLib::MeshLib::Mesh2d_Mesh::Mesh2d_Mesh()
	: theNbNodes_(0)
	, theNbEdges_(0)
	, thenbElements_(0)
{
	Set_Numbering(theNodes_, Mesh2d_NodeTools::IsLess);

	Set_Numbering(theEdges_, Mesh2d_EdgeTools::IsLess);

	Set_Numbering(theElements_, Mesh2d_ElementTools::IsLess);

	Set_Numbering(theFrontNodes_, Mesh2d_NodeTools::IsLess);

	Set_Numbering(theFrontEdges_, Mesh2d_EdgeTools::IsLess);

	theNodes_.SetName(" Mesh Nodes Tree");
	theEdges_.SetName(" Mesh Edges Tree");
	theElements_.SetName(" Mesh Elements Tree");

	theFrontNodes_.SetName(" Mesh Front Nodes Tree");
	theFrontEdges_.SetName(" Mesh Front Edges Tree");
}

AutLib::MeshLib::Mesh2d_Mesh::~Mesh2d_Mesh()
{
	//ReleaseMemory();
}

Standard_Real AutLib::MeshLib::Mesh2d_Mesh::WorstQuality
(
	const Mesh2d_Node & theNode, 
	const Mesh2d_SizeMap& theSizeMap,
	const Mesh2d_QualityMap& theQualityMap
) const
{
	TColMesh2d_HAry1dOfElement Elements;
	theNode.RetrieveElementsTo(Elements);

	Standard_Real Worst = RealLast();
	forThose
	(
		Index,
		0,
		MaxIndexOf(Elements)
	)
	{
		Debug_Null_Pointer(Elements[Index]);

		Get_Const_Object(P0) = Elements[Index]->Node0()->Coord();
		Get_Const_Object(P1) = Elements[Index]->Node1()->Coord();
		Get_Const_Object(P2) = Elements[Index]->Node2()->Coord();

		Standard_Real Quality = theSizeMap.ElementQuality(P0, P1, P2, theQualityMap);

		if (Quality < Worst) Worst = Quality;
	}
	return Worst;
}

M_AUT TColMesh2d_HAry1dOfNode AutLib::MeshLib::Mesh2d_Mesh::SortedNodes() const
{
	NodesCompactNumbering();

	TColMesh2d_HAry1dOfNode Nodes;

	RetrieveTo(Nodes);

	TColMesh2d_HAry1dOfNode Sorted(Nodes.Size());

	forThose
	(
		Index,
		0,
		MaxIndexOf(Nodes)
	)
	{
		Debug_Null_Pointer(Nodes[Index]);

		Try_Exception_Handle_Exit(Sorted[Index_Of(Nodes[Index]->Index())] = Nodes[Index]);
	}

	MOVE(Sorted);
}

M_AUT TColMesh2d_HAry1dOfEdge AutLib::MeshLib::Mesh2d_Mesh::SortedEdges() const
{
	EdgesCompactNumbering();

	TColMesh2d_HAry1dOfEdge Edges;

	RetrieveTo(Edges);

	TColMesh2d_HAry1dOfEdge Sorted(Edges.Size());

	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		Try_Exception_Handle_Exit(Sorted[Index_Of(Edges[Index]->Index())] = Edges[Index];);
	}

	MOVE(Sorted);
}

M_AUT TColMesh2d_HAry1dOfElement AutLib::MeshLib::Mesh2d_Mesh::SortedElements() const
{
	ElementsCompactNumbering();

	TColMesh2d_HAry1dOfElement Elements;

	RetrieveTo(Elements);

	TColMesh2d_HAry1dOfElement Sorted(Elements.Size());

	forThose
	(
		Index,
		0,
		MaxIndexOf(Elements)
	)
	{
		Debug_Null_Pointer(Elements[Index]);

		Try_Exception_Handle_Exit(Sorted[Index_Of(Elements[Index]->Index())] = Elements[Index];);
	}

	MOVE(Sorted);
}

Standard_String AutLib::MeshLib::Mesh2d_Mesh::Name() const
{
	return theName_;
}

Entity_Triangulation2d AutLib::MeshLib::Mesh2d_Mesh::Static() const
{
	TColMesh2d_HAry1dOfNode Nodes = Mesh2d_Mesh::SortedNodes();

	TColMesh2d_HAry1dOfElement Elements = Mesh2d_Mesh::SortedElements();

	Entity_Triangulation2d Triangulation;
	Triangulation.Points() = Mesh2d_NodeTools::GetCoordOf(Nodes);
	Triangulation.Triangles() = Mesh2d_ElementTools::StaticOf(Elements);

	MOVE(Triangulation);
}

void AutLib::MeshLib::Mesh2d_Mesh::SetName(const Standard_String theName)
{
	theName_ = theName;
}

void AutLib::MeshLib::Mesh2d_Mesh::RetrieveSortedTo(TColGeom_Ary1dOfPnt2d & Points) const
{
	Get_Const_Object(Nodes) = SortedNodes();

	Points = Mesh2d_NodeTools::GetCoordOf(Nodes);
}

void AutLib::MeshLib::Mesh2d_Mesh::RetrieveSortedTo(TColEntity_Ary1dOfEdgeIndex & Edges) const
{
	Get_Const_Object(Edges0) = SortedEdges();

	Edges = Mesh2d_EdgeTools::StaticOf(Edges0);
}

void AutLib::MeshLib::Mesh2d_Mesh::RetrieveSortedTo(TColEntity_Ary1dOfTriangleIndex & Elements) const
{
	Get_Const_Object(Elements0) = SortedElements();

	Elements = Mesh2d_ElementTools::StaticOf(Elements0);
}

void AutLib::MeshLib::Mesh2d_Mesh::NodesCompactNumbering() const
{
	TColMesh2d_HAry1dOfNode Nodes;

	RetrieveTo(Nodes);

	Standard_Integer MaxIndex = 0;

	forThose
	(
		Index,
		0,
		MaxIndexOf(Nodes)
	)
	{
		Debug_Null_Pointer(Nodes[Index]);

		Get_Object(Node) = *Nodes[Index];

		if (Node.Index() > MaxIndex) MaxIndex = Node.Index();
	}

	TColMesh2d_HAry1dOfNode Sorted(MaxIndex);

	Sorted.Init(NULL);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Nodes)
	)
	{
		Debug_Null_Pointer(Nodes[Index]);

		Try_Exception_Handle_Exit(Sorted[Index_Of(Nodes[Index]->Index())] = Nodes[Index];);
	}

	TColMesh2d_HBasicQueueOfNode QNodes;

	forThose
	(
		Index,
		0,
		MaxIndexOf(Sorted)
	)
	{
		if (Sorted[Index]) QNodes.EnQueue(Sorted[Index]);
	}

	QNodes.RetrieveTo(Nodes);

	Standard_Integer K = 0;

	forThose
	(
		Index,
		0,
		MaxIndexOf(Nodes)
	)
	{
		Nodes[Index]->SetIndex(++K);
	}
}

void AutLib::MeshLib::Mesh2d_Mesh::EdgesCompactNumbering() const
{
	TColMesh2d_HAry1dOfEdge Edges;

	RetrieveTo(Edges);

	Standard_Integer MaxIndex = 0;

	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		Get_Object(Edge) = *Edges[Index];

		if (Edge.Index() > MaxIndex) MaxIndex = Edge.Index();
	}

	TColMesh2d_HAry1dOfEdge Sorted(MaxIndex);

	Sorted.Init(NULL);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		Try_Exception_Handle_Exit(Sorted[Index_Of(Edges[Index]->Index())] = Edges[Index];);
	}

	TColMesh2d_HBasicQueueOfEdge QEdges;

	forThose
	(
		Index,
		0,
		MaxIndexOf(Sorted)
	)
	{
		if (Sorted[Index]) QEdges.EnQueue(Sorted[Index]);
	}

	QEdges.RetrieveTo(Edges);

	Standard_Integer K = 0;

	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Edges[Index]->SetIndex(++K);
	}
}

void AutLib::MeshLib::Mesh2d_Mesh::ElementsCompactNumbering() const
{
	TColMesh2d_HAry1dOfElement Elements;

	RetrieveTo(Elements);

	Standard_Integer MaxIndex = 0;

	forThose
	(
		Index,
		0,
		MaxIndexOf(Elements)
	)
	{
		Debug_Null_Pointer(Elements[Index]);

		Get_Object(Element) = *Elements[Index];

		if (Element.Index() > MaxIndex) MaxIndex = Element.Index();
	}

	TColMesh2d_HAry1dOfElement Sorted(MaxIndex);

	Sorted.Init(NULL);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Elements)
	)
	{
		Debug_Null_Pointer(Elements[Index]);

		Try_Exception_Handle_Exit(Sorted[Index_Of(Elements[Index]->Index())] = Elements[Index];);
	}

	TColMesh2d_HBasicQueueOfElement QElements;

	forThose
	(
		Index,
		0,
		MaxIndexOf(Sorted)
	)
	{
		if (Sorted[Index]) QElements.EnQueue(Sorted[Index]);
	}

	QElements.RetrieveTo(Elements);

	Standard_Integer K = 0;

	forThose
	(
		Index,
		0,
		MaxIndexOf(Elements)
	)
	{
		Elements[Index]->SetIndex(++K);
	}
}

void AutLib::MeshLib::Mesh2d_Mesh::CompactNumbering() const
{
	NodesCompactNumbering();

	EdgesCompactNumbering();

	ElementsCompactNumbering();
}

void AutLib::MeshLib::Mesh2d_Mesh::CalcQuality(const Mesh2d_SizeMap& theSizeMap) const
{
	QualityMap2d_Vlrms2Ratio QualityMap;

	CompactNumbering();

	TColMesh2d_HAry1dOfElement Elements = SortedElements();
	theQuality_.Resize(Elements.Size());

	forThose
	(
		Index,
		0,
		MaxIndexOf(Elements)
	)
	{
		Debug_Null_Pointer(Elements[Index]);

		Debug_Null_Pointer(Elements[Index]->Node0());
		Debug_Null_Pointer(Elements[Index]->Node1());
		Debug_Null_Pointer(Elements[Index]->Node2());

		Get_Const_Object(P0) = Elements[Index]->Node0()->Coord();
		Get_Const_Object(P1) = Elements[Index]->Node1()->Coord();
		Get_Const_Object(P2) = Elements[Index]->Node2()->Coord();

		theQuality_.SetValue(Index, theSizeMap.ElementQuality(P0, P1, P2, QualityMap));
	}
}

void AutLib::MeshLib::Mesh2d_Mesh::ExportElementsToPlt(fstream & File) const
{
	CompactNumbering();

	TColEntity_Ary1dOfTriangleIndex Triangles;
	TColGeom_Ary1dOfPnt2d Points;

	RetrieveSortedTo(Points);
	RetrieveSortedTo(Triangles);

	M_IO IO_TecPlot::ExportMesh
	(
		Points,
		Triangles,
		File
	);
}

void AutLib::MeshLib::Mesh2d_Mesh::ExportQualityToPlt
(
	fstream & File, 
	const Mesh2d_SizeMap& theSizeMap
) const
{
	CompactNumbering();

	CalcQuality(theSizeMap);

	Primitive_Field Field(1, theQuality_.Size());
	forThose(Index, 0, MaxIndexOf(theQuality_))
	{
		Field.SetValue(Index, 0, theQuality_[Index]);
	}
	Field.SetVariablesName("Quality[0-1]");

	M_IO IO_TecPlot::ExportCellCenteredField(Static(), Field, File);
}

void AutLib::MeshLib::Mesh2d_Mesh::ReportQualityTo
(
	Standard_OStream& Ostream,
	const Mesh2d_SizeMap & theSizeMap
) const
{
	CompactNumbering();

	CalcQuality(theSizeMap);

	Standard_Integer K02 = 0;
	Standard_Integer K24 = 0;
	Standard_Integer K46 = 0;
	Standard_Integer K68 = 0;
	Standard_Integer K80 = 0;

	forThose
	(
		Index,
		0,
		MaxIndexOf(theQuality_)
	)
	{
		if (INSIDE(theQuality_[Index], 0.0, 0.2)) { K02++; continue; }
		if (INSIDE(theQuality_[Index], 0.2, 0.4)) { K24++; continue; }
		if (INSIDE(theQuality_[Index], 0.4, 0.6)) { K46++; continue; }
		if (INSIDE(theQuality_[Index], 0.6, 0.8)) { K68++; continue; }
		if (INSIDE(theQuality_[Index], 0.8, 1.0)) { K80++; continue; }
	}

	Ostream << "   The Quality of Mesh: \n";
	Ostream << "    [0.0-0.2]: " << K02 << endl;
	Ostream << "    [0.2-0.4]: " << K24 << endl;
	Ostream << "    [0.4-0.6]: " << K46 << endl;
	Ostream << "    [0.6-0.8]: " << K68 << endl;
	Ostream << "    [0.8-1.0]: " << K80 << endl;
}

void AutLib::MeshLib::Mesh2d_Mesh::LaplacianSmoothing
(
	const Standard_Integer NbLevels,
	const Standard_Real UnderRelaxation,
	Standard_Real(*Distance)(const Geom_Pnt2d&, const Geom_Pnt2d&, const Mesh2d_SizeMap&),
	const Mesh2d_SizeMap& Map,
	const Standard_Boolean Verbose
)
{
	if (Verbose) cout << " Laplacian Smoothing has been started: " << endl;
	if (Verbose) cout << "   Nb. of Levels= " << NbLevels << ",  Relaxation= " << UnderRelaxation << endl;
	if (Verbose) cout << endl;

	QualityMap2d_Vlrms2Ratio Quality;

	TColMesh2d_HAry1dOfNode Nodes;
	RetrieveTo(Nodes);

	forThose
	(
		Level,
		1,
		NbLevels
	)
	{
		if (Verbose) cout << "   Level no. " << Level << endl;

		forThose
		(
			iNode,
			0,
			MaxIndexOf(Nodes)
		)
		{
			Debug_Null_Pointer(Nodes[iNode]);

			if (dynamic_cast<Global_Handle(Mesh2d_BoundaryNode)>(Nodes[iNode])) continue;

			Get_Object(Node) = *Nodes[iNode];

			Geom_Pnt2d Saved = Node.Coord();
			Standard_Real Worst0 = WorstQuality(Node, Map, Quality);

			TColMesh2d_HAry1dOfEdge EdgesAroundNodes;
			Node.RetrieveEdgesTo(EdgesAroundNodes);

			Geom_Pnt2d AvgPt(0, 0);
			forThose
			(
				Index,
				0,
				MaxIndexOf(EdgesAroundNodes)
			)
			{
				Get_Const_Object(n1) = *EdgesAroundNodes[Index]->Node(0);
				Get_Const_Object(n2) = *EdgesAroundNodes[Index]->Node(1);

				if (n1.Index() NOT_EQUAL Node.Index()) { AvgPt += n1.Coord(); }
				else { AvgPt += n2.Coord(); }

				/*if (n1.Index() NOT_EQUAL Node.Index()) { AvgPt += n1.Coord() + UnderRelaxation * (1.0 / Distance(n1.Coord(), Node.Coord(), Map))*(Node.Coord() - n1.Coord()); }
				else { AvgPt += n2.Coord() + UnderRelaxation * (1.0 / Distance(n2.Coord(), Node.Coord(), Map))*(Node.Coord() - n2.Coord()); }*/
			}

			auto P = AvgPt / (Standard_Real)EdgesAroundNodes.Size();
			P = Node.Coord() + (P - Node.Coord())*UnderRelaxation;
			Node.SetCoord(P);

			if (WorstQuality(Node, Map, Quality) < Worst0) Node.SetCoord(Saved);
		}
	}
}

void AutLib::MeshLib::Mesh2d_Mesh::ReleaseMemory()
{
	TColMesh2d_HAry1dOfNode Nodes;
	TColMesh2d_HAry1dOfEdge Edges;
	TColMesh2d_HAry1dOfElement Elements;

	RetrieveTo(Nodes);
	RetrieveTo(Edges);
	RetrieveTo(Elements);

	FreeMemory(Nodes);
	FreeMemory(Edges);
	FreeMemory(Elements);
}