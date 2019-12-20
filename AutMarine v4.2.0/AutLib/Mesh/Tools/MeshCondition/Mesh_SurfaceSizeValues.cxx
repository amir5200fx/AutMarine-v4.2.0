#include <Mesh_SurfaceSizeValues.hxx>

#include <Standard_Real.hxx>
#include <Global_Macros.hxx>

static const Standard_Real DEFAULT_TARGET_SIZE = 100.0;
static const Standard_Real DEFAULT_MIN_SIZE = 20.0;
static const Standard_Real MIN_PERCENTAGE = 0.001;
static const Standard_Real MAX_PERCENTAGE = 100.0;

AutLib::MeshLib::Mesh_SurfaceSizeValues::Mesh_SurfaceSizeValues()
	: theMinSize_(DEFAULT_MIN_SIZE)
	, theTargetSize_(DEFAULT_TARGET_SIZE)
{
	theSizeMethod_ = Mesh_SizeMethodInfo::Mesh_SizeMethodInfo_MinAndTarget;
	theRelativeAbsolute_ = Mesh_RelativeAbsoluteInfo::Mesh_RelativeAbsoluteInfo_RelativeToBase;
}

void AutLib::MeshLib::Mesh_SurfaceSizeValues::SetMinSize(const Standard_Real Value)
{
	theMinSize_ = MAX(Value, 0);
}

void AutLib::MeshLib::Mesh_SurfaceSizeValues::SetTargetSize(const Standard_Real Value)
{
	theTargetSize_ = MAX(Value, 0);
}

void AutLib::MeshLib::Mesh_SurfaceSizeValues::SetSizeMethod(Mesh_SizeMethodInfo SizeMethod)
{
	theSizeMethod_ = SizeMethod;
}

void AutLib::MeshLib::Mesh_SurfaceSizeValues::SetRelativeAbsolute(Mesh_RelativeAbsoluteInfo RelativeAbsolute)
{
	theRelativeAbsolute_ = RelativeAbsolute;
}