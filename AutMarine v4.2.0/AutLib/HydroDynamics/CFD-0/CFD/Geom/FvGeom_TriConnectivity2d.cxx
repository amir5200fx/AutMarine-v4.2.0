#include <FvGeom_TriConnectivity2d.hxx>

AutLib::FvLib::FvGeom_TriConnectivity2d::FvGeom_TriConnectivity2d()
{
}

void AutLib::FvLib::FvGeom_TriConnectivity2d::Import(fstream & File)
{
	File >> theV0_ >> theV1_ >> theV2_;
}