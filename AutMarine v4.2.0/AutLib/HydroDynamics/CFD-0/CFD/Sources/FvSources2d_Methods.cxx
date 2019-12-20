#include <FvSources2d_Methods.hxx>

AutLib::FvLib::FvSources2d_Methods::FvSources2d_Methods()
{
}

void AutLib::FvLib::FvSources2d_Methods::Insert(const Global_Handle(FvSources2d) theSource)
{
	theMethods_.EnQueue((Global_Handle(FvSources2d))theSource);
}

void AutLib::FvLib::FvSources2d_Methods::RetrieveTo(FvSources2d_List & theSources)
{
	theMethods_.RetrieveTo(theSources);
}