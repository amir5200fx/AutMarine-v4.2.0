#include <SizeMap2d_SharpCornersSizeMapTool.hxx>

#include <Geometry_Tools.hxx>
#include <Cad2d_Plane.hxx>
#include <Cad2d_PointOnPlane.hxx>
#include <Cad2d_BlockPointOnPlane.hxx>
#include <Cad2d_EdgeOnPlaneTools.hxx>

using namespace AutLib;
using namespace CadLib;
using namespace GeoLib;

static const Standard_Real DEFAULT_SHARPNESS = 30;

AutLib::MeshLib::SizeMap2d_SharpCornersSizeMapTool::SizeMap2d_SharpCornersSizeMapTool
(
	const Global_Handle(Mesh_ReferenceValues) theReference,
	const Global_Handle(M_CAD Cad2d_Plane)thePlane
)
	: SizeMap2d_PointsSizeMapTool(theReference, thePlane)
	, theSharpAngle_(DEFAULT_SHARPNESS)
{
}

AutLib::MeshLib::SizeMap2d_SharpCornersSizeMapTool::~SizeMap2d_SharpCornersSizeMapTool()
{
}

void AutLib::MeshLib::SizeMap2d_SharpCornersSizeMapTool::SetAngle(const Standard_Real theAngle)
{
	theSharpAngle_ = theAngle;
}

//void AutLib::MeshLib::SizeMap2d_SharpCornersSizeMapTool::CreateSizeMap()
//{
//	Global_Handle(Cad2d_Plane) Plane = thePlane_->Copy();
//	thePlane_ = Plane;
//
//	Plane->CreateSharpCornerBlock(theSharpAngle_, "Sharp Corners");
//
//	thePointPatches_.Clear();
//
//	ImportPointPatch("Sharp Corners");
//
//	SizeMap2d_PointsSizeMapTool::CreateSizeMap();
//
//	FreePointer(Plane);
//}

void AutLib::MeshLib::SizeMap2d_SharpCornersSizeMapTool::CreateSizeMap()
{
	//Global_Handle(Cad2d_Plane) Plane = thePlane_->Copy();
	//thePlane_ = Plane;

	TColCad2d_HAry1dOfEdgeOnPlane Edges;
	SizeMap2d_BoundarySizeMapTool::RetrieveCurvesTo(Edges);

	if (Edges.IsEmpty()) { return; }

	TColCad2d_HAry1dOfPointOnPlane Corners = Cad2d_EdgeOnPlaneTools::RetrievePointsFrom(Edges);

	Get_Pointer(Points) = thePlane_->Corners();
	Debug_Null_Pointer(Points);

	if (Points->NbBlocks() > 1)
	{
		Points->CompactBlocks("Default Point Block");
	}

	TColCad2d_HAry1dOfBlockPointOnPlane Blocks;
	Points->RetrieveTo(Blocks);

	Debug_If_Condition_Message(Blocks.Size() NOT_EQUAL 1, "Conflict Data");

	Global_Handle(Cad2d_BlockPointOnPlane) Block = Points->SelectBlockPoint(Blocks[0]->Name());
	Debug_Null_Pointer(Block);

	Standard_Real Angle = Geometry_Tools::DegToRadian(theSharpAngle_);
	forThose
	(
		Index,
		0, 
		MaxIndexOf(Corners)
	)
	{
		Debug_Null_Pointer(Corners[Index]);

		if(Corners[Index]->IsSharp(Angle)) Block->SelectPoint(Corners[Index]->Index());
	}

	Points->Split("Sharp Corners");

	thePointPatches_.Clear();

	ImportPointPatch("Sharp Corners");

	SizeMap2d_PointsSizeMapTool::CreateSizeMap();

	//FreePointer(Plane);
}