#include <SizeMap3d_SizeMapTool.hxx>

#include <Entity_Box3d.hxx>
#include <Cad3d_Solid.hxx>
#include <GeoMesh_BackGroundMesh3d.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh_VariationRate.hxx>

using namespace AutLib;
using namespace GeoLib;

AutLib::MeshLib::SizeMap3d_SizeMapTool::~SizeMap3d_SizeMapTool()
{
	FreePointer(theBackMesh_);
}

Standard_Real AutLib::MeshLib::SizeMap3d_SizeMapTool::ElementSize(const Geom_Pnt3d & Coord) const
{
	return theBackMesh_->ElementSize(Coord);
}

Entity_Box3d AutLib::MeshLib::SizeMap3d_SizeMapTool::BoundingBox(const Standard_Real theOffset) const
{
	return theSolid_->BoundingBox(theOffset);
}

void AutLib::MeshLib::SizeMap3d_SizeMapTool::SpecifyValues
(
	Standard_Real & theElementSize,
	Standard_Real & theMinElementSize,
	Standard_Real & theSpanAngle
) const
{
	Get_Const_Object(Reference) = *theReference_;

	if (theConditions_.CustomSurfaceSize())
	{
		// Specify Relative or Absolute sizes
		if (theValues_.SurfaceSize().RelativeAbsolute() EQUAL Mesh_RelativeAbsoluteInfo_Absolute)
		{
			theElementSize = theValues_.SurfaceSize().TargetSize();
			theMinElementSize = theValues_.SurfaceSize().MinSize();
		}
		else
		{ // is Relative to Base
			theElementSize = theValues_.SurfaceSize().TargetSize()*Reference.BaseSize() / 100.0;
			theMinElementSize = theValues_.SurfaceSize().MinSize()*Reference.BaseSize() / 100.0;
		}
	}
	else
	{
		if (Reference.SurfaceSize().RelativeAbsolute() EQUAL Mesh_RelativeAbsoluteInfo_Absolute)
		{
			theElementSize = Reference.SurfaceSize().TargetSize();
			theMinElementSize = Reference.SurfaceSize().MinSize();
		}
		else
		{
			theElementSize = Reference.SurfaceSize().TargetSize()*Reference.BaseSize() / 100.0;
			theMinElementSize = Reference.SurfaceSize().MinSize()*Reference.BaseSize() / 100.0;
		}
	}

	if (theElementSize <= 0 OR theMinElementSize <= 0) { THROW_STANDARD_EXCEPTION(" NULL Element size detected"); }

	// Specify Combination of min, target sizes
	if (theValues_.SurfaceSize().SizeMethod() EQUAL Mesh_SizeMethodInfo_MinOnly) { theElementSize = theMinElementSize; }

	if (theConditions_.CustomSurfaceCurvature() EQUAL Mesh_SurfaceCurvatureInfo_Disable) { theSpanAngle = RealLast(); }
	else if (theConditions_.CustomSurfaceCurvature() EQUAL Mesh_SurfaceCurvatureInfo_Continuum_Values) { theSpanAngle = Reference.SurfaceCurvature().SpanAngle(); }
	else
	{ // Specify Surface curvature value 	
		theSpanAngle = theValues_.SurfaceCurvature().SpanAngle();
	}

	if (theSpanAngle <= 0) { THROW_STANDARD_EXCEPTION(" NULL Span Angle detected"); }
}

void AutLib::MeshLib::SizeMap3d_SizeMapTool::ExportMeshToPlt(fstream & File) const
{
	theBackMesh_->ExportMeshToPlt(File);
}

void AutLib::MeshLib::SizeMap3d_SizeMapTool::ExportContourToPlt(fstream & File) const
{
	theBackMesh_->ExportToPlt(File);
}

Standard_Real AutLib::MeshLib::SizeMap3d_SizeMapTool::RetrieveTargetSize() const
{
	if (theValues_.SurfaceSize().RelativeAbsolute() EQUAL Mesh_RelativeAbsoluteInfo_Absolute)
	{
		return theValues_.SurfaceSize().TargetSize();
	}
	else
	{
		return theValues_.SurfaceSize().TargetSize()*theReference_->BaseSize() / 100.0;
	}
}

Standard_Real AutLib::MeshLib::SizeMap3d_SizeMapTool::GetBaseSize() const
{
	return theReference_->BaseSize();
}

Standard_Real AutLib::MeshLib::SizeMap3d_SizeMapTool::GetTargetSurfaceSize() const
{
	if (theConditions_.CustomSurfaceSize())
	{
		if (theValues_.SurfaceSize().RelativeAbsolute() EQUAL Mesh_RelativeAbsoluteInfo_Absolute)
		{
			return theValues_.SurfaceSize().TargetSize();
		}
		else
		{
			return theValues_.SurfaceSize().TargetSize()*theReference_->BaseSize() / 100.0;
		}
	}
	else
	{
		if (theReference_->SurfaceSize().RelativeAbsolute() EQUAL Mesh_RelativeAbsoluteInfo_Absolute)
		{
			return theReference_->SurfaceSize().TargetSize();
		}
		else
		{
			return theReference_->SurfaceSize().TargetSize()*theReference_->BaseSize() / 100.0;
		}
	}
}

Standard_Real AutLib::MeshLib::SizeMap3d_SizeMapTool::GetBoundaryGrowthRate() const
{
	if (theConditions_.CustomBoundaryGrowthRate())
	{
		return Mesh_VariationRate::Rate(theValues_.BoundaryGrowthRate());
	}
	else
	{
		return Mesh_VariationRate::Rate(theReference_->DefaultGrowthRate());
	}
}

AutLib::MeshLib::SizeMap3d_SizeMapTool::SizeMap3d_SizeMapTool
(
	const Global_Handle(Mesh_ReferenceValues) theReference,
	const Global_Handle(M_CAD Cad3d_Solid) theSolid
)
	: theReference_(theReference)
	, theSolid_(theSolid)
	, theBackMesh_(NULL)
{
}