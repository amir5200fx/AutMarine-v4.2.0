#include <Mesh3d_VolumetricSizeMapControl.hxx>

#include <SizeMap3d_PrimitiveShapesSizeMapTool.hxx>

using namespace AutLib;
using namespace MeshLib;

AutLib::MeshLib::Mesh3d_VolumetricSizeMapControl::Mesh3d_VolumetricSizeMapControl
(
	const Global_Handle(Mesh_ReferenceValues) theReference,
	const Global_Handle(M_CAD Cad3d_Solid)theSolid
)
	: Mesh3d_SizeMapControl(theReference, theSolid)
{
}

AutLib::MeshLib::Mesh3d_VolumetricSizeMapControl::~Mesh3d_VolumetricSizeMapControl()
{
}

void AutLib::MeshLib::Mesh3d_VolumetricSizeMapControl::CreateNewMap(const Standard_String & theName)
{
	Global_Handle(SizeMap3d_SizeMapTool) Map = new SizeMap3d_PrimitiveShapesSizeMapTool(theReference_, theSolid_);
	Mesh3d_SizeMapControl::ImportMap(Map, theName);
}

Global_Handle(SizeMap3d_PrimitiveShapesSizeMapTool) AutLib::MeshLib::Mesh3d_VolumetricSizeMapControl::SelectMap(const Standard_String & theName) const
{
	TColSizeMap3d_StringMapOfHSizeMapTool::const_iterator Iter = theBoundaries_.find(theName);
	if (Iter EQUAL theBoundaries_.end())
		return 0;

	return Global_DownCast(SizeMap3d_PrimitiveShapesSizeMapTool, Iter->second);
}