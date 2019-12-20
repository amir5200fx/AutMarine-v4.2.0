#include <FvGeom_QuadConnectivity2d.hxx>

AutLib::FvLib::FvGeom_QuadConnectivity2d::FvGeom_QuadConnectivity2d()
{
}

void AutLib::FvLib::FvGeom_QuadConnectivity2d::Import(fstream & File)
{
	File >> theV0_ >> theV1_ >> theV2_ >> theV3_;
}