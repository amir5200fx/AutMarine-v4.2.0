#include <Mesh3d_ShapeDiscrete.hxx>

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
#include <Mesh3d_FaceDiscrete.hxx>
#include <MetricMap_ExactSurfaceMetric.hxx>
#include <SizeMap2d_FullIntAnIso.hxx>
#include <SizeMap3d_SurfaceSizeMap.hxx>
#include <IO_Tecplot.hxx>
#include <TColGeom_Ary1dOfPnt3d.hxx>
#include <TColMesh3d_HBasicQueueOfFaceDiscrete.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace MeshLib;
using namespace GeoLib;

#include <TopoDS.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <TopoDS_Shape.hxx>
#include <TopExp_Explorer.hxx>
#include <BRep_Tool.hxx>
#include <BRepBndLib.hxx>
#include <Bnd_Box.hxx>
#include <BRepBuilderAPI_Sewing.hxx>
#include <GeomAPI_ProjectPointOnCurve.hxx>

using namespace AutLib;
using namespace MeshLib;
using namespace GeoLib;

#define HANDLE_BAD_BOUNDARY \
   SurfaceMesher->ExportParametricBoundaryToPlt(ExceptionPlot2d); \
   K++;  \
   continue;

#define HANDLE_CREATE_DIRECTORY AutLib::CreateDirectoryRecursively(ExceptionPath + "/" + theShapeName_);

AutLib::MeshLib::Mesh3d_ShapeDiscrete::Mesh3d_ShapeDiscrete
(
	const Standard_Real theSize,
	const TopoDS_Shape & theShape
)
	: theShape_(theShape)
	, ApplySmoothing_(Standard_True)
	, ApplyOptimization_(Standard_False)
	, UseExactMetric_(Standard_False)
	, IsDone_(Standard_False)
	, theShapeName_("Unknown")
	, theSize_(theSize)
	, theVerbose_(0)
{
}

AutLib::MeshLib::Mesh3d_ShapeDiscrete::~Mesh3d_ShapeDiscrete()
{
	ReleaseMemory();
}

void AutLib::MeshLib::Mesh3d_ShapeDiscrete::SetSize(const Standard_Real theSize)
{
	theSize_ = theSize;
}

void AutLib::MeshLib::Mesh3d_ShapeDiscrete::SetName(const Standard_String theShapeName)
{
	theShapeName_ = theShapeName;
}

void AutLib::MeshLib::Mesh3d_ShapeDiscrete::ApplyMetricSmoothing(const Standard_Boolean ApplySmoothing)
{
	ApplySmoothing_ = ApplySmoothing;
}

void AutLib::MeshLib::Mesh3d_ShapeDiscrete::SetToUseExactMetric()
{
	UseExactMetric_ = Standard_True;
}

void AutLib::MeshLib::Mesh3d_ShapeDiscrete::Perform()
{
	Open_OutputFile_txt_read(ExceptionPathFile, "Report Path");

	Standard_String ExceptionPath;
	std::getline(ExceptionPathFile, ExceptionPath);

	TColMesh3d_HBasicQueueOfFaceDiscrete QMesher;
	Standard_Integer K = 0;
	for (TopExp_Explorer Explorer(theShape_, TopAbs_FACE); Explorer.More(); Explorer.Next())
	{
		TopoDS_Face Face = TopoDS::Face(Explorer.Current());

		Global_Handle(Mesh3d_FaceDiscrete) SurfaceMesher = new Mesh3d_FaceDiscrete(theSize_, Face);

		if (UseExactMetric_) SurfaceMesher->SetToUseExactMetric();
		SurfaceMesher->ApplySmoothing(ApplySmoothing_);
		SurfaceMesher->ApplyOptimization(ApplyOptimization_);
		SurfaceMesher->SetSurfaceName(theShapeName_);

		Standard_String SurfaceName = theShapeName_ + "_Surface No. " + std::to_string(K + 1);
		cout << K << endl;
		Try_Exception_Handle_Bad_Boundary
		(
			SurfaceMesher->Perform(),
			theShapeName_ + "_Surface No. " + std::to_string(K),
			ExceptionPath + "/" + theShapeName_
		);
		PAUSE;
		QMesher.EnQueue(SurfaceMesher);
		K++;
	}
	QMesher.RetrieveTo(theMesh_);

	Merging();

	IsDone_ = Standard_True;
}

void AutLib::MeshLib::Mesh3d_ShapeDiscrete::ExportMeshToPlt(fstream & File) const
{
	if (NOT IsDone_) return;
	forThose(Index, 0, MaxIndexOf(theMesh_))
	{
		Debug_Null_Pointer(theMesh_[Index]);
		theMesh_[Index]->ExportTriangulationToPlt(File);
	}
}

void AutLib::MeshLib::Mesh3d_ShapeDiscrete::ExportMergedMeshToPlt(fstream & File) const
{
	if (NOT IsDone_) return;
	theMergedMesh_.ExportTo(File);
}

namespace AutLib
{
	namespace MeshLib
	{
		static inline TColEntity_HAry1dOfTriangulation3d GetTriangulations(const TColMesh3d_HAry1dOfFaceDiscrete& theMeshes)
		{
			TColEntity_HAry1dOfTriangulation3d Triangulations(theMeshes.Size());
			forThose(Index, 0, MaxIndexOf(Triangulations))
				Triangulations[Index] = (Global_Handle(Entity_Triangulation3d))&theMeshes[Index]->SurfaceMesh();
			MOVE(Triangulations);
		}
	}
}

void AutLib::MeshLib::Mesh3d_ShapeDiscrete::Merging()
{
	Merge_Triangulation3d Merge;
	Merge.Import(GetTriangulations(theMesh_));

	Merge.Perform();

	theMergedMesh_ = *Merge.Merged();
}

void AutLib::MeshLib::Mesh3d_ShapeDiscrete::ReleaseMemory()
{
	FreeMemory(theMesh_);
}