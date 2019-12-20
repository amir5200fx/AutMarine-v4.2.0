#include <MetricMap2d_MetricMapTool.hxx>

#include <Entity_Metric1Tools.hxx>
#include <GeoMesh_BackGroundMetric2d.hxx>

using namespace AutLib;
using namespace GeoLib;

AutLib::MeshLib::MetricMap2d_MetricMapTool::~MetricMap2d_MetricMapTool()
{
	FreePointer(theBackMetric_);
}

void AutLib::MeshLib::MetricMap2d_MetricMapTool::SetH1(const Standard_Real theH1)
{
	theH1_ = theH1;
}

void AutLib::MeshLib::MetricMap2d_MetricMapTool::SetH2(const Standard_Real theH2)
{
	theH2_ = theH2;
}

void AutLib::MeshLib::MetricMap2d_MetricMapTool::SetE1(const Geom_Pnt2d & theE1)
{
	theE1_ = theE1;
}

void AutLib::MeshLib::MetricMap2d_MetricMapTool::SetE2(const Geom_Pnt2d & theE2)
{
	theE2_ = theE2;
}

void AutLib::MeshLib::MetricMap2d_MetricMapTool::SetIntersection(GeoLib::Entity_Metric1(*theInterSection)(const M_GEO Entity_Metric1 &, const M_GEO Entity_Metric1 &))
{
	InterSection = theInterSection;
}

void AutLib::MeshLib::MetricMap2d_MetricMapTool::ExportToPlt(fstream & File) const
{
	if (NOT theBackMetric_) return;

	theBackMetric_->ExportMeshToPlt(File);
	theBackMetric_->ExportToPlt(File);
}

AutLib::MeshLib::MetricMap2d_MetricMapTool::MetricMap2d_MetricMapTool()
	: theBackMetric_(0)
	, theH1_(1)
	, theH2_(1)
{
	InterSection = &Entity_Metric1Tools::IntersectionPD;
}