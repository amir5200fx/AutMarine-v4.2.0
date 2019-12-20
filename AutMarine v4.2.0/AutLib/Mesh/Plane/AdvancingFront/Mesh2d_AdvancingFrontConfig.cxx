#include <Mesh2d_AdvancingFrontConfig.hxx>

AutLib::MeshLib::Mesh2d_AdvancingFrontConfig::Mesh2d_AdvancingFrontConfig()
{
}

void AutLib::MeshLib::Mesh2d_AdvancingFrontConfig::SetFrontType(const Mesh2d_FrontType & theType)
{
	theFrontType_ = theType;
}