#include <FvGeom_GeneralConnectivity2d.hxx>

AutLib::FvLib::FvGeom_GeneralConnectivity2d::FvGeom_GeneralConnectivity2d()
{
}

void AutLib::FvLib::FvGeom_GeneralConnectivity2d::Import(fstream & File)
{
	Standard_Integer Size;
	File >> Size;

	theValues_.Resize(Size);
	forThose(Index, 0, MaxIndexOf(theValues_))
	{
		File >> theValues_[Index];
	}
}