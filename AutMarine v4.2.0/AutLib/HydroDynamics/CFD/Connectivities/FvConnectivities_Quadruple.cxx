#include <FvConnectivities_Quadruple.hxx>

AutLib::FvLib::FvConnectivities_Quadruple::FvConnectivities_Quadruple()
{
}

void AutLib::FvLib::FvConnectivities_Quadruple::Import(fstream & File)
{
	File >> theV0_ >> theV1_ >> theV2_ >> theV3_;
}