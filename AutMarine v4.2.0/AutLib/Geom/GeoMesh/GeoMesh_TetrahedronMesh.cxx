#include <GeoMesh_TetrahedronMesh.hxx>

#include <Entity_Node3dTools.hxx>
#include <Entity_Edge3dTools.hxx>
#include <Entity_FacetTools.hxx>
#include <Entity_Element3dTools.hxx>
#include <Entity_Tetrahedralization.hxx>
#include <Geometry_Tools.hxx>
#include <IO_Tecplot.hxx>

using namespace AutLib;
using namespace GeoLib;

AutLib::GeoLib::GeoMesh_TetrahedronMesh::GeoMesh_TetrahedronMesh()
	: theNbNodes_(0)
	, theNbEdges_(0)
	, theNbFacets_(0)
	, thenbElements_(0)
	, IsDone_(Standard_False)
{
	Set_Numbering(theNodes_, Entity_Node3dTools::IsLess);
	Set_Numbering(theEdges_, Entity_Edge3dTools::IsLess);
	Set_Numbering(theFacets_, Entity_FacetTools::IsLess);
	Set_Numbering(theElements_, Entity_Element3dTools::IsLess);

	theNodes_.SetName(" Mesh Nodes Tree");
	theEdges_.SetName(" Mesh Edges Tree");
	theFacets_.SetName(" Mesh Facets Tree");
	theElements_.SetName(" Mesh Elements Tree");
}

Entity_Tetrahedralization AutLib::GeoLib::GeoMesh_TetrahedronMesh::Static() const
{
	Debug_If_Condition(NOT IsDone_);
	return Entity_Tetrahedralization(Entity_Node3dTools::GetStaticOf(theNodesSequence_), Entity_Element3dTools::GetStaticOf(theElementsSequence_));
}

void AutLib::GeoLib::GeoMesh_TetrahedronMesh::Construct(const Entity_Tetrahedralization & Tetrahedralization)
{
	IsDone_ = Standard_True;

	Get_Const_Object(Points) = Tetrahedralization.Points();
	Get_Const_Object(Tetrahedrons) = Tetrahedralization.Tetrahedrons();

	theNodesSequence_.Resize(Points.Size());
	theElementsSequence_.Resize(Tetrahedrons.Size());

	// Create Nodes
	forThose(Index, 0, MaxIndexOf(Points))
		theNodesSequence_[Index] = new Entity_Node3d(Index + 1, Points[Index]);

	Standard_Integer MaxIndex = 0;
	TColEntity_HBasicQueueOfEdge3d AllEdges;

	// Create Elements
	forThose
	(
		Index,
		0,
		MaxIndexOf(Tetrahedrons)
	)
	{
		theElementsSequence_[Index] = new Entity_Element3d(Index + 1);

		Standard_Integer V0 = Index_Of(Tetrahedrons[Index].V0());
		Standard_Integer V1 = Index_Of(Tetrahedrons[Index].V1());
		Standard_Integer V2 = Index_Of(Tetrahedrons[Index].V2());
		Standard_Integer V3 = Index_Of(Tetrahedrons[Index].V3());

		theElementsSequence_[Index]->SetNode0(theNodesSequence_[V0]);
		theElementsSequence_[Index]->SetNode1(theNodesSequence_[V1]);
		theElementsSequence_[Index]->SetNode2(theNodesSequence_[V2]);
		theElementsSequence_[Index]->SetNode3(theNodesSequence_[V3]);

		theElementsSequence_[Index]->CalcVolume();
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
		Element.Node3()->InsertToElements(&Element);
	}

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
			5
		)
		{
			Standard_Integer Id1, Id2;
			Entity_Element3dTools::EdgeIndices(I, Id1, Id2);

			Global_Handle(Entity_Node3d) Node1 = Element->Node(Index_Of(Id1));
			Global_Handle(Entity_Node3d) Node2 = Element->Node(Index_Of(Id2));

			Global_Handle(Entity_Edge3d) Edge = NULL;

			Standard_Integer V1 = Node1->Index();
			Standard_Integer V2 = Node2->Index();

			Standard_Boolean Create = Standard_False;

			if ((NOT Node1->NbEdges()) OR(NOT Node2->NbEdges()))
			{
				Create = Standard_True;
			}
			else
			{
				Standard_Integer Size1 = Node1->NbEdges();
				Standard_Integer Size2 = Node2->NbEdges();

				TColEntity_HAry1dOfEdge3d TempEdges;

				Global_Handle(Entity_Node3d) Compare;

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
					if ((TempEdges[J]->Node(0) EQUAL Compare) OR(TempEdges[J]->Node(1) EQUAL Compare))
					{
						Exist = Standard_True;
						Edge = TempEdges[J];

						Edge->SetAsNonBoundary();

						break;
					}
				}

				if (NOT Exist)
					Create = Standard_True;
			}

			if (Create)
			{
				Debug_If_Condition(Edge);

				Edge = new Entity_Edge3d(++MaxIndex, Node1, Node2);
				theEdges_.Insert(Edge);
				AllEdges.EnQueue(Edge);

				Edge->SetAsBoundary();

				Node1->InsertToEdges(Edge);
				Node2->InsertToEdges(Edge);
			}
		}
	}

	MaxIndex = 0;
	TColEntity_HBasicQueueOfFacet AllFacets;

	// Create Facets
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
			3
		)
		{
			Standard_Integer Id1, Id2, Id3;
			Entity_Element3dTools::FacetIndices(I, Id1, Id2, Id3);

			Global_Handle(Entity_Node3d) Node1 = Element->Node(Index_Of(Id1));
			Global_Handle(Entity_Node3d) Node2 = Element->Node(Index_Of(Id2));
			Global_Handle(Entity_Node3d) Node3 = Element->Node(Index_Of(Id3));

			Global_Handle(Entity_Facet) Facet = NULL;

			Standard_Integer V1 = Node1->Index();
			Standard_Integer V2 = Node2->Index();
			Standard_Integer V3 = Node3->Index();

			Standard_Boolean Create = Standard_False;

			if ((NOT Node1->NbFacets()) OR (NOT Node2->NbFacets()) OR(NOT Node3->NbFacets()))
			{
				Create = Standard_True;
			}
			else
			{
				Standard_Integer Size1 = Node1->NbFacets();
				Standard_Integer Size2 = Node2->NbFacets();
				Standard_Integer Size3 = Node3->NbFacets();

				TColEntity_HAry1dOfFacet TempFacets;

				if (Size1 <= Size2 AND Size1 <= Size3)
				{
					Node1->Facets(TempFacets);
				}
				else if (Size2 <= Size1 AND Size2 <= Size3)
				{
					Node2->Facets(TempFacets);
				}
				else
				{
					Node3->Facets(TempFacets);
				}

				Standard_Boolean Exist = Standard_False;

				forThose
				(
					J,
					0,
					MaxIndexOf(TempFacets)
				)
				{
					Get_Const_Object(Current) = *TempFacets[J];

					Debug_Null_Pointer(Current.Node0());
					Debug_Null_Pointer(Current.Node1());
					Debug_Null_Pointer(Current.Node2());

					if (Geometry_Tools::IsThreeCommonTwoTriangle(Node1->Index(), Node2->Index(), Node3->Index(), Current.Node0()->Index(), Current.Node1()->Index(), Current.Node2()->Index()))
					{
						Exist = Standard_True;
						Facet = TempFacets[J];

						Facet->SetRightNeighbor(theElementsSequence_[Index]);
						Facet->SetAsNonBoundary();

						break;
					}
				}

				if (NOT Exist)
					Create = Standard_True;
			}

			if (Create)
			{
				Debug_If_Condition(Facet);

				Facet = new Entity_Facet(++MaxIndex, Node1, Node2, Node3);
				theFacets_.Insert(Facet);
				AllFacets.EnQueue(Facet);

				Facet->SetLeftNeighbor(theElementsSequence_[Index]);
				Facet->SetAsBoundary();

				Node1->InsertToFacets(Facet);
				Node2->InsertToFacets(Facet);
				Node3->InsertToFacets(Facet);

				Facet->CalcNormal();
			}

			Element->SetFacet(I, Facet);
		}
	}

	AllEdges.RetrieveTo(theEdgesSequence_);
	AllFacets.RetrieveTo(theFacetsSequence_);

	// Identify Neighbors
	forThose
	(
		Index,
		0,
		MaxIndexOf(theElementsSequence_)
	)
	{
		Debug_Null_Pointer(theElementsSequence_[Index]->Facet0());
		Get_Const_Object(Facet0) = *theElementsSequence_[Index]->Facet0();

		theElementsSequence_[Index]->SetNeighbor0(Facet0.LeftElement());
		if (Facet0.LeftElement() EQUAL theElementsSequence_[Index]) theElementsSequence_[Index]->SetNeighbor0(Facet0.RightElement());

		Debug_Null_Pointer(theElementsSequence_[Index]->Facet1());
		Get_Const_Object(Facet1) = *theElementsSequence_[Index]->Facet1();

		theElementsSequence_[Index]->SetNeighbor1(Facet1.LeftElement());
		if (Facet1.LeftElement() EQUAL theElementsSequence_[Index]) theElementsSequence_[Index]->SetNeighbor1(Facet1.RightElement());

		Debug_Null_Pointer(theElementsSequence_[Index]->Facet2());
		Get_Const_Object(Facet2) = *theElementsSequence_[Index]->Facet2();

		theElementsSequence_[Index]->SetNeighbor2(Facet2.LeftElement());
		if (Facet2.LeftElement() EQUAL theElementsSequence_[Index]) theElementsSequence_[Index]->SetNeighbor2(Facet2.RightElement());

		Debug_Null_Pointer(theElementsSequence_[Index]->Facet3());
		Get_Const_Object(Facet3) = *theElementsSequence_[Index]->Facet3();

		theElementsSequence_[Index]->SetNeighbor3(Facet3.LeftElement());
		if (Facet3.LeftElement() EQUAL theElementsSequence_[Index]) theElementsSequence_[Index]->SetNeighbor3(Facet3.RightElement());
	}
}

void AutLib::GeoLib::GeoMesh_TetrahedronMesh::ReleaseMemory()
{
	FreeMemory(theNodesSequence_);
	FreeMemory(theEdgesSequence_);
	FreeMemory(theFacetsSequence_);
	FreeMemory(theElementsSequence_);
}

void AutLib::GeoLib::GeoMesh_TetrahedronMesh::ExportToPlt(fstream & File) const
{
	M_IO IO_TecPlot::ExportMesh
	(
		Entity_Node3dTools::GetStaticOf(theNodesSequence_),
		Entity_Element3dTools::GetStaticOf(theElementsSequence_),
		File
	);
}

void AutLib::GeoLib::GeoMesh_TetrahedronMesh::ExportBoundaryFacetsToPlt(fstream & File) const
{
	TColEntity_HBasicQueueOfFacet QBndFacets;
	forThose(Index, 0, MaxIndexOf(theFacetsSequence_))
		if (theFacetsSequence_[Index]->IsOnBoundary()) QBndFacets.EnQueue(theFacetsSequence_[Index]);

	M_IO IO_TecPlot::ExportMesh(Entity_Node3dTools::GetStaticOf(theNodesSequence_), Entity_FacetTools::StaticOf(QBndFacets.Retrive()), File);
}