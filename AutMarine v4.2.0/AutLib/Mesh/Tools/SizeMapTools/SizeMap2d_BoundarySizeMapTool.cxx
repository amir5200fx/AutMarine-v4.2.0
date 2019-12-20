#include <SizeMap2d_BoundarySizeMapTool.hxx>

#include <Cad2d_Plane.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Cad2d_BlockPointOnPlane.hxx>
#include <Cad2d_BlockEdgeOnPlane.hxx>

using namespace AutLib;
using namespace GeoLib;

AutLib::MeshLib::SizeMap2d_BoundarySizeMapTool::SizeMap2d_BoundarySizeMapTool
(
	const Global_Handle(Mesh_ReferenceValues) theReference,
	const Global_Handle(M_CAD Cad2d_Plane) thePlane
)
	: SizeMap2d_SizeMapTool(theReference, thePlane)
{
}

AutLib::MeshLib::SizeMap2d_BoundarySizeMapTool::~SizeMap2d_BoundarySizeMapTool()
{
}

void AutLib::MeshLib::SizeMap2d_BoundarySizeMapTool::RetrievePointsTo(TColCad2d_HAry1dOfPointOnPlane & Points) const
{
	TColStd_Ary1dOfString Patches;
	thePointPatches_.RetrieveTo(Patches);

	TColCad2d_HBasicQueueOfPointOnPlane QPoints;

	if (NOT thePlane_->Corners()) { THROW_STANDARD_EXCEPTION(" The solid has no points"); }

	Get_Const_Object(PointPatches) = *thePlane_->Corners();

	forThose
	(
		Index,
		0,
		MaxIndexOf(Patches)
	)
	{
		Global_Handle(M_CAD Cad2d_BlockPointOnPlane) Patch = PointPatches.GetBlockPoint(Patches[Index]);

		if (NOT Patch) { THROW_STANDARD_EXCEPTION(" Invalid Data"); }

		Patch->RetrieveTo(QPoints);
	}

	QPoints.RetrieveTo(Points);
}

void AutLib::MeshLib::SizeMap2d_BoundarySizeMapTool::RetrieveCurvesTo(TColCad2d_HAry1dOfEdgeOnPlane & Edges) const
{
	TColStd_Ary1dOfString Patches;
	theCurvePatches_.RetrieveTo(Patches);

	TColCad2d_HBasicQueueOfEdgeOnPlane QCurves;

	if (NOT thePlane_->Edges()) { THROW_STANDARD_EXCEPTION(" The solid has no Curves"); }

	Get_Const_Object(CurvePatches) = *thePlane_->Edges();

	forThose
	(
		Index,
		0,
		MaxIndexOf(Patches)
	)
	{
		Global_Handle(M_CAD Cad2d_BlockEdgeOnPlane) Patch = CurvePatches.GetBlockCurve(Patches[Index]);

		if (NOT Patch) { THROW_STANDARD_EXCEPTION(" Invalid Data"); }

		Patch->RetrieveTo(QCurves);
	}

	QCurves.RetrieveTo(Edges);
}
