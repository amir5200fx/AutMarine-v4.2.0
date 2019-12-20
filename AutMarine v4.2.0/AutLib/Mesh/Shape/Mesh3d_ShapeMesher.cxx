#include <Mesh3d_ShapeMesher.hxx>

#include <Standard_Directory.hxx>
#include <Merge_Pnt3d.hxx>
#include <Merge_Triangulation3d.hxx>
#include <Mesh3d_SurfaceMesher.hxx>
#include <IO_Tecplot.hxx>
#include <TColMesh3d_HBasicQueueOfSurfaceMesher.hxx>

using namespace AutLib;
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

#define HANDLE_BAD_BOUNDARY \
   SurfaceMesher->ExportParametricBoundaryToPlt(ExceptionPlot2d); \
   IoLib::IO_TecPlot::ExportSurface(Face, ExceptionPlot3d);  \
   K++;  \
   continue;

#define HANDLE_CREATE_DIRECTORY AutLib::CreateDirectoryRecursively(ExceptionPath + "/" + theShapeName_);

static const Standard_Real DEFAULT_GRADIENTFACTOR = 5.0;
static const Standard_Real DEFAULT_SEWINGTOLERANCE = 1.0E-3;

AutLib::MeshLib::Mesh3d_ShapeMesher::Mesh3d_ShapeMesher
(
	const Mesh3d_SizeMap & theSizeMap,
	const TopoDS_Shape & theShape
)
	: theSizeMap_(theSizeMap)
	, theShape_(theShape)
	, ApplySmoothing_(Standard_True)
	, UseExactMetric_(Standard_False)
	, theMaxGradation_(DEFAULT_GRADIENTFACTOR)
	, theSewingTolerance_(DEFAULT_SEWINGTOLERANCE)
	, IsDone_(Standard_False)
	, theShapeName_("Unknown")
{
}

void AutLib::MeshLib::Mesh3d_ShapeMesher::ApplyMetricSmoothing(const Standard_Boolean ApplySmoothing)
{
	ApplySmoothing_ = ApplySmoothing;
}

void AutLib::MeshLib::Mesh3d_ShapeMesher::SetMaxMetricGradation(const Standard_Real Gradation)
{
	theMaxGradation_ = Gradation;
}

void AutLib::MeshLib::Mesh3d_ShapeMesher::SetSwingTolerance(const Standard_Real Tolerance)
{
	theSewingTolerance_ = Tolerance;
}

void AutLib::MeshLib::Mesh3d_ShapeMesher::SetShapeName(const Standard_String Name)
{
	theShapeName_ = Name;
}

void AutLib::MeshLib::Mesh3d_ShapeMesher::UseExactMetric()
{
	UseExactMetric_ = Standard_True;
}

void AutLib::MeshLib::Mesh3d_ShapeMesher::Perform()
{
	Open_OutputFile_txt_read(ExceptionPathFile, "Report Path");

	Standard_String ExceptionPath;
	std::getline(ExceptionPathFile, ExceptionPath);

	TColMesh3d_HBasicQueueOfSurfaceMesher QMesher;

	Standard_Integer K = 0;
	for (TopExp_Explorer Explorer(theShape_, TopAbs_FACE); Explorer.More(); Explorer.Next())
	{
		TopoDS_Face Face = TopoDS::Face(Explorer.Current());
		if (Face.Orientation() EQUAL TopAbs_REVERSED)
		{
			Face.Reverse();
		}

		Global_Handle(Mesh3d_SurfaceMesher) SurfaceMesher = new Mesh3d_SurfaceMesher(theSizeMap_, Face);

		if (UseExactMetric_) SurfaceMesher->UseExactMetric();
		if (NOT ApplySmoothing_) SurfaceMesher->ApplyMetricSmoothing(Standard_False);

		SurfaceMesher->SetSurfaceName(theShapeName_);

		Standard_String SurfaceName = theShapeName_ + "_Surface No. " + std::to_string(K + 1);

		Try_Exception_Handle_Bad_Boundary(SurfaceMesher->Perform(), SurfaceName, ExceptionPath + "/" + theShapeName_);

		QMesher.EnQueue(SurfaceMesher);
		K++;
	}

	QMesher.RetrieveTo(theMesh_);

	Merging();

	IsDone_ = Standard_True;
}

void AutLib::MeshLib::Mesh3d_ShapeMesher::ExportMeshToPlt(fstream & File)
{
	if (NOT IsDone_) THROW_STANDARD_EXCEPTION(" ShapeMesher is not performed");

	forThose(Index, 0, MaxIndexOf(theMesh_))
	{
		theMesh_[Index]->ExportSurfaceMeshToPlt(File);
	}
}

void AutLib::MeshLib::Mesh3d_ShapeMesher::ExportMergedMeshToPlt(fstream & File)
{
	if (NOT IsDone_) THROW_STANDARD_EXCEPTION(" ShapeMesher is not performed");

	theMergedMesh_.ExportToPlt(File);
}

namespace AutLib
{
	namespace MeshLib
	{
		static inline TColEntity_HAry1dOfTriangulation3d GetTriangulations(const TColMesh3d_HAry1dOfSurfaceMesher& theMeshes)
		{
			TColEntity_HAry1dOfTriangulation3d Triangulations(theMeshes.Size());
			forThose(Index, 0, MaxIndexOf(Triangulations))
				Triangulations[Index] = (Global_Handle(Entity_Triangulation3d))&theMeshes[Index]->SurfaceMesh();
			MOVE(Triangulations);
		}
	}
}

void AutLib::MeshLib::Mesh3d_ShapeMesher::Merging()
{
	Merge_Triangulation3d Merge;
	Merge.Import(GetTriangulations(theMesh_));

	Merge.Perform();

	theMergedMesh_ = *Merge.Merged();
}

void AutLib::MeshLib::Mesh3d_ShapeMesher::ReleaseMemory()
{
	FreeMemory(theMesh_);
}