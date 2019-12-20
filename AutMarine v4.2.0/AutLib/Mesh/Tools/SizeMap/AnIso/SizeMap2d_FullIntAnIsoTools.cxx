#include <SizeMap2d_FullIntAnIsoTools.hxx>

#include <Mesh2d_SizeMap.hxx>
#include <SizeMap2d_FullIntAnIso.hxx>
#include <SizeMap2d_FullIntAnIsoRefineSearch.hxx>
#include <SizeMap2d_FullIntAnIsoRefineSearchRefineElementSize.hxx>

using namespace AutLib;
using namespace MeshLib;

Global_Handle(SizeMap2d_FullIntAnIso) AutLib::MeshLib::SizeMap2d_FullIntAnIsoTools::CreateStdAnIsoSizeMap
(
	const Global_Handle(Mesh2d_SizeMap) theSizeMap,
	const Global_Handle(Mesh2d_MetricMap) theMetricMap
)
{
	return new SizeMap2d_FullIntAnIso(theSizeMap, theMetricMap);
}

Global_Handle(SizeMap2d_FullIntAnIso) AutLib::MeshLib::SizeMap2d_FullIntAnIsoTools::CreateModifiedSearchAnIsoSizeMap
(
	const Global_Handle(Mesh2d_SizeMap) theSizeMap,
	const Global_Handle(Mesh2d_MetricMap) theMetricMap
)
{
	return new SizeMap2d_FullIntAnIsoRefineSearch(theSizeMap, theMetricMap);
}

Global_Handle(SizeMap2d_FullIntAnIso) AutLib::MeshLib::SizeMap2d_FullIntAnIsoTools::CreateModifiedSearchAndElementSizeAnIsoSizeMap
(
	const Global_Handle(Mesh2d_SizeMap) theSizeMap,
	const Global_Handle(Mesh2d_MetricMap) theMetricMap
)
{
	return new SizeMap2d_FullIntAnIsoRefineSearchRefineElementSize(theSizeMap, theMetricMap);
}