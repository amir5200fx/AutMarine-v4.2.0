#include <Mesh3d_Cavity.hxx>

#include <Mesh3d_FacetTools.hxx>

AutLib::MeshLib::Mesh3d_Cavity::Mesh3d_Cavity()
{
	Set_Numbering(theCertainty_, Mesh3d_FacetTools::IsLess);

	Set_Numbering(theUnCertainty_, Mesh3d_FacetTools::IsLess);

	theCertainty_.SetName(" Mesh3d_Cavity - Certainty Tree");

	theUnCertainty_.SetName(" Mesh3d_Cavity - UnCertainty Tree");
}