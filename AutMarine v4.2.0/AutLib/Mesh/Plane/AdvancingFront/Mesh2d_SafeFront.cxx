#include <Mesh2d_SafeFront.hxx>

#include <Mesh2d_NodeTools.hxx>
#include <Mesh2d_EdgeTools.hxx>

AutLib::MeshLib::Mesh2d_SafeFront::Mesh2d_SafeFront()
{
	Set_Numbering(theCurrentLevels_, Mesh2d_EdgeTools::IsLess);
	Set_Numbering(theNextLevels_, Mesh2d_EdgeTools::IsLess);

	theCurrentLevels_.SetName(" Front Tree- Current Levels");

	theNextLevels_.SetName(" Front Tree- Next Levels");
}