#include <Cad3d_Solid.hxx>

#include <Entity_Box3d.hxx>
#include <Entity_StaticChain3d.hxx>
#include <Entity_Triangulation3d.hxx>
#include <Entity_Triangulation3dTools.hxx>
#include <Merge_Triangulation3d.hxx>
#include <Geometry_Tools.hxx>
#include <Cad3d_EntityOnSolid.hxx>
#include <Cad3d_SurfaceOnSolid.hxx>
#include <Cad3d_SurfaceOnSolidTools.hxx>
#include <Cad3d_BlockEntityOnSolid.hxx>
#include <Cad3d_ShellOnSolid.hxx>
#include <Cad3d_ShellOnSolidTools.hxx>
#include <Cad3d_PointOnSolid.hxx>
#include <Cad3d_EntitiesOnSolid.hxx>
#include <Cad3d_RingOnSurface.hxx>
#include <Cad3d_RingOnSurfaceTools.hxx>
#include <Cad3d_CurveOnSurface.hxx>
#include <Cad3d_EdgeOnSolid.hxx>
#include <Cad3d_CurveOnSurfaceTools.hxx>
#include <Cad3d_EdgeOnSolidTools.hxx>
#include <Cad3d_PointOnSolidTools.hxx>
#include <Cad3d_PairedOnSolid.hxx>
#include <Cad3d_BlockEntityOnSolid.hxx>
#include <Cad3d_Plane.hxx>
#include <IO_Tecplot.hxx>
#include <TColCad3d_HBasicQueueOfEdgeOnSolid.hxx>
#include <TColCad3d_HBasicQueueOfEntityOnSolid.hxx>
#include <TColCad3d_HBasicQueueOfSurfaceOnSolid.hxx>
#include <TColCad3d_HBasicQueueOfBlockEntityOnSolid.hxx>
#include <TColCad3d_HAry1dOfPointOnSolid.hxx>
#include <TColCad3d_HAry1dOfPairedOnSolid.hxx>
#include <TColEntity_HAry1dOfTriangulation3d.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

static const Standard_Real DEFAULT_RADIUS = 1.0E-6;
static const Standard_Real DEFAULT_RESOLUTION = 1.0E-3;

AutLib::CadLib::Cad3d_Solid::Cad3d_Solid()
	: theIndex_(0)
	, theName_("Unknown")
	, theOutterShell_(NULL)
	, theVertices_(NULL)
	, thePairedEdges_(NULL)
	, theSurfaces_(NULL)
{
}

AutLib::CadLib::Cad3d_Solid::~Cad3d_Solid()
{
	Clear();
}

Standard_Integer AutLib::CadLib::Cad3d_Solid::NbFreeEdges() const
{
	Standard_Integer K = 0;
	TColCad3d_HAry1dOfEntityOnSolid Edges;
	Cad3d_Solid::RetrievePairedEdgesTo(Edges);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);
		Debug_Null_Pointer(Global_DownCast(Cad3d_PairedOnSolid, Edges[Index]));

		if (NOT Global_DownCast(Cad3d_PairedOnSolid, Edges[Index])->IsPaired()) K++;
	}
	return K;
}

Standard_Boolean AutLib::CadLib::Cad3d_Solid::HasFreeEdge() const
{
	TColCad3d_HAry1dOfEntityOnSolid Edges;
	Cad3d_Solid::RetrievePairedEdgesTo(Edges);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);
		Debug_Null_Pointer(Global_DownCast(Cad3d_PairedOnSolid, Edges[Index]));

		if (NOT Global_DownCast(Cad3d_PairedOnSolid, Edges[Index])->IsPaired()) return Standard_True;
	}
	return Standard_False;
}

namespace AutLib
{
	namespace CadLib
	{
		static void GetStaticChain(const TColCad3d_HAry1dOfEdgeOnSolid& Curves, Entity_StaticChain3d& Chain)
		{
			TColGeom_Ary1dOfPnt3d Pts(2 * Curves.Size());
			TColEntity_Ary1dOfEdgeIndex Edges(Curves.Size());

			Standard_Integer IP = 0;
			forThose
			(
				Index,
				0,
				MaxIndexOf(Curves)
			)
			{
				Debug_Null_Pointer(Curves[Index]);
				Debug_Null_Pointer(Curves[Index]->CurveOnSurface());

				Get_Const_Object(Curve) = *Curves[Index]->CurveOnSurface();

				Pts.SetValue(IP, Curve.StartCoord());
				IP++;

				Pts.SetValue(IP, Curve.LastCoord());
				IP++;

				Edges.SetValue(Index, Entity_EdgeIndex(IP - 1, IP));
			}

			Chain.Init(Pts, Edges);
		}

		static void CreatePointsOnSolid(const Entity_StaticChain3d& Chain, Global_Handle(Cad3d_EntitiesOnSolid)& thePointsOnSolid, TColCad3d_HAry1dOfEntityOnSolid& Ary1dOfPts)
		{
			Get_Const_Object(Points) = Chain.Coords();

			Ary1dOfPts.Resize(Points.Size());
			forThose(Index, 0, MaxIndexOf(Ary1dOfPts))
				Ary1dOfPts[Index] = new Cad3d_PointOnSolid(Index + 1, Points[Index]);

			thePointsOnSolid = new Cad3d_EntitiesOnSolid(new Cad3d_BlockEntityOnSolid(Ary1dOfPts, "Default Block Point"), "Default Block Point");
		}

		static void Pairing(const TColCad3d_HAry1dOfEdgeOnSolid& Curves)
		{
			if (Curves.Size() < 2) THROW_STANDARD_EXCEPTION(" Invalid Solid");

			Open_OutputFile_TecPlot(Plot, "Pairing");

			TColCad3d_HNumbAvlTreeOfEdgeOnSolid Tree;
			Tree.SetComparable(&Cad3d_EdgeOnSolidTools::IsLess);

			forThose(Index, 0, MaxIndexOf(Curves))
				Try_Exception_Handle_Exit(Tree.Insert(Curves[Index]));

			Debug_If_Condition(Tree.IsEmpty());

			Global_Handle(Cad3d_EdgeOnSolid) Edge;
			Tree.Root(Edge);
			Tree.Remove(Edge);

			while (NOT Tree.IsEmpty())
			{
				Global_Handle(Cad3d_PointOnSolid) Node0 = (Global_Handle(Cad3d_PointOnSolid))Edge->StartPoint();
				Global_Handle(Cad3d_PointOnSolid) Node1 = (Global_Handle(Cad3d_PointOnSolid))Edge->LastPoint();

				Global_Handle(Cad3d_PointOnSolid) Node;
				if (Node0->NbEdges() <= Node1->NbEdges())
					Node = Node0;
				else
					Node = Node1;

				TColCad3d_HAry1dOfEdgeOnSolid Compare;
				Node->RetrieveEdgesTo(Compare);

				Standard_Integer V0 = Node0->Index();
				Standard_Integer V1 = Node1->Index();

				Global_Handle(Cad3d_RingOnSurface) Ring = Global_DownCast(Cad3d_RingOnSurface, (Global_Handle(Cad3d_CurveOnSurface))Edge->CurveOnSurface());

				if (Ring)
				{
					forThose
					(
						Index,
						0,
						MaxIndexOf(Compare)
					)
					{
						if (Compare[Index] EQUAL Edge) continue;

						Global_Handle(Cad3d_RingOnSurface) CompareRing = Global_DownCast(Cad3d_RingOnSurface, (Global_Handle(Cad3d_CurveOnSurface))Compare[Index]->CurveOnSurface());

						if (CompareRing)
						{
							if (Cad3d_RingOnSurfaceTools::AreCoincident(*Ring, *CompareRing))
							{
								Edge->SetPaired(Compare[Index]);
								Compare[Index]->SetPaired(Edge);

								Try_Exception_Handle_Exit(Tree.Remove(Compare[Index]));
							}
						}
					}
				}
				else
				{
					TColCad3d_HBasicQueueOfEdgeOnSolid QPaired;
					Geom_Pnt3d Mid = Edge->CurveOnSurface()->MidCoord();
					forThose
					(
						Index,
						0,
						MaxIndexOf(Compare)
					)
					{
						if (Compare[Index] EQUAL Edge) continue;

						if (Geometry_Tools::IsPairedTwoLineSegment(V0, V1, Compare[Index]->StartPoint()->Index(), Compare[Index]->LastPoint()->Index()))
						{
							/*Edge->SetPaired(Compare[Index]);
							Compare[Index]->SetPaired(Edge);*/

							Entity_Box3d Box = Compare[Index]->CurveOnSurface()->BoundingBox();
							Box.Expand(Box.Diameter()*1.0E-3);

							if (NOT Geometry_Tools::IsPointInsideOnBox(Mid, Box.Xmin(), Box.Xmax(), Box.Ymin(), Box.Ymax(), Box.Zmin(), Box.Zmax()))
							{
								continue;
							}

							if (Cad3d_CurveOnSurfaceTools::Distance(Mid, *Compare[Index]->CurveOnSurface()) > 1.0e-3)
							{
								continue;
							}

							QPaired.EnQueue(Compare[Index]);

							//Try_Exception_Handle_Exit(Tree.Remove(Compare[Index]));
						}
					}

					TColCad3d_HAry1dOfEdgeOnSolid PairedEdges;
					QPaired.RetrieveTo(PairedEdges);

					if (PairedEdges.Size() > 1)
					{
						forThose(Index, 0, MaxIndexOf(PairedEdges))
							PairedEdges[Index]->ExportToPlt(Plot);
					}

					if (PairedEdges.Size() EQUAL 1)
					{
						Edge->SetPaired(PairedEdges[0]);
						PairedEdges[0]->SetPaired(Edge);
					}
				}

				if (Tree.IsEmpty()) break;

				Tree.Root(Edge);
				Tree.Remove(Edge);
			}
		}

		static void Assembly(const Entity_StaticChain3d& Chain, const TColCad3d_HAry1dOfEntityOnSolid& Points, const TColCad3d_HAry1dOfEdgeOnSolid& Curves)
		{
			Get_Const_Object(Edges) = Chain.Edges();

			Debug_If_Condition(Edges.Size() NOT_EQUAL Curves.Size());

			forThose
			(
				Index,
				0,
				MaxIndexOf(Edges)
			)
			{
				Standard_Integer V0 = Edges[Index].V0();
				Standard_Integer V1 = Edges[Index].V1();

				Get_Pointer(Point0) = Global_DownCast(Cad3d_PointOnSolid, Points[Index_Of(V0)]);
				Get_Pointer(Point1) = Global_DownCast(Cad3d_PointOnSolid, Points[Index_Of(V1)]);

				Debug_Null_Pointer(Point0);
				Debug_Null_Pointer(Point1);

				Curves[Index]->SetStart(Point0);
				Curves[Index]->SetLast(Point1);

				Curves[Index]->SetIndex(Index + 1);

				if (V0 EQUAL V1)
				{
					//! For ring configuration
					Point0->InsertToEdges(Curves[Index]);
				}
				else
				{
					Point0->InsertToEdges(Curves[Index]);
					Point1->InsertToEdges(Curves[Index]);
				}
			}

			Try_Exception_Handle_Exit(Pairing(Curves));

			forThose
			(
				Index,
				0,
				MaxIndexOf(Points)
			)
			{
				Debug_Null_Pointer(Points[Index]);

				Get_Pointer(Point) = Global_DownCast(Cad3d_PointOnSolid, Points[Index]);
				Debug_Null_Pointer(Point);

				TColCad3d_HAry1dOfEdgeOnSolid EdgesAroundPoint;
				Point->RetrieveEdgesTo(EdgesAroundPoint);

				forThose(I, 0, MaxIndexOf(EdgesAroundPoint))
					Point->InsertToSurfacesIgnoreDup((Global_Handle(Cad3d_SurfaceOnSolid))EdgesAroundPoint[I]->Surface());
			}
		}

		static void CreatePairedEdges(const TColCad3d_HAry1dOfEdgeOnSolid& Curves, Global_Handle(Cad3d_EntitiesOnSolid)& PairedEdges)
		{
			TColCad3d_HNumbAvlTreeOfEdgeOnSolid Tree;
			Tree.SetComparable(&Cad3d_EdgeOnSolidTools::IsLess);

			Tree.Insert(Curves);

			TColCad3d_HBasicQueueOfEntityOnSolid QPaired;
			Global_Handle(Cad3d_EdgeOnSolid) Edge;

			Tree.Root(Edge);
			Tree.Remove(Edge);

			Standard_Integer K = 0;
			while (NOT Tree.IsEmpty())
			{
				Global_Handle(Cad3d_EdgeOnSolid) Paired = (Global_Handle(Cad3d_EdgeOnSolid))Edge->Paired();

				/*TColCad3d_HAry1dOfEdgeOnSolid Items;
				Tree.RetrieveTo(Items);*/

				if (Paired)
				{
					Try_Exception_Handle_Exit(Tree.Remove(Paired));
				}

				Global_Handle(Cad3d_PairedOnSolid) PairedOnSolid = new Cad3d_PairedOnSolid(++K, Edge, Paired);

				QPaired.EnQueue(PairedOnSolid);

				Edge->SetPairedOnSolid(PairedOnSolid);
				if (Paired) Paired->SetPairedOnSolid(PairedOnSolid);

				if (Tree.IsEmpty()) break;

				Tree.Root(Edge);
				Tree.Remove(Edge);
			}

			PairedEdges = new Cad3d_EntitiesOnSolid(new Cad3d_BlockEntityOnSolid(QPaired.Retrive(), "Default Block Edge"), "Default Block Edge");
		}

		static void MarchingOnShell(Global_Handle(Cad3d_SurfaceOnSolid) Surface, TColCad3d_HNumbAvlTreeOfSurfaceOnSolid& Tree, TColCad3d_HBasicQueueOfEntityOnSolid& QShell)
		{
			Try_Exception_Handle_Exit(Tree.Remove(Surface));

			QShell.EnQueue(Surface);

			Get_Const_Object(Edges) = Surface->Edges();
			TColCad3d_HAry1dOfEdgeOnSolid Paireds(Edges.Size());

			forThose
			(
				Index,
				0,
				MaxIndexOf(Edges)
			)
			{
				Debug_Null_Pointer(Edges[Index]);

				Paireds[Index] = (Global_Handle(Cad3d_EdgeOnSolid))Edges[Index]->Paired();
				Edges[Index]->SetPaired(NULL);
			}

			forThose
			(
				Index,
				0,
				MaxIndexOf(Paireds)
			)
			{
				Global_Handle(Cad3d_EdgeOnSolid) Paired = Paireds[Index];

				if (Paired)
				{
					if (Paired->Paired())
					{
						MarchingOnShell((Global_Handle(Cad3d_SurfaceOnSolid))Paired->Surface(), Tree, QShell);
					}
				}
			}
		}

		static void CreateSurfaces(const TColCad3d_HAry1dOfSurfaceOnSolid & theSurfaces, Global_Handle(Cad3d_EntitiesOnSolid)& BlockSurfaces)
		{
			/*TColCad3d_HNumbAvlTreeOfSurfaceOnSolid Tree;
			Tree.SetComparable(&Cad3d_SurfaceOnSolidTools::IsLess);

			forThose(Index, 0, MaxIndexOf(Surfaces))
				Try_Exception_Handle_Exit(Tree.Insert(Surfaces[Index]));

			TColCad3d_HBasicQueueOfBlockEntityOnSolid QBlocks;

			Global_Handle(Cad3d_SurfaceOnSolid) Surface(0);

			Standard_Integer K = 0;
			while (NOT Tree.IsEmpty())
			{
				Tree.Root(Surface);

				TColCad3d_HBasicQueueOfEntityOnSolid QShell;

				MarchingOnShell(Surface, Tree, QShell);

				QBlocks.EnQueue(new Cad3d_BlockEntityOnSolid(QShell.Retrive(), "Block Surface " + std::to_string(++K)));
			}

			BlockSurfaces = new Cad3d_EntitiesOnSolid(QBlocks.Retrive());*/

			TColCad3d_HAry1dOfEntityOnSolid Surfaces(theSurfaces.Size());
			forThose(Index, 0, MaxIndexOf(theSurfaces))
				Surfaces.SetValue(Index, theSurfaces[Index]);

			BlockSurfaces = new Cad3d_EntitiesOnSolid(new Cad3d_BlockEntityOnSolid(Surfaces, "Default Block Surface"), "Default Block Surface");
		}

		static void LinkEdges(Global_Handle(Cad3d_EntitiesOnSolid) PairedEdgesOnSolid)
		{
			TColCad3d_HAry1dOfEntityOnSolid Edges;
			PairedEdgesOnSolid->RetrieveTo(Edges);

			forThose
			(
				Index, 
				0, 
				MaxIndexOf(Edges)
			)
			{
				Debug_Null_Pointer(Global_DownCast(Cad3d_PairedOnSolid, Edges[Index]));

				Global_Handle(Cad3d_EdgeOnSolid) Edge0 = (Global_Handle(Cad3d_EdgeOnSolid))(Global_DownCast(Cad3d_PairedOnSolid, Edges[Index]))->Edge0();
				Global_Handle(Cad3d_EdgeOnSolid) Edge1 = (Global_Handle(Cad3d_EdgeOnSolid))(Global_DownCast(Cad3d_PairedOnSolid, Edges[Index]))->Edge1();

				Debug_Null_Pointer(Edge0);

				if (Edge1)
				{
					Edge0->SetPaired(Edge1);
					Edge1->SetPaired(Edge0);
				}
			}
		}

		Entity_Box3d CalcBoundingBox(const TColCad3d_HAry1dOfSurfaceOnSolid & Surfaces)
		{
			if (NOT Surfaces.Size()) THROW_STANDARD_EXCEPTION(" The List is empty");

			return Cad3d_SurfaceOnSolidTools::BoundingBoxOf(Surfaces);
		}
	}
}

void AutLib::CadLib::Cad3d_Solid::Make
(
	const TColCad3d_HAry1dOfSurfaceOnSolid & theSurfaces,
	const Standard_Real Tolerance
)
{
	TColCad3d_HAry1dOfEdgeOnSolid EdgesOnSolid = Cad3d_EdgeOnSolidTools::RetrieveEdgesFrom(theSurfaces);

	Entity_StaticChain3d Chain;
	::GetStaticChain(EdgesOnSolid, Chain);

	Chain.Merging(DEFAULT_RESOLUTION, Tolerance, Standard_False);

	TColCad3d_HAry1dOfEntityOnSolid PointsOnSolid;
	CreatePointsOnSolid(Chain, theVertices_, PointsOnSolid);

	Debug_Null_Pointer(theVertices_);

	Assembly(Chain, PointsOnSolid, EdgesOnSolid);

	CreatePairedEdges(EdgesOnSolid, thePairedEdges_);

	Debug_Null_Pointer(thePairedEdges_);

	CreateSurfaces(theSurfaces, theSurfaces_);

	LinkEdges(thePairedEdges_);

	theBoundingBox_ = CalcBoundingBox(theSurfaces);

	if (Cad3d_Solid::CreateShells(theSurfaces))
	{
		Cad3d_Solid::SplitByShells();
	}
}

void AutLib::CadLib::Cad3d_Solid::SetName(const Standard_String Name)
{
	theName_ = Name;
}

void AutLib::CadLib::Cad3d_Solid::RetrieveVerticesTo(TColCad3d_HAry1dOfPointOnSolid & theVertices) const
{
	TColCad3d_HAry1dOfEntityOnSolid Points;
	RetrieveVerticesTo(Points);

	theVertices.Resize(Points.Size());
	forThose(Index, 0, MaxIndexOf(Points))
		theVertices.SetValue(Index, Global_DownCast(Cad3d_PointOnSolid, Points.Value(Index)));
}

void AutLib::CadLib::Cad3d_Solid::RetrieveFreeEdgesTo(TColCad3d_HAry1dOfEntityOnSolid& theFreeEdges) const
{
	TColCad3d_HAry1dOfEntityOnSolid Edges;
	RetrievePairedEdgesTo(Edges);

	TColCad3d_HBasicQueueOfEntityOnSolid QEdges;
	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		Global_Handle(Cad3d_PairedOnSolid) Paired = Global_DownCast(Cad3d_PairedOnSolid, Edges.Value(Index));
		if (NOT Paired) { THROW_STANDARD_EXCEPTION("Invalid Data"); }
		if (NOT Paired->IsPaired()) QEdges.EnQueue(Paired);
	}
	QEdges.RetrieveTo(theFreeEdges);
}

void AutLib::CadLib::Cad3d_Solid::RetrieveFreeEdgesTo(TColCad3d_HAry1dOfPairedOnSolid & theFreeEdges) const
{
	TColCad3d_HAry1dOfEntityOnSolid Edges;
	RetrieveFreeEdgesTo(Edges);

	theFreeEdges.Resize(Edges.Size());
	forThose(Index, 0, MaxIndexOf(Edges))
		theFreeEdges.SetValue(Index, Global_DownCast(Cad3d_PairedOnSolid, Edges.Value(Index)));
}

void AutLib::CadLib::Cad3d_Solid::RetrieveSurfacesTo(TColCad3d_HAry1dOfSurfaceOnSolid & theSurfaces) const
{
	TColCad3d_HAry1dOfEntityOnSolid Surfaces;
	RetrieveSurfacesTo(Surfaces);

	theSurfaces.Resize(Surfaces.Size());
	forThose(Index, 0, MaxIndexOf(Surfaces))
		theSurfaces.SetValue(Index, Global_DownCast(Cad3d_SurfaceOnSolid, Surfaces.Value(Index)));
}

void AutLib::CadLib::Cad3d_Solid::SplitByShells()
{
	if (theSurfaces_->NbBlocks() > 1)
	{
		theSurfaces_->CompactBlocks("Default Block Surface");
	}

	if (theSurfaces_->NbBlocks() NOT_EQUAL 1) { THROW_STANDARD_EXCEPTION("Invalid Data"); }

	if (theInnerShells_.IsEmpty()) { return; }

	TColCad3d_HAry1dOfBlockEntityOnSolid Blocks;
	theSurfaces_->RetrieveTo(Blocks);

	Debug_If_Condition_Message(Blocks.Size() NOT_EQUAL 1, "Conflict Data");
	Get_Const_Object(Block) = theSurfaces_->SelectBlockEntity(Blocks[0]->Name());

	forThose
	(
		Index,
		0, 
		MaxIndexOf(theInnerShells_)
	)
	{
		Debug_Null_Pointer(theInnerShells_[Index]);

		Get_Const_Object(Surfaces) = theInnerShells_[Index]->Surfaces();
		forThose
		(
			I,
			0,
			MaxIndexOf(Surfaces)
		)
		{
			Debug_Null_Pointer(Surfaces[I]);
			Block->SelectEntity(Surfaces[I]->Index());
		}
		theSurfaces_->Split("Default Inner Shell " + std::to_string(Index + 1));
	}

	if (NOT Block->Size()) { THROW_STANDARD_EXCEPTION("Conflict Data"); }
}

void AutLib::CadLib::Cad3d_Solid::Clear()
{
	FreePointer(theVertices_);
	FreePointer(thePairedEdges_);
	FreePointer(theSurfaces_);

	FreeMemory(theInnerShells_);
	FreePointer(theOutterShell_);
}

void AutLib::CadLib::Cad3d_Solid::ExportToPlt(fstream & File) const
{
	ExportPointsToPlt(File);

	ExportCurvesToPlt(File);

	ExportSurfacesToPlt(File);
}

void AutLib::CadLib::Cad3d_Solid::ExportPointsToPlt(fstream & File) const
{
	if (NOT theVertices_) return;

	TColCad3d_HAry1dOfEntityOnSolid Entities;
	theVertices_->RetrieveTo(Entities);

	TColCad3d_HAry1dOfPointOnSolid Points(Entities.Size());
	forThose(Index, 0, MaxIndexOf(Entities))
		Points.SetValue(Index, Global_DownCast(Cad3d_PointOnSolid, Entities.Value(Index)));

	M_IO IO_TecPlot::ExportPoints(Cad3d_PointOnSolidTools::GetStaticCoordsOf(Points), File);
}

void AutLib::CadLib::Cad3d_Solid::ExportPlanesToPlt(fstream & File) const
{
	if (NOT theSurfaces_) return;

	TColCad3d_HAry1dOfEntityOnSolid Surfaces;
	theSurfaces_->RetrieveTo(Surfaces);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Surfaces)
	)
	{
		Debug_Null_Pointer(Surfaces[Index]);
		Debug_Null_Pointer(Global_DownCast(Cad3d_SurfaceOnSolid, Surfaces[Index]));

		Get_Const_Pointer(Surface) = Global_DownCast(Cad3d_SurfaceOnSolid, Surfaces[Index]);

		Debug_Null_Pointer(Surface->Plane());

		Surface->Plane()->ExportToPlt(File);
	}
}

void AutLib::CadLib::Cad3d_Solid::ExportParametricCurvesToPlt(fstream & File) const
{
	if (NOT theSurfaces_) return;

	TColCad3d_HAry1dOfEntityOnSolid Surfaces;
	theSurfaces_->RetrieveTo(Surfaces);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Surfaces)
	)
	{
		Debug_Null_Pointer(Surfaces[Index]);
		Debug_Null_Pointer(Global_DownCast(Cad3d_SurfaceOnSolid, Surfaces[Index]));

		Get_Const_Pointer(Surface) = Global_DownCast(Cad3d_SurfaceOnSolid, Surfaces[Index]);

		Surface->ExportParametricCurvesToPlt(File);
	}
}

void AutLib::CadLib::Cad3d_Solid::ExportParametricWiresToPlt(fstream & File) const
{
	if (NOT theSurfaces_) return;

	TColCad3d_HAry1dOfEntityOnSolid Surfaces;
	theSurfaces_->RetrieveTo(Surfaces);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Surfaces)
	)
	{
		Debug_Null_Pointer(Surfaces[Index]);
		Debug_Null_Pointer(Global_DownCast(Cad3d_SurfaceOnSolid, Surfaces[Index]));

		Get_Const_Pointer(Surface) = Global_DownCast(Cad3d_SurfaceOnSolid, Surfaces[Index]);

		Surface->Plane()->ExportWiresToPlt(File);
	}
}

void AutLib::CadLib::Cad3d_Solid::ExportCurvesToPlt(fstream & File) const
{
	if (NOT thePairedEdges_) return;

	TColCad3d_HAry1dOfEntityOnSolid PairedOnSolid;
	thePairedEdges_->RetrieveTo(PairedOnSolid);

	forThose
	(
		Index,
		0,
		MaxIndexOf(PairedOnSolid)
	)
	{
		Debug_Null_Pointer(PairedOnSolid[Index]);
		Debug_Null_Pointer(Global_DownCast(Cad3d_PairedOnSolid, PairedOnSolid[Index]));

		Get_Const_Pointer(Paired) = Global_DownCast(Cad3d_PairedOnSolid, PairedOnSolid[Index]);

		Paired->ExportToPlt(File);
	}
}

void AutLib::CadLib::Cad3d_Solid::ExportFreeEdgesToPlt(fstream & File) const
{
	TColCad3d_HAry1dOfPairedOnSolid Edges;
	RetrieveFreeEdgesTo(Edges);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Edges)
	)
	{
		Debug_Null_Pointer(Edges[Index]);

		Edges[Index]->ExportToPlt(File);
	}
}

void AutLib::CadLib::Cad3d_Solid::ExportSurfacesToPlt(fstream & File) const
{
	if (NOT theSurfaces_) return;

	TColCad3d_HAry1dOfEntityOnSolid Surfaces;
	theSurfaces_->RetrieveTo(Surfaces);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Surfaces)
	)
	{
		Debug_Null_Pointer(Surfaces[Index]);
		Debug_Null_Pointer(Global_DownCast(Cad3d_SurfaceOnSolid, Surfaces[Index]));

		Get_Const_Pointer(Surface) = Global_DownCast(Cad3d_SurfaceOnSolid, Surfaces[Index]);

		if (Surface->HasTriangulation())
			M_IO IO_TecPlot::ExportMesh(Surface->Triangulation(), File);
	}
}

void AutLib::CadLib::Cad3d_Solid::ExportNormalsToPlt
(
	fstream & File, 
	const Standard_Real theCoeff
) const
{
	if (NOT theSurfaces_) return;

	TColCad3d_HAry1dOfEntityOnSolid Surfaces;
	theSurfaces_->RetrieveTo(Surfaces);

	forThose
	(
		Index,
		0,
		MaxIndexOf(Surfaces)
	)
	{
		Debug_Null_Pointer(Surfaces[Index]);
		Debug_Null_Pointer(Global_DownCast(Cad3d_SurfaceOnSolid, Surfaces[Index]));

		Get_Const_Pointer(Surface) = Global_DownCast(Cad3d_SurfaceOnSolid, Surfaces[Index]);

		Surface->ExportGeometryNormalsToPlt(File, theCoeff);
	}
}

void AutLib::CadLib::Cad3d_Solid::ExportShellsToPlt(fstream & File) const
{
	forThose(Index, 0, MaxIndexOf(theInnerShells_))
	{
		if (theInnerShells_[Index]) theInnerShells_[Index]->ExportToPlt(File);
	}

	if (theOutterShell_) theOutterShell_->ExportToPlt(File);
}

void AutLib::CadLib::Cad3d_Solid::ExportBlockSurfacesToPlt(fstream & File) const
{
	TColCad3d_HAry1dOfBlockEntityOnSolid Blocks;
	theSurfaces_->RetrieveTo(Blocks);

	forThose
	(
		Index, 
		0,
		MaxIndexOf(Blocks)
	)
	{
		Debug_Null_Pointer(Blocks[Index]);

		TColCad3d_HAry1dOfEntityOnSolid Surfaces;
		Blocks[Index]->RetrieveTo(Surfaces);

		TColEntity_HAry1dOfTriangulation3d Triangulations(Surfaces.Size());
		Triangulations.Init(0);
		forThose
		(
			Inner,
			0, 
			MaxIndexOf(Surfaces)
		)
		{
			Debug_Null_Pointer(Surfaces[Inner]);

			Global_Handle(Cad3d_SurfaceOnSolid) Surface = Global_DownCast(Cad3d_SurfaceOnSolid, Surfaces[Inner]);
			Debug_Null_Pointer(Surface);

			Global_Handle(Entity_Triangulation3d) Triangulation = new Entity_Triangulation3d;
			if (Surface->Triangulation()) Entity_Triangulation3dTools::GetTriangulation(Surface->Triangulation(), *Triangulation);

			Triangulations[Inner] = Triangulation;
		}

		Merge_Triangulation3d Merge;
		Merge.Import(Triangulations);
		Merge.Perform();

		Merge.Merged()->ExportToPlt(File);

		FreeMemory(Triangulations);
	}
}

void AutLib::CadLib::Cad3d_Solid::Report(Standard_OStream & Ostream) const
{
	Ostream << "----------------{ Solid Report }----------------" << endl;
	Ostream << endl;
	Ostream << "   Name: " << theName_ << endl;
	Ostream << "   Index: " << theIndex_ << endl;
	Ostream << endl;
	Ostream << "   Nb. of Vertices: " << NbVertices() << endl;
	Ostream << "   Nb. of Edges: " << NbPairedEdges() << endl;
	Ostream << "   Nb. of Surfaces: " << NbSurfaces() << endl;
	Ostream << "   Nb. of Holes: " << NbHoles() << endl;
	Ostream << endl;
	Ostream << "   Has Free Corner? " << (HasFreeEdge() ? "YES" : "NO") << endl;
	if (HasFreeEdge()) Ostream << "   Nb. of Free Edges: " << NbFreeEdges() << endl;
	Ostream << endl;
	Ostream << "-------------{ End of Solid Report }-------------" << endl;
}

Standard_Boolean AutLib::CadLib::Cad3d_Solid::CreateShells(const TColCad3d_HAry1dOfSurfaceOnSolid & theSurfaces)
{
	TColCad3d_HAry1dOfShellOnSolid Shells;
	Try_Exception_Handle_Exit(Shells = Cad3d_ShellOnSolidTools::TrackShells(theSurfaces));

	forThose
	(
		Index,
		0, 
		MaxIndexOf(Shells)
	)
	{
		Debug_Null_Pointer(Shells[Index]);

		//Cad3d_ShellOnSolidTools::SortOrientation(*Shells[Index]);
	}

	forThose
	(
		Index,
		0,
		MaxIndexOf(Shells)
	)
	{
		Debug_Null_Pointer(Shells[Index]);
		if (NOT Shells[Index]->IsClosed())
		{
			theInnerShells_ = Shells;
			return Standard_False;
		}
	}

	if (NOT Cad3d_ShellOnSolidTools::IdentifyBoundaries(Shells, theInnerShells_, theOutterShell_))
	{
		return Standard_False;
	}
	return Standard_True;
}