#pragma once
#include <Geometry_Sort.hxx>
#include <Mesh3d_FacetTools.hxx>
#include <TColStd_Ary1dOfInteger.hxx>
#include <TColMesh3d_HBasicQueueOfNode.hxx>

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_BasicAft::IsNewNode() const
{
	Debug_Null_Pointer(theInfo_.ValidNode());

	return theInfo_.ValidNode() EQUAL theInfo_.CreatedNode();
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_BasicAft::GetFront()
{
	Global_Handle(Mesh3d_Facet) theFacet;
	Standard_Boolean Get = theFront_.GetItemFromFront(theFacet);

	theInfo_.Reset();

	if (!Get) return Standard_False;

	Debug_Null_Pointer(theFacet);

	theInfo_.SetCurrent(theFacet);

	return Standard_True;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_BasicAft::IsBelongToFront() const
{
	Debug_Null_Pointer(theInfo_.Current());

	return theInfo_.Current()->IsOnFront();
}

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_BasicAft::IsValidNewPoint(const TColMesh3d_HAry1dOfFacet & theEffectives) const
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

		Get_Const_Object(Facet) = *theEffectives[Index];

		Standard_Real Length = Factor*Facet.Length();
		Standard_Real Criteria = Length*Length;

		Standard_Real DistanceSQ = theMap_.CalcDistanceFromTriangleSQ
		(
			Point, 
			Facet.Node0()->Coord(),
			Facet.Node1()->Coord(),
			Facet.Node2()->Coord()
		);

		if (DistanceSQ < Criteria)
		{
			return Standard_False;
		}
	}
	return Standard_True;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_BasicAft::IsValidNewEdge
(
	const Geom_Pnt3d & theP0, 
	const Geom_Pnt3d & theP1,
	const TColMesh3d_HAry1dOfEdge & theEffectives
) const
{
	Standard_Real Factor = theInfo_.MinDistanceFactor();
	Debug_If_Condition(Factor <= ZERO);

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

		Standard_Real DistanceSQ = theMap_.CalcDistanceEdgeFromEdgeSQ
		(
			theP0,
			theP1, 
			Edge.Node0()->Coord(),
			Edge.Node1()->Coord()
		);

		if (DistanceSQ < Criteria)
		{
			return Standard_False;
		}
	}
	return Standard_True;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_BasicAft::IsSameLevelSupply()
{
	if (theFront_.IsCurrentLevelEmpty())
	{
		return Standard_False;
	}

	TColMesh3d_HAry1dOfFacet Facets;
	theFront_.RetrieveCurrentLevelTo(Facets);

	Try_Exception_Handle_Exit(theFront_.InsertToFronts(Facets));

	theFront_.ClearCurrentLevel();

	return Standard_True;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_BasicAft::IsNextLevelSupply()
{
	if (theFront_.IsNextLevelEmpty())
	{
		return Standard_False;
	}

	TColMesh3d_HAry1dOfFacet Facets;
	theFront_.RetrieveNextLevelTo(Facets);

	forThose
	(
		Index, 
		0, 
		MaxIndexOf(Facets)
	)
	{
		Debug_Null_Pointer(Facets[Index]);

		Facets[Index]->SetAsNotCavity();
	}

	Try_Exception_Handle_Exit(theFront_.InsertToFronts(Facets));

	theFront_.ClearNextLevel();

	theFront_.SetLevelMaxIndex(NbNodes());

	return Standard_True;
}

inline 
Standard_Boolean AutLib::MeshLib::Mesh3d_BasicAft::IsCavityRemoverSupply()
{
	if (theCavity_.IsUnCertaintyEmpty())
	{
		return Standard_False;
	}

	if (theInfo_.Type() EQUAL Mesh3d_Aft_Generation)
	{
		TColMesh3d_HAry1dOfFacet Facets;
		theCavity_.RetrieveUnCertaintyTo(Facets);

		forThose
		(
			Index,
			0,
			MaxIndexOf(Facets)
		)
		{
			Debug_Null_Pointer(Facets[Index]);

			Facets[Index]->SetAsNotCavity();
		}

		Try_Exception_Handle_Exit(theFront_.InsertToFronts(Facets));

		theCavity_.ClearUnCertainty();

		return Standard_True;
	}

	if (theInfo_.Type() EQUAL Mesh3d_Aft_Rapair)
	{
		TColMesh3d_HAry1dOfFacet Facets;
		theCavity_.RetrieveUnCertaintyTo(Facets);

		forThose
		(
			Index,
			0,
			MaxIndexOf(Facets)
		)
		{
			Debug_Null_Pointer(Facets[Index]);

			if (Facets[Index]->IsCavity())
			{
				Try_Exception_Handle_Exit(theCavity_.InsertToCertainty(Facets[Index]));
			}
		}

		theCavity_.ClearUnCertainty();

		return Standard_False;
	}

	THROW_STANDARD_EXCEPTION(" Fatal Error in IsCavityRemoverSupply");

	return Standard_True;
}

inline 
const M_MESH Mesh3d_Facet & AutLib::MeshLib::Mesh3d_BasicAft::CurrentFacet() const
{
	Debug_Null_Pointer(theInfo_.Current());
	return *theInfo_.Current();
}

inline 
const M_MESH Mesh3d_Node & AutLib::MeshLib::Mesh3d_BasicAft::ValidNode() const
{
	Debug_Null_Pointer(theInfo_.ValidNode());
	return *theInfo_.ValidNode();
}

inline 
M_MESH Mesh3d_Facet & AutLib::MeshLib::Mesh3d_BasicAft::CurrentFacet()
{
	Debug_Null_Pointer(theInfo_.Current());
	return *theInfo_.Current();
}

inline 
void AutLib::MeshLib::Mesh3d_BasicAft::RetrieveEarlyNodes(TColMesh3d_HAry1dOfNode & theNodes) const
{
	theSearch_.Search(theMap_.CalcSearchingRegion(theInfo_.SearchRadius(), theInfo_.Coord()), theNodes);

	Mesh3d_BasicAft::RetrieveNodesInRadius(theNodes, theNodes);
}

inline 
void AutLib::MeshLib::Mesh3d_BasicAft::RetrieveLocalFacets
(
	const TColMesh3d_HAry1dOfNode & theEarly,
	TColMesh3d_HAry1dOfFacet & theLocal
) const
{
	TColMesh3d_HAvlTreeOfFacet Compact;
	Set_Numbering(Compact, Mesh3d_FacetTools::IsLess);

	forThose
	(
		Index,
		0, 
		MaxIndexOf(theEarly)
	)
	{
		Debug_Null_Pointer(theEarly[Index]);

		TColMesh3d_HAry1dOfFacet Facets;
		theEarly[Index]->RetrieveFrontsTo(Facets);

		forThose
		(
			J,
			0, 
			MaxIndexOf(Facets)
		)
		{
			Debug_Null_Pointer(Facets[J]);
			Try_Exception_Handle_Exit(Compact.InsertIgnoreDup(Facets[J]));
		}
	}
	Compact.RetrieveTo(theLocal);
}

inline 
void AutLib::MeshLib::Mesh3d_BasicAft::RetrieveEffectiveFronts
(
	const TColMesh3d_HAry1dOfNode & theNodesInRadius,
	const TColMesh3d_HAry1dOfFacet & theLocal,
	TColMesh3d_HAry1dOfFacet & theEffectives
) const
{
	Debug_Null_Pointer(theInfo_.Current());
	Get_Const_Object(theCurrent) = *theInfo_.Current();

	Debug_Null_Pointer(theCurrent.Node0());
	Debug_Null_Pointer(theCurrent.Node1());
	Debug_Null_Pointer(theCurrent.Node2());

	Standard_Real Xmin, Xmax, Ymin, Ymax, Zmin, Zmax;
	Standard_Real X, Y, Z;

	Xmin = Xmax = theInfo_.Coord().X();
	Ymin = Ymax = theInfo_.Coord().Y();
	Zmin = Zmax = theInfo_.Coord().Z();

	Get_Const_Object(theP0) = theCurrent.Node0()->Coord();
	theP0.Get(X, Y, Z);

	if (X > Xmax) Xmax = X;
	if (X < Xmin) Xmin = X;
	if (Y > Ymax) Ymax = Y;
	if (Y < Ymin) Ymin = Y;
	if (Z > Zmax) Zmax = Z;
	if (Z < Zmin) Zmin = Z;

	Get_Const_Object(theP1) = theCurrent.Node1()->Coord();
	theP1.Get(X, Y, Z);

	if (X > Xmax) Xmax = X;
	if (X < Xmin) Xmin = X;
	if (Y > Ymax) Ymax = Y;
	if (Y < Ymin) Ymin = Y;
	if (Z > Zmax) Zmax = Z;
	if (Z < Zmin) Zmin = Z;

	Get_Const_Object(theP2) = theCurrent.Node2()->Coord();
	theP2.Get(X, Y, Z);

	if (X > Xmax) Xmax = X;
	if (X < Xmin) Xmin = X;
	if (Y > Ymax) Ymax = Y;
	if (Y < Ymin) Ymin = Y;
	if (Z > Zmax) Zmax = Z;
	if (Z < Zmin) Zmin = Z;

	forThose
	(
		Index,
		0, 
		MaxIndexOf(theNodesInRadius)
	)
	{
		Debug_Null_Pointer(theNodesInRadius[Index]);
		Get_Const_Object(thePoint) = theNodesInRadius[Index]->Coord();

		thePoint.Get(X, Y, Z);

		if (X > Xmax) Xmax = X;
		if (X < Xmin) Xmin = X;
		if (Y > Ymax) Ymax = Y;
		if (Y < Ymin) Ymin = Y;
		if (Z > Zmax) Zmax = Z;
		if (Z < Zmin) Zmin = Z;
	}

	Standard_Real X0, X1, X2, Y0, Y1, Y2, Z0, Z1, Z2;
	TColMesh3d_HBasicQueueOfFacet QFaces;
	forThose(Index, 0, MaxIndexOf(theLocal))
	{
		Debug_Null_Pointer(theLocal[Index]);
		Get_Const_Object(Facet) = *theLocal[Index];

		Debug_Null_Pointer(Facet.Node0());
		Debug_Null_Pointer(Facet.Node1());
		Debug_Null_Pointer(Facet.Node2());

		Get_Const_Object(P0) = Facet.Node0()->Coord();
		Get_Const_Object(P1) = Facet.Node1()->Coord();
		Get_Const_Object(P2) = Facet.Node2()->Coord();

		X0 = P0.X();
		X1 = P1.X();
		X2 = P2.X();

		Continue_If(X0 > Xmax AND X1 > Xmax AND X2 > Xmax);
		Continue_If(X0 < Xmin AND X1 < Xmin AND X2 < Xmin);

		Y0 = P0.Y();
		Y1 = P1.Y();
		Y2 = P2.Y();

		Continue_If(Y0 > Ymax AND Y1 > Ymax AND Y2 > Ymax);
		Continue_If(Y0 < Ymin AND Y1 < Ymin AND Y2 < Ymin);

		Z0 = P0.Z();
		Z1 = P1.Z();
		Z2 = P2.Z();

		Continue_If(Z0 > Zmax AND Z1 > Zmax AND Z2 > Zmax);
		Continue_If(Z0 < Zmin AND Z1 < Zmin AND Z2 < Zmin);

		QFaces.EnQueue(theLocal[Index]);
	}
	QFaces.RetrieveTo(theEffectives);
}

inline 
void AutLib::MeshLib::Mesh3d_BasicAft::RetrieveNodesInRadius(const TColMesh3d_HAry1dOfNode & theNodes, TColMesh3d_HAry1dOfNode & theInnerNodes) const
{
	Standard_Real Radius = theInfo_.SearchRadius();
	Standard_Real RadiusSQ = Radius*Radius;

	Debug_If_Condition_Message(Radius <= 0, " Invalid Radius");

	Get_Const_Object(Centre) = theInfo_.Coord();

	TColMesh3d_HBasicQueueOfNode QInners;
	forThose
	(
		Index,
		0,
		MaxIndexOf(theNodes)
	)
	{
		Debug_Null_Pointer(theNodes[Index]);

		if (theMap_.CalcDistanceSQ(Centre, theNodes[Index]->Coord()) <= RadiusSQ)
		{
			QInners.EnQueue(theNodes[Index]);
		}
	}
	QInners.RetrieveTo(theInnerNodes);
}

inline
void AutLib::MeshLib::Mesh3d_BasicAft::RetrieveNodesInRadius
(
	const TColMesh3d_HAry1dOfNode & theNodes,
	TColMesh3d_HAry1dOfNode & theNodesLevel1,
	TColMesh3d_HAry1dOfNode & theNodesLevel2
) const
{
	Standard_Real Radius1 = theInfo_.SearchRadiusLevel1();
	Standard_Real Radius2 = theInfo_.SearchRadiusLevel2();

	Standard_Real RadiusSQ1 = Radius1*Radius1;
	Standard_Real RadiusSQ2 = Radius2*Radius2;

	Debug_If_Condition_Message(Radius1 <= 0, " Invalid Radius1");
	Debug_If_Condition_Message(Radius2 <= 0, " Invalid Radius2");

	Get_Const_Object(Centre) = theInfo_.Coord();

	TColMesh3d_HBasicQueueOfNode QInners1, QInners2;
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
void AutLib::MeshLib::Mesh3d_BasicAft::NodesInRadius
(
	const Standard_Real theRadius,
	const Geom_Pnt3d & theCoord,
	const TColMesh3d_HAry1dOfNode & theNodes, 
	TColMesh3d_HAry1dOfNode & theInnerNodes
) const
{
	Debug_If_Condition_Message(theRadius <= 0.0, "Invalid Radius");

	const Standard_Real RadiusSQ = theRadius*theRadius;

	TColMesh3d_HBasicQueueOfNode QNodes;
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
void AutLib::MeshLib::Mesh3d_BasicAft::AppendOptimumPoint(TColMesh3d_HAry1dOfNode & theNodesInRadius)
{
	Global_Handle(Mesh3d_Node) Node = new Mesh3d_Node(CurrentMesh()->NbNodes() + 1, theInfo_.Coord());
	Debug_Null_Pointer(Node);

	theInfo_.SetCreatedNode(Node);

	theNodesInRadius.DynResize(theNodesInRadius.Size() + 1);

	Try_Exception_Handle_Exit(theNodesInRadius.Last() = Node);

	theInfo_.SetAppendedCondition(Standard_True);
}

inline 
void AutLib::MeshLib::Mesh3d_BasicAft::CalcQuality
(
	const TColMesh3d_HAry1dOfNode & theNodes, 
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
void AutLib::MeshLib::Mesh3d_BasicAft::SortNodes(TColMesh3d_HAry1dOfNode & NodesInRadius) const
{
	TColStd_Ary1dOfReal Quality;

	TColMesh3d_HAry1dOfNode Nodes = NodesInRadius;

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
void AutLib::MeshLib::Mesh3d_BasicAft::RemoveCurrentFromFront()
{
	Debug_Null_Pointer(theInfo_.Current());

	Get_Object(Current) = *theInfo_.Current();

	Debug_Null_Pointer(Mesh3d_Volume::CurrentMesh());
	Get_Object(theMesh) = *Mesh3d_Volume::CurrentMesh();

	//! deAttach the current from fronts
	theMesh.deAttachFromFront(&Current);

	//! Remove the current from fronts
	theMesh.RemoveFromFronts(&Current);
}

inline
void AutLib::MeshLib::Mesh3d_BasicAft::CalcElementSize()
{
	Debug_Null_Pointer(theInfo_.Current());

	Try_Exception_Handle_Exit(theInfo_.SetElementSize(theMap_.ElementSize(*theInfo_.Current())*0.866025404));
}

inline 
void AutLib::MeshLib::Mesh3d_BasicAft::CalcOptimumPoint()
{
	Debug_Null_Pointer(theInfo_.Current());

	theInfo_.SetCoord(theMap_.CalcOptimumCoord(theInfo_.ElementSize(), *theInfo_.Current()));
}

inline 
void AutLib::MeshLib::Mesh3d_BasicAft::CalcSearchRadius()
{
	Debug_Null_Pointer(theInfo_.Current());

	Get_Const_Object(Current) = *theInfo_.Current();

	Debug_Null_Pointer(Current.Node0());
	Debug_Null_Pointer(Current.Node1());
	Debug_Null_Pointer(Current.Node2());

	Standard_Real MaxL = 0;
	forThose
	(
		Index,
		0,
		2
	)
	{
		Standard_Real L = theMap_.CalcDistance(theInfo_.Coord(), Current.Node(Index)->Coord());
		if (L > MaxL) MaxL = L;
	}

	MaxL = MAX(MaxL, theInfo_.ElementSize() / 0.866025);

	Try_Exception_Handle_Exit(theInfo_.SetSearchingRadius(MAX(MaxL, Current.MaxRadius())));
}

inline 
void AutLib::MeshLib::Mesh3d_BasicAft::SetDepthSearching()
{
	if (theInfo_.Type() == Mesh3d_Aft_Generation)
	{
		//theInfo_.SetSearchingRadius(0.95*MAX(theMap_.CalcDistance(theInfo_.Coord(), theInfo_.Current()->Centre()), theInfo_.ElementSize()));
		Standard_Real L = MAX(theMap_.CalcDistance(theInfo_.Coord(), theInfo_.Current()->Centre()), theInfo_.ElementSize());
		theInfo_.SetSearchingRadiusLevel1(0.95*L);
		theInfo_.SetSearchingRadiusLevel2(1.05*L);
	}
	else
	{
		//theInfo_.SetSearchingRadius(MIN((1.0 + theMaxGradation_)*(theMap_.CalcDistance(theInfo_.Coord(), theInfo_.Current()->Centre()), theInfo_.ElementSize()), theInfo_.SearchRadius()));
		Standard_Real L = MIN((1.0 + theMaxGradation_)*(theMap_.CalcDistance(theInfo_.Coord(), theInfo_.Current()->Centre()), theInfo_.ElementSize()), theInfo_.SearchRadius());
		theInfo_.SetSearchingRadiusLevel1(L);
		theInfo_.SetSearchingRadiusLevel2(L);
	}

	// else: no changing is made in depth of searching radius
}

inline 
void AutLib::MeshLib::Mesh3d_BasicAft::CreateElement()
{
	Debug_Null_Pointer(Mesh3d_Volume::CurrentMesh());
	Get_Object(theMesh) = *Mesh3d_Volume::CurrentMesh();

	theMesh.NbElements()++;
	Global_Handle(Mesh3d_Element) theElement = new Mesh3d_Element(theMesh.NbElements());

	Debug_Null_Pointer(theElement);
	Get_Object(Element) = *theElement;

	Debug_Null_Pointer(theInfo_.Current());
	Get_Const_Object(Current) = *theInfo_.Current();

	Element.SetNode(0, Current.Node0());
	Element.SetNode(1, Current.Node1());
	Element.SetNode(2, Current.Node2());
	Element.SetNode(3, theInfo_.ValidNode());

	Element.SetEdge(0, Current.Edge0());
	Element.SetEdge(1, Current.Edge1());
	Element.SetEdge(2, Current.Edge2());
	
	if (theInfo_.IsCreatedEdge3()) { Element.SetEdge(3, theInfo_.CreatedEdge3()); }
	else { Element.SetEdge(3, theInfo_.PairedEdge3()); }

	if (theInfo_.IsCreatedEdge4()) { Element.SetEdge(4, theInfo_.CreatedEdge4()); }
	else { Element.SetEdge(4, theInfo_.PairedEdge4()); }

	if (theInfo_.IsCreatedEdge5()) { Element.SetEdge(5, theInfo_.CreatedEdge5()); }
	else { Element.SetEdge(5, theInfo_.PairedEdge5()); }

	if (theInfo_.IsCreatedFacet0()) { Element.SetFacet(0, theInfo_.CreatedFacet0()); }
	else { Element.SetFacet(0, theInfo_.PairedFacet0()); }

	if (theInfo_.IsCreatedFacet1()) { Element.SetFacet(1, theInfo_.CreatedFacet1()); }
	else { Element.SetFacet(1, theInfo_.PairedFacet1()); }

	if (theInfo_.IsCreatedFacet2()) { Element.SetFacet(2, theInfo_.CreatedFacet2()); }
	else { Element.SetFacet(2, theInfo_.PairedFacet2()); }

	Element.SetFacet(3, theInfo_.Current());

	theInfo_.SetCreatedElement(theElement);
}

inline
void AutLib::MeshLib::Mesh3d_BasicAft::Reject(Mesh3d_Facet & theFacet)
{
	if (theFacet.IsCavity()) { THROW_STANDARD_EXCEPTION("Failed to Reject facet"); }

	theFacet.SetAsCavity();

	Debug_Null_Pointer(CurrentMesh());
	Get_Object(theCurrentMesh) = *CurrentMesh();

	Try_Exception_Handle_Exit(theCurrentMesh.AttachToFront(&theFacet));
	Try_Exception_Handle_Exit(theCurrentMesh.InsertToFronts(&theFacet));

	Try_Exception_Handle_Exit(theCavity_.InsertToUnCertainty(&theFacet));
}

inline 
void AutLib::MeshLib::Mesh3d_BasicAft::CalcGeometryOf(Mesh3d_Facet & theFacet)
{
	Debug_Null_Pointer(theFacet.Node0());
	Debug_Null_Pointer(theFacet.Node1());
	Debug_Null_Pointer(theFacet.Node2());

	Get_Const_Object(P0) = theFacet.Node0()->Coord();
	Get_Const_Object(P1) = theFacet.Node1()->Coord();
	Get_Const_Object(P2) = theFacet.Node2()->Coord();

	theFacet.SetArea(theMap_.CalcArea(P0, P1, P2));
	theFacet.SetCentre((P0 + P1 + P2) / 3.0);

	Debug_Null_Pointer(theFacet.Edge0());
	Debug_Null_Pointer(theFacet.Edge1());
	Debug_Null_Pointer(theFacet.Edge2());

	theFacet.SetLength(MAX(theFacet.Edge0()->Length(), MAX(theFacet.Edge1()->Length(), theFacet.Edge2()->Length())));
}

inline
void AutLib::MeshLib::Mesh3d_BasicAft::UpdateFront()
{
	Global_Handle(Mesh3d_Node) ValidNode = theInfo_.ValidNode();
	Debug_Null_Pointer(ValidNode);

	Debug_Null_Pointer(CurrentMesh());
	Get_Object(theMesh) = *CurrentMesh();

	theInfo_.SetCondition(Mesh3d_PointCondition::Mesh3d_PickedUp);

	// check for updating the nodes tree
	if (ValidNode->Index() EQUAL NbNodes() + 1)
	{
		theMesh.NbNodes()++;
		
		theInfo_.SetCondition(Mesh3d_PointCondition::Mesh3d_NewPoint);

		// insert the new node into the NODES TREE
		theMesh.InsertToMesh(ValidNode);
		theMesh.InsertToFronts(ValidNode);

		theSearch_.Insert(ValidNode);
	}

	SetPairedEdges();

	SetPairedFacets();

	UpdateEdges();

	Try_Exception_Handle_Exit(UpdateFacets());

	CreateElement();

	UpdateElement();

	// remove non-GF nodes from the ADT
	Debug_Null_Pointer(theInfo_.CreatedElement());
	Get_Object(theElement) = *theInfo_.CreatedElement();

	forThose
	(
		Index,
		0,
		5
	)
	{
		Debug_Null_Pointer(theElement.Edge(Index));

		if (theElement.Edge(Index)->IsFrontFacetsEmpty())
		{
			Get_Object(Edge) = *theElement.Edge(Index);

			Try_Exception_Handle_Exit(Edge.Node0()->RemoveFromFronts(&Edge));
			Try_Exception_Handle_Exit(Edge.Node1()->RemoveFromFronts(&Edge));
		}
	}

	forThose
	(
		Index,
		0,
		3
	)
	{
		Debug_Null_Pointer(theElement.Node(Index));

		if (theElement.Node(Index)->IsFrontFacetsEmpty()) 
		{ 
			Try_Exception_Handle_Exit(theMesh.RemoveFromFronts(theElement.Node(Index)));

			theSearch_.Remove(theElement.Node(Index));
		}
	}
}

inline 
void AutLib::MeshLib::Mesh3d_BasicAft::Update()
{
	if (theInfo_.ValidNode())
	{
		Try_Exception_Handle_Exit(UpdateFront());

		if (theInfo_.IsAppended())
		{
			if (theInfo_.ValidNode() NOT_EQUAL theInfo_.CreatedNode())
				Delete_Pointer(theInfo_.CreatedNode());
		}
		
		Try_Exception_Handle_Exit(InsertNewFacetsToLevels());
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
void AutLib::MeshLib::Mesh3d_BasicAft::InsertNewFacetsToLevels()
{
	Global_Handle(Mesh3d_Facet) Facet = theInfo_.CreatedFacet0();
	if (Facet)
	{
		if (theFront_.IsOnLevel(*Facet))
		{
			theFront_.InsertToCurrentLevel(Facet);
		}
		else
		{
			theFront_.InsertToNextLevel(Facet);
		}
	}

	Facet = theInfo_.CreatedFacet1();
	if (Facet)
	{
		if (theFront_.IsOnLevel(*Facet))
		{
			theFront_.InsertToCurrentLevel(Facet);
		}
		else
		{
			theFront_.InsertToNextLevel(Facet);
		}
	}

	Facet = theInfo_.CreatedFacet2();
	if (Facet)
	{
		if (theFront_.IsOnLevel(*Facet))
		{
			theFront_.InsertToCurrentLevel(Facet);
		}
		else
		{
			theFront_.InsertToNextLevel(Facet);
		}
	}
}

inline 
void AutLib::MeshLib::Mesh3d_BasicAft::UpdateMaxLength
(
	const Standard_Real theLength,
	Mesh3d_Edge & theEdge
)
{
	theEdge.Node0()->SetMaxAdjLength(MAX(theLength, theEdge.Node0()->MaxAdjLength()));
	theEdge.Node1()->SetMaxAdjLength(MAX(theLength, theEdge.Node1()->MaxAdjLength()));
}