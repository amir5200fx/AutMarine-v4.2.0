#include <SizeMap2d_FullIntAnIsoRefineSearch.hxx>

static const Standard_Real DEFAULT_CORRECTIONFACTOR = 1.0;

AutLib::MeshLib::SizeMap2d_FullIntAnIsoRefineSearch::SizeMap2d_FullIntAnIsoRefineSearch
(
	const Global_Handle(Mesh2d_SizeMap) theSizeMap,
	const Global_Handle(Mesh2d_MetricMap) theMetricMap
)
	: SizeMap2d_FullIntAnIso(theSizeMap, theMetricMap)
	, theCorrectionFactor_(DEFAULT_CORRECTIONFACTOR)
{
}