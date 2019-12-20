#include <Mesh3d_SolidMesher.hxx>

#include <Time.hxx>
#include <Standard_Directory.hxx>
#include <Entity_Box3dTools.hxx>
#include <Merge_Triangulation3d.hxx>
#include <Geom_ADTree3d.hxx>
#include <Cad3d_CurveOnPlane.hxx>
#include <Cad3d_EdgeOnSolid.hxx>
#include <Cad3d_PairedOnSolid.hxx>
#include <Cad3d_Solid.hxx>
#include <Cad3d_SurfaceOnSolid.hxx>
#include <Mesh2d_Curve.hxx>
#include <Mesh3d_SurfaceMesher.hxx>
#include <MetricMap_ExactSurfaceMetric.hxx>
#include <SizeMap2d_FullIntAnIso.hxx>
#include <SizeMap3d_SurfaceSizeMap.hxx>
#include <SizeMap2d_FullIntAnIsoTools.hxx>
#include <IO_Tecplot.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <TColMesh3d_HBasicQueueOfSurfaceMesher.hxx>
#include <TColCad3d_HAry1dOfSurfaceOnSolid.hxx>
#include <TColCad3d_HAry1dOfPairedOnSolid.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;
using namespace GeoLib;

static const Standard_Real DEFAULT_GRADIENTFACTOR = 5.0;
static const Standard_Real DEFAULT_MINGRADATION = 0.5;
static const Standard_Real DEFAULT_SMOOTHING_FACTOR = 1.5;
static const Standard_Real DEFAULT_DEGENERACY = 1.0E-5;
static const Standard_Integer DEFAULT_MAXITERS = 5;

#define HANDLE_BAD_BOUNDARY \
   SurfaceMesher->ExportParametricBoundaryToPlt(ExceptionPlot2d); \
   Surfaces[Index]->ExportTriangulationToPlt(ExceptionPlot3d);  \
   K++;  \
   continue;

#define HANDLE_CREATE_DIRECTORY AutLib::CreateDirectoryRecursively(ExceptionPath + "/" + theSolidName_);

AutLib::MeshLib::Mesh3d_SolidMesher::Mesh3d_SolidMesher
(
	const Mesh3d_SizeMap & theSizeMap, 
	const M_CAD Cad3d_Solid & theShape
)
	: theSizeMap_(theSizeMap)
	, theSolid_(theShape)
	, ApplySmoothing_(Standard_True)
	, UseExactMetric_(Standard_False)
	, theMaxGradation_(DEFAULT_GRADIENTFACTOR)
	, IsDone_(Standard_False)
	, theSolidName_("Unknown")
	, theVerbose_(0)
	, theAnIsoSizeMapType_(SizeMap2d_AnIsoBackSizeType_FullIntAnIsoRefineSearchRefineElementSize)
	, ApplyOptimization_(Standard_True)
{
	theSolidName_ = theShape.Name();
}

AutLib::MeshLib::Mesh3d_SolidMesher::~Mesh3d_SolidMesher()
{
	ReleaseMemory();
}

void AutLib::MeshLib::Mesh3d_SolidMesher::ApplyOptimization(const Standard_Boolean ApplyOptimization)
{
	ApplyOptimization_ = ApplyOptimization;
}

void AutLib::MeshLib::Mesh3d_SolidMesher::ApplySmoothing(const Standard_Boolean ApplySmoothing)
{
	ApplySmoothing_ = ApplySmoothing;
}

void AutLib::MeshLib::Mesh3d_SolidMesher::SetAnIsoSizeMapType(const SizeMap2d_AnIsoBackSizeType theType)
{
	theAnIsoSizeMapType_ = theType;
}

void AutLib::MeshLib::Mesh3d_SolidMesher::UseExactMetric()
{
	UseExactMetric_ = Standard_True;
}

void AutLib::MeshLib::Mesh3d_SolidMesher::SetVerbosity(Standard_Integer theVerbose)
{
	theVerbose_ = MAX(theVerbose, 0);
}

void AutLib::MeshLib::Mesh3d_SolidMesher::Perform()
{
	Open_OutputFile_txt_read(ExceptionPathFile, "Report Path");

	Standard_String ExceptionPath;
	std::getline(ExceptionPathFile, ExceptionPath);

	TColCad3d_HAry1dOfSurfaceOnSolid Surfaces;
	theSolid_.RetrieveSurfacesTo(Surfaces);

	if (theVerbose_)
	{
		cout << endl;
		cout << "  Solid Mesher has been involved!\n";
		cout << "    - Solid Name: " << theSolidName_ << endl;
		cout << "    - No. of Surfaces: " << theSolid_.NbSurfaces() << endl;
		cout << "    - Use Exact metric: " << (UseExactMetric_ ? "YES" : "NO") << endl;
		if (theVerbose_ > 1) cout << endl;
	}

	if (theSolid_.HasFreeEdge())
	{
		cout << "  WARNING! the Solid has FREE-EDGE.\n";
		cout << "   For WATERTIGHT discretized model, there must be no FREE-EDGE in model\n";
		cout << "   Nb. of FREE-EDGE: " << theSolid_.NbFreeEdges() << endl;
		cout << endl;
	}

	Standard_Real FirstTime = getCPUTime();
	Standard_Integer K = 1;
	TColMesh3d_HBasicQueueOfSurfaceMesher QMesher;
	forThose
	(
		Index,
		0,
		MaxIndexOf(Surfaces)
	)
	{
		Global_Handle(Mesh3d_SurfaceMesher) SurfaceMesher = new Mesh3d_SurfaceMesher(theSizeMap_, *Surfaces[Index]);
		
		SurfaceMesher->SetSurfaceName(theSolidName_);
		if (theVerbose_) SurfaceMesher->SetVerbosity(theVerbose_ - 1);
		if (UseExactMetric_) SurfaceMesher->UseExactMetric();
		if (NOT ApplySmoothing_) SurfaceMesher->ApplyMetricSmoothing(Standard_False);
		if (NOT ApplyOptimization_) SurfaceMesher->ApplyOptimization(Standard_False);

		switch (theAnIsoSizeMapType_)
		{
		case SizeMap2d_AnIsoBackSizeType_FullIntAnIso: {SurfaceMesher->SetAnIsoSizeMap(&SizeMap2d_FullIntAnIsoTools::CreateStdAnIsoSizeMap); break; }
		case SizeMap2d_AnIsoBackSizeType_FullIntAnIsoRefineSearch: {SurfaceMesher->SetAnIsoSizeMap(&SizeMap2d_FullIntAnIsoTools::CreateModifiedSearchAnIsoSizeMap); break; }
		case SizeMap2d_AnIsoBackSizeType_FullIntAnIsoRefineSearchRefineElementSize: {SurfaceMesher->SetAnIsoSizeMap(&SizeMap2d_FullIntAnIsoTools::CreateModifiedSearchAndElementSizeAnIsoSizeMap); break; }
		default: THROW_STANDARD_EXCEPTION("Invalid AnIso SizeMap Type");
		}

		if (theVerbose_ > 1)
		{
			cout << "   Surface Mesher has been involed!\n";
			cout << "   Surface No. " << K << endl;
			cout << endl;
		}

		Try_Exception_Handle_Bad_Boundary
		(
			SurfaceMesher->Perform(),
			theSolidName_ + "_Surface No. " + std::to_string(K),
			ExceptionPath + "/" + theSolidName_
		);

		QMesher.EnQueue(SurfaceMesher);
		K++;
	}

	Standard_Real LastTime = getCPUTime();
	QMesher.RetrieveTo(theMesher_);

	if (NOT theSolid_.HasFreeEdge())
	{
		Try_Exception_Handle_Exit(ConformBoundaries(Surfaces));  

		Merging();
	}

	if (theVerbose_)
	{
		if (theVerbose_ > 1) cout << endl;
		cout << "    - " << theMesher_.Size() << " Surfaces has been discretized successfully!\n";
		cout << "    - " << theMergedMesh_.NbTriangles() << " Triangles has been generated in " << (LastTime - FirstTime) << " sec" << endl;
	}

	IsDone_ = Standard_True;
}

void AutLib::MeshLib::Mesh3d_SolidMesher::ExportMeshToPlt(fstream & File) const
{
	if (NOT IsDone_) return;

	forThose
	(
		Index,
		0, 
		MaxIndexOf(theMesher_)
	)
	{
		Debug_Null_Pointer(theMesher_[Index]);
		theMesher_[Index]->ExportSurfaceMeshToPlt(File);
	}
}

void AutLib::MeshLib::Mesh3d_SolidMesher::ExportQualityMeshToPlt
(
	fstream & File,
	const Mesh2d_QualityMap & theQualityMap
) const
{
	if (NOT IsDone_) return;

	forThose
	(
		Index,
		0,
		MaxIndexOf(theMesher_)
	)
	{
		Debug_Null_Pointer(theMesher_[Index]);
		theMesher_[Index]->ExportQualityMeshToPlt(File, theQualityMap);
	}
}

void AutLib::MeshLib::Mesh3d_SolidMesher::ExportMergedMeshToPlt(fstream & File) const
{
	if (NOT IsDone_) return;
	theMergedMesh_.ExportToPlt(File);
}

void AutLib::MeshLib::Mesh3d_SolidMesher::ExportNormalsToPlt(fstream & File) const
{
	if (NOT IsDone_) return;
	theMergedMesh_.ExportNormalsToPlt(File);
}

void AutLib::MeshLib::Mesh3d_SolidMesher::ExportMeshTo(fstream & File) const
{
	theMergedMesh_.ExportTo(File);
}

namespace AutLib
{
	namespace CadLib
	{

		static void DiscretizedPairedEdge(const Cad3d_PairedOnSolid& thePaired, const Mesh3d_SizeMap& theSizeMap, TColGeom_Ary1dOfPnt3d& theCoords0, TColGeom_Ary1dOfPnt3d& theCoords1, Standard_Integer& theSurfaceIndex0, Standard_Integer& theSurfaceIndex1)
		{
			Debug_Null_Pointer(thePaired.Edge0());
			Debug_Null_Pointer(thePaired.Edge1());

			Get_Const_Object(Edge0) = *thePaired.Edge0();
			Get_Const_Object(Edge1) = *thePaired.Edge1();

			Debug_Null_Pointer(Edge0.Surface());
			Debug_Null_Pointer(Edge1.Surface());

			Get_Const_Object(Surface0) = *Edge0.Surface();
			Get_Const_Object(Surface1) = *Edge1.Surface();

			Get_Const_Object(Curve0) = *Edge0.CurveOnPlane();
			Get_Const_Object(Curve1) = *Edge1.CurveOnPlane();

			MetricMap_ExactSurfaceMetric ExactSurfaceMetric0(Surface0);
			MetricMap_ExactSurfaceMetric ExactSurfaceMetric1(Surface1);

			SizeMap3d_SurfaceSizeMap SurfaceSizeMap0(theSizeMap, Surface0.Geometry());
			SizeMap3d_SurfaceSizeMap SurfaceSizeMap1(theSizeMap, Surface1.Geometry());

			SizeMap2d_FullIntAnIso MetricMap0(&SurfaceSizeMap0, &ExactSurfaceMetric0);
			SizeMap2d_FullIntAnIso MetricMap1(&SurfaceSizeMap1, &ExactSurfaceMetric1);

			Mesh2d_Curve MeshCurve0(MetricMap0, Edge0.CurveOnPlane());
			Mesh2d_Curve MeshCurve1(MetricMap1, Edge1.CurveOnPlane());

			Try_Exception_Handle_Exit(MeshCurve0.Perform());
			Try_Exception_Handle_Exit(MeshCurve1.Perform());

			Get_Const_Object(Parameters0) = MeshCurve0.Chain().Coords();
			Get_Const_Object(Parameters1) = MeshCurve1.Chain().Coords();

			theCoords0.Resize(Parameters0.Size());
			theCoords1.Resize(Parameters1.Size());

			forThose(Index, 0, MaxIndexOf(Parameters0))
				theCoords0.SetValue(Index, Surface0.Value(Parameters0[Index]));

			forThose(Index, 0, MaxIndexOf(Parameters1))
				theCoords1.SetValue(Index, Surface1.Value(Parameters1[Index]));

			if (Surface0.Orientation() EQUAL Cad3d_SurfaceOrientation_OUTWARD) theCoords0.Reverse();
			if (Surface1.Orientation() EQUAL Cad3d_SurfaceOrientation_OUTWARD) theCoords1.Reverse();

			theSurfaceIndex0 = Surface0.Index();
			theSurfaceIndex1 = Surface1.Index();
		}
	}
}

M_MESH_SPACE(Node)

namespace AutLib
{
	typedef ADT_BasicQueue<Global_Handle(M_MESH Node)> TColMesh3d_HBasicQueueOfNode1;
	typedef ADT_Ary1d<Global_Handle(M_MESH Node)> TColMesh3d_HAry1dOfNode1;
}

namespace AutLib
{
	namespace MeshLib
	{

		class Node
		{

		private:

			Standard_Integer theIndex_;

			Geom_Pnt3d thePrior_;
			Geom_Pnt3d theModified_;

			Standard_Boolean IsModified_;

			TColMesh3d_HBasicQueueOfNode1 theLinked_;

		public:

			Node(const Standard_Integer theIndex, const Geom_Pnt3d& theCoord);

			const Geom_Pnt3d& Prior() const;

			const Geom_Pnt3d& Modified() const;

			Standard_Boolean IsModified() const;

			Standard_Integer Index() const;

			Standard_Integer NbLinked() const;

			TColMesh3d_HAry1dOfNode1 Linked() const;

			void ImportToLink(const Global_Handle(Node) theNode);

			void SetModified(const Geom_Pnt3d& theCoord);

		};

		inline const Geom_Pnt3d & AutLib::MeshLib::Node::Prior() const
		{
			return thePrior_;
		}

		inline const Geom_Pnt3d & AutLib::MeshLib::Node::Modified() const
		{
			return theModified_;
		}

		inline Standard_Integer AutLib::MeshLib::Node::Index() const
		{
			return theIndex_;
		}

		inline Standard_Integer AutLib::MeshLib::Node::NbLinked() const
		{
			return theLinked_.Size();
		}

		inline Standard_Boolean AutLib::MeshLib::Node::IsModified() const
		{
			return IsModified_;
		}

		class NodeTools
		{

		public:

			static const Geom_Pnt3d& CoordOf(Global_Handle(Node) theNode)
			{
				Debug_Null_Pointer(theNode);
				return theNode->Prior();
			}
		};
	}
}

AutLib::MeshLib::Node::Node
(
	const Standard_Integer theIndex,
	const Geom_Pnt3d & theCoord
)
	: theIndex_(theIndex)
	, thePrior_(theCoord)
	, IsModified_(Standard_False)
{
}

TColMesh3d_HAry1dOfNode1 AutLib::MeshLib::Node::Linked() const
{
	return theLinked_.Retrive();
}

void AutLib::MeshLib::Node::ImportToLink(const Global_Handle(Node) theNode)
{
	theLinked_.EnQueue((Global_Handle(Node))theNode);
}

void AutLib::MeshLib::Node::SetModified(const Geom_Pnt3d & theCoord)
{
	theModified_ = theCoord;
	IsModified_ = Standard_True;
}

namespace AutLib
{
	typedef Geom_ADTree3d<Global_Handle(M_MESH Node)> RegisterOfNode;
}

namespace AutLib
{
	typedef ADT_Ary1d<Global_Handle(RegisterOfNode)> TColMesh3d_HAry1dOfRegisterOfNode;
}

namespace AutLib
{
	namespace MeshLib
	{
		static TColMesh3d_HAry1dOfNode1 GetSurfaceNodes(const Mesh3d_SurfaceMesher& theMesh)
		{
			Get_Const_Object(Points) = theMesh.SurfaceMesh().Points();
			TColMesh3d_HAry1dOfNode1 Nodes(Points.Size());
			forThose(Index, 0, MaxIndexOf(Nodes))
				Nodes[Index] = new Node(Index + 1, Points[Index]);
			MOVE(Nodes);
		}

		static Global_Handle(Node) Search(const TColMesh3d_HAry1dOfRegisterOfNode& theRegisters, const Standard_Integer theIndex, const Geom_Pnt3d& theCentre)
		{
			Debug_Bad_Index_Array1(theIndex, theRegisters);
			Debug_Null_Pointer(theRegisters[theIndex]);

			Get_Const_Object(Register) = *theRegisters[theIndex];

			TColMesh3d_HAry1dOfNode1 Nodes;
			Register.Search(Entity_Box3dTools::BoxOf(theCentre, 1.0E-3), Nodes);

			if (Nodes.IsEmpty()) { THROW_STANDARD_EXCEPTION("Invalid Data"); }

			if (Nodes.Size() EQUAL 1) return Nodes[0];

			Standard_Real MinDis = RealLast();
			Standard_Integer MinIndex;
			forThose
			(
				Index,
				0, 
				MaxIndexOf(Nodes)
			)
			{
				Debug_Null_Pointer(Nodes[Index]);
				Standard_Real Dis = Distance(Nodes[Index]->Prior(), theCentre);

				if (Dis < MinDis)
				{
					MinDis = Dis;
					MinIndex = Index;
				}
			}
			return Nodes[MinIndex];
		}

		static void ModifyBoundaries(const TColMesh3d_HAry1dOfRegisterOfNode& theRegisters, const TColGeom_Ary1dOfPnt3d& theCoords0, const TColGeom_Ary1dOfPnt3d& theCoords1, const Standard_Integer theSurfaceIndex0, const Standard_Integer theSurfaceIndex1)
		{
			forThose
			(
				Index, 
				0,
				MaxIndexOf(theCoords0)
			)
			{
				Geom_Pnt3d Pm = MEAN(theCoords0[Index], theCoords1[Index]);

				Global_Handle(Node) Node0 = ::Search(theRegisters, theSurfaceIndex0 - 1, theCoords0[Index]);
				Global_Handle(Node) Node1 = ::Search(theRegisters, theSurfaceIndex1 - 1, theCoords1[Index]);

				Debug_Null_Pointer(Node0);
				Debug_Null_Pointer(Node1);

				Node0->SetModified(Pm);
				Node1->SetModified(Pm);

				if (Node0->NbLinked())
				{
					TColMesh3d_HAry1dOfNode1 Nodes = Node0->Linked();
					forThose(Index, 0, MaxIndexOf(Nodes))
						Nodes[Index]->SetModified(Pm);
				}

				if (Node1->NbLinked())
				{
					TColMesh3d_HAry1dOfNode1 Nodes = Node1->Linked();
					forThose(Index, 0, MaxIndexOf(Nodes))
						Nodes[Index]->SetModified(Pm);
				}

				Node0->ImportToLink(Node1);
				Node1->ImportToLink(Node0);
			}
		}

		static TColMesh3d_HAry1dOfNode1 GetSorted(const TColMesh3d_HAry1dOfNode1& theNodes)
		{
			TColMesh3d_HAry1dOfNode1 Nodes(theNodes.Size());
			forThose(Index, 0, MaxIndexOf(Nodes))
				Nodes[theNodes[Index]->Index() - 1] = theNodes[Index];
			MOVE(Nodes);
		}

		static TColGeom_Ary1dOfPnt3d GetCoords(const TColMesh3d_HAry1dOfNode1& theNodes)
		{
			TColGeom_Ary1dOfPnt3d Coords(theNodes.Size());
			forThose
			(
				Index,
				0,
				MaxIndexOf(theNodes)
			)
			{
				if (theNodes[Index]->IsModified())
				{
					Coords[Index] = theNodes[Index]->Modified();
				}
				else
					Coords[Index] = theNodes[Index]->Prior();
				
			}
			MOVE(Coords);
		}
	}
}

void AutLib::MeshLib::Mesh3d_SolidMesher::ConformBoundaries(const TColCad3d_HAry1dOfSurfaceOnSolid& theSurfaces)
{
	Standard_Integer MaxIndex = 0;
	forThose
	(
		Index,
		0,
		MaxIndexOf(theMesher_)
	)
	{
		Debug_Null_Pointer(theMesher_[Index]);

		Get_Const_Object(Mesher) = *theMesher_.Value(Index);

		if (Mesher.Index() > MaxIndex) MaxIndex = Mesher.Index();
	}

	TColMesh3d_HAry1dOfRegisterOfNode Registers(MaxIndex + 1);
	Registers.Init(0);

	forThose
	(
		Index,
		0,
		MaxIndexOf(theMesher_)
	)
	{
		if (NOT theMesher_[Index]) continue;

		Debug_Null_Pointer(theMesher_[Index]);

		Get_Const_Object(Mesher) = *theMesher_.Value(Index);

		Registers[Mesher.Index() - 1] = new RegisterOfNode;
		Registers[Mesher.Index() - 1]->SetCoordinateFunction(&NodeTools::CoordOf);

		Try_Exception_Handle_Exit(Registers[Mesher.Index() - 1]->Insert(GetSurfaceNodes(Mesher)));
	}
	TColCad3d_HAry1dOfEntityOnSolid PairedEdges;
	theSolid_.RetrievePairedEdgesTo(PairedEdges);

	forThose
	(
		Index,
		0,
		MaxIndexOf(PairedEdges)
	)
	{
		Get_Const_Pointer(Edge) = Global_DownCast(Cad3d_PairedOnSolid, PairedEdges[Index]);
		Debug_Null_Pointer(Edge);

		Standard_Integer SurfaceIndex0, SurfaceIndex1;
		TColGeom_Ary1dOfPnt3d Coords0, Coords1;
		::DiscretizedPairedEdge
		(
			*Edge, 
			theSizeMap_,
			Coords0,
			Coords1,
			SurfaceIndex0,
			SurfaceIndex1
		);
		
		if (Coords0.Size() NOT_EQUAL Coords1.Size())
		{
			THROW_STANDARD_EXCEPTION("Conflict Data");
		}

		Coords1.Reverse();

		::ModifyBoundaries
		(
			Registers, 
			Coords0,
			Coords1,
			SurfaceIndex0, 
			SurfaceIndex1
		);
	}
	
	forThose
	(
		Index,
		0,
		MaxIndexOf(theMesher_)
	)
	{
		if (NOT theMesher_[Index]) continue;

		Debug_Null_Pointer(theMesher_[Index]);

		Get_Const_Object(Mesher) = *theMesher_.Value(Index);

		TColMesh3d_HAry1dOfNode1 Nodes;
		Registers[Mesher.Index() - 1]->RetrieveTo(Nodes);

		TColGeom_Ary1dOfPnt3d Coords = ::GetCoords(::GetSorted(Nodes));

		theMesher_[Index]->ModifiedSurfaceMesh().Points() = Coords;
		theMesher_[Index]->ModifiedSurfaceMesh().Triangles() = theMesher_[Index]->SurfaceMesh().Triangles();

		FreeMemory(Nodes);
	}

	FreeMemory(Registers);
}

namespace AutLib
{
	namespace MeshLib
	{
		static inline TColEntity_HAry1dOfTriangulation3d GetTriangulations(const TColMesh3d_HAry1dOfSurfaceMesher& theMeshes)
		{
			TColEntity_HAry1dOfTriangulation3d Triangulations(theMeshes.Size());
			forThose(Index, 0, MaxIndexOf(Triangulations))
				Triangulations[Index] = (Global_Handle(Entity_Triangulation3d))&theMeshes[Index]->ModifiedSurfaceMesh();
			MOVE(Triangulations);
		}
	}
}

void AutLib::MeshLib::Mesh3d_SolidMesher::Merging()
{
	Merge_Triangulation3d Merge(0.001, 1.0E-5);
	Merge.Import(GetTriangulations(theMesher_));

	Merge.Perform();

	theMergedMesh_ = *Merge.Merged();
}

void AutLib::MeshLib::Mesh3d_SolidMesher::ReleaseMemory()
{
	FreeMemory(theMesher_);
}