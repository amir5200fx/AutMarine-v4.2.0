#include <FvVector_Laspack.hxx>

AutLib::FvLib::FvVector_Laspack::FvVector_Laspack()
{
}

AutLib::FvLib::FvVector_Laspack::~FvVector_Laspack()
{
	ReleaseMemory();
}

void AutLib::FvLib::FvVector_Laspack::Init(const Scalar theValue)
{
	V_SetAllCmp(&theVector_, (Real)theValue);
}

void AutLib::FvLib::FvVector_Laspack::Allocate(const Label theSize)
{
	V_Constr(&theVector_, (char*)FvVector::Name().c_str(), (size_t)theSize, InstanceType::Normal, True);
}

void AutLib::FvLib::FvVector_Laspack::ReleaseMemory()
{
	V_Destr(&theVector_);
}