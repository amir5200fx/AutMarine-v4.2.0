#include <Mesh3d_BoundarySizeMapControl.hxx>

#include <SizeMap3d_UniformSurfacesSizeMapTool.hxx>

using namespace AutLib;
using namespace MeshLib;

AutLib::MeshLib::Mesh3d_BoundarySizeMapControl::Mesh3d_BoundarySizeMapControl
(
	const Global_Handle(Mesh_ReferenceValues) theReference,
	const Global_Handle(M_CAD Cad3d_Solid)theSolid
)
	: Mesh3d_SizeMapControl(theReference, theSolid)
{
}

AutLib::MeshLib::Mesh3d_BoundarySizeMapControl::~Mesh3d_BoundarySizeMapControl()
{
}

void AutLib::MeshLib::Mesh3d_BoundarySizeMapControl::CreateNewMap(const Standard_String & theName)
{
	Global_Handle(SizeMap3d_SizeMapTool) Map = new SizeMap3d_UniformSurfacesSizeMapTool(theReference_, theSolid_);
	Mesh3d_SizeMapControl::ImportMap(Map, theName);
}

Global_Handle(SizeMap3d_UniformSurfacesSizeMapTool) AutLib::MeshLib::Mesh3d_BoundarySizeMapControl::SelectMap(const Standard_String & theName) const
{
	TColSizeMap3d_StringMapOfHSizeMapTool::const_iterator Iter = theBoundaries_.find(theName);
	if (Iter EQUAL theBoundaries_.end())
		return 0;

	return Global_DownCast(SizeMap3d_UniformSurfacesSizeMapTool, Iter->second);
}