#include <FvConnectivities_Dual.hxx>

AutLib::FvLib::FvConnectivities_Dual::FvConnectivities_Dual()
{
}

void AutLib::FvLib::FvConnectivities_Dual::Import(fstream & File)
{
	File >> theV0_ >> theV1_;
}