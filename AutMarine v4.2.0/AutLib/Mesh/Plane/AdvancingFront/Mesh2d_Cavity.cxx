#include <Mesh2d_Cavity.hxx>

#include <Mesh2d_EdgeTools.hxx>

AutLib::MeshLib::Mesh2d_Cavity::Mesh2d_Cavity()
{
	Set_Numbering(theCertainty_, Mesh2d_EdgeTools::IsLess);

	Set_Numbering(theUnCertainty_, Mesh2d_EdgeTools::IsLess);

	theCertainty_.SetName(" Mesh2d_Cavity - Certainty Tree");

	theUnCertainty_.SetName(" Mesh2d_Cavity - UnCertainty Tree");
}