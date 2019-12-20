#include <Mesh_SurfaceCurvatureValues.hxx>

#include <Standard_Real.hxx>
#include <Global_Macros.hxx>

static const Standard_Real MIN_SPAN_ANGLE = 1;
static const Standard_Real MAX_SPAN_ANGLE = RealLast();
static const Standard_Real DEFAULT_SPAN_ANGLE = 15;

AutLib::MeshLib::Mesh_SurfaceCurvatureValues::Mesh_SurfaceCurvatureValues()
	: theSpanAngle_(DEFAULT_SPAN_ANGLE)
{
}

void AutLib::MeshLib::Mesh_SurfaceCurvatureValues::Init
(
	const Standard_Real SpanAngle, 
	const Mesh_SurfaceCurvatureInfo SurfaceCurvatureInfo
)
{
	theSpanAngle_ = MAX(MIN_SPAN_ANGLE, MIN(SpanAngle, MAX_SPAN_ANGLE));
	theCurvatureInfo_ = SurfaceCurvatureInfo;
}

void AutLib::MeshLib::Mesh_SurfaceCurvatureValues::SetSpanAngle(const Standard_Real Value)
{
	theSpanAngle_ = MAX(MIN_SPAN_ANGLE, MIN(Value, MAX_SPAN_ANGLE));
}

void AutLib::MeshLib::Mesh_SurfaceCurvatureValues::SetCurvatureInfo(const Mesh_SurfaceCurvatureInfo SurfaceCurvatureInfo)
{
	theCurvatureInfo_ = SurfaceCurvatureInfo;
}