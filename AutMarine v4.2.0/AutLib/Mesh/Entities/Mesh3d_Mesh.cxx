#include <Mesh3d_Mesh.hxx>

#include <Primitive_Field.hxx>
#include <Entity_StaticChain3d.hxx>
#include <Entity_Tetrahedralization.hxx>
#include <Mesh3d_Node.hxx>
#include <Mesh3d_Element.hxx>
#include <Mesh3d_NodeTools.hxx>
#include <Mesh3d_EdgeTools.hxx>
#include <Mesh3d_FacetTools.hxx>
#include <Mesh3d_ElementTools.hxx>
#include <QualityMap3d_MaxAngle.hxx>
#include <QualityMap3d_MeanSine.hxx>
#include <QualityMap3d_MinAngle.hxx>
#include <QualityMap3d_MinSine.hxx>
#include <QualityMap3d_RadiusRatio.hxx>
#include <QualityMap3d_Vlrms3Ratio.hxx>
#include <QualityMap3d_WarpedMinSine.hxx>
#include <IO_Tecplot.hxx>
#include <TColMesh3d_HBasicQueueOfNode.hxx>
#include <TColMesh3d_HBasicQueueOfEdge.hxx>
#include <TColMesh3d_HBasicQueueOfFacet.hxx>
#include <TColMesh3d_HBasicQueueOfElement.hxx>

using namespace AutLib;
using namespace MeshLib;
using namespace GeoLib;

AutLib::MeshLib::Mesh3d_Mesh::Mesh3d_Mesh()
	: theNbNodes_(0)
	, theNbEdges_(0)
	, theNbFacets_(0)
	, theNbElements_(0)
	, theName_("Unknown")
{
	Set_Numbering(theNodes_, Mesh3d_NodeTools::IsLess);

	Set_Numbering(theEdges_, Mesh3d_EdgeTools::IsLess);

	Set_Numbering(theFacets_, Mesh3d_FacetTools::IsLess);

	Set_Numbering(theElements_, Mesh3d_ElementTools::IsLess);

	Set_Numbering(theFrontFacets_, Mesh3d_FacetTools::IsLess);

	Set_Numbering(theFrontNodes_, Mesh3d_NodeTools::IsLess);

	theNodes_.SetName(" Mesh Nodes Tree");
	theEdges_.SetName(" Mesh Edges Tree");
	theFacets_.SetName(" Mesh Facets Tree");
	theElements_.SetName(" Mesh Elements Tree");
}

AutLib::MeshLib::Mesh3d_Mesh::~Mesh3d_Mesh()
{
}

Standard_Boolean AutLib::MeshLib::Mesh3d_Mesh::CheckFront1() const
{
	TColMesh3d_HAry1dOfFacet Facets;
	RetrieveFrontsTo(Facets);

	forThose
	(
		Index, 
		0, 
		MaxIndexOf(Facets)
	)
	{
		Debug_Null_Pointer(Facets[Index]);
		forThose(J, 0, 2)
		{
			Debug_Null_Pointer(Facets[Index]->Edge(J));
			if (NOT Facets[Index]->Edge(J)->IsContainAtFront(Facets[Index]))
			{
				return Standard_True;
			}
		}
	}
	return Standard_False;
}

Entity_Tetrahedralization AutLib::MeshLib::Mesh3d_Mesh::Static() const
{
	TColMesh3d_HAry1dOfNode Nodes = Mesh3d_Mesh::SortedNodes();

	TColMesh3d_HAry1dOfElement Elements = Mesh3d_Mesh::SortedElements();

	Entity_Tetrahedralization Tetrahedralization;
	Tetrahedralization.Points() = Mesh3d_NodeTools::GetCoordOf(Nodes);
	Tetrahedralization.Tetrahedrons() = Mesh3d_ElementTools::StaticOf(Elements);

	MOVE(Tetrahedralization);
}

TColMesh3d_HAry1dOfNode AutLib::MeshLib::Mesh3d_Mesh::SortedNodes() const
{
	NodesCompactNumbering();

	TColMesh3d_HAry1dOfNode Nodes;
	RetrieveTo(Nodes);

	TColMesh3d_HAry1dOfNode Sorted(Nodes.Size());

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

TColMesh3d_HAry1dOfEdge AutLib::MeshLib::Mesh3d_Mesh::SortedEdges() const
{
	EdgesCompactNumbering();

	TColMesh3d_HAry1dOfEdge Edges;

	RetrieveTo(Edges);

	TColMesh3d_HAry1dOfEdge Sorted(Edges.Size());

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

TColMesh3d_HAry1dOfFacet AutLib::MeshLib::Mesh3d_Mesh::SortedFacets() const
{
	FacetsCompactNumbering();

	TColMesh3d_HAry1dOfFacet Facets;

	RetrieveTo(Facets);

	TColMesh3d_HAry1dOfFacet Sorted(Facets.Size());

	forThose
	(
		Index,
		0,
		MaxIndexOf(Facets)
	)
	{
		Debug_Null_Pointer(Facets[Index]);

		Try_Exception_Handle_Exit(Sorted[Index_Of(Facets[Index]->Index())] = Facets[Index];);
	}

	MOVE(Sorted);
}

TColMesh3d_HAry1dOfElement AutLib::MeshLib::Mesh3d_Mesh::SortedElements() const
{
	ElementsCompactNumbering();

	TColMesh3d_HAry1dOfElement Elements;

	RetrieveTo(Elements);

	TColMesh3d_HAry1dOfElement Sorted(Elements.Size());

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

TColStd_Ary1dOfReal & AutLib::MeshLib::Mesh3d_Mesh::Quality()
{
	return theQuality_;
}

void AutLib::MeshLib::Mesh3d_Mesh::SetName(const Standard_String theName)
{
	theName_ = theName;
}

void AutLib::MeshLib::Mesh3d_Mesh::CalcQuality(const QualityMap3d_TypesInfo theQualityType) const
{
	Global_Handle(Mesh3d_QualityMap) QualityMap(0);
	switch (theQualityType)
	{
	case QualityMap3d_TypesInfo::QualityMap3d_MAXANGLE: {QualityMap = new QualityMap3d_MaxAngle; break; }
	case QualityMap3d_TypesInfo::QualityMap3d_MEANSINE: {QualityMap = new QualityMap3d_MeanSine; break; }
	case QualityMap3d_TypesInfo::QualityMap3d_MINANGLE: {QualityMap = new QualityMap3d_MinAngle; break; }
	case QualityMap3d_TypesInfo::QualityMap3d_MINSINE: {QualityMap = new QualityMap3d_MinSine; break; }
	//case QualityMap3d_TypesInfo::QualityMap3d_MINSINEANDEDGERATIO: {break; }
	case QualityMap3d_TypesInfo::QualityMap3d_RADIUSRATIO: {QualityMap = new QualityMap3d_RadiusRatio; break; }
	case QualityMap3d_TypesInfo::QualityMap3d_VLRMS3RATIO: {QualityMap = new QualityMap3d_Vlrms3Ratio; break; }
	case QualityMap3d_TypesInfo::QualityMap3d_WARPEDMINSINE: {QualityMap = new QualityMap3d_WarpedMinSine; break; }
	default: {THROW_STANDARD_EXCEPTION("Invalid Data: The Type of Quality Map not supported!"); break; }
	}

	Get_Const_Object(Quality) = *QualityMap;

	TColMesh3d_HAry1dOfElement Elements = SortedElements();
	theQuality_.Resize(Elements.Size());
	forThose
	(
		Index,
		0,
		MaxIndexOf(Elements)
	)
	{
		Debug_Null_Pointer(Elements[Index]);
		
		Debug_Null_Pointer(Elements[Index]->Node(0));
		Debug_Null_Pointer(Elements[Index]->Node(1));
		Debug_Null_Pointer(Elements[Index]->Node(2));
		Debug_Null_Pointer(Elements[Index]->Node(3));

		Get_Const_Object(P0) = Elements[Index]->Node(0)->Coord();
		Get_Const_Object(P1) = Elements[Index]->Node(1)->Coord();
		Get_Const_Object(P2) = Elements[Index]->Node(2)->Coord();
		Get_Const_Object(P3) = Elements[Index]->Node(3)->Coord();

		theQuality_.SetValue(Index, Quality.CalcQuality(P0, P1, P2, P3));
	}

	FreePointer(QualityMap);
}

void AutLib::MeshLib::Mesh3d_Mesh::RetrieveSortedTo(TColGeom_Ary1dOfPnt3d & Points) const
{
	Get_Const_Object(Nodes) = SortedNodes();

	Points = Mesh3d_NodeTools::GetCoordOf(Nodes);
}

void AutLib::MeshLib::Mesh3d_Mesh::RetrieveSortedTo(TColEntity_Ary1dOfEdgeIndex & Edges) const
{
	Get_Const_Object(Edges0) = SortedEdges();

	Edges = Mesh3d_EdgeTools::StaticOf(Edges0);
}

void AutLib::MeshLib::Mesh3d_Mesh::RetrieveSortedTo(TColEntity_Ary1dOfTriangleIndex & Facets) const
{
	Get_Const_Object(Elements0) = SortedFacets();

	Facets = Mesh3d_FacetTools::StaticOf(Elements0);
}

void AutLib::MeshLib::Mesh3d_Mesh::RetrieveSortedTo(TColEntity_Ary1dOfTetrahedronIndex & Elements) const
{
	Get_Const_Object(Elements0) = SortedElements();

	Elements = Mesh3d_ElementTools::StaticOf(Elements0);
}

void AutLib::MeshLib::Mesh3d_Mesh::NodesCompactNumbering() const
{
	TColMesh3d_HAry1dOfNode Nodes;
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

	TColMesh3d_HAry1dOfNode Sorted(MaxIndex);

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
	
	TColMesh3d_HBasicQueueOfNode QNodes;

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

void AutLib::MeshLib::Mesh3d_Mesh::EdgesCompactNumbering() const
{
	TColMesh3d_HAry1dOfEdge Edges;

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

	TColMesh3d_HAry1dOfEdge Sorted(MaxIndex);

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

	TColMesh3d_HBasicQueueOfEdge QEdges;

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

void AutLib::MeshLib::Mesh3d_Mesh::FacetsCompactNumbering() const
{
	TColMesh3d_HAry1dOfFacet Elements;

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

	TColMesh3d_HAry1dOfFacet Sorted(MaxIndex);

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

	TColMesh3d_HBasicQueueOfFacet QElements;

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

void AutLib::MeshLib::Mesh3d_Mesh::ElementsCompactNumbering() const
{
	TColMesh3d_HAry1dOfElement Elements;

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

	TColMesh3d_HAry1dOfElement Sorted(MaxIndex);

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

	TColMesh3d_HBasicQueueOfElement QElements;

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

void AutLib::MeshLib::Mesh3d_Mesh::CompactNumbering() const
{
	NodesCompactNumbering();

	EdgesCompactNumbering();

	FacetsCompactNumbering();

	ElementsCompactNumbering();
}

void AutLib::MeshLib::Mesh3d_Mesh::ExportElementsToPlt(fstream & File) const
{
	CompactNumbering();

	M_IO IO_TecPlot::ExportMesh
	(
		Mesh3d_NodeTools::GetCoordOf(Mesh3d_Mesh::SortedNodes()),
		Mesh3d_ElementTools::StaticOf(Mesh3d_Mesh::SortedElements()),
		File
	);
}

void AutLib::MeshLib::Mesh3d_Mesh::ExportQualityToPlt
(
	fstream & File,
	const QualityMap3d_TypesInfo theQualityType
) const
{
	CompactNumbering();

	CalcQuality(theQualityType);

	Primitive_Field Field(1, theQuality_.Size());
	forThose(Index, 0, MaxIndexOf(theQuality_))
	{
		Field.SetValue(Index, 0, theQuality_[Index]);
	}
	Field.SetVariablesName("Quality[0-1]");

	M_IO IO_TecPlot::ExportCellCenteredField(Static(), Field, File);
}

void AutLib::MeshLib::Mesh3d_Mesh::ExportEdgesToPlt
(
	const TColMesh3d_HAry1dOfEdge & theEdges,
	fstream & File
) const
{
	CompactNumbering();

	M_IO IO_TecPlot::ExportMesh
	(
		Mesh3d_NodeTools::GetCoordOf(Mesh3d_Mesh::SortedNodes()),
		Mesh3d_EdgeTools::StaticOf(theEdges),
		File
	);
}

void AutLib::MeshLib::Mesh3d_Mesh::ExportFacetsToPlt
(
	const TColMesh3d_HAry1dOfFacet & theFacets,
	fstream & File
) const
{
	CompactNumbering();

	M_IO IO_TecPlot::ExportMesh
	(
		Mesh3d_NodeTools::GetCoordOf(Mesh3d_Mesh::SortedNodes()),
		Mesh3d_FacetTools::StaticOf(theFacets),
		File
	);
}

void AutLib::MeshLib::Mesh3d_Mesh::ExportFacetsWithNormalsToPlt
(
	const TColMesh3d_HAry1dOfFacet & theFacets, 
	fstream & File
) const
{
	CompactNumbering();

	M_IO IO_TecPlot::ExportMesh
	(
		Mesh3d_NodeTools::GetCoordOf(Mesh3d_Mesh::SortedNodes()),
		Mesh3d_FacetTools::StaticOf(theFacets),
		File
	);

	Entity_StaticChain3d Chain;
	Mesh3d_FacetTools::RetrieveNormals(theFacets, Chain);

	Chain.ExportToPlt(File);
}

void AutLib::MeshLib::Mesh3d_Mesh::ExportElementsToPlt
(
	const TColMesh3d_HAry1dOfElement & theElements,
	fstream & File
) const
{
	CompactNumbering();

	M_IO IO_TecPlot::ExportMesh
	(
		Mesh3d_NodeTools::GetCoordOf(Mesh3d_Mesh::SortedNodes()),
		Mesh3d_ElementTools::StaticOf(theElements),
		File
	);
}

void AutLib::MeshLib::Mesh3d_Mesh::ReportQuality(Standard_OStream & Ostream, const QualityMap3d_TypesInfo theQualityType) const
{
	CompactNumbering();

	CalcQuality(theQualityType);

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

void AutLib::MeshLib::Mesh3d_Mesh::ReleaseMemory()
{
	TColMesh3d_HAry1dOfNode Nodes;
	TColMesh3d_HAry1dOfEdge Edges;
	TColMesh3d_HAry1dOfFacet Facets;
	TColMesh3d_HAry1dOfElement Elements;

	RetrieveTo(Nodes);
	RetrieveTo(Edges);
	RetrieveTo(Facets);
	RetrieveTo(Elements);

	FreeMemory(Nodes);
	FreeMemory(Edges);
	FreeMemory(Facets);
	FreeMemory(Elements);
}