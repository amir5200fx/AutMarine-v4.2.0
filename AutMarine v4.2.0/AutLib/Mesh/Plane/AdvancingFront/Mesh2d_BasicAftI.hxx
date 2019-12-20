#pragma once
#include <Geometry_Sort.hxx>
#include <Geometry_Tools.hxx>
#include <Mesh2d_EdgeTools.hxx>
#include <TColMesh2d_HBasicQueueOfNode.hxx>
#include <TColMesh2d_HBasicQueueOfEdge.hxx>

inline
M_MESH Mesh2d_AdvancingFrontConfig & AutLib::MeshLib::Mesh2d_BasicAft::Config()
{
	return theConfig_;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh2d_BasicAft::IsNewNode() const
{
	Debug_Null_Pointer(theInfo_.ValidNode());
	return theInfo_.ValidNode() EQUAL theInfo_.CreatedNode();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_BasicAft::GetFront()
{
	Global_Handle(Mesh2d_Edge) Edge;
	Standard_Boolean Get = theFront_.GetItemFromFront(Edge);

	theInfo_.Reset();

	if (!Get) return Standard_False;

	Debug_Null_Pointer(Edge);

	theInfo_.SetCurrent(Edge);

	return Standard_True;
}

inline
Standard_Boolean AutLib::MeshLib::Mesh2d_BasicAft::IsBelongToFront() const
{
	Debug_Null_Pointer(theInfo_.Current());
	return theInfo_.Current()->IsOnFront();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_BasicAft::IsValidNewPoint(const TColMesh2d_HAry1dOfEdge & theEffectives) const
{
	Standard_Real Factor = theInfo_.MinDistanceFactor();
	Debug_If_Condition(Factor <= ZERO);
	
	Get_Const_Object(Point) = theInfo_.Coord();
	forThose
	(
		Index,
		0,
		MaxIndexOf(theEffectives)
	)
	{
		Debug_Null_Pointer(theEffectives[Index]);

		Get_Const_Object(Edge) = *theEffectives[Index];

		Standard_Real Length = Factor*Edge.Length();
		Standard_Real Criteria = Length*Length;
		
		Standard_Real DistanceSQ = theMap_.CalcDistancePointFromLSegSQ(Point, Edge.Node0()->Coord(), Edge.Node1()->Coord());

		if (DistanceSQ < Criteria)
		{
			return Standard_False;
		}
	}
	return Standard_True;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_BasicAft::IsSameLevelSupply()
{
	if (theFront_.IsCurrentLevelEmpty())
	{
		return Standard_False;
	}

	TColMesh2d_HAry1dOfEdge Edges;
	theFront_.RetrieveCurrentLevelTo(Edges);

	Try_Exception_Handle_Exit(theFront_.InsertToFronts(Edges));

	theFront_.ClearCurrentLevel();

	return Standard_True;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_BasicAft::IsNextLevelSupply()
{
	if (theFront_.IsNextLevelEmpty())
	{
		return Standard_False;
	}

	TColMesh2d_HAry1dOfEdge Edges;
	theFront_.RetrieveNextLevelTo(Edges);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		Edges[Index]->SetCavity(Standard_False);
	}

	Try_Exception_Handle_Exit(theFront_.InsertToFronts(Edges));

	theFront_.ClearNextLevel();
	theFront_.SetLevelMaxIndex(NbNodes());

	return Standard_True;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh2d_BasicAft::IsCavityRemoverSupply()
{
	if (theCavity_.IsUnCertaintyEmpty())
	{
		return Standard_False;
	}

	if (theInfo_.Type() EQUAL Mesh2d_Aft_Generation)
	{
		TColMesh2d_HAry1dOfEdge Edges;
		theCavity_.RetrieveUnCertaintyTo(Edges);

		forThose
		(
			Index,
			0,
			MaxIndexOf(Edges)
		)
		{
			Debug_Null_Pointer(Edges[Index]);

			Edges[Index]->SetCavity(Standard_False);
		}

		Try_Exception_Handle_Exit(theFront_.InsertToFronts(Edges));

		theCavity_.ClearUnCertainty();

		return Standard_True;
	}

	if (theInfo_.Type() EQUAL Mesh2d_Aft_Rapair)
	{
		TColMesh2d_HAry1dOfEdge Edges;
		theCavity_.RetrieveUnCertaintyTo(Edges);

		forThose
		(
			Index,
			0,
			MaxIndexOf(Edges)
		)
		{
			Debug_Null_Pointer(Edges[Index]);

			if (Edges[Index]->IsCavity())
			{
				Try_Exception_Handle_Exit(theCavity_.InsertToCertainty(Edges[Index]));
			}
		}

		theCavity_.ClearUnCertainty();

		return Standard_False;
	}

	THROW_STANDARD_EXCEPTION(" Fatal Error in IsCavityRemoverSupply");

	return Standard_True;
}

inline 
const M_MESH Mesh2d_Edge & AutLib::MeshLib::Mesh2d_BasicAft::CurrentEdge() const
{
	Debug_Null_Pointer(theInfo_.Current());
	return *theInfo_.Current();
}

inline 
const M_MESH Mesh2d_Node & AutLib::MeshLib::Mesh2d_BasicAft::ValidNode() const
{
	Debug_Null_Pointer(theInfo_.ValidNode());
	return *theInfo_.ValidNode();
}

inline 
M_MESH Mesh2d_Edge & AutLib::MeshLib::Mesh2d_BasicAft::CurrentEdge()
{
	Debug_Null_Pointer(theInfo_.Current());
	return *theInfo_.Current();
}

inline
void AutLib::MeshLib::Mesh2d_BasicAft::RetrieveEarlyNodes(TColMesh2d_HAry1dOfNode & theNodes) const
{
	theSearch_.Search(theMap_.CalcSearchRegion(theInfo_.SearchRadius(), theInfo_.Coord()), theNodes);

	Mesh2d_BasicAft::RetrieveNodesInRadius(theNodes, theNodes);
}

inline 
void AutLib::MeshLib::Mesh2d_BasicAft::RetrieveLocalEdges
(
	const TColMesh2d_HAry1dOfNode & theEarly,
	TColMesh2d_HAry1dOfEdge & theLocal
) const
{
	TColMesh2d_HAvlTreeOfEdge Compact;
	Set_Numbering(Compact, Mesh2d_EdgeTools::IsLess);

	forThose
	(
		Index,
		0,
		MaxIndexOf(theEarly)
	)
	{
		Debug_Null_Pointer(theEarly[Index]);

		TColMesh2d_HAry1dOfEdge Edges;
		theEarly[Index]->RetrieveFrontsTo(Edges);

		forThose
		(
			J,
			0,
			MaxIndexOf(Edges)
		)
		{
			Debug_Null_Pointer(Edges[J]);
			Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(Edges[J]));
		}
	}
	Compact.RetrieveTo(theLocal);
}

inline 
void AutLib::MeshLib::Mesh2d_BasicAft::RetrieveEffectiveFronts
(
	const TColMesh2d_HAry1dOfNode & theNodesInRadius,
	const TColMesh2d_HAry1dOfEdge & theLocal, 
	TColMesh2d_HAry1dOfEdge & theEffectives
) const
{
	Debug_Null_Pointer(theInfo_.Current());
	Get_Const_Object(theCurrent) = *theInfo_.Current();

	Debug_Null_Pointer(theCurrent.Node0());
	Debug_Null_Pointer(theCurrent.Node1());

	Standard_Real Xmin, Xmax, Ymin, Ymax;
	Standard_Real X, Y;

	Xmin = Xmax = theInfo_.Coord().X();
	Ymin = Ymax = theInfo_.Coord().Y();

	Get_Const_Object(theP0) = theCurrent.Node0()->Coord();
	theP0.Get(X, Y);

	if (X > Xmax) Xmax = X;
	if (X < Xmin) Xmin = X;
	if (Y > Ymax) Ymax = Y;
	if (Y < Ymin) Ymin = Y;

	Get_Const_Object(theP1) = theCurrent.Node1()->Coord();
	theP1.Get(X, Y);

	if (X > Xmax) Xmax = X;
	if (X < Xmin) Xmin = X;
	if (Y > Ymax) Ymax = Y;
	if (Y < Ymin) Ymin = Y;

	forThose
	(
		Index,
		0,
		MaxIndexOf(theNodesInRadius)
	)
	{
		Debug_Null_Pointer(theNodesInRadius[Index]);
		Get_Const_Object(thePoint) = theNodesInRadius[Index]->Coord();

		thePoint.Get(X, Y);

		if (X > Xmax) Xmax = X;
		if (X < Xmin) Xmin = X;
		if (Y > Ymax) Ymax = Y;
		if (Y < Ymin) Ymin = Y;
	}

	Standard_Real X0, X1, Y0, Y1;
	TColMesh2d_HBasicQueueOfEdge QEdges;
	forThose
	(
		Index,
		0, 
		MaxIndexOf(theLocal)
	)
	{
		Debug_Null_Pointer(theLocal[Index]);
		Get_Const_Object(Edge) = *theLocal[Index];

		Debug_Null_Pointer(Edge.Node0());
		Debug_Null_Pointer(Edge.Node1());


		Get_Const_Object(P0) = Edge.Node0()->Coord();
		Get_Const_Object(P1) = Edge.Node1()->Coord();

		X0 = P0.X();
		X1 = P1.X();

		Continue_If(X0 > Xmax AND X1 > Xmax);
		Continue_If(X0 < Xmin AND X1 < Xmin);

		Y0 = P0.Y();
		Y1 = P1.Y();

		Continue_If(Y0 > Ymax AND Y1 > Ymax);
		Continue_If(Y0 < Ymin AND Y1 < Ymin);

		QEdges.EnQueue(theLocal[Index]);
	}
	QEdges.RetrieveTo(theEffectives);
}

inline 
void AutLib::MeshLib::Mesh2d_BasicAft::RetrieveNodesInRadius
(
	const TColMesh2d_HAry1dOfNode & theNodes,
	TColMesh2d_HAry1dOfNode & theInnerNodes
) const
{
	Standard_Real Radius = theInfo_.SearchRadius();
	Standard_Real RadiusSQ = Radius*Radius;

	Debug_If_Condition_Message(Radius <= 0, " Invalid Radius");

	Get_Const_Object(Centre) = theInfo_.Coord();

	// Modified : 16 March 2019
	auto N0 = CurrentEdge().Node0();
	auto N1 = CurrentEdge().Node1();

	TColMesh2d_HBasicQueueOfNode QInners;
	forThose
	(
		Index,
		0,
		MaxIndexOf(theNodes)
	)
	{
		Debug_Null_Pointer(theNodes[Index]);

		// Modified : 16 March 2019
		if (theNodes[Index] EQUAL N0) continue;
		if (theNodes[Index] EQUAL N1) continue;

		if (theMap_.CalcDistanceSQ(Centre, theNodes[Index]->Coord()) <= RadiusSQ)
		{
			QInners.EnQueue(theNodes[Index]);
		}
	}
	QInners.RetrieveTo(theInnerNodes);
}

inline 
void AutLib::MeshLib::Mesh2d_BasicAft::RetrieveNodesInRadius
(
	const TColMesh2d_HAry1dOfNode & theNodes,
	TColMesh2d_HAry1dOfNode & theNodesLevel1,
	TColMesh2d_HAry1dOfNode & theNodesLevel2
) const
{
	Standard_Real Radius1 = theInfo_.SearchRadiusLevel1();
	Standard_Real Radius2 = theInfo_.SearchRadiusLevel2();

	Standard_Real RadiusSQ1 = Radius1*Radius1;
	Standard_Real RadiusSQ2 = Radius2*Radius2;

	Debug_If_Condition_Message(Radius1 <= 0, " Invalid Radius1");
	Debug_If_Condition_Message(Radius2 <= 0, " Invalid Radius2");

	Get_Const_Object(Centre) = theInfo_.Coord();

	TColMesh2d_HBasicQueueOfNode QInners1, QInners2;
	forThose
	(
		Index,
		0,
		MaxIndexOf(theNodes)
	)
	{
		Debug_Null_Pointer(theNodes[Index]);

		Standard_Real Dis = theMap_.CalcDistanceSQ(Centre, theNodes[Index]->Coord());

		if (Dis <= RadiusSQ1)
		{
			QInners1.EnQueue(theNodes[Index]);
		}

		if (Dis <= RadiusSQ2)
		{
			QInners2.EnQueue(theNodes[Index]);
		}
	}
	QInners1.RetrieveTo(theNodesLevel1);
	QInners2.RetrieveTo(theNodesLevel2);
}

inline 
void AutLib::MeshLib::Mesh2d_BasicAft::NodesInRadius
(
	const Standard_Real theRadius,
	const Geom_Pnt2d & theCoord, 
	const TColMesh2d_HAry1dOfNode & theNodes,
	TColMesh2d_HAry1dOfNode & theInnerNodes
) const
{
	Debug_If_Condition_Message(theRadius <= 0.0, "Invalid Radius");

	const Standard_Real RadiusSQ = theRadius*theRadius;

	TColMesh2d_HBasicQueueOfNode QNodes;
	forThose
	(
		Index,
		0,
		MaxIndexOf(theNodes)
	)
	{
		if (theMap_.CalcDistanceSQ(theCoord, theNodes[Index]->Coord()) <= RadiusSQ)
			QNodes.EnQueue(theNodes[Index]);
	}
	QNodes.RetrieveTo(theInnerNodes);
}

inline 
void AutLib::MeshLib::Mesh2d_BasicAft::AppendOptimumPoint(TColMesh2d_HAry1dOfNode & theNodesInRadius)
{
	Global_Handle(Mesh2d_Node) Node = new Mesh2d_Node(CurrentMesh()->NbNodes() + 1, theInfo_.Coord());
	Debug_Null_Pointer(Node);

	theInfo_.SetCreatedNode(Node);

	theNodesInRadius.DynResize(theNodesInRadius.Size() + 1);

	Try_Exception_Handle_Exit(theNodesInRadius.Last() = Node);

	theInfo_.SetAppendedCondition(Standard_True);
}

inline 
void AutLib::MeshLib::Mesh2d_BasicAft::CalcQuality
(
	const TColMesh2d_HAry1dOfNode & theNodes,
	TColStd_Ary1dOfReal & theQuality
) const
{
	theQuality.Resize(theNodes.Size());

	Debug_Null_Pointer(theInfo_.Current());

	Get_Const_Object(Point) = theInfo_.Current()->Centre();

	forThose
	(
		Index,
		0,
		MaxIndexOf(theNodes)
	)
	{
		Try_Exception_Handle_Exit(theQuality[Index] = theMap_.CalcDistanceSQ(Point, theNodes[Index]->Coord()));
	}
}

inline 
void AutLib::MeshLib::Mesh2d_BasicAft::SortNodes(TColMesh2d_HAry1dOfNode & NodesInRadius) const
{
	TColStd_Ary1dOfReal Quality;

	TColMesh2d_HAry1dOfNode Nodes = NodesInRadius;

	CalcQuality(Nodes, Quality);

	TColStd_Ary1dOfInteger Indices = IndexAray(SizeOf(Quality));

	if (theInfo_.IsAppended())
		Quality[MaxIndexOf(Quality)] = RealLast();

	M_GEO Geometry_Sort<Standard_Real>::Sort(Quality, Indices);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Nodes)
	)
	{
		NodesInRadius[Index] = Nodes[Indices[Index]];
	}
}

inline 
void AutLib::MeshLib::Mesh2d_BasicAft::RemoveCurrentFromFront()
{
	Debug_Null_Pointer(theInfo_.Current());

	Get_Object(Current) = *theInfo_.Current();

	Debug_Null_Pointer(Mesh2d_Plane::CurrentMesh());
	Get_Object(theMesh) = *Mesh2d_Plane::CurrentMesh();

	//! deAttach the current from fronts
	Try_Exception_Handle_Exit(theMesh.deAttachFromFront(&Current));

	//! Remove the current from fronts
	//Try_Exception_Handle_Exit(theMesh.RemoveFromFronts(&Current));
}

inline 
void AutLib::MeshLib::Mesh2d_BasicAft::CalcElementSize()
{
	Debug_Null_Pointer(theInfo_.Current());

	Try_Exception_Handle_Exit(theInfo_.SetElementSize(theMap_.ElementSize(*theInfo_.Current())*0.866025404));  // Modify: July 14 2018
	//Try_Exception_Handle_Exit(theInfo_.SetElementSize(theMap_.ElementSize(*theInfo_.Current())));   // Modify: June 13 2018
}

inline 
void AutLib::MeshLib::Mesh2d_BasicAft::CalcOptimumPoint()
{
	Debug_Null_Pointer(theInfo_.Current());

	Try_Exception_Handle_Exit(theInfo_.SetCoord(theMap_.CalcOptimumPoint(theInfo_.ElementSize(), *theInfo_.Current())));  // Modify: July 14 2018
	//theInfo_.SetCoord(theMap_.CalcOptimumPoint(theInfo_.ElementSize()*0.866025404, *theInfo_.Current()));  // Modify: June 13 2018
}

inline 
void AutLib::MeshLib::Mesh2d_BasicAft::CalcSearchRadius()
{
	Debug_Null_Pointer(theInfo_.Current());

	Get_Const_Object(Current) = *theInfo_.Current();

	Debug_Null_Pointer(Current.Node0());
	Debug_Null_Pointer(Current.Node1());

	Standard_Real MaxL = 1.15 * MAX(theMap_.CalcDistance(theInfo_.Coord(), Current.Node0()->Coord()), theMap_.CalcDistance(theInfo_.Coord(), Current.Node1()->Coord()));
	//theInfo_.SetSearchingRadiusLevel2(MaxL); // Modify: July 14 2018
	//MaxL = MAX(MaxL, theInfo_.ElementSize() / 0.866025);  Modify: June 13 2018
	//MaxL = MAX(MaxL, theInfo_.ElementSize());   // Modify: June 13 2018
	MaxL = MAX(MaxL, theInfo_.ElementSize() / 0.866025);   // Modify: July 14 2018
	Try_Exception_Handle_Exit(theInfo_.SetSearchingRadius(MAX(MaxL, Current.SearchRadius())));
	//Try_Exception_Handle_Exit(theInfo_.SetSearchingRadiusLevel1(theInfo_.SearchRadius()));   // Modify July 14 2018
	//Try_Exception_Handle_Exit(theInfo_.SetSearchingRadiusLevel2(theInfo_.SearchRadius()));
}

inline 
void AutLib::MeshLib::Mesh2d_BasicAft::SetDepthSearching()
{
	if (theInfo_.Type() EQUAL Mesh2d_Aft_Generation)
		theInfo_.SetSearchingRadius(0.95*MAX(theMap_.CalcDistance(theInfo_.Coord(), theInfo_.Current()->Centre()), theInfo_.ElementSize()));   // Modify: June 13 2018

	//if (theInfo_.Type() EQUAL Mesh2d_Aft_Generation)
	//	theInfo_.SetSearchingRadiusLevel2(MAX(theInfo_.SearchRadiusLevel2(), theInfo_.ElementSize()));     // Modify: July 14 2018

	//if (theInfo_.Type() EQUAL Mesh2d_Aft_Generation)
	//	theInfo_.SetSearchingRadiusLevel1(MAX(theMap_.CalcDistance(theInfo_.Coord(), theInfo_.Current()->Centre()), theInfo_.ElementSize()));     // Modify: June 13 2018

	// else: no changing is made in depth of searching radius
}

inline 
void AutLib::MeshLib::Mesh2d_BasicAft::CreateElement()
{
	Debug_Null_Pointer(Mesh2d_Plane::CurrentMesh());
	Get_Object(theMesh) = *Mesh2d_Plane::CurrentMesh();

	theMesh.NbElements()++;
	Global_Handle(Mesh2d_Element) theElement = new Mesh2d_Element(theMesh.NbElements());

	Debug_Null_Pointer(theElement);
	Get_Object(Element) = *theElement;

	Debug_Null_Pointer(theInfo_.Current());
	Get_Const_Object(Current) = *theInfo_.Current();

	Element.SetNode(0, Current.Node0());
	Element.SetNode(1, Current.Node1());
	Element.SetNode(2, theInfo_.ValidNode());

	if (theInfo_.IsCreatedEdge0()) { Element.SetEdge(0, theInfo_.CreatedEdge0()); }
	else { Element.SetEdge(0, theInfo_.PairedEdge0()); }

	if (theInfo_.IsCreatedEdge1()) { Element.SetEdge(1, theInfo_.CreatedEdge1()); }
	else { Element.SetEdge(1, theInfo_.PairedEdge1()); }

	Element.SetEdge(2, theInfo_.Current());

	theInfo_.SetCreatedElement(theElement);
}

inline 
void AutLib::MeshLib::Mesh2d_BasicAft::Reject(Mesh2d_Edge & theEdge)
{
	if (theEdge.IsCavity()) { THROW_STANDARD_EXCEPTION("Failed to Reject facet"); }

	theEdge.SetCavity(Standard_True);

	Debug_Null_Pointer(CurrentMesh());
	Get_Object(theCurrentMesh) = *CurrentMesh();

	Try_Exception_Handle_Exit(theCurrentMesh.AttachToFrontNodes(&theEdge));
	//Try_Exception_Handle_Exit(theCurrentMesh.InsertToFronts(&theEdge));

	Try_Exception_Handle_Exit(theCavity_.InsertToUnCertainty(&theEdge));
}

//inline 
//void AutLib::MeshLib::Mesh2d_BasicAft::CalcGeometryOf(Mesh2d_Edge & theEdge)
//{
//	Debug_Null_Pointer(theEdge.Node0());
//	Debug_Null_Pointer(theEdge.Node1());
//
//	Get_Const_Object(P0) = theEdge.Node0()->Coord();
//	Get_Const_Object(P1) = theEdge.Node1()->Coord();
//
//	theEdge.SetLength(theMap_.CalcDistance(P0, P1));
//	theEdge.SetCentre((P0 + P1) / 2.0);
//}

inline
void AutLib::MeshLib::Mesh2d_BasicAft::SetPairedEdges()
{
	theInfo_.SetCreatedEdge0(NULL);
	theInfo_.SetCreatedEdge1(NULL);

	theInfo_.SetPairedEdge0(NULL);
	theInfo_.SetPairedEdge1(NULL);

	if (theInfo_.Condition() EQUAL Mesh2d_NewPoint)
	{
		return;
	}

	Get_Const_Object(CurrentEdge) = Mesh2d_BasicAft::CurrentEdge();

	Standard_Integer Vn = ValidNode().Index();

	Debug_Null_Pointer(CurrentEdge.Node0());
	Debug_Null_Pointer(CurrentEdge.Node1());

	Standard_Integer V0 = CurrentEdge.Node0()->Index();
	Standard_Integer V1 = CurrentEdge.Node1()->Index();

	TColMesh2d_HBasicQueueOfEdge QEdges;
	ValidNode().RetrieveFrontsTo(QEdges);

	Global_Handle(Mesh2d_Edge) Edge;
	while (QEdges.DeQueue(Edge))
	{
		Debug_Null_Pointer(Edge);
		Get_Const_Object(theEdge) = *Edge;

		Standard_Integer E0 = theEdge.Node0()->Index();
		Standard_Integer E1 = theEdge.Node1()->Index();

		if (M_GEO Geometry_Tools::IsPairedTwoLineSegment(E0, E1, V0, Vn))
		{
			theInfo_.SetPairedEdge1(Edge);
		}

		if (M_GEO Geometry_Tools::IsPairedTwoLineSegment(E0, E1, V1, Vn))
		{
			theInfo_.SetPairedEdge0(Edge);
		}
	}
}

inline
void AutLib::MeshLib::Mesh2d_BasicAft::UpdateFront()
{
	Global_Handle(Mesh2d_Node) ValidNode = theInfo_.ValidNode();
	Debug_Null_Pointer(ValidNode);

	Debug_Null_Pointer(CurrentMesh());
	Get_Object(theMesh) = *CurrentMesh();

	// check for updating the nodes tree
	if (ValidNode->Index() EQUAL NbNodes() + 1)
	{
		theMesh.NbNodes()++;

		theInfo_.SetCondition(Mesh2d_PointCondition::Mesh2d_NewPoint);

		// insert the new node into the NODES TREE
		theMesh.InsertToMesh(ValidNode);
		theMesh.InsertToFronts(ValidNode);

		theSearch_.Insert(ValidNode);
	}
	else
	{
		theInfo_.SetCondition(Mesh2d_PointCondition::Mesh2d_PickedUp);
	}

	SetPairedEdges();

	Try_Exception_Handle_Exit(UpdateEdges());

	CreateElement();

	UpdateElement();

	// remove non-GF nodes from the ADT
	Debug_Null_Pointer(theInfo_.CreatedElement());
	Get_Object(theElement) = *theInfo_.CreatedElement();

	forThose
	(
		Index,
		0,
		2
	)
	{
		Debug_Null_Pointer(theElement.Node(Index));

		if (theElement.Node(Index)->IsEmptyFront())
		{
			Try_Exception_Handle_Exit(theMesh.RemoveFromFronts(theElement.Node(Index)));

			theSearch_.Remove(theElement.Node(Index));
		}
	}
}

inline 
void AutLib::MeshLib::Mesh2d_BasicAft::Update()
{
	if (theInfo_.ValidNode())
	{
		Try_Exception_Handle_Exit(UpdateFront());

		if (theInfo_.IsAppended())
		{
			if (theInfo_.ValidNode() NOT_EQUAL theInfo_.CreatedNode())
				Delete_Pointer(theInfo_.CreatedNode());
		}

		Try_Exception_Handle_Exit(InsertNewEdgesToLevels());
	}
	else
	{
		Try_Exception_Handle_Exit(Reject(*theInfo_.Current()));

		if (theInfo_.IsAppended())
		{
			Delete_Pointer(theInfo_.CreatedNode());
		}
	}
}

inline
void AutLib::MeshLib::Mesh2d_BasicAft::InsertNewEdgesToLevels()
{
	Global_Handle(Mesh2d_Edge) Edge = theInfo_.CreatedEdge0();
	if (Edge)
	{
		if (theFront_.IsOnLevel(*Edge))
		{
			theFront_.InsertToCurrentLevel(Edge);
		}
		else
		{
			theFront_.InsertToNextLevel(Edge);
		}
	}

	Edge = theInfo_.CreatedEdge1();
	if (Edge)
	{
		if (theFront_.IsOnLevel(*Edge))
		{
			theFront_.InsertToCurrentLevel(Edge);
		}
		else
		{
			theFront_.InsertToNextLevel(Edge);
		}
	}
}

inline 
void AutLib::MeshLib::Mesh2d_BasicAft::UpdateMaxLength
(
	const Standard_Real theLength,
	Mesh2d_Edge & theEdge
)
{
	theEdge.Node0()->SetMaxAdjLength(MAX(theLength, theEdge.Node0()->MaxAdjLength()));
	theEdge.Node1()->SetMaxAdjLength(MAX(theLength, theEdge.Node1()->MaxAdjLength()));
}

inline
Standard_Real AutLib::MeshLib::Mesh2d_BasicAft::CalcUnitDistance(const Geom_Pnt2d & P1, const Geom_Pnt2d & P2, const Mesh2d_SizeMap& Map)
{
	return Map.CalcUnitDistance(P1, P2);
}