#include <Mesh_Conditions.hxx>

AutLib::MeshLib::Mesh_Conditions::Mesh_Conditions()
	: CustomBoundaryGrowthRate_(Standard_False)
	, CustomSurfaceSize_(Standard_False)
	, theCustomSurfaceCurvature_(Mesh_SurfaceCurvatureInfo_Continuum_Values)
{
}

void AutLib::MeshLib::Mesh_Conditions::SetCustomBoundaryGrowthRate(const Standard_Boolean CustomBoundaryGrowthRate)
{
	CustomBoundaryGrowthRate_ = CustomBoundaryGrowthRate;
}

void AutLib::MeshLib::Mesh_Conditions::SetCustomSurfaceSize(const Standard_Boolean CustomSurfaceSize)
{
	CustomSurfaceSize_ = CustomSurfaceSize;
}

void AutLib::MeshLib::Mesh_Conditions::SetCustomSurfaceCurvature(const Mesh_SurfaceCurvatureInfo SurfaceCurvatureInfo)
{
	theCustomSurfaceCurvature_ = SurfaceCurvatureInfo;
}
