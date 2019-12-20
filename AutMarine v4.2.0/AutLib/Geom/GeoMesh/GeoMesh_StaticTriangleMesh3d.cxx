#include <GeoMesh_StaticTriangleMesh3d.hxx>

#include <Global_Memory.hxx>
#include <ADT_AdressAvlTree.hxx>
#include <TColEntity_BasicQueueOfEdgeIndex.hxx>
#include <TColStd_Ary1dOfInteger.hxx>

AutLib::GeoLib::GeoMesh_StaticTriangleMesh3d::GeoMesh_StaticTriangleMesh3d()
{
}

AutLib::GeoLib::GeoMesh_StaticTriangleMesh3d::GeoMesh_StaticTriangleMesh3d(const Entity_Triangulation3d & theTriangulation)
	: Entity_Triangulation3d(theTriangulation)
{
	CreateEdges();
}

AutLib::GeoLib::GeoMesh_StaticTriangleMesh3d::GeoMesh_StaticTriangleMesh3d
(
	const TColGeom_Ary1dOfPnt3d & theCoord,
	const TColEntity_Ary1dOfTriangleIndex & theElements
)
	: Entity_Triangulation3d(theCoord, theElements)
{
	CreateEdges();
}

namespace AutLib
{
	namespace GeoLib
	{

		static inline Standard_Integer CommomEdge(const TColStd_Ary1dOfInteger& theV1, const TColStd_Ary1dOfInteger& theV2)
		{
			ADT_AdressAvlTree<Standard_Integer> Tree;
			Tree.Insert(theV1);
			forThose(Index,0 , MaxIndexOf(theV2))
				if (Tree.IsContains(theV2[Index])) { return theV2[Index]; }
			return -1;
		}
	}
}

void AutLib::GeoLib::GeoMesh_StaticTriangleMesh3d::CreateEdges()
{
	ADT_Ary1d<ADT_AdressAvlTree<Standard_Integer>*> Nodes(NbPoints());
	forThose(Index, 0, MaxIndexOf(Nodes))
		Nodes[Index] = new ADT_AdressAvlTree<Standard_Integer>;

	TColEntity_BasicQueueOfEdgeIndex QEdges;
	forThose
	(
		Index, 
		0,
		MaxIndexOf(theTriangles_)
	)
	{
		Standard_Integer V0 = theTriangles_[Index].V0();
		Standard_Integer V1 = theTriangles_[Index].V1();
		Standard_Integer V2 = theTriangles_[Index].V2();

		if (Nodes[Index_Of(V0)]->IsEmpty() OR NOT Nodes[Index_Of(V0)]->IsContains(V1))
		{
			QEdges.EnQueue(Entity_EdgeIndex(V0, V1));

			Try_Exception_Handle_Exit(Nodes[Index_Of(V0)]->Insert(V1));
			Try_Exception_Handle_Exit(Nodes[Index_Of(V1)]->Insert(V0));
		}

		if (Nodes[Index_Of(V1)]->IsEmpty() OR NOT Nodes[Index_Of(V1)]->IsContains(V2))
		{
			QEdges.EnQueue(Entity_EdgeIndex(V1, V2));

			Try_Exception_Handle_Exit(Nodes[Index_Of(V1)]->Insert(V2));
			Try_Exception_Handle_Exit(Nodes[Index_Of(V2)]->Insert(V1);)
		}

		if (Nodes[Index_Of(V2)]->IsEmpty() OR NOT Nodes[Index_Of(V2)]->IsContains(V0))
		{
			QEdges.EnQueue(Entity_EdgeIndex(V2, V0));

			Try_Exception_Handle_Exit(Nodes[Index_Of(V2)]->Insert(V0));
			Try_Exception_Handle_Exit(Nodes[Index_Of(V0)]->Insert(V2));
		}
	}

	QEdges.RetrieveTo(theEdges_);

	ADT_Ary1d<ADT_AdressAvlTree<Standard_Integer>*> EANodes(NbPoints());

	forThose(Index, 0, MaxIndexOf(EANodes))
		EANodes[Index] = new ADT_AdressAvlTree<Standard_Integer>;

	forThose
	(
		Index,
		0, 
		MaxIndexOf(theEdges_)
	)
	{
		Standard_Integer V0 = theEdges_[Index].V0();
		Standard_Integer V1 = theEdges_[Index].V1();

		EANodes[Index_Of(V0)]->Insert(Index + 1);
		EANodes[Index_Of(V1)]->Insert(Index + 1);
	}

	theEdgesOfTriangles_.Resize(NbTriangles());

	forThose
	(
		Index,
		0,
		MaxIndexOf(theTriangles_)
	)
	{
		Standard_Integer V0 = theTriangles_[Index].V0();
		Standard_Integer V1 = theTriangles_[Index].V1();
		Standard_Integer V2 = theTriangles_[Index].V2();

		theEdgesOfTriangles_[Index].V0() = CommomEdge(EANodes[Index_Of(V1)]->Retrieve(), EANodes[Index_Of(V2)]->Retrieve());
		theEdgesOfTriangles_[Index].V1() = CommomEdge(EANodes[Index_Of(V2)]->Retrieve(), EANodes[Index_Of(V0)]->Retrieve());
		theEdgesOfTriangles_[Index].V2() = CommomEdge(EANodes[Index_Of(V0)]->Retrieve(), EANodes[Index_Of(V1)]->Retrieve());
	}

	FreeMemory(Nodes);
	FreeMemory(EANodes);
}