#include <FvGeom_Face2d.hxx>

AutLib::FvLib::FvGeom_Face2d::FvGeom_Face2d()
{
}

void AutLib::FvLib::FvGeom_Face2d::Import(fstream & File)
{
	File >> theIndex_;
	theConnectivity_.Import(File);
	File >> thephysics_;
}