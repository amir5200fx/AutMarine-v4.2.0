#include <Mesh2d_Region.hxx>

#include <Entity_Metric2.hxx>
#include <Entity_Metric1Tools.hxx>
#include <GeoMesh_BackGroundMesh2d.hxx>
#include <SizeMap2d_UnionSizeMaps.hxx>
#include <SizeMap2d_UnionMetricMaps.hxx>
#include <SizeMap2d_UniSize.hxx>
#include <SizeMap2d_StdBackSize.hxx>
#include <SizeMap2d_ModifyBackSize.hxx>
#include <SizeMap2d_FullIntBackSize.hxx>
#include <SizeMap2d_FullIntAnIso.hxx>
#include <SizeMap2d_FullIntAnIsoRefineSearch.hxx>
#include <SizeMap2d_FullIntAnIsoRefineSearchRefineElementSize.hxx>
#include <SizeMap2d_PrimitiveShapesSizeMapTool.hxx>
#include <MetricMap2d_PrimitivesMetricMapTool.hxx>
#include <MetricMap2d_StdBackMetric.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh2d_NodeTools.hxx>
#include <Mesh2d_BasicAft.hxx>
#include <Mesh2d_Optimization.hxx>
#include <QualityMap2d_Vlrms2Ratio.hxx>
#include <TColMesh2d_ADTree2dOfNode.hxx>

using namespace AutLib;
using namespace GeoLib;
using namespace MeshLib;

AutLib::MeshLib::Mesh2d_Region::Mesh2d_Region
(
	const Global_Handle(Mesh_ReferenceValues) theReference,
	const Global_Handle(M_CAD Cad2d_Plane)thePlane
)
	: theBoundaries_(theReference, thePlane)
	, theFeatures_(theReference, thePlane)
	, theVolumetrics_(theReference, thePlane)
	, theReference_(theReference)
	, thePlane_(thePlane)
	, theSizeMapType_(SizeMap2d_IsoBackSizeType_ModifyBackSize)
	, theAnIsoSizeMapType_(SizeMap2d_AnIsoBackSizeType_FullIntAnIsoRefineSearchRefineElementSize)
	, IsAnIsotropic_(Standard_False)
{
}

void AutLib::MeshLib::Mesh2d_Region::SetIsoSizeMapType(const SizeMap2d_IsoBackSizeType theIsoSizeMapType)
{
	theSizeMapType_ = theIsoSizeMapType;
}

void AutLib::MeshLib::Mesh2d_Region::SetAnIsoSizeMapType(const SizeMap2d_AnIsoBackSizeType theAnIsoSizeMapType)
{
	theAnIsoSizeMapType_ = theAnIsoSizeMapType;
}

void AutLib::MeshLib::Mesh2d_Region::Perform()
{
	if (NOT theReference_) { THROW_STANDARD_EXCEPTION("Null Reference"); }
	if (NOT thePlane_) { THROW_STANDARD_EXCEPTION("Null Plane"); }

	CreateSizeMap();

	CreateMetricMap();

	TColMesh2d_ADTree2dOfNode Engine;
	Engine.SetCoordinateFunction(&Mesh2d_NodeTools::GetCoordOf);

	Global_Handle(Mesh2d_SizeMap) AnIsoSizeMap(0);
	if (theMetricMap_)
	{
		switch (theAnIsoSizeMapType_)
		{
		case SizeMap2d_AnIsoBackSizeType_FullIntAnIso:
			AnIsoSizeMap = new SizeMap2d_FullIntAnIso(theSizeMap_, theMetricMap_);
			break;
		case SizeMap2d_AnIsoBackSizeType_FullIntAnIsoRefineSearch:
			AnIsoSizeMap = new SizeMap2d_FullIntAnIsoRefineSearch(theSizeMap_, theMetricMap_);
			break;
		case SizeMap2d_AnIsoBackSizeType_FullIntAnIsoRefineSearchRefineElementSize:
			AnIsoSizeMap = new SizeMap2d_FullIntAnIsoRefineSearchRefineElementSize(theSizeMap_, theMetricMap_);
			break;
		default:
			THROW_STANDARD_EXCEPTION("Wrong AnIsoSizeMap Type");
			return;
		}
	}

	if (AnIsoSizeMap)
	{
		theMesh_ = new Mesh2d_BasicAft(*AnIsoSizeMap, &Engine);
	}
	else
	{
		theMesh_ = new Mesh2d_BasicAft(*theSizeMap_, &Engine);
	}

	Get_Pointer(Aft) = Global_DownCast(Mesh2d_BasicAft, theMesh_);
	Aft->Import(*thePlane_);
	if (theVerbose_ > 1) Aft->SetVerbosity(theVerbose_ - 1);

	Try_Exception_Handle_Exit(Aft->Perform());

	QualityMap2d_Vlrms2Ratio QualityMap;
	Mesh2d_Optimization Optimization(QualityMap, *theSizeMap_, theMetricMap_, *theMesh_);

	Optimization.Perform();

	FreePointer(AnIsoSizeMap);
}

void AutLib::MeshLib::Mesh2d_Region::SetVerbosity(const Standard_Integer theVerbose)
{
	theVerbose_ = theVerbose;
}

void AutLib::MeshLib::Mesh2d_Region::ExportQualityToPlt(fstream & File) const
{
	if (theMetricMap_)
	{
		SizeMap2d_FullIntAnIso AnIso(theSizeMap_, theMetricMap_);
		theMesh_->ExportQualityToPlt(File, AnIso);
	}
	else
	{
		theMesh_->ExportQualityToPlt(File, *theSizeMap_);
	}
}

void AutLib::MeshLib::Mesh2d_Region::CreateSizeMap()
{
	if (NOT theReference_) { THROW_STANDARD_EXCEPTION("Null Reference"); }

	Global_Handle(GeoMesh_BackGroundMesh2d) BoundarySize = theBoundaries_.CalcSizeMap();
	Global_Handle(GeoMesh_BackGroundMesh2d) FeatureSize = theFeatures_.CalcSizeMap();
	Global_Handle(GeoMesh_BackGroundMesh2d) VolumetricSize = theVolumetrics_.CalcSizeMap();

	SizeMap2d_UnionSizeMaps Operator;
	if (BoundarySize) Operator.ImportSizeMap(BoundarySize);
	if (FeatureSize) Operator.ImportSizeMap(FeatureSize);
	if (VolumetricSize) Operator.ImportSizeMap(VolumetricSize);

	Operator.Perform();

	Global_Handle(GeoMesh_BackGroundMesh2d) BackMesh = Operator.BackGroundMesh();

	if (NOT BackMesh)
	{
		theSizeMap_ = new SizeMap2d_UniSize(theReference_->BaseSize());
		return;
	}

	switch (theSizeMapType_)
	{
	case SizeMap2d_IsoBackSizeType_UniSize:
		theSizeMap_ = new SizeMap2d_UniSize(theReference_->BaseSize());
		break;
	case SizeMap2d_IsoBackSizeType_StdBackSize:
		theSizeMap_ = new SizeMap2d_StdBackSize(theReference_->BaseSize(), *BackMesh);
		break;
	case SizeMap2d_IsoBackSizeType_ModifyBackSize:
		theSizeMap_ = new SizeMap2d_ModifyBackSize(theReference_->BaseSize(), *BackMesh);
		break;
	case SizeMap2d_IsoBackSizeType_FullIntBackSize:
		theSizeMap_ = new SizeMap2d_FullIntBackSize(theReference_->BaseSize(), *BackMesh);
		break;
	default:
	{
		THROW_STANDARD_EXCEPTION("Wrong IsoSizeMap Type");
		return;
	}
	}
}

void AutLib::MeshLib::Mesh2d_Region::CreateMetricMap()
{
	Get_Const_Object(Maps) = theVolumetrics_.Maps();

	ADT_BasicQueue<Global_Handle(MetricMap2d_PrimitivesMetricMapTool)> QMetricMaps;

	SizeMap2d_UnionMetricMaps Operator;
	TColSizeMap2d_StringMapOfHSizeMapTool::const_iterator Iter = Maps.begin();
	while (Iter NOT_EQUAL Maps.end())
	{
		Global_Handle(SizeMap2d_PrimitiveShapesSizeMapTool) Primitive = Global_DownCast(SizeMap2d_PrimitiveShapesSizeMapTool, Iter->second);

		if (Primitive->Metric())
		{
			Global_Handle(MetricMap2d_PrimitivesMetricMapTool) MetricMap = new MetricMap2d_PrimitivesMetricMapTool(Primitive);

			Get_Const_Object(Metric) = *Primitive->Metric();
			MetricMap->SetE1(Metric.E1());
			MetricMap->SetE2(Metric.E2());
			MetricMap->SetH1(Metric.H1());
			MetricMap->SetH2(Metric.H2());

			MetricMap->SetIntersection(&Entity_Metric1Tools::IntersectionSR);
			MetricMap->Perform();

			Operator.ImportSizeMap(MetricMap->Metric());

			QMetricMaps.EnQueue(MetricMap);
		}
		Iter++;
	}
	if (QMetricMaps.IsEmpty()) return;
	
	Operator.Perform();
	
	Debug_If_Condition_Message(NOT Operator.IsDone(), "UnionMetricMaps is not performed");

	theMetricMap_ = new MetricMap2d_StdBackMetric(*Operator.BackGroundMetric());
	
	ADT_Ary1d<Global_Handle(MetricMap2d_PrimitivesMetricMapTool)> MetricMaps;
	QMetricMaps.RetrieveTo(MetricMaps);

	FreeMemory(MetricMaps);
}