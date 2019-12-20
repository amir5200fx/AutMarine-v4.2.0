#include <Mesh2d_BasicAft.hxx>

#include <Time.hxx>
#include <Entity_Box2dTools.hxx>
#include <Entity_StaticChain2d.hxx>
#include <Geometry_Tools.hxx>
#include <Geometry_Intersect.hxx>
#include <Mesh2d_BoundaryNode.hxx>
#include <Mesh2d_BoundaryEdge.hxx>
#include <Mesh2d_NodeTools.hxx>
#include <Mesh2d_DegenBoundaryNode.hxx>
#include <Mesh2d_Domain.hxx>
#include <Mesh2d_SafeFront.hxx>
#include <Mesh2d_FastFront.hxx>
#include <TColCad2d_HAry1dOfPlane.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace MeshLib;

static const Standard_Real DEAFULT_PaintingFactor = 1.05;
static const Standard_Integer MaxLevel = 1500;
static Standard_Real DEFAULT_MACHINE_ZERO;

#define GET_DOMAIN_NAME theDomainName_

#define Get_Current_Mesh(MESH) Get_Object(MESH) = *Mesh2d_Plane::CurrentMesh()
#define Get_Current_Const_Mesh(MESH) Get_Const_Object(MESH) = *Mesh2d_Plane::CurrentMesh()

static Mesh2d_SafeFront Default_SafeFront;
static Mesh2d_FastFront Default_FastFront;

AutLib::MeshLib::Mesh2d_BasicAft::Mesh2d_BasicAft
(
	const Mesh2d_SizeMap & Map,
	Global_Handle(TColMesh2d_GeomSearchOfNode) SearchEngine
)
	: Mesh2d_Plane()
	, theMap_(Map)
	, theBoundaryMap_(Map)
	, theSearch_(*SearchEngine)
	, theVerbosity_(0)
	, theDomainName_(" Unknown")
	, theFront_(Default_SafeFront)
{
	theALLOWED_MAX_LEVEL_ = MaxLevel;
	DEFAULT_MACHINE_ZERO = Geometry_Tools::MachineEpsilon();
}

AutLib::MeshLib::Mesh2d_BasicAft::Mesh2d_BasicAft
(
	const Mesh2d_SizeMap & Map,
	const Mesh2d_SizeMap & BoundaryMap,
	Global_Handle(TColMesh2d_GeomSearchOfNode) SearchEngine
)
	: Mesh2d_Plane()
	, theMap_(Map)
	, theBoundaryMap_(BoundaryMap)
	, theSearch_(*SearchEngine)
	, theVerbosity_(0)
	, theDomainName_(" Unknown")
	, theFront_(Default_SafeFront)
{
	theALLOWED_MAX_LEVEL_ = MaxLevel;
	DEFAULT_MACHINE_ZERO = Geometry_Tools::MachineEpsilon();
}

AutLib::MeshLib::Mesh2d_BasicAft::~Mesh2d_BasicAft()
{
}

const TColMesh2d_HAry1dOfEdge & AutLib::MeshLib::Mesh2d_BasicAft::Boundary() const
{
	return theBoundary_;
}

TColMesh2d_HAry1dOfEdge & AutLib::MeshLib::Mesh2d_BasicAft::Boundary()
{
	return theBoundary_;
}

Standard_Integer AutLib::MeshLib::Mesh2d_BasicAft::NbRegions() const
{
	return theShapes_.Size();
}

Standard_Boolean AutLib::MeshLib::Mesh2d_BasicAft::IsDone() const
{
	return IsDone_;
}

void AutLib::MeshLib::Mesh2d_BasicAft::SetVerbosity(const Standard_Integer Verbose)
{
	theVerbosity_ = Verbose;
}

void AutLib::MeshLib::Mesh2d_BasicAft::SetDomainName(const Standard_String Name)
{
	theDomainName_ = Name;
}

void AutLib::MeshLib::Mesh2d_BasicAft::Import(const M_CAD Cad2d_Plane & thePlane)
{
	theShapes_.EnQueue((Global_Handle(M_CAD Cad2d_Plane))&thePlane);
}

void AutLib::MeshLib::Mesh2d_BasicAft::Perform()
{
	SetConfig();

	//Geometry_Tools::InitExact(DEFAULT_MACHINE_ZERO);
	if (DEFAULT_MACHINE_ZERO EQUAL 0) { THROW_STANDARD_EXCEPTION("exactinit(1) is not performed"); }

	Standard_Integer nbRegions = NbRegions();
	Standard_Integer Region;

	IsDone_ = Standard_True;

	if (NOT nbRegions)
	{
		THROW_STANDARD_EXCEPTION(" There is no Region to be Meshed");
	}

	Mesh2d_Plane::AllocateMemory(nbRegions);

	TColCad2d_HAry1dOfPlane Shapes;
	theShapes_.RetrieveTo(Shapes);

	forThose
	(
		Index,
		0,
		nbRegions - 1
	)
	{
		Region = Index;

		//Get_Object(Mesh) = *Meshes_[Region];
		Get_Object(Domain) = Mesh2d_Plane::Domain(Region);

		Domain.SetPlane(Shapes[Region]);
		Domain.SetSizeMap(theBoundaryMap_);

		Try_Exception_Handle_Exit(Domain.Perform());

		if (NOT Domain.IsDone())
		{
			THROW_STANDARD_EXCEPTION(" Boundary Region Is NOT discretized");
		}

		Mesh2d_Plane::SetCurrent(Region);

		Import(Domain.Merged());

		MeshGeneration();
	}
}

void AutLib::MeshLib::Mesh2d_BasicAft::Perform(const M_GEO Entity_StaticChain2d & Shape)
{
	SetConfig();

	IsDone_ = Standard_True;

	Standard_Integer nbRegions = 1;

	Mesh2d_Plane::AllocateMemory(nbRegions);
	Mesh2d_Plane::SetCurrent(0);

	Import(Shape);

	if (theVerbosity_)
	{
		cout << "  The domain is imported successfully!" << endl;
	}

	MeshGeneration();
}

void AutLib::MeshLib::Mesh2d_BasicAft::Perform(const TColMesh2d_HAry1dOfEdge & theEdges)
{
	SetConfig();

	IsDone_ = Standard_True;

	Standard_Integer nbRegions = 1;

	Mesh2d_Plane::AllocateMemory(nbRegions);
	Mesh2d_Plane::SetCurrent(0);

	Import(theEdges);

	if (theVerbosity_)
	{
		cout << "  The domain is imported successfully!" << endl;
	}

	MeshGeneration();
}

void AutLib::MeshLib::Mesh2d_BasicAft::ExportQualityToPlt(fstream & File) const
{
	Mesh2d_Plane::ExportQualityToPlt(File, theMap_);
}

void AutLib::MeshLib::Mesh2d_BasicAft::ReportQualityTo(Standard_OStream& Ostream) const
{
	Mesh2d_Plane::ReportQualityTo(Ostream, theMap_);
}

Standard_Integer AutLib::MeshLib::Mesh2d_BasicAft::MeshGeneration()
{
	if (theFront_.IsFrontEmpty())
	{
		THROW_BAD_BOUNDARY_EXCEPTION(" Front is empty");
	}

	Get_Current_Const_Mesh(Mesh);

	theFront_.SetLevelNumber(0);
	theFront_.SetLevelMaxIndex(Mesh.NbNodes());

	const Standard_Real StartTime = (Standard_Real)getCPUTime();

	while (NOT theFront_.IsFrontEmpty())
	{

		Try_Exception_Handle_Exit(MeshingOneLevel());

		if (IsSameLevelSupply())
		{
			theInfo_.SetType(Mesh2d_Aft_Generation);

			continue;
		}

		if (IsCavityRemoverSupply())
		{
			theInfo_.SetType(Mesh2d_Aft_Rapair);

			continue;
		}

		theFront_.SetLevelNumber(theFront_.LevelNumber() + 1);

		if (theFront_.LevelNumber() >= theALLOWED_MAX_LEVEL_)
			return 1;

		if (IsNextLevelSupply())
		{
			theInfo_.SetType(Mesh2d_Aft_Generation);
		}
	}

	const Standard_Real EndTime = (Standard_Real)getCPUTime();

	if (theVerbosity_)
	{
		cout << "\n\n";
		cout << "  Meshing Process has been done!\n\n";

		cout << "  Nb. of Elements = " << Mesh.NbElements() << endl;
		cout << "  Nb. of Nodes = " << Mesh.NbNodes() << endl;
		cout << endl;
		cout << "  CPU time used = " << (EndTime - StartTime) << " sec\n";
		cout << "  SPEED = " << Mesh.NbElements() / (EndTime - StartTime) * 60.0 << " ELMs/ min\n";
		cout << "  SPEED = " << Mesh.NbElements() / (EndTime - StartTime) << " ELMs/ sec\n\n";
	}

	if (LaplacianSmoothing().beApply()) { LaplacianSmoothing(&Mesh2d_BasicAft::CalcUnitDistance, theMap_, (theVerbosity_ ? Standard_True : Standard_False)); }

	return 0;
}

Standard_Boolean AutLib::MeshLib::Mesh2d_BasicAft::CheckCcwOrder(const TColMesh2d_HAry1dOfNode& theNodes) const
{
	TColGeom_Ary1dOfPnt2d Coords = Mesh2d_NodeTools::GetCoordOf(theNodes);
	return NOT Geometry_Tools::IsCcwOrder(Coords);
}

Standard_Boolean AutLib::MeshLib::Mesh2d_BasicAft::CheckSelfIntersection() const
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(theBoundary_)
	)
	{
		Debug_Null_Pointer(theBoundary_[Index]);

		Get_Const_Object(Edge) = *theBoundary_[Index];

		Standard_Real Radius = 1.05*Edge.MaxAdjastedLength();
		Get_Const_Object(Centre) = Edge.Centre();

		TColMesh2d_HAry1dOfNode Nodes;
		theSearch_.Search(Entity_Box2d(Centre.X() - Radius, Centre.X() + Radius, Centre.Y() - Radius, Centre.Y() + Radius), Nodes);

		TColMesh2d_HAry1dOfEdge Edges;
		Mesh2d_BasicAft::RetrieveLocalEdges(Nodes, Edges);

		forThose
		(
			I,
			0, 
			MaxIndexOf(Edges)
		)
		{
			Debug_Null_Pointer(Edges[I]);

			if (Mesh2d_EdgeTools::IsIntersect(Edge, *Edges[I])) { return Standard_True; }
		}
	}

	return Standard_False;
}

void AutLib::MeshLib::Mesh2d_BasicAft::SetConfig()
{
	switch (theConfig_.FrontType())
	{
	case Mesh2d_FrontType_FAST: theFront_ = Default_FastFront; break;
	case Mesh2d_FrontType_SAFE: theFront_ = Default_SafeFront; break;
	default: THROW_STANDARD_EXCEPTION("Invalid Front Type");
	}
}

void AutLib::MeshLib::Mesh2d_BasicAft::Import(const M_GEO Entity_StaticChain2d & theFront)
{
	CurrentMesh() = new Mesh2d_TMesh;

	Debug_Null_Pointer(CurrentMesh());

	Get_Current_Mesh(Mesh);

	Mesh.NbNodes() = theFront.NbPoints();
	Mesh.NbElements() = 0;
	Mesh.NbEdges() = theFront.NbEdges();

	CreateBoundary(theFront);
	
	RemoveDegeneracy(1.0E-8);  // bug fixed: Friday, April, 13, 2018 - Set Degeneracy criteria to 1.0E-8

	ActiveFront();

	Get_Const_Object(Nodes) = Mesh2d_EdgeTools::RetrieveNodesFrom(theBoundary_);

	/*Compute MIN and Max coords for X and Y
	Compute MAX overall dimension*/

	// Set Searching Region
	theSearch_.SetRegion(theFront.BoundingBox().OffsetBox(EPS6));

	// insert nodes into the ADtree
	theSearch_.Insert(Nodes);

	// Insert To Front
	Try_Exception_Handle_Exit(theFront_.InsertToFronts(theBoundary_));

	// Insert To Mesh
	Try_Exception_Handle_Exit(Mesh.InsertToMesh(Nodes));
	Try_Exception_Handle_Exit(Mesh.InsertToFronts(Nodes));
	Try_Exception_Handle_Exit(Mesh.InsertToMesh(theBoundary_));

	// Checking for boundary self intersection
	if (CheckSelfIntersection()) { THROW_BAD_BOUNDARY_EXCEPTION(" Boundary self intersection has been detected!"); }

	// Checking for degeneracy of the surface
	if (theBoundary_.Size() == 2) { THROW_BAD_BOUNDARY_EXCEPTION(" Degenerated Face"); }

	// Checking for polygon order
	if (CheckCcwOrder(Nodes)) { THROW_BAD_BOUNDARY_EXCEPTION(" Polygon CW order: Probably due to the size map"); }

	theDimension_ = theSearch_.BoundingBox().Diameter();
}

void AutLib::MeshLib::Mesh2d_BasicAft::Import(const TColMesh2d_HAry1dOfEdge & theFront)
{
	CurrentMesh() = new Mesh2d_TMesh;

	Debug_Null_Pointer(CurrentMesh());

	Get_Current_Mesh(Mesh);

	CreateBoundary(theFront);

	RemoveDegeneracy(1.0E-8);  // bug fixed: Friday, April, 13, 2018 - Set Degeneracy criteria to 1.0E-8
	
	ActiveFront();

	Get_Const_Object(Nodes) = Mesh2d_EdgeTools::RetrieveNodesFrom(theBoundary_);

	Mesh.NbNodes() = Nodes.Size();
	Mesh.NbElements() = 0;
	Mesh.NbEdges() = theBoundary_.Size();

	/*Compute MIN and Max coords for X and Y
	Compute MAX overall dimension*/

	// Set Searching Region
	theSearch_.SetRegion(Entity_Box2dTools::BoxOf(Mesh2d_NodeTools::GetCoordOf(Nodes), EPS6));

	// insert nodes into the ADtree
	theSearch_.Insert(Nodes);

	// Insert To Front
	Try_Exception_Handle_Exit(theFront_.InsertToFronts(theBoundary_));

	// Insert To Mesh
	Try_Exception_Handle_Exit(Mesh.InsertToMesh(Nodes));
	Try_Exception_Handle_Exit(Mesh.InsertToFronts(Nodes));
	Try_Exception_Handle_Exit(Mesh.InsertToMesh(theBoundary_));

	// Checking for boundary self intersection
	if (CheckSelfIntersection()) { THROW_BAD_BOUNDARY_EXCEPTION(" Boundary self intersection has been detected!"); }

	// Checking for degeneracy of the surface
	if (theBoundary_.Size() == 2) { THROW_BAD_BOUNDARY_EXCEPTION(" Degenerated Face"); }

	// Checking for polygon order
	if (CheckCcwOrder(Nodes)) { THROW_BAD_BOUNDARY_EXCEPTION(" Polygon CW order: Probably due to the size map"); }

	theDimension_ = theSearch_.BoundingBox().Diameter();
}

void AutLib::MeshLib::Mesh2d_BasicAft::CreateBoundary(const M_GEO Entity_StaticChain2d & theFront)
{
	TColMesh2d_HAry1dOfNode Nodes(theFront.NbPoints());

	Get_Const_Object(Coords) = theFront.Coords();
	Get_Const_Object(Edges) = theFront.Edges();

	forThose
	(
		Index,
		0,
		MaxIndexOf(Nodes)
	)
	{
		Nodes[Index] =
			new Mesh2d_BoundaryNode
			(
				Index + 1,
				Coords[Index]
			);
	}

	theBoundary_.Resize(theFront.NbEdges());

	forThose
	(
		Index,
		0,
		MaxIndexOf(theBoundary_)
	)
	{
		Get_Object(Node0) = *Nodes[Index_Of(Edges[Index].V0())];
		Get_Object(Node1) = *Nodes[Index_Of(Edges[Index].V1())];

		//Geom_Pnt2d Pm = MEAN(Node0.Coord(), Node1.Coord());

		theBoundary_[Index] =
			new Mesh2d_BoundaryEdge
			(
				Index + 1,
				theBoundaryMap_.CalcDistance(Node0.Coord(), Node1.Coord()),
				theMap_.CalcCentreOf(Node0.Coord(), Node1.Coord()),  // Debug: 5/18/2018
				&Node0,
				&Node1
			);

		Try_Exception_Handle_Exit(Node0.InsertToEdges(theBoundary_[Index]));
		Try_Exception_Handle_Exit(Node1.InsertToEdges(theBoundary_[Index]));
	}

	// Checking for Valid boundary
	forThose
	(
		Index,
		0,
		MaxIndexOf(theBoundary_)
	)
	{
		Get_Const_Object(Node0) = *Nodes[Index_Of(Edges[Index].V0())];
		Get_Const_Object(Node1) = *Nodes[Index_Of(Edges[Index].V1())];

		if (Node0.NbEdges() NOT_EQUAL 2) { THROW_BAD_BOUNDARY_EXCEPTION(" Invalid Boundary: The Boundary is open or have non-maifold edges"); }
		if (Node1.NbEdges() NOT_EQUAL 2) { THROW_BAD_BOUNDARY_EXCEPTION(" Invalid Boundary: The Boundary is open or have non-maifold edges"); }
	}
}

void AutLib::MeshLib::Mesh2d_BasicAft::CreateBoundary(const TColMesh2d_HAry1dOfEdge & theFront)
{
	theBoundary_ = theFront;

	// Checking for Valid boundary
	forThose
	(
		Index,
		0,
		MaxIndexOf(theBoundary_)
	)
	{
		Get_Const_Object(Node0) = *theBoundary_[Index]->Node0();
		Get_Const_Object(Node1) = *theBoundary_[Index]->Node1();

		if (Node0.NbEdges() NOT_EQUAL 2) { THROW_BAD_BOUNDARY_EXCEPTION(" Invalid Boundary: The Boundary is open or have non-maifold edges"); }
		if (Node1.NbEdges() NOT_EQUAL 2) { THROW_BAD_BOUNDARY_EXCEPTION(" Invalid Boundary: The Boundary is open or have non-maifold edges"); }
	}
}

void AutLib::MeshLib::Mesh2d_BasicAft::RemoveDegeneracy(const Standard_Real LengthCriteria)
{
	Standard_Integer Captured = 0;
	TColMesh2d_HBasicQueueOfEdge QEdges;
	forThose
	(
		Index,
		0,
		MaxIndexOf(theBoundary_)
	)
	{
		Debug_Null_Pointer(theBoundary_[Index]);

		Get_Object(Edge) = *theBoundary_[Index];

		if (Edge.Length() > LengthCriteria)
		{
			QEdges.EnQueue(&Edge);
		}
		else
		{
			//Verbose_Message(" Degeneracy has been captured\n");

			Captured++;

			// The current Edge has zero length; that must be deleted

			Debug_Null_Pointer(Edge.Node(0));
			Debug_Null_Pointer(Edge.Node(1));

			Get_Object(Node0) = *Edge.Node(0);
			Get_Object(Node1) = *Edge.Node(1);

			// Remove the Edge
			Try_Exception_Handle_Exit(Node0.RemoveFromEdges(&Edge););
			Try_Exception_Handle_Exit(Node1.RemoveFromEdges(&Edge););
			
			// Move Two end Nodes to the centre of The Edge 
			Node0.SetCoord(Edge.Centre());
			Node1.SetCoord(Edge.Centre());

			/*if (Global_DownCast(Mesh2d_DegenBoundaryNode, Edge.Node0()))
			{
				Global_DownCast(Mesh2d_DegenBoundaryNode, Edge.Node0())->SetOrigin(Edge.Centre());
			}

			if (Global_DownCast(Mesh2d_DegenBoundaryNode, Edge.Node1()))
			{
				Global_DownCast(Mesh2d_DegenBoundaryNode, Edge.Node1())->SetOrigin(Edge.Centre());
			}*/

			// Now, one of the nodes must be deleted (e.g Node 1)
			TColMesh2d_HAry1dOfEdge Edges;
			Node1.RetrieveEdgesTo(Edges);

			forThose
			(
				K,
				0,
				MaxIndexOf(Edges)
			)
			{
				Debug_Null_Pointer(Edges[K]);

				Try_Exception_Handle_Exit(Node0.InsertToEdges(Edges[K]));
				Try_Exception_Handle_Exit(Node1.RemoveFromEdges(Edges[K]));
			}

			forThose
			(
				K,
				0,
				MaxIndexOf(Edges)
			)
			{
				Debug_Null_Pointer(Edges[K]);

				if (Edges[K]->Node(0) EQUAL &Node1)
					Edges[K]->SetNode(0, &Node0);

				if (Edges[K]->Node(1) EQUAL &Node1)
					Edges[K]->SetNode(1, &Node0);
			}

			// Free memory from the removed entities

			FreePointer(Edge.Node(1));
			FreePointer(theBoundary_[Index]);
		}
	}

	if (NOT Captured)
	{
		return;
	}

	QEdges.RetrieveTo(theBoundary_);

	Get_Const_Object(Nodes) = Mesh2d_EdgeTools::RetrieveSortedNodesFrom(theBoundary_);
	
	Get_Current_Mesh(Mesh);

	Mesh.NbNodes() = Nodes.Size();
	Mesh.NbEdges() = theBoundary_.Size();

	Standard_Integer k = 0;

	// Renumbering the nodes
	forThose
	(
		Index,
		0,
		MaxIndexOf(Nodes)
	)
	{
		Nodes[Index]->SetIndex(0);
	}

	forThose
	(
		Index,
		0,
		MaxIndexOf(theBoundary_)
	)
	{
		Debug_Null_Pointer(theBoundary_[Index]);

		Get_Object(Edge) = *theBoundary_[Index];

		Debug_Null_Pointer(Edge.Node(0));
		Debug_Null_Pointer(Edge.Node(1));

		Get_Object(Node0) = *Edge.Node(0);
		Get_Object(Node1) = *Edge.Node(1);

		if (NOT Node0.Index()) Node0.SetIndex(++k);
		if (NOT Node1.Index()) Node1.SetIndex(++k);
	}

	k = 0;

	// Renumbering and recalculating of the boundaries
	forThose
	(
		Index,
		0,
		MaxIndexOf(theBoundary_)
	)
	{
		Debug_Null_Pointer(theBoundary_[Index]);

		Get_Object(Edge) = *theBoundary_[Index];

		Edge.SetIndex(++k);

		Debug_Null_Pointer(Edge.Node(0));
		Debug_Null_Pointer(Edge.Node(1));

		Get_Const_Object(Node0) = *Edge.Node(0);
		Get_Const_Object(Node1) = *Edge.Node(1);

		Get_Const_Object(Pm) = MEAN(Node0.Coord(), Node1.Coord());
		
		Edge.SetCentre(Pm);

		Edge.SetLength(theMap_.CalcDistance(Node0.Coord(), Node1.Coord()));
	}
}

void AutLib::MeshLib::Mesh2d_BasicAft::ActiveFront()
{
	forThose
	(
		Index,
		0,
		MaxIndexOf(theBoundary_)
	)
	{
		Debug_Null_Pointer(theBoundary_[Index]);

		Get_Object(Edge) = *theBoundary_[Index];

		Debug_Null_Pointer(Edge.Node(0));
		Debug_Null_Pointer(Edge.Node(1));

		Try_Exception_Handle_Exit(Edge.Node(0)->InsertToFronts(&Edge));
		Try_Exception_Handle_Exit(Edge.Node(1)->InsertToFronts(&Edge));
	}
}

void AutLib::MeshLib::Mesh2d_BasicAft::MeshingOneLevel()
{
	ModifyLocalFront(DEAFULT_PaintingFactor);

	/*fstream output;
	output.open("local front nb.txt", ios::app);*/

	TColMesh2d_HAry1dOfNode
		NodesInRadius,
		EarlyNodes;

	TColMesh2d_HAry1dOfEdge
		Effectives,
		Local;

	TColStd_Ary1dOfReal Quality;

	while (GetFront())
	{
		if (NOT IsBelongToFront())
			continue;

		// Remove the Current from front
		RemoveCurrentFromFront();

		// get desired element size from back-ground mesh
		CalcElementSize();

		// Calculate optimum corrdinate of new point
		CalcOptimumPoint();

		CalcSearchRadius();

		// Geometric search of the front
		RetrieveEarlyNodes(EarlyNodes);

		RetrieveLocalEdges(EarlyNodes, Local);

		// Set depth of searching radius
		SetDepthSearching();

		RetrieveNodesInRadius(EarlyNodes, NodesInRadius);

		RetrieveEffectiveFronts(NodesInRadius, Local, Effectives);
		//output << Local.Size() << "  " << Effectives.Size() << endl;
		if (IsValidNewPoint(Effectives))
		{
			AppendOptimumPoint(NodesInRadius);
		}

		SortNodes(NodesInRadius);

		FindValidNode(NodesInRadius, Effectives);

		Update();
	}
}

void AutLib::MeshLib::Mesh2d_BasicAft::FindValidNode
(
	const TColMesh2d_HAry1dOfNode & NodesInRadius,
	const TColMesh2d_HAry1dOfEdge & Effectives
)
{
	Debug_Null_Pointer(theInfo_.Current());

	Debug_Null_Pointer(theInfo_.Current()->Node(0));
	Debug_Null_Pointer(theInfo_.Current()->Node(1));

	Get_Const_Object(Vertex0) = *theInfo_.Current()->Node(0);
	Get_Const_Object(Vertex1) = *theInfo_.Current()->Node(1);

	Standard_Integer Vrtx0Index = Vertex0.Index();
	Standard_Integer Vrtx1Index = Vertex1.Index();

	Standard_Integer
		NodeIndex,
		Flag,
		ENodeIndex;

	TColMesh2d_HAry1dOfNode Nodes = Mesh2d_EdgeTools::RetrieveNodesFrom(Effectives);

	forThose
	(
		Index,
		0,
		MaxIndexOf(NodesInRadius)
	)
	{
		Debug_Null_Pointer(NodesInRadius[Index]);

		Get_Object(Node) = *NodesInRadius[Index];

		NodeIndex = Node.Index();

		Continue_If((NodeIndex EQUAL Vertex0.Index()) OR(NodeIndex EQUAL Vertex1.Index()));
		
		// test 1: is it the new point on the left side of iEDG
		Continue_If(Geometry_Tools::Oriented(Node.Coord(), Vertex0.Coord(), Vertex1.Coord()) <= DEFAULT_MACHINE_ZERO);

		Flag = 0;

		// test 2: intersection test
		forThose
		(
			J,
			0,
			MaxIndexOf(Effectives)
		)
		{
			Debug_Null_Pointer(Effectives[J]);

			Get_Const_Object(Ne0) = *Effectives[J]->Node(0);
			Get_Const_Object(Ne1) = *Effectives[J]->Node(1);

			if (NOT M_GEO Geometry_Tools::IsOneCommonPointTwoLineSegment(Vertex0.Index(), NodeIndex, Ne0.Index(), Ne1.Index()))
			{
				if (M_GEO Geometry_Intersect::IsIntersect(Vertex0.Coord(), Node.Coord(), Ne0.Coord(), Ne1.Coord()))
				{
					Flag = 1;
					break;
				}
			}

			if (NOT M_GEO Geometry_Tools::IsOneCommonPointTwoLineSegment(NodeIndex, Vertex1.Index(), Ne0.Index(), Ne1.Index()))
			{
				if (M_GEO Geometry_Intersect::IsIntersect(Node.Coord(), Vertex1.Coord(), Ne0.Coord(), Ne1.Coord()))
				{
					Flag = 1;
					break;
				}
			}
		}

		Continue_If(Flag);

		forThose
		(
			J,
			0,
			MaxIndexOf(Nodes)
		)
		{
			Debug_Null_Pointer(Nodes[J]);

			Get_Const_Object(ENode) = *Nodes[J];

			ENodeIndex = ENode.Index();

			if ((ENodeIndex NOT_EQUAL NodeIndex) AND(ENodeIndex NOT_EQUAL Vrtx0Index) AND(ENodeIndex NOT_EQUAL Vrtx1Index))
			{
				if (M_GEO Geometry_Tools::IsPointInsideOnTriangle(ENode.Coord(), Vertex0.Coord(), Vertex1.Coord(), Node.Coord()))
				{
					Flag = 1;

					break;
				}
			}
		}

		Continue_If(Flag);

		theInfo_.SetValidNode(&Node);

		return;
	}

	theInfo_.SetValidNode(NULL);
}

void AutLib::MeshLib::Mesh2d_BasicAft::ModifyLocalFront(const Standard_Real Factor)
{
	if (Factor < ONE)
	{
		THROW_STANDARD_EXCEPTION(" Invalid Factor");
	}

	if (theSearch_.IsEmpty())
		return;

	Get_Current_Mesh(Mesh);

	TColMesh2d_HAry1dOfNode Nodes;
	Mesh.RetrieveFrontsTo(Nodes);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Nodes)
	)
	{
		Debug_Null_Pointer(Nodes[Index]);

		Get_Object(Node) = *Nodes[Index];

		TColMesh2d_HAry1dOfEdge Edges;
		Node.RetrieveFrontsTo(Edges);

		Standard_Real MaxLength = 0.;
		forThose
		(
			J,
			0,
			MaxIndexOf(Edges)
		)
		{
			Debug_Null_Pointer(Edges[J]);

			if (Edges[J]->Length() > MaxLength)
				MaxLength = Edges[J]->Length();
		}

		MaxLength *= Factor;

		Debug_If_Condition_Message(MaxLength EQUAL 0, " Invalid MaxLength Value");

		Node.SetRadius(MAX(Node.Radius(), MaxLength));

		TColMesh2d_HAry1dOfNode theFronts;
		theSearch_.Search(theMap_.CalcSearchRegion(MaxLength, Node.Coord()), theFronts);

		TColMesh2d_HAry1dOfNode theInners;
		Mesh2d_BasicAft::NodesInRadius(MaxLength, Node.Coord(), theFronts, theInners);

		forThose
		(
			J,
			0,
			MaxIndexOf(theInners)
		)
		{
			theInners[J]->SetRadius(MAX(theInners[J]->Radius(), MaxLength));
		}
	}
}

void AutLib::MeshLib::Mesh2d_BasicAft::UpdateEdges()
{
	Get_Current_Mesh(Mesh);

	Get_Const_Object(theCurrent) = Mesh2d_BasicAft::CurrentEdge();

	Global_Handle(Mesh2d_Edge) Edge = theInfo_.PairedEdge0();

	if (Edge)
	{
		theInfo_.SetCreatedEdge0(NULL);

		// remove the old coicident face from the GF
		Try_Exception_Handle_Exit(Mesh.deAttachFromFront(Edge));
		//Try_Exception_Handle_Exit(Mesh.RemoveFromFronts(Edge));

		// remove cavity face
		if (Edge->IsCavity())
		{
			Edge->SetCavity(Standard_False);
		}
	}
	else
	{
		Mesh.NbEdges()++;

		Get_Const_Object(P1) = theInfo_.ValidNode()->Coord();
		Get_Const_Object(P2) = theCurrent.Node1()->Coord();

		Standard_Real Length = theMap_.CalcDistance(P1, P2);

		Global_Handle(Mesh2d_Edge) newEdge = new Mesh2d_Edge
		(
			NbEdges(),
			Length,
			theMap_.CalcCentreOf(P1, P2),
			theInfo_.ValidNode(),
			theCurrent.Node1()
		);

		Debug_Null_Pointer(newEdge);

		UpdateMaxLength(Length, *newEdge);

		theInfo_.SetCreatedEdge0(newEdge);

		// insert the new Face into the FACES TREE
		Mesh.AttachToFrontNodes(newEdge);
		Mesh.AttachToMeshNodes(newEdge);

		Mesh.InsertToMesh(newEdge);
	}

	Edge = theInfo_.PairedEdge1();

	if (Edge)
	{
		theInfo_.SetCreatedEdge1(NULL);

		// remove the old coicident face from the GF
		Try_Exception_Handle_Exit(Mesh.deAttachFromFront(Edge));
		//Try_Exception_Handle_Exit(Mesh.RemoveFromFronts(Edge));

		// remove cavity face
		if (Edge->IsCavity())
		{
			Edge->SetCavity(Standard_False);
		}
	}
	else
	{
		Mesh.NbEdges()++;

		Get_Const_Object(P1) = theInfo_.ValidNode()->Coord();
		Get_Const_Object(P2) = theCurrent.Node0()->Coord();

		Standard_Real Length = theMap_.CalcDistance(P1, P2);

		Global_Handle(Mesh2d_Edge) newEdge = new Mesh2d_Edge
		(
			Mesh.NbEdges(),
			Length,
			theMap_.CalcCentreOf(P1, P2),
			theCurrent.Node0(),
			theInfo_.ValidNode()
		);

		Debug_Null_Pointer(newEdge);

		UpdateMaxLength(Length, *newEdge);

		theInfo_.SetCreatedEdge1(newEdge);

		// insert the new Face into the FACES TREE
		Mesh.AttachToFrontNodes(newEdge);
		Mesh.AttachToMeshNodes(newEdge);

		Mesh.InsertToMesh(newEdge);
	}
}

void AutLib::MeshLib::Mesh2d_BasicAft::UpdateElement()
{
	Get_Current_Mesh(Mesh);

	Global_Handle(Mesh2d_Element) theElement = theInfo_.CreatedElement();
	Debug_Null_Pointer(theElement);

	Mesh.AttachToMeshNodes(theElement);

	/* Attach the element to the edges */

	Get_Object(theCurrent) = Mesh2d_BasicAft::CurrentEdge();

	// update right/ left side element pointer of the faces
	// update adjacent elements
	theCurrent.SetLeftElement(theElement);
	theElement->SetNeighbor(2, theCurrent.RightElement());

	if (theCurrent.RightElement())
	{
		theCurrent.RightElement()->SetNeighbor(theCurrent.RightElement()->OppositeVertexIndex(theCurrent), theElement);
	}

	if (theInfo_.IsCreatedEdge0())
	{
		theInfo_.CreatedEdge0()->SetRightElement(theElement);
		theElement->SetNeighbor(0, NULL);
	}
	else
	{
		Global_Handle(Mesh2d_Edge) Edge = theInfo_.PairedEdge0();
		Debug_Null_Pointer(Edge);

		Global_Handle(Mesh2d_Element) Neighbor0 = Edge->RightElement();
		theElement->SetNeighbor(0, Neighbor0);

		if (Edge->LeftElement()) { THROW_STANDARD_EXCEPTION("Contradiction data"); }

		Edge->SetLeftElement(theElement);

		if (Neighbor0) { Neighbor0->SetNeighbor(Neighbor0->OppositeVertexIndex(*Edge), theElement); }
	}

	if (theInfo_.IsCreatedEdge1())
	{
		theInfo_.CreatedEdge1()->SetRightElement(theElement);
		theElement->SetNeighbor(1, NULL);
	}
	else
	{
		Global_Handle(Mesh2d_Edge) Edge = theInfo_.PairedEdge1();
		Debug_Null_Pointer(Edge);

		Global_Handle(Mesh2d_Element) Neighbor1 = Edge->RightElement();
		theElement->SetNeighbor(1, Neighbor1);

		if (Edge->LeftElement()) { THROW_STANDARD_EXCEPTION("Contradiction data"); }

		Edge->SetLeftElement(theElement);

		if (Neighbor1) { Neighbor1->SetNeighbor(Neighbor1->OppositeVertexIndex(*Edge), theElement); }
	}

	// updating the ELMENTS TREE
	Mesh.InsertToMesh(theElement);
}