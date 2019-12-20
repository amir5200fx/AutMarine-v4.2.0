#include <Cad3d_EntityOnSolid.hxx>

AutLib::CadLib::Cad3d_EntityOnSolid::Cad3d_EntityOnSolid()
	: theIndex_(0)
{
}

AutLib::CadLib::Cad3d_EntityOnSolid::Cad3d_EntityOnSolid(const Standard_Integer theIndex)
	: theIndex_(theIndex)
{
}

AutLib::CadLib::Cad3d_EntityOnSolid::~Cad3d_EntityOnSolid()
{
}

void AutLib::CadLib::Cad3d_EntityOnSolid::SetIndex(const Standard_Integer theIndex)
{
	theIndex_ = theIndex;
}