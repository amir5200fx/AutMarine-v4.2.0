#include <Mesh2d_BoundarySizeMapControl.hxx>

#include <SizeMap2d_AdaptiveCurvesSizeMapTool.hxx>

using namespace AutLib;
using namespace MeshLib;

AutLib::MeshLib::Mesh2d_BoundarySizeMapControl::Mesh2d_BoundarySizeMapControl
(
	const Global_Handle(Mesh_ReferenceValues) theReference, 
	const Global_Handle(M_CAD Cad2d_Plane) thePlane
)
	: Mesh2d_SizeMapControl(theReference, thePlane)
{
}

AutLib::MeshLib::Mesh2d_BoundarySizeMapControl::~Mesh2d_BoundarySizeMapControl()
{
}

void AutLib::MeshLib::Mesh2d_BoundarySizeMapControl::CreateNewMap(const Standard_String & theName)
{
	Global_Handle(SizeMap2d_SizeMapTool) Map = new SizeMap2d_AdaptiveCurvesSizeMapTool(theReference_, thePlane_);
	Mesh2d_SizeMapControl::ImportMap(Map, theName);
}

Global_Handle(SizeMap2d_AdaptiveCurvesSizeMapTool) AutLib::MeshLib::Mesh2d_BoundarySizeMapControl::SelectMap(const Standard_String & theName) const
{
	TColSizeMap2d_StringMapOfHSizeMapTool::const_iterator Iter = theBoundaries_.find(theName);
	if (Iter EQUAL theBoundaries_.end())
		return 0;

	return Global_DownCast(SizeMap2d_AdaptiveCurvesSizeMapTool, Iter->second);
}