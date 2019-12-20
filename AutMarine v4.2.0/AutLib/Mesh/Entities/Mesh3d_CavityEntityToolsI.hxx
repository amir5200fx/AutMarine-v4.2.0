#pragma once
#include <Global_Debug.hxx>

inline
Standard_Boolean AutLib::MeshLib::Mesh3d_CavityEntityTools::IsLess
(
	Global_Handle(Mesh3d_CavityEntity) const & theCavity1,
	Global_Handle(Mesh3d_CavityEntity) const & theCavity2
)
{
	Debug_Null_Pointer(theCavity1);
	Debug_Null_Pointer(theCavity2);

	return theCavity1->Index() < theCavity2->Index();
}