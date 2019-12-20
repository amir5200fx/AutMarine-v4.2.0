#include <SizeMap2d_SizeMapTool.hxx>

#include <Entity_Box2d.hxx>
#include <Cad2d_Plane.hxx>
#include <GeoMesh_BackGroundMesh2d.hxx>
#include <Mesh_ReferenceValues.hxx>
#include <Mesh_VariationRate.hxx>

using namespace AutLib;
using namespace GeoLib;

Standard_Real AutLib::MeshLib::SizeMap2d_SizeMapTool::ElementSize(const Geom_Pnt2d & Coord) const
{
	return theBackMesh_->ElementSize(Coord);
}

M_GEO Entity_Box2d AutLib::MeshLib::SizeMap2d_SizeMapTool::BoundingBox(const Standard_Real theOffset) const
{
	return *theBackMesh_->BoundingBox();
}

//void AutLib::MeshLib::SizeMap2d_SizeMapTool::SetName(const Standard_String & theName)
//{
//	theName_ = theName;
//}

void AutLib::MeshLib::SizeMap2d_SizeMapTool::ExportMeshToPlt(fstream & File) const
{
	theBackMesh_->ExportMeshToPlt(File);
}

void AutLib::MeshLib::SizeMap2d_SizeMapTool::ExportContourToPlt(fstream & File) const
{
	theBackMesh_->ExportToPlt(File);
}

Standard_Real AutLib::MeshLib::SizeMap2d_SizeMapTool::RetrieveTargetSize() const
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

Standard_Real AutLib::MeshLib::SizeMap2d_SizeMapTool::GetBaseSize() const
{
	return theReference_->BaseSize();
}

Standard_Real AutLib::MeshLib::SizeMap2d_SizeMapTool::GetTargetSurfaceSize() const
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

Standard_Real AutLib::MeshLib::SizeMap2d_SizeMapTool::GetBoundaryGrowthRate() const
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

AutLib::MeshLib::SizeMap2d_SizeMapTool::SizeMap2d_SizeMapTool
(
	const Global_Handle(Mesh_ReferenceValues) theReference,
	const Global_Handle(M_CAD Cad2d_Plane)thePlane
)
	: theReference_(theReference)
	, thePlane_(thePlane)
	, theBackMesh_(NULL)
{
}

AutLib::MeshLib::SizeMap2d_SizeMapTool::~SizeMap2d_SizeMapTool()
{
	FreePointer(theBackMesh_);
}

void AutLib::MeshLib::SizeMap2d_SizeMapTool::SpecifyValues
(
	Standard_Real & ElementSize,
	Standard_Real & MinElementSize,
	Standard_Real & SpanAngle
) const
{
	Get_Const_Object(Reference) = *theReference_;

	if (theConditions_.CustomSurfaceSize())
	{
		// Specify Relative or Absolute sizes
		if (theValues_.SurfaceSize().RelativeAbsolute() EQUAL Mesh_RelativeAbsoluteInfo_Absolute)
		{
			ElementSize = theValues_.SurfaceSize().TargetSize();
			MinElementSize = theValues_.SurfaceSize().MinSize();
		}
		else
		{ // is Relative to Base
			ElementSize = theValues_.SurfaceSize().TargetSize()*Reference.BaseSize() / 100.0;
			MinElementSize = theValues_.SurfaceSize().MinSize()*Reference.BaseSize() / 100.0;
		}
	}
	else
	{
		if (Reference.SurfaceSize().RelativeAbsolute() EQUAL Mesh_RelativeAbsoluteInfo_Absolute)
		{
			ElementSize = Reference.SurfaceSize().TargetSize();
			MinElementSize = Reference.SurfaceSize().MinSize();
		}
		else
		{
			ElementSize = Reference.SurfaceSize().TargetSize()*Reference.BaseSize() / 100.0;
			MinElementSize = Reference.SurfaceSize().MinSize()*Reference.BaseSize() / 100.0;
		}
	}

	if (ElementSize <= 0 OR MinElementSize <= 0) { THROW_STANDARD_EXCEPTION(" NULL Element size detected"); }

	// Specify Combination of min, target sizes
	if (theValues_.SurfaceSize().SizeMethod() EQUAL Mesh_SizeMethodInfo_MinOnly) { ElementSize = MinElementSize; }

	if (theConditions_.CustomSurfaceCurvature() EQUAL Mesh_SurfaceCurvatureInfo_Disable) { SpanAngle = RealLast(); }
	else if (theConditions_.CustomSurfaceCurvature() EQUAL Mesh_SurfaceCurvatureInfo_Continuum_Values) { SpanAngle = Reference.SurfaceCurvature().SpanAngle(); }
	else
	{ // Specify Surface curvature value 	
		SpanAngle = theValues_.SurfaceCurvature().SpanAngle();
	}

	if (SpanAngle <= 0) { THROW_STANDARD_EXCEPTION(" NULL Span Angle detected"); }
}