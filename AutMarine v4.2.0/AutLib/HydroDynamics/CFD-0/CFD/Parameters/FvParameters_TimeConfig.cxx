#include <FvParameters_TimeConfig.hxx>

#include <FvParameters_TimeConfigInfo.hxx>

AutLib::FvLib::FvParameters_TimeConfig::FvParameters_TimeConfig()
	: theStart_(FvParameters_TimeConfigInfo::Start())
	, theEnd_(FvParameters_TimeConfigInfo::End())
{
}

AutLib::FvLib::FvParameters_TimeConfig::~FvParameters_TimeConfig()
{
}

void AutLib::FvLib::FvParameters_TimeConfig::SetStart(const Standard_Real theValue)
{
	theStart_ = theValue;
}

void AutLib::FvLib::FvParameters_TimeConfig::SetEnd(const Standard_Real theValue)
{
	theEnd_ = theValue;
}
