#include "Mesh2d_Edge.hxx"

#include <TColMesh2d_HAry1dOfEdge.hxx>

Standard_Real AutLib::MeshLib::Mesh2d_Edge::MaxAdjastedLength() const
{
	Get_Const_Object(Node0) = *Node(0);
	Get_Const_Object(Node1) = *Node(1);

	TColMesh2d_HAry1dOfEdge Left, Right;
	Node0.RetrieveEdgesTo(Left);
	Node1.RetrieveEdgesTo(Right);

	Standard_Real Length = Mesh2d_Edge::Length();

	forThose(Index, 0, MaxIndexOf(Left))
		if (Left[Index] NOT_EQUAL this) Length = MAX(Length, Left[Index]->Length());

	forThose(Index, 0, MaxIndexOf(Right))
		if (Right[Index] NOT_EQUAL this) Length = MAX(Length, Right[Index]->Length());

	return Length;
}