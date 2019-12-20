#include <SizeMap2d_FullIntAnIsoRefineSearchRefineElementSize.hxx>

static const Standard_Real DEFAULT_CORRECTIONFACTOR = 1.0;

AutLib::MeshLib::SizeMap2d_FullIntAnIsoRefineSearchRefineElementSize::SizeMap2d_FullIntAnIsoRefineSearchRefineElementSize
(
	const Global_Handle(Mesh2d_SizeMap) theSizeMap,
	const Global_Handle(Mesh2d_MetricMap) theMetricMap,
	const Standard_Real theCoefficent,
	const Standard_Real theDelta
)
	: SizeMap2d_FullIntAnIso(theSizeMap, theMetricMap)
	, theCoeff_(theCoefficent)
	, theDelta_(theDelta)
	, theCorrectionFactor_(DEFAULT_CORRECTIONFACTOR)
{
}