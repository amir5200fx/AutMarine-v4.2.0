#include <Mesh_ReferenceValues.hxx>

static const Standard_Real DEFAULT_SPAN_ANGLE = 25;

AutLib::MeshLib::Mesh_ReferenceValues::Mesh_ReferenceValues(const Standard_Real BaseSize)
	: theBaseSize_(BaseSize)
	, theDefaultGrowthRate_(Mesh_VariationRateInfo_MODERATE)
{
	theSurfaceCurvature_.SetCurvatureInfo(Mesh_SurfaceCurvatureInfo_Continuum_Values);

	theSurfaceCurvature_.SetSpanAngle(DEFAULT_SPAN_ANGLE);

	theSurfaceSize_.SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo_RelativeToBase);
	theSurfaceSize_.SetSizeMethod(Mesh_SizeMethodInfo_MinAndTarget);

	theSurfaceSize_.SetTargetSize(100.0);
	theSurfaceSize_.SetMinSize(10.0);
}

void AutLib::MeshLib::Mesh_ReferenceValues::SetDefaultGrowthRate(Mesh_VariationRateInfo Rate)
{
	theDefaultGrowthRate_ = Rate;
}