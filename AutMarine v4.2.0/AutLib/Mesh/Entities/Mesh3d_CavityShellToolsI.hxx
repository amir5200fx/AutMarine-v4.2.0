#pragma once
inline
Standard_Boolean AutLib::MeshLib::Mesh3d_CavityShellTools::IsLess
(
	Global_Handle(Mesh3d_CavityShell) const & theShell0, 
	Global_Handle(Mesh3d_CavityShell) const & theShell1
)
{
	Debug_Null_Pointer(theShell0);
	Debug_Null_Pointer(theShell1);

	return theShell0->Index() < theShell1->Index();
}