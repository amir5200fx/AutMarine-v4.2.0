#include <Mesh3d_Region.hxx>

#include <GeoMesh_BackGroundMesh3d.hxx>
#include <SizeMap3d_UnionSizeMaps.hxx>
#include <SizeMap3d_UniSize.hxx>
#include <SizeMap3d_StdBackSize.hxx>
#include <SizeMap3d_ModifyBackSize.hxx>
#include <SizeMap3d_FullIntBackSize.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh3d_NodeTools.hxx>
#include <Mesh3d_BasicAft.hxx>
#include <Mesh3d_CavityRemover.hxx>
#include <Mesh3d_Optimization.hxx>
#include <QualityMap3d_MaxAngle.hxx>
#include <QualityMap3d_MeanSine.hxx>
#include <QualityMap3d_MinAngle.hxx>
#include <QualityMap3d_MinSine.hxx>
#include <QualityMap3d_RadiusRatio.hxx>
#include <QualityMap3d_Vlrms3Ratio.hxx>
#include <QualityMap3d_WarpedMinSine.hxx>
#include <TColMesh3d_ADTree3dOfNode.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace MeshLib;

AutLib::MeshLib::Mesh3d_Region::Mesh3d_Region
(
	const Global_Handle(Mesh_ReferenceValues) theReference,
	const Global_Handle(M_CAD Cad3d_Solid)theSolid
)
	: theBoundaries_(theReference, theSolid)
	, theVolumetric_(theReference, theSolid)
	, theReference_(theReference)
	, theSolid_(theSolid)
	, theSizeMapType_(SizeMap3d_IsoBackSizeType_ModifyBackSize)
	, theQualityType_(QualityMap3d_VLRMS3RATIO)
	, SurfaceMeshOnly_(Standard_False)
	, UseExactMetricForSurfaceMeshing_(Standard_False)
{
}

void AutLib::MeshLib::Mesh3d_Region::Perform()
{
	if (NOT theReference_) { THROW_STANDARD_EXCEPTION("Null Reference"); }
	if (NOT theSolid_) { THROW_STANDARD_EXCEPTION("Null Solid"); }

	CreateSizeMap();

	TColMesh3d_ADTree3dOfNode Engine;
	Engine.SetCoordinateFunction(&Mesh3d_NodeTools::GetCoordOf);

	theMesh_ = new Mesh3d_CavityRemover(*theSizeMap_, &Engine);

	Get_Pointer(Aft) = Global_DownCast(Mesh3d_CavityRemover, theMesh_);
	Aft->Import(*theSolid_);
	if (SurfaceMeshOnly_) Aft->SetToSurfaceMeshOnly();
	if (theVerbose_) Aft->SetVerbosity(theVerbose_ - 1);
	if (UseExactMetricForSurfaceMeshing_) Aft->SetToUseExactMetricForSurfaceMesh();

	Try_Exception_Handle_Exit(Aft->Perform());

	if (SurfaceMeshOnly_) return;

	Global_Handle(Mesh3d_QualityMap) QualityMap(0);
	switch (theQualityType_)
	{
	case QualityMap3d_MAXANGLE: { QualityMap = new QualityMap3d_MaxAngle; break; }
	case QualityMap3d_MEANSINE: { QualityMap = new QualityMap3d_MeanSine; break; }
	case QualityMap3d_MINANGLE: { QualityMap = new QualityMap3d_MinAngle; break; }
	case QualityMap3d_MINSINE: { QualityMap = new QualityMap3d_MinSine; break; }
	case QualityMap3d_RADIUSRATIO: { QualityMap = new  QualityMap3d_RadiusRatio; break; }
	case QualityMap3d_VLRMS3RATIO: { QualityMap = new QualityMap3d_Vlrms3Ratio; break; }
	case QualityMap3d_WARPEDMINSINE: { QualityMap = new QualityMap3d_WarpedMinSine; break; }
	default: THROW_STANDARD_EXCEPTION("Invalid Quality Map"); break;
	}
	
	Mesh3d_Optimization Optimization(*QualityMap, *theSizeMap_, *theMesh_);
	Optimization.Perform();

	FreePointer(QualityMap);
}

void AutLib::MeshLib::Mesh3d_Region::SetVerbosity(const Standard_Integer theVerbose)
{
	theVerbose_ = theVerbose;
}

void AutLib::MeshLib::Mesh3d_Region::SetToSurfaceMeshOnly()
{
	SurfaceMeshOnly_ = Standard_True;
}

void AutLib::MeshLib::Mesh3d_Region::SetToUseExactMetricForSurfaceMeshing()
{
	UseExactMetricForSurfaceMeshing_ = Standard_True;
}

void AutLib::MeshLib::Mesh3d_Region::ExportQualityToPlt(fstream & File) const
{
	theMesh_->ExportQualityToPlt(File, theQualityType_);
}

void AutLib::MeshLib::Mesh3d_Region::ExportBoundaryQualityMeshToPlt(fstream & File) const
{
	theMesh_->ExportBoundaryQualityMeshToPlt(File);
}

void AutLib::MeshLib::Mesh3d_Region::ExportSizeMap(fstream & File) const
{
	theSizeMap_->ExportSizeMapToPlt(File);
}

void AutLib::MeshLib::Mesh3d_Region::CreateSizeMap()
{
	if (NOT theReference_) { THROW_STANDARD_EXCEPTION("Null Reference"); }

	Global_Handle(GeoMesh_BackGroundMesh3d) BoundarySize = theBoundaries_.CalcSizeMap();
	Global_Handle(GeoMesh_BackGroundMesh3d) VolumetricSize = theVolumetric_.CalcSizeMap();

	SizeMap3d_UnionSizeMaps Operator;
	if (BoundarySize) Operator.ImportSizeMap(BoundarySize);
	if (VolumetricSize) Operator.ImportSizeMap(VolumetricSize);

	Operator.Perform();

	Global_Handle(GeoMesh_BackGroundMesh3d) BackMesh = Operator.BackGroundMesh();

	theBoundaries_.ReleaseMemory();
	theVolumetric_.ReleaseMemory();

	if (NOT BackMesh)
	{
		theSizeMap_ = new SizeMap3d_UniSize(theReference_->BaseSize());
		return;
	}

	switch (theSizeMapType_)
	{
	case SizeMap3d_IsoBackSizeType_UniSize:
		theSizeMap_ = new SizeMap3d_UniSize(theReference_->BaseSize());
		break;
	case SizeMap3d_IsoBackSizeType_StdBackSize:
		theSizeMap_ = new SizeMap3d_StdBackSize(theReference_->BaseSize(), *BackMesh);
		break;
	case SizeMap3d_IsoBackSizeType_ModifyBackSize:
		theSizeMap_ = new SizeMap3d_ModifyBackSize(theReference_->BaseSize(), *BackMesh);
		break;
	case SizeMap3d_IsoBackSizeType_FullIntBackSize:
		theSizeMap_ = new SizeMap3d_FullIntBackSize(theReference_->BaseSize(), *BackMesh);
		break;
	default:
	{
		THROW_STANDARD_EXCEPTION("Wrong IsoSizeMap Type");
		return;
	}
	}
}