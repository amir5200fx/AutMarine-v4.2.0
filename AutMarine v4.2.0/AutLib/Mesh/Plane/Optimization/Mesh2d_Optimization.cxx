#include <Mesh2d_Optimization.hxx>

#include <Geometry_Intersect.hxx>
#include <Mesh2d_BoundaryEdge.hxx>
#include <Mesh2d_QualityMap.hxx>
#include <Mesh2d_TMesh.hxx>
#include <Mesh2d_SizeMap.hxx>
#include <Mesh2d_Plane.hxx>
#include <SizeMap2d_FullIntAnIso.hxx>

using namespace AutLib;
using namespace GeoLib;

static const Standard_Real DEFAULT_UNDER_RELAXATION = 0.85;

AutLib::MeshLib::Mesh2d_Optimization::Mesh2d_Optimization
(
	const Mesh2d_QualityMap & theQualityMap, 
	const Mesh2d_SizeMap & theSizeMap,
	const Global_Handle(Mesh2d_MetricMap) theMetricMap,
	Mesh2d_Plane & theMesh
)
	: theQualityMap_(theQualityMap)
	, theSizeMap_(theSizeMap)
	, theMetricMap_(theMetricMap)
	, theMesh_(theMesh)
	, theVerbose_(0)
{
	if (theMetricMap_)
	{
		UnionSizeMap_ = new SizeMap2d_FullIntAnIso(&theSizeMap_, theMetricMap);
	}
	else
	{
		UnionSizeMap_ = (Global_Handle(Mesh2d_SizeMap))&theSizeMap;
	}
}

AutLib::MeshLib::Mesh2d_Optimization::~Mesh2d_Optimization()
{
	if (theMetricMap_)
	{
		FreePointer(UnionSizeMap_);
	}
}

void AutLib::MeshLib::Mesh2d_Optimization::SetVerbosity(const Standard_Integer theVerbose)
{
	theVerbose_ = MAX(theVerbose, 0);
}

void AutLib::MeshLib::Mesh2d_Optimization::Perform()
{
	forThose
	(
		Index,
		0,
		theMesh_.NbMeshes() - 1
	)
	{
		Debug_Null_Pointer(theMesh_.Mesh(Index));
		Debug_Null_Pointer(Global_DownCast(Mesh2d_TMesh, theMesh_.Mesh(Index)));

		Global_Handle(Mesh2d_TMesh) Mesh = Global_DownCast(Mesh2d_TMesh, theMesh_.Mesh(Index));

		Perform(*Mesh);
	}

	forThose
	(
		Index,
		0,
		theMesh_.NbMeshes() - 1
	)
	{
		Debug_Null_Pointer(theMesh_.Mesh(Index));
		Debug_Null_Pointer(Global_DownCast(Mesh2d_TMesh, theMesh_.Mesh(Index)));

		Global_Handle(Mesh2d_TMesh) Mesh = Global_DownCast(Mesh2d_TMesh, theMesh_.Mesh(Index));

		LaplacianSmoothing(*Mesh, DEFAULT_UNDER_RELAXATION);

	}

	/*forThose
	(
		Index,
		0,
		theMesh_.NbMeshes() - 1
	)
	{
		Debug_Null_Pointer(theMesh_.Mesh(Index));
		Debug_Null_Pointer(Global_DownCast(Mesh2d_TMesh, theMesh_.Mesh(Index)));

		Global_Handle(Mesh2d_TMesh) Mesh = Global_DownCast(Mesh2d_TMesh, theMesh_.Mesh(Index));

		Mesh->CompactNumbering();

	}*/
}

void AutLib::MeshLib::Mesh2d_Optimization::Perform(Mesh2d_TMesh & theMesh)
{
	//Standard_Real Worst0 = CalcWorstQuality(theMesh);

	/*if (theVerbose_)
	{
		cout << "   Optimization is Applied to: " << theMesh.Name() << endl;
		cout << "    Worst Element Quality= " << Worst0 << endl;
	}*/

	LaplacianSmoothing(theMesh, DEFAULT_UNDER_RELAXATION);

	Topological(theMesh);

	Topological(theMesh);

	//Standard_Real Worst = CalcWorstQuality(theMesh);

	/*if (theVerbose_)
	{
		cout << "   Optimization has been Done!\n";
		cout << "    Worst Element Quality= " << Worst << endl;
	}*/
}

Standard_Real AutLib::MeshLib::Mesh2d_Optimization::WorstQuality(const Mesh2d_Edge & theEdge) const
{
	Debug_Null_Pointer(theEdge.LeftElement());
	Debug_Null_Pointer(theEdge.RightElement());

	Get_Const_Object(Left) = *theEdge.LeftElement();
	Get_Const_Object(Right) = *theEdge.RightElement();

	Standard_Real Quality1 = UnionSizeMap_->ElementQuality(Left.Node0()->Coord(), Left.Node1()->Coord(), Left.Node2()->Coord(), theQualityMap_);
	Standard_Real Quality2 = UnionSizeMap_->ElementQuality(Right.Node0()->Coord(), Right.Node1()->Coord(), Right.Node2()->Coord(), theQualityMap_);

	return MIN(Quality1, Quality2);
}

void AutLib::MeshLib::Mesh2d_Optimization::Topological(Mesh2d_TMesh & theMesh)
{
	TColMesh2d_HAry1dOfEdge Edges;
	theMesh.RetrieveTo(Edges);

	Standard_Integer NbAttempts = 0;
	Standard_Integer NbSuccess = 0;

	forThose(Index, 0, MaxIndexOf(Edges))
	{
		Debug_Null_Pointer(Edges[Index]);

		if (Edges[Index]->IsOnFront()) continue;
		if (Global_DownCast(Mesh2d_BoundaryEdge, (Global_Handle(Mesh2d_Edge))Edges[Index])) continue;

		NbAttempts++;

		if (Flip(Edges[Index], theMesh)) NbSuccess++;
	}

	if (theVerbose_ > 1)
	{
		cout << "    Flip23 - Nb. of Attempts= " << NbAttempts << endl;
		cout << "    Flip23 - Nb. of success= " << NbSuccess << endl;
	}
}

void AutLib::MeshLib::Mesh2d_Optimization::LaplacianSmoothing
(
	Mesh2d_TMesh & theMesh, 
	const Standard_Real theUnderRelaxation
)
{
	theMesh.LaplacianSmoothing(3, theUnderRelaxation, &Mesh2d_Optimization::CalcUnitDistance, *UnionSizeMap_, (theVerbose_ > 0 ? Standard_True : Standard_False));
}

Global_Handle(Mesh2d_Edge) AutLib::MeshLib::Mesh2d_Optimization::ImportEdgeToMesh
(
	Global_Handle(Mesh2d_Node) theNode0,
	Global_Handle(Mesh2d_Node) theNode1, 
	Mesh2d_TMesh & theMesh
)
{
	Standard_Real Length = UnionSizeMap_->CalcDistance(theNode0->Coord(), theNode1->Coord());

	Global_Handle(Mesh2d_Edge) Edge = new Mesh2d_Edge
	(
		++theMesh.NbEdges(),
		Length,
		UnionSizeMap_->CalcCentreOf(theNode0->Coord(), theNode1->Coord()),
		theNode0, 
		theNode1
	);

	Debug_Null_Pointer(Edge);

	theMesh.UpdateMaxLength(Length, *Edge);

	theMesh.AttachToMeshNodes(Edge);
	//theMesh.AttachToFrontNodes(Edge);

	theMesh.InsertToMesh(Edge);

	return Edge;
}

Standard_Boolean AutLib::MeshLib::Mesh2d_Optimization::Flip
(
	Global_Handle(Mesh2d_Edge) theEdge,
	Mesh2d_TMesh & theMesh
)
{
	Debug_Null_Pointer(theEdge);

	Global_Handle(Mesh2d_Node) Vertex0;
	Global_Handle(Mesh2d_Node) Vertex1;
	if (CheckFlip(theEdge, Vertex0, Vertex1)) { return Standard_False; }

	Global_Handle(Mesh2d_Node) Node0 = theEdge->Node0();
	Global_Handle(Mesh2d_Node) Node1 = theEdge->Node1();

	theMesh.ForcedToRemoveFromTopology(theEdge, Standard_True);

	Global_Handle(Mesh2d_Edge) Edge = ImportEdgeToMesh(Vertex0, Vertex1, theMesh);

	Try_Exception_Handle_Exit(theMesh.AddToTopology(Edge, Node1, *UnionSizeMap_, Standard_False));

	Edge->Reverse();

	Try_Exception_Handle_Exit(theMesh.AddToTopology(Edge, Node0, *UnionSizeMap_, Standard_False));

	return Standard_True;
}

Standard_Boolean AutLib::MeshLib::Mesh2d_Optimization::CheckFlip
(
	const Global_Handle(Mesh2d_Edge) theEdge,
	Global_Handle(Mesh2d_Node)& theVertex0,
	Global_Handle(Mesh2d_Node)& theVertex1
) const
{
	Debug_Null_Pointer(theEdge);

	if (theEdge->IsOnFront()) { return Standard_True; }
	if (Global_DownCast(Mesh2d_BoundaryEdge, (Global_Handle(Mesh2d_Edge))theEdge)) { return Standard_True; }

	Debug_Null_Pointer(theEdge->LeftElement());
	Debug_Null_Pointer(theEdge->RightElement());

	Get_Const_Object(Left) = *theEdge->LeftElement();
	Get_Const_Object(Right) = *theEdge->RightElement();

	Debug_Null_Pointer(Left.OppositeVertex(*theEdge));
	Debug_Null_Pointer(Right.OppositeVertex(*theEdge));

	theVertex0 = Left.OppositeVertex(*theEdge);
	theVertex1 = Right.OppositeVertex(*theEdge);

	Debug_Null_Pointer(theEdge->Node0());
	Debug_Null_Pointer(theEdge->Node1());

	if (NOT Geometry_Intersect::IsIntersect(theEdge->Node0()->Coord(), theEdge->Node1()->Coord(), theVertex0->Coord(), theVertex1->Coord()))
	{
		return Standard_True;
	}
	
	Standard_Real Worst = WorstQuality(*theEdge);

	Standard_Real Quality1 = UnionSizeMap_->ElementQuality(theEdge->Node0()->Coord(), theVertex1->Coord(), theVertex0->Coord(), theQualityMap_);
	Standard_Real Quality2 = UnionSizeMap_->ElementQuality(theEdge->Node1()->Coord(), theVertex0->Coord(), theVertex1->Coord(), theQualityMap_);

	if (MIN(Quality1, Quality2) <= Worst) return Standard_True;
	return Standard_False;
}

Standard_Real AutLib::MeshLib::Mesh2d_Optimization::CalcUnitDistance
(
	const Geom_Pnt2d & P1, 
	const Geom_Pnt2d & P2, 
	const Mesh2d_SizeMap & Map
)
{
	return Map.CalcUnitDistance(P1, P2);
}