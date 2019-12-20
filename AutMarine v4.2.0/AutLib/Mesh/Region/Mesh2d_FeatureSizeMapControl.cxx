#include <Mesh2d_FeatureSizeMapControl.hxx>

#include <SizeMap2d_SharpCornersSizeMapTool.hxx>

using namespace AutLib;
using namespace MeshLib;

AutLib::MeshLib::Mesh2d_FeatureSizeMapControl::Mesh2d_FeatureSizeMapControl
(
	const Global_Handle(Mesh_ReferenceValues) theReference,
	const Global_Handle(M_CAD Cad2d_Plane)thePlane
)
	: Mesh2d_SizeMapControl(theReference, thePlane)
{
}

AutLib::MeshLib::Mesh2d_FeatureSizeMapControl::~Mesh2d_FeatureSizeMapControl()
{
}

Global_Handle(SizeMap2d_SharpCornersSizeMapTool) AutLib::MeshLib::Mesh2d_FeatureSizeMapControl::SelectMap(const Standard_String & theName) const
{
	TColSizeMap2d_StringMapOfHSizeMapTool::const_iterator Iter = theBoundaries_.find(theName);
	if (Iter EQUAL theBoundaries_.end())
		return 0;

	return Global_DownCast(SizeMap2d_SharpCornersSizeMapTool, Iter->second);
}

void AutLib::MeshLib::Mesh2d_FeatureSizeMapControl::CreateNewMap(const Standard_String & theName)
{
	Global_Handle(SizeMap2d_SizeMapTool) Map = new SizeMap2d_SharpCornersSizeMapTool(theReference_, thePlane_);
	Mesh2d_SizeMapControl::ImportMap(Map, theName);
}
