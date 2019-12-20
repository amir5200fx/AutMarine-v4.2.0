#pragma once
#include <Geometry_Tools.hxx>

inline
Standard_Integer AutLib::GeoLib::GeoMesh_TriangleMesh2d::NbNodes() const
{
	Debug_If_Condition(NOT IsDone_);
	return theNodesSequence_.Size();
}

inline 
Standard_Integer AutLib::GeoLib::GeoMesh_TriangleMesh2d::NbEdges() const
{
	Debug_If_Condition(NOT IsDone_);
	return theEdgesSequence_.Size();
}

inline 
Standard_Integer AutLib::GeoLib::GeoMesh_TriangleMesh2d::NbElements() const
{
	Debug_If_Condition(NOT IsDone_);
	return theElementsSequence_.Size();
}

inline 
Standard_Integer AutLib::GeoLib::GeoMesh_TriangleMesh2d::NbBoundaries() const
{
	Debug_If_Condition(NOT IsDone_);
	return theBoundaries_.Size();
}

inline 
Global_Handle(M_GEO Entity_Element2d) AutLib::GeoLib::GeoMesh_TriangleMesh2d::TriangleLocation(Global_Handle(Entity_Element2d) ElementPtr, const Geom_Pnt2d & Coord) const
{
	if (NOT ElementPtr) return ElementPtr;

	Get_Const_Object(Element) = *ElementPtr;

	if (Geometry_Tools::IsPointRightEdge(Coord, Element.Node0()->Coord(), Element.Node1()->Coord())) { return TriangleLocation(Element.Neighbor2(), Coord); }
	else if (Geometry_Tools::IsPointRightEdge(Coord, Element.Node1()->Coord(), Element.Node2()->Coord())) { return TriangleLocation(Element.Neighbor0(), Coord); }
	else if (Geometry_Tools::IsPointRightEdge(Coord, Element.Node2()->Coord(), Element.Node0()->Coord())) { return TriangleLocation(Element.Neighbor1(), Coord); }

	// found the Triangle
	return ElementPtr;
}

inline 
Global_Handle(M_GEO Entity_Element2d) AutLib::GeoLib::GeoMesh_TriangleMesh2d::FirstElement() const
{
	return theElementsSequence_[0];
}

inline 
const M_AUT TColEntity_HAry1dOfNode2d & AutLib::GeoLib::GeoMesh_TriangleMesh2d::NodesSequence() const
{
	Debug_If_Condition(NOT IsDone_);
	return theNodesSequence_;
}

inline 
const M_AUT TColEntity_HAry1dOfEdge2d & AutLib::GeoLib::GeoMesh_TriangleMesh2d::EdgesSequence() const
{
	Debug_If_Condition(NOT IsDone_);
	return theEdgesSequence_;
}

inline 
const M_AUT TColEntity_HAry1dOfElement2d & AutLib::GeoLib::GeoMesh_TriangleMesh2d::ElementsSequence() const
{
	Debug_If_Condition(NOT IsDone_);
	return theElementsSequence_;
}

template<typename T>
inline void AutLib::GeoLib::GeoMesh_TriangleMesh2d::LaplacianSmoothing
(
	ADT_Ary1d<T>& Values,
	const Standard_Integer NbIterations, 
	const Standard_Real Factor
) const
{
	if (Values.Size() NOT_EQUAL theNodesSequence_.Size()) { THROW_STANDARD_EXCEPTION(" "); }

	Standard_Real factor = MAX(0, MIN(Factor, 1.0));

	forThose
	(
		Iter,
		1,
		NbIterations
	)
	{
		forThose
		(
			Index,
			0, 
			MaxIndexOf(theNodesSequence_)
		)
		{
			Get_Const_Object(Node) = *theNodesSequence_[Index];
			Standard_Integer Centre = Node.Index();
			T Avg;
			Avg = (Standard_Real)0;

			TColEntity_HAry1dOfEdge2d Edges = Node.Edges();
			forThose
			(
				Inner,
				0, 
				MaxIndexOf(Edges)
			)
			{
				Standard_Integer Neighbor = Edges[Inner]->Node(0)->Index();
				if (Centre EQUAL Neighbor) Neighbor = Edges[Inner]->Node(1)->Index();

				Avg += Values[Inner];
			}

			Avg /= (Standard_Real)Edges.Size();

			Values[Index] = Values[Index] + factor*(Avg - Values[Index]);
		}
	}
}

inline
void AutLib::GeoLib::GeoMesh_TriangleMesh2d::Insert(Global_Handle(Entity_Node2d) Node)
{
	theNodes_.Insert(Node);
}

inline 
void AutLib::GeoLib::GeoMesh_TriangleMesh2d::Insert(Global_Handle(Entity_Edge2d) Edge)
{
	theEdges_.Insert(Edge);
}

inline 
void AutLib::GeoLib::GeoMesh_TriangleMesh2d::Insert(Global_Handle(Entity_Element2d) Element)
{
	theElements_.Insert(Element);
}

inline 
void AutLib::GeoLib::GeoMesh_TriangleMesh2d::Remove(Global_Handle(Entity_Node2d) Node)
{
	theNodes_.Remove(Node);
}

inline 
void AutLib::GeoLib::GeoMesh_TriangleMesh2d::Remove(Global_Handle(Entity_Edge2d) Edge)
{
	theEdges_.Remove(Edge);
}

inline 
void AutLib::GeoLib::GeoMesh_TriangleMesh2d::Remove(Global_Handle(Entity_Element2d) Element)
{
	theElements_.Remove(Element);
}

inline 
void AutLib::GeoLib::GeoMesh_TriangleMesh2d::RetrieveTo(TColEntity_HAry1dOfNode2d & Nodes) const
{
	Debug_If_Condition(NOT IsDone_);
	theNodes_.RetrieveTo(Nodes);
}

inline 
void AutLib::GeoLib::GeoMesh_TriangleMesh2d::RetrieveTo(TColEntity_HAry1dOfEdge2d & Edges) const
{
	Debug_If_Condition(NOT IsDone_);
	theEdges_.RetrieveTo(Edges);
}

inline 
void AutLib::GeoLib::GeoMesh_TriangleMesh2d::RetrieveTo(TColEntity_HAry1dOfElement2d & Elements) const
{
	Debug_If_Condition(NOT IsDone_);
	theElements_.RetrieveTo(Elements);
}