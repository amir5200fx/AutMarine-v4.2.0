#include <SizeMap2d_ModifyBackSize.hxx>

static const Standard_Real DEFAULT_Coefficient = 0.3;
static const Standard_Real DEFAULT_Delta = 0.2;

AutLib::MeshLib::SizeMap2d_ModifyBackSize::SizeMap2d_ModifyBackSize
(
	const Standard_Real theBaseSize,
	const M_GEO GeoMesh_BackGroundMesh2d & BackGround
)
	: SizeMap2d_StdBackSize(theBaseSize, BackGround)
	, theCoeff_(DEFAULT_Coefficient)
	, theDelta_(DEFAULT_Delta)
{
}
