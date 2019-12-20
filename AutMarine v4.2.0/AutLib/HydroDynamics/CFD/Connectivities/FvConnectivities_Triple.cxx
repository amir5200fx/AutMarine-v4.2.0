#include <FvConnectivities_Triple.hxx>

AutLib::FvLib::FvConnectivities_Triple::FvConnectivities_Triple()
	: theV0_((Label)0)
	, theV1_((Label)0)
	, theV2_((Label)0)
{
}

void AutLib::FvLib::FvConnectivities_Triple::Import(fstream & File)
{
	File >> theV0_ >> theV1_ >> theV2_;
}