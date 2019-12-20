#include <FvConnectivities_General.hxx>

AutLib::FvLib::FvConnectivities_General::FvConnectivities_General()
{
}

void AutLib::FvLib::FvConnectivities_General::Import(fstream & File)
{
	Label Size;
	File >> Size;

	theValues_.Resize(Size);
	forThose(Index, 0, MaxIndexOf(theValues_))
		File >> theValues_[Index];
}