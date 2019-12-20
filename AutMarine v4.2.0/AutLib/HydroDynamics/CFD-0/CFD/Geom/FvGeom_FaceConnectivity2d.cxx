#include <FvGeom_FaceConnectivity2d.hxx>

AutLib::FvLib::FvGeom_FaceConnectivity2d::FvGeom_FaceConnectivity2d()
{
}

void AutLib::FvLib::FvGeom_FaceConnectivity2d::Import(fstream & File)
{
	File >> theV0_ >> theV1_;
}